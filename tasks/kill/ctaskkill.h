/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CTASK_KILL_H_
#define _CTASK_KILL_H_

#include "ctask.h"

#include <QList>

class CContext;

class CTaskKill : public CTask
{
    Q_OBJECT

public:
    CTaskKill(CContext *context, const QString &name, const QList<QString> &processes);
    virtual ~CTaskKill();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    bool runProcess(const QString &path, int pid);

private:
    QList<QString> m_processes;

    CTASK_HELPER;
};

#endif
