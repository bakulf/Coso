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

#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>

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
    m_sysTray(new QSystemTrayIcon())
{
    m_sysTray->setIcon(QIcon(":/images/icon.png"));
}

CCmdSystray::~CCmdSystray()
{
    delete m_sysTray;
}

int CCmdSystray::run()
{
    QMenu *menu = new QMenu();

    foreach(const CContext *context, m_application->contexts()) {
        QAction *action = new QAction(context->name(), this);
        menu->addAction(action);
        connect(action,
                SIGNAL(triggered()),
                SLOT(changeContext()));
    }

    menu->addSeparator();

    {
        QAction *quit = new QAction("Quit", this);
        menu->addAction(quit);
        connect(quit,
                SIGNAL(triggered()),
                m_application,
                SLOT(quit()));
    }

    m_sysTray->setContextMenu(menu);
    m_sysTray->show();

    return m_application->exec();
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
