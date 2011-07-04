/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CCMD_DELETE_H_
#define _CCMD_DELETE_H_

#include "ccmd.h"

#include <QStringList>

class CApplication;

class CCmdDelete : public CCmd
{
    Q_OBJECT

public:
    CCmdDelete(CApplication *application, const QStringList &arguments);
    virtual ~CCmdDelete();

public:
    int run();

private:
   int runHelp();
   int runContext(const QString &context);
   int runTask(const QString &context, const QString &task);

private:
    CApplication *m_application;
    QStringList m_arguments;

    CCMD_HELPER;
};

#endif
