/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _C_APPLICATION_H_
#define _C_APPLICATION_H_

#include <QCoreApplication>
#include <QStringList>
#include <QPointer>

#include "ccontext.h"

// Main class for this application:
class CApplication : public QCoreApplication
{
    Q_OBJECT

public:
    CApplication(int argc, char **argv);
    virtual ~CApplication();

public:
    int exec();

public: // For Tasks:
    const CContext *globalContext() const { return m_globalContext.data(); }

    const QList<const CContext*> contexts() const { return m_contexts; }

private:
    void readContexts();

private:
    QStringList m_arguments;

    QPointer<CContext> m_globalContext;
    QList<const CContext*> m_contexts;
};

#endif
