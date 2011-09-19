/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CTASK_SUBCONTEXT_H_
#define _CTASK_SUBCONTEXT_H_

#include "ctask.h"

class CContext;

class CTaskSubContext : public CTask
{
    Q_OBJECT

public:
    CTaskSubContext(CContext *context, const QString &name, const QString &subcontext);
    virtual ~CTaskSubContext();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    CContext *m_context;
    QString m_subContext;

    CTASK_HELPER;
};

#endif
