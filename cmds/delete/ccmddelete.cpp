/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ccmddelete.h"

#include "capplication.h"
#include "chelper.h"
#include "ccmdnew.h"
#include "constants.h"

#include <QStringList>
#include <QFileInfo>
#include <QDir>

#include <iostream>

CCmd* CCmdDelete::helper(CApplication *application, const QStringList &arguments)
{
    if (arguments.size() >= 1 &&
        (arguments[0] == "delete" || arguments[0] == "d"))
        return new CCmdDelete(application, arguments);

    return 0;
}

CCmdDelete::CCmdDelete(CApplication *application, const QStringList &arguments) :
    CCmd(application),
    m_application(application),
    m_arguments(arguments)
{
    m_arguments.removeFirst();
}

CCmdDelete::~CCmdDelete()
{
}

int CCmdDelete::run()
{
    if (m_arguments.size() == 0)
        return runHelp();

    if (m_arguments.size() == 2 && m_arguments[0] == "context")
        return runContext(m_arguments[1]);

    if (m_arguments.size() == 3 && m_arguments[0] == "task") {
        return runTask(m_arguments[1], m_arguments[2]);
    }

    return runHelp();
}

int CCmdDelete::runHelp()
{
    std::cerr << "Usage: ... delete [context|task] <option>" << std::endl;
    std::cerr << std::endl;

    std::cerr << "Usage for context:" << std::endl;
    std::cerr << "Usage: ... delete context [contextName] (use '"
              << C_GLOBAL << "` for the global context)" << std::endl;
    std::cerr << std::endl;

    std::cerr << "Usage for task:" << std::endl;
    std::cerr << "Usage: ... delete task [contextName] [taskName]" << std::endl;
    std::cerr << std::endl;

    return 1;
}

int CCmdDelete::runContext(const QString &context)
{
    if (!CCmdNew::validateName(context)) {
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
    if (!info.exists()) {
        std::cerr << "WARNING: This context doesn't exist." << std::endl;
        return 1;
    }

    // I feel uncomfortable any time I delete a file...
    QFileInfoList list(QDir(info.absoluteFilePath()).entryInfoList(QDir::Files));
    foreach(const QFileInfo file, list) {
        QFile::remove(file.absoluteFilePath());
    }

    if (!home.rmdir(context)) {
        std::cerr << "WARNING: Error removing the folder '"
                  << qPrintable(info.absoluteFilePath())
                  << "`." << std::endl;
        return 1;
    }

    return 0;
}

int CCmdDelete::runTask(const QString &context, const QString &task)
{
    if (context != C_GLOBAL && !CCmdNew::validateName(context)) {
        std::cerr << "The name '" << qPrintable(context)
                  << "` contains not acceptable characters or the length is wrong."
                  << std::endl;
        return 1;
    }

    if (!CCmdNew::validateName(task)) {
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
    if (!info.exists()) {
        std::cerr << "WARNING: This task doesn't exist." << std::endl;
        return 1;
    }

    if (!QFile::remove(info.absoluteFilePath())) {
        std::cerr << "ERROR: Error removing the file '"
                  << qPrintable(info.absoluteFilePath())
                  << "`." << std::endl;
        return 1;
    }

    return 1;
}
