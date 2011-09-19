/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ctaskkill.h"

#include "ccontext.h"
#include "constants.h"

#include <iostream>

#include <QDir>

#include <sys/types.h>
#include <signal.h>

CTask *CTaskKill::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QList<QString> list;

    for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling()) {
        if (!n.isElement())
            continue;

        QDomElement e = n.toElement();

        if (e.tagName() != C_TASK_KILL_PROCESS_NAME_TAG)
            continue;

        QString process = e.text();
        if (!process.isEmpty()) {
            list << process;
        }
    }

    return new CTaskKill(context, name, list);
}

bool CTaskKill::generator(const QFileInfo &file)
{
    return CTask::generator(file, C_TASK_KILL_TEMPLATE);
}

CTaskKill::CTaskKill(CContext *context, const QString &name, const QList<QString> &processes) :
    CTask(context, name, C_TASK_KILL_NAME),
    m_processes(processes)
{
}

CTaskKill::~CTaskKill()
{
}

const QString CTaskKill::info() const
{
    return QString("Kill a list of processes");
}


int CTaskKill::run(const QString &context)
{
    Q_UNUSED(context);

    QDir dir("/proc");
    foreach(QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        bool ok;
        int pid(d.toInt(&ok));
        if (ok && pid) {
            if (runProcess(dir.absoluteFilePath(d + "/cmdline"), pid) == false)
                return 1;
        }
    }

    return 0;
}

bool CTaskKill::runProcess(const QString &path, int pid)
{
    QFile fl(path);
    if (!fl.exists())
        return true;

    if (!fl.open(QIODevice::ReadOnly))
        return true;

    char buf[1024];
    qint64 lineLength = fl.readLine(buf, sizeof(buf));

    if (lineLength != -1) {
        QFileInfo file(buf);
        if (m_processes.contains(file.fileName())) {
            if (kill(pid, SIGTERM) != 0)
                std::cerr << "Error killing process `"
                          << qPrintable(file.fileName())
                          << "' (pid: " << pid << ")." << std::endl;
        }
    }

    fl.close();
    return true;
}
