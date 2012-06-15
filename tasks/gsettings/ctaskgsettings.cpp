/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ctaskgsettings.h"

#include "ccontext.h"
#include "constants.h"

#include <iostream>

#undef signals // Collides with GTK symbols
#include <glib-2.0/gio/gio.h>

CTask *CTaskGSettings::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QList<CTaskGSettingsValue> list;

    for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling()) {
        if (!n.isElement())
            continue;

        QDomElement e = n.toElement();
        if (e.tagName() != C_TASK_GSETTINGS_ENTRY_TAG)
            continue;

        QString key, value, schema;
        CTaskGSettingsValue::Type type(CTaskGSettingsValue::Unknown);

        for (QDomNode nn = e.firstChild(); !nn.isNull(); nn = nn.nextSibling()) {
            if (!nn.isElement())
                continue;

            QDomElement ee = nn.toElement();
            if (ee.tagName() == C_TASK_GSETTINGS_KEY_TAG) {
                key = ee.text();
            } else if (ee.tagName() == C_TASK_GSETTINGS_VALUE_TAG) {
                value = ee.text();
                type = CTaskGSettingsValue::stringToType(ee.attribute(C_TASK_GSETTINGS_TYPE_ATTR));
            } else if (ee.tagName() == C_TASK_GSETTINGS_SCHEMA_TAG) {
                schema = ee.text();
            }
        }

        // Type and value can be empty
        if (!key.isEmpty() && !schema.isEmpty()) {
            list << CTaskGSettingsValue(schema, key, value, type);
        }
    }

    return new CTaskGSettings(context, name, list);
}

bool CTaskGSettings::generator(const QFileInfo &file)
{
    return CTask::generator(file, C_TASK_GSETTINGS_TEMPLATE);
}

CTaskGSettings::CTaskGSettings(CContext *context, const QString &name, const QList<CTaskGSettingsValue> &value) :
    CTask(context, name, C_TASK_GSETTINGS_NAME),
    m_values(value)
{
}

CTaskGSettings::~CTaskGSettings()
{
}

const QString CTaskGSettings::info() const
{
    return QString("Changes some GSettings keys/values.");
}


int CTaskGSettings::run(const QString &context)
{
    Q_UNUSED(context);

    foreach(const CTaskGSettingsValue &value, m_values) {
        run(value);
    }

    g_settings_sync();
    return 0;
}

void CTaskGSettings::run(const CTaskGSettingsValue &value)
{
    GSettings *settings = g_settings_new(qPrintable(value.schema));

    switch (value.type) {
        case CTaskGSettingsValue::Bool:
            g_settings_set_boolean(settings, qPrintable(value.key), value.value == "true" ? TRUE : FALSE);
            break;

        case CTaskGSettingsValue::Integer:
            g_settings_set_int(settings, qPrintable(value.key), value.value.toInt());
            break;

        case CTaskGSettingsValue::UInteger:
            g_settings_set_uint(settings, qPrintable(value.key), value.value.toUInt());
            break;

        case CTaskGSettingsValue::Double:
            g_settings_set_double(settings, qPrintable(value.key), value.value.toDouble());
            break;

        case CTaskGSettingsValue::String:
            g_settings_set_string(settings, qPrintable(value.key), qPrintable(value.value));
            break;

        case CTaskGSettingsValue::Enum:
            g_settings_set_enum(settings, qPrintable(value.key), value.value.toInt());
            break;

        case CTaskGSettingsValue::Flags:
            g_settings_set_flags(settings, qPrintable(value.key), value.value.toUInt());
            break;

        case CTaskGSettingsValue::Unknown:
            std::cerr << "WARNING: unknown type for the key '"
                      << qPrintable(value.key)
                      << "`." << std::endl;
            break;

    }

    g_object_unref(settings);
}

CTaskGSettingsValue::Type CTaskGSettingsValue::stringToType(const QString &str)
{
    if (str == "bool")
        return Bool;

    if (str == "integer")
        return Integer;

    if (str == "uinteger")
        return UInteger;

    if (str == "double")
        return Double;

    if (str == "string")
        return String;

    if (str == "enum")
        return Enum;

    if (str == "flags")
        return Flags;

    return Unknown;
}
