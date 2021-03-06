/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "capplication.h"

#include "ccontext.h"
#include "chelper.h"
#include "ccmd.h"
#include "constants.h"

#include <QDir>
#include <QFileInfo>

#include <iostream>

CApplication::CApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    // Parse the contexts list
    readContexts();
}

CApplication::~CApplication()
{
}

// The real main:
int CApplication::run()
{
    int ret = 0;
    QStringList args = arguments();


    // Removing argv[0]:
    if (args.size())
        args.removeFirst();

    // Let's find the best command and exec it:
    for (int i = 0; CCmdHelpers[i].name; i++)
    {
        CCmd *cmd(CCmdHelpers[i].helper(this, args));
        if (cmd)
        {
            ret = cmd->run();
            break;
        }
    }

    return ret;
}

const QString CApplication::path() const
{
    QDir home(QDir::home());
    return home.absoluteFilePath(C_PATH);
}

void CApplication::readContexts()
{
    qDeleteAll(m_contexts.begin(), m_contexts.end());
    m_contexts.clear();

    QDir home(QDir::home());
    QFileInfo info(home.absoluteFilePath(C_PATH));

    if (info.exists() && !info.isDir()) {
        std::cerr << "ERROR: The folder '"
                  << C_PATH << "` exists but it's not a folder... ?"
                  << std::endl;
        return;
    }

    if (!info.exists() && !home.mkdir(C_PATH)) {
        std::cerr << "ERROR: Error creating the folder '"
                  << C_PATH << "`." << std::endl;
        return;
    }

    if (!home.cd(C_PATH)) {
        std::cerr << "ERROR: Error opening the folder '"
                  << C_PATH << "`." << std::endl;
        return;
    }

    QFileInfo globalInfo(home.absoluteFilePath(C_GLOBAL));
    if (!globalInfo.exists() && !home.mkdir(C_GLOBAL)) {
        std::cerr << "ERROR: Error creating the folder '"
                  << C_GLOBAL << "`." << std::endl;
        return;
    }

    // Reading the global context:
    m_globalContext = new CContext(this, globalInfo);

    // Reading the list of contexts:
    QFileInfoList list = home.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::NoSort);
    foreach(const QFileInfo &info, list) {
        if (info.fileName() != C_GLOBAL)
            m_contexts << new CContext(this, info);
    }
}
