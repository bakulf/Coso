/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ctaskexec.h"

#include "ccontext.h"
#include "constants.h"

#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

CTask *CTaskExec::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QList<QStringList> list;

    for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling()) {
        if (!n.isElement())
            continue;

        QDomElement e = n.toElement();

        if (e.tagName() != C_TASK_EXEC_PROCESS_TAG)
            continue;

        QString process = e.text();
        if (!process.isEmpty()) {
            QStringList cmd;
            foreach(QString part, process.split(" ")) {
                QString p(part.trimmed());
                if (!p.isEmpty())
                    cmd << p;
            }

            if (!cmd.isEmpty())
                list << cmd;
        }
    }

    return new CTaskExec(context, name, list);
}

bool CTaskExec::generator(const QFileInfo &file)
{
    return CTask::generator(file, C_TASK_EXEC_TEMPLATE);
}

CTaskExec::CTaskExec(CContext *context, const QString &name, const QList<QStringList> &processes) :
    CTask(context, name, C_TASK_EXEC_NAME),
    m_processes(processes)
{
}

CTaskExec::~CTaskExec()
{
}

const QString CTaskExec::info() const
{
    return QString("Exec a list of processes");
}


int CTaskExec::run(const QString &context)
{
    Q_UNUSED(context);

    foreach(QStringList process, m_processes) {
        // I like this part:
        int pid(fork());
        switch (pid) {
            case -1:
                std::cerr << "Error executing the command (fork error?!?)" << std::endl;
                return 1;

            case 0: // Child
            {
                const char **argv = (const char **)malloc(sizeof(char *) + (process.size() + 1));

                int argc(0);
                foreach(QString part, process) {
                    argv[argc++] = strdup(qPrintable(part));
                }
                argv[argc] = 0;

                if (execvp(argv[0], (char* const*)argv)) {
                    std::cerr << "Error executing the command `" << argv[0] << "'." << std::endl;
                }

                exit(0);
            }

            break;

            default: // Father or mother
                break;
        }
    }

    return 0;
}
