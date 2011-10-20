/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ccmdsystray.h"

#include "capplication.h"
#include "ccmdswitch.h"
#include "ccontext.h"
#include "ctask.h"

#include <QDir>
#include <QMenu>
#include <QAction>
#include <QFileSystemWatcher>

#include <iostream>

CCmd* CCmdSystray::helper(CApplication *application, const QStringList &arguments)
{
    if (arguments.size() != 1)
        return 0;

    if (arguments[0] != "systray" && arguments[0] != "st")
        return 0;

    return new CCmdSystray(application);
}

CCmdSystray::CCmdSystray(CApplication *application) :
    CCmd(application),
    m_application(application),
    m_sysTray(new QSystemTrayIcon()),
    m_menu(new QMenu()),
    m_watcher(new QFileSystemWatcher())
{
    m_sysTray->setIcon(QIcon(":/images/icon.png"));

    foreach(const CContext *context, m_application->contexts()) {
        QAction *action = new QAction(context->name(), this);
        m_menu->addAction(action);
        connect(action,
                SIGNAL(triggered()),
                SLOT(changeContext()));
    }

    m_menu->addSeparator();

    {
        QAction *quit = new QAction("Quit", this);
        m_menu->addAction(quit);
        connect(quit,
                SIGNAL(triggered()),
                m_application,
                SLOT(quit()));
    }

    m_sysTray->setContextMenu(m_menu);

    connect(m_sysTray,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            SLOT(activated(QSystemTrayIcon::ActivationReason)));

    connect(m_application,
            SIGNAL(aboutToQuit()),
            SLOT(aboutToQuit()));

    connect(m_watcher,
            SIGNAL(directoryChanged(QString)),
            SLOT(fileSystemChanged()));
    connect(m_watcher,
            SIGNAL(fileChanged(QString)),
            SLOT(fileSystemChanged()));

    watchPath();
}

CCmdSystray::~CCmdSystray()
{
}

void CCmdSystray::aboutToQuit()
{
    if (m_watcher) {
        delete m_watcher;
        m_watcher = 0;
    }
}

// When something changes, let's restart:
void CCmdSystray::fileSystemChanged()
{
    QStringList arguments(m_application->arguments());

    const char **argv = (const char **)malloc(sizeof(char *) + (arguments.size() + 1));
    int argc(0);
    foreach(QString part, arguments) {
        argv[argc++] = strdup(qPrintable(part));
    }

    if (execvp(argv[0], (char* const*)argv)) {
        std::cerr << "Error executing the command `" << argv[0] << "'." << std::endl;
    }

    exit(0);
}

void CCmdSystray::watchPath()
{
    QString path(m_application->path());
    m_watcher->addPath(path);

    QDir home(path);
    watchPath(home);
}

void CCmdSystray::watchPath(const QDir &dir)
{
    QFileInfoList list = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot, QDir::NoSort);
    foreach(const QFileInfo &info, list) {
        m_watcher->addPath(info.absoluteFilePath());
        if (info.isDir())
            watchPath(QDir(info.absoluteFilePath()));
    }
}

int CCmdSystray::run()
{
    m_sysTray->show();
    return m_application->exec();
}

void CCmdSystray::activated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        m_menu->popup(QCursor::pos());
}

void CCmdSystray::changeContext()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    CCmdSwitch *cmd(new CCmdSwitch(m_application, action->text(), false));
    cmd->run();
    delete cmd;
}
