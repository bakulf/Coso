/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ccmdnew.h"

#include "capplication.h"
#include "chelper.h"
#include "constants.h"

#include <QStringList>
#include <QFileInfo>
#include <QDir>

#include <iostream>

CCmd* CCmdNew::helper(CApplication *application, const QStringList &arguments)
{
    if (arguments.size() >= 1 &&
        (arguments[0] == "new" || arguments[0] == "n"))
        return new CCmdNew(application, arguments);

    return 0;
}

CCmdNew::CCmdNew(CApplication *application, const QStringList &arguments) :
    CCmd(application),
    m_application(application),
    m_arguments(arguments)
{
    m_arguments.removeFirst();
}

CCmdNew::~CCmdNew()
{
}

int CCmdNew::run()
{
    if (m_arguments.size() == 0)
        return runHelp();

    if (m_arguments.size() == 2 && m_arguments[0] == "context")
        return runContext(m_arguments[1]);

    if (m_arguments.size() == 4 && m_arguments[0] == "task") {
        return runTask(m_arguments[1], m_arguments[2], m_arguments[3]);
    }

    return runHelp();
}

int CCmdNew::runHelp()
{
    std::cerr << "Usage: ... new [context|task] <option>" << std::endl;
    std::cerr << std::endl;

    std::cerr << "Usage for context:" << std::endl;
    std::cerr << "Usage: ... new context [contextName] (use '"
              << C_GLOBAL << "` for the global context)" << std::endl;
    std::cerr << std::endl;

    std::cerr << "Usage for task:" << std::endl;
    std::cerr << "Usage: ... new task [contextName] [taskName] [type]" << std::endl;
    std::cerr << std::endl;

    std::cerr << "List of types for tasks:" << std::endl;
    for (int i = 0; CTaskHelpers[i].type; i++) {
        std::cerr << " . " << CTaskHelpers[i].type;

        for (int s = strlen(CTaskHelpers[i].type); s < 30; s++)
            std::cerr << ' ';

        std::cerr << CTaskHelpers[i].description << std::endl;
    }

    std::cerr << std::endl;

    return 1;
}

int CCmdNew::runContext(const QString &context)
{
    if (!validateName(context)) {
        std::cerr << "The name '"
                  << qPrintable(context)
                  << "` contains not acceptable characters or the length is wrong."
                  << std::endl;
        return 1;
    }

    QDir home(QDir::home());
    if (!home.cd(C_PATH)) {
        std::cerr << "WARNING: Error opening the folder '"
                  << C_PATH << "`." << std::endl;
        return 1;
    }

    QFileInfo info(home.absoluteFilePath(context));
    if (info.exists()) {
        std::cerr << "WARNING: This context already exists." << std::endl;
        return 1;
    }

    if (!home.mkdir(context)) {
        std::cerr << "WARNING: Error creating the folder '"
                  << qPrintable(info.absoluteFilePath())
                  << "`." << std::endl;
        return 1;
    }

    return 0;
}

int CCmdNew::runTask(const QString &context, const QString &task, const QString &type)
{
    if (context != C_GLOBAL && !validateName(context)) {
        std::cerr << "The name '" << qPrintable(context)
                  << "` contains not acceptable characters or the length is wrong."
                  << std::endl;
        return 1;
    }

    if (!validateName(task)) {
        std::cerr << "The name '"
                  << qPrintable(task)
                  << "` contains not acceptable characters or the length is wrong."
                  << std::endl;
        return 1;
    }

    QDir home(QDir::home());
    if (!home.cd(C_PATH)) {
        std::cerr << "WARNING: Error opening the folder '"
                  << C_PATH << "`." << std::endl;
        return 1;
    }

    QFileInfo info(home.absoluteFilePath(context));
    if (!info.exists()) {
        std::cerr << "WARNING: This context doesn't exist." << std::endl;
        return 1;
    }

    if (!home.cd(context)) {
        std::cerr << "WARNING: Error opening the folder '"
                  << C_PATH << "`." << std::endl;
        return 1;
    }

    info = home.absoluteFilePath(task);
    if (info.exists()) {
        std::cerr << "WARNING: This task already exists." << std::endl;
        return 1;
    }

    for (int i = 0; CTaskHelpers[i].type; i++) {
        if (type == CTaskHelpers[i].type) {
            if (!CTaskHelpers[i].generator(info))
                return 1;

            std::cout << "Edit your new task: "
                      << qPrintable(info.absoluteFilePath())
                      << std::endl;
            return 0;
        }
    }

    std::cerr << "This type of task doesn't exist." << std::endl;
    return 1;
}

bool CCmdNew::validateName(const QString &name)
{
    for (int i = 0, len = name.size(); i < len; i++) {
        if ((name.at(i) < 'a' || name.at(i) > 'z') &&
            (name.at(i) < 'A' || name.at(i) > 'Z') &&
            (name.at(i) < '0' || name.at(i) > '9') &&
            name.at(i) != '_' &&
            name.at(i) != '-') {
            return false;
        }
    }

    return !(name.isEmpty());
}
