/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CTASK_EXEC_H_
#define _CTASK_EXEC_H_

#include "ctask.h"

#include <QList>
#include <QStringList>

class CContext;

class CTaskExec : public CTask
{
    Q_OBJECT

public:
    CTaskExec(CContext *context, const QString &name, const QList<QStringList> &processes);
    virtual ~CTaskExec();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    QList<QStringList> m_processes;

    CTASK_HELPER;
};

#endif
