/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _C_APPLICATION_H_
#define _C_APPLICATION_H_

#include <QApplication>
#include <QStringList>
#include <QPointer>

#include "ccontext.h"

// Main class for this application:
class CApplication : public QApplication
{
    Q_OBJECT

public:
    CApplication(int &argc, char **argv);
    virtual ~CApplication();

public:
    int run();

public: // For Tasks:
    const CContext *globalContext() const { return m_globalContext.data(); }

    const QList<const CContext*> contexts() const { return m_contexts; }

public: // For Commands:
    const QString path() const;

    void readContexts();

private:
    QPointer<CContext> m_globalContext;
    QList<const CContext*> m_contexts;
};

#endif
