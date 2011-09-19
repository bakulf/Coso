/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _C_CONTEXT_H_
#define _C_CONTEXT_H_

#include  <QFileInfo>

class CTask;
class CApplication;

class CContext : public QObject
{
    Q_OBJECT

public:
    CContext(CApplication *application, const QFileInfo &info);
    virtual ~CContext();

public:
    CApplication *application() const { return m_application; }

    const QString name() const { return m_name; }

    const QList<CTask*> tasks() const { return m_tasks; }

private:
    void readTask(const QFileInfo &file);

private:
    CApplication *m_application;

    QString m_name;
    QList<CTask*> m_tasks;
};

#endif
