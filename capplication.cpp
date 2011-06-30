#include "capplication.h"

#include "ccontext.h"
#include "chelper.h"
#include "ccmd.h"
#include "constants.h"

#include <QDir>
#include <QFileInfo>

#include <iostream>

CApplication::CApplication(int argc, char **argv) :
    QCoreApplication(argc, argv)
{
    // Get the list of args
    m_arguments = arguments();

    // Parse the contexts list
    readContexts();
}

CApplication::~CApplication()
{
}

// The real main:
int CApplication::exec()
{
    int ret = 0;

    // Removing argv[0]:
    if (m_arguments.size())
        m_arguments.removeFirst();

    // Let's find the best command and exec it:
    for (int i = 0; CCmdHelpers[i].name; i++)
    {
        CCmd *cmd(CCmdHelpers[i].helper(this, m_arguments));
        if (cmd)
        {
            ret = cmd->run();
            break;
        }
    }

    return ret;
}

void CApplication::readContexts()
{
    QDir home(QDir::home());
    QFileInfo info(home.absoluteFilePath(C_PATH));

    if (info.exists() && !info.isDir()) {
        std::cerr << "WARNING: The folder '" << C_PATH << "` exists but it's not a folder... ?" << std::endl;
        return;
    }

    if (!info.exists() && !home.mkdir(C_PATH)) {
        std::cerr << "WARNING: Error creating the folder '" << C_PATH << "`." << std::endl;
        return;
    }

    if (!home.cd(C_PATH)) {
        std::cerr << "WARNING: Error opening the folder '" << C_PATH << "`." << std::endl;
        return;
    }

    // Reading the list of tasks + config:
    QFileInfoList list = home.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::NoSort);
    foreach(const QFileInfo &info, list) {
        m_contexts << new CContext(this, info);
    }
}
