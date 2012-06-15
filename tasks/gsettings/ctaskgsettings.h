/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CTASK_GSETTINGS_H_
#define _CTASK_GSETTINGS_H_

#include "ctask.h"

#include <QList>

class CContext;

class CTaskGSettingsValue
{
public:
    enum Type {
        Unknown,
        Bool,
        Integer,
        UInteger,
        Double,
        String,
        Enum,
        Flags,
    };

public:
    CTaskGSettingsValue(QString &s, QString &k, QString &v, Type &t) :
      schema(s), key(k), value(v), type(t) {}

    static Type stringToType(const QString &str);

public: // data
    QString schema;
    QString key;
    QString value;
    Type    type;
};

class CTaskGSettings : public CTask
{
    Q_OBJECT

public:
    CTaskGSettings(CContext *context, const QString &name, const QList<CTaskGSettingsValue> &values);
    virtual ~CTaskGSettings();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    void run(const CTaskGSettingsValue &value);

private:
    QList<CTaskGSettingsValue> m_values;

    CTASK_HELPER;
};

#endif
