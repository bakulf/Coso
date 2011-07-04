/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ctaskgconf.h"

#include "ccontext.h"
#include "constants.h"

#include <iostream>

CTask *CTaskGConf::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QMap<QString, QPair<Type, QString> > map;

    for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling()) {
        if (!n.isElement())
            continue;

        QDomElement e = n.toElement();
        if (e.tagName() != C_TASK_GCONF_ENTRY_TAG)
            continue;

        QString key, value;
        Type type(Unknown);

        for (QDomNode nn = e.firstChild(); !nn.isNull(); nn = nn.nextSibling()) {
            if (!nn.isElement())
                continue;

            QDomElement ee = nn.toElement();
            if (ee.tagName() == C_TASK_GCONF_KEY_TAG) {
                key = ee.text();
            } else if (ee.tagName() == C_TASK_GCONF_VALUE_TAG) {
                value = ee.text();
                type = CTaskGConf::stringToType(ee.attribute(C_TASK_GCONF_TYPE_ATTR));
            }
        }

        // Type and value can be empty
        if (!key.isEmpty()) {
            map.insert(key, QPair<Type, QString>(type, value));
        }
    }

    return new CTaskGConf(context, name, map);
}

bool CTaskGConf::generator(const QFileInfo &file)
{
    return CTask::generator(file, C_TASK_GCONF_TEMPLATE);
}

CTaskGConf::CTaskGConf(CContext *context, const QString &name, const QMap<QString, QPair<Type, QString> > &value) :
    CTask(context, name, C_TASK_GCONF_NAME),
    m_values(value)
{
}

CTaskGConf::~CTaskGConf()
{
}

const QString CTaskGConf::info() const
{
    return QString("Changes some GCOnf keys/values.");
}


int CTaskGConf::run(const QString &context)
{
    Q_UNUSED(context);

    gconf_init(0, NULL, NULL);
    GConfClient *client = gconf_client_get_default();

    for (QMap<QString, QPair<Type, QString> >::iterator i = m_values.begin(); i != m_values.end(); i++) {
        GConfValue *value = valueToGConf(i.key(), i.value().first, i.value().second);
        if (value) {
            gconf_client_set(client, qPrintable(i.key()), value, NULL);
            gconf_value_free(value);
        }
    }

    g_object_unref(client);

    return 0;
}

CTaskGConf::Type CTaskGConf::stringToType(const QString &str)
{
    if (str == "string")
        return String;

    if (str == "integer")
        return Integer;

    if (str == "float")
        return Float;

    if (str == "bool")
        return Bool;

    return Unknown;
}

GConfValue *CTaskGConf::valueToGConf(const QString &key, Type type, const QString &str)
{
    GConfValue *value = 0;

    switch (type) {
        case Unknown:
            std::cerr << "WARNING: unknown type for the key '"
                      << qPrintable(key)
                      << "`." << std::endl;
          return NULL;

        case String:
            value = gconf_value_new(GCONF_VALUE_STRING);
            gconf_value_set_string(value, qPrintable(str));
            return value;

        case Integer:
            value = gconf_value_new(GCONF_VALUE_INT);
            gconf_value_set_int(value, str.toInt());
            return value;

        case Float:
            value = gconf_value_new(GCONF_VALUE_FLOAT);
            gconf_value_set_float(value, str.toFloat());
            return value;

        case Bool:
            value = gconf_value_new(GCONF_VALUE_BOOL);
            gconf_value_set_bool(value, str == "true" ? TRUE : FALSE);
            return value;
    }

    return NULL;
}
