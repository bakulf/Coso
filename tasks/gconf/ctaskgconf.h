#ifndef _CTASK_GCONF_H_
#define _CTASK_GCONF_H_

#include "ctask.h"

#include <QMap>
#include <QPair>

#include <gconf/gconf-client.h>

class CContext;

class CTaskGConf : public CTask
{
    Q_OBJECT

    enum Type {
        Unknown,
        String,
        Integer,
        Float,
        Bool
    };

public:
    CTaskGConf(CContext *context, const QString &name, const QMap<QString, QPair<Type, QString> > &values);
    virtual ~CTaskGConf();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

public:
    static Type stringToType(const QString &str);
    static GConfValue *valueToGConf(const QString &key, Type type, const QString &str);

private:
    QMap<QString, QPair<Type,QString> > m_values;

    CTASK_HELPER;
};

#endif
