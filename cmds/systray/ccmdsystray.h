/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CCMD_SYSTRAY_H_
#define _CCMD_SYSTRAY_H_

#include "ccmd.h"

#include <QSystemTrayIcon>
#include <QPointer>

class CApplication;
class CContext;

class QFileSystemWatcher;
class QMenu;
class QDir;

// Systray
class CCmdSystray : public CCmd
{
    Q_OBJECT

public:
    CCmdSystray(CApplication *application);
    virtual ~CCmdSystray();

public:
    int run();

private Q_SLOTS:
    void changeContext();
    void activated(QSystemTrayIcon::ActivationReason reason);

    void aboutToQuit();

    void fileSystemChanged();

private:
    void createMenu();

    void watchPath();
    void watchPath(const QDir &dir);

private:
    CApplication *m_application;

    QPointer<QSystemTrayIcon> m_sysTray;
    QPointer<QMenu> m_menu;

    QPointer<QFileSystemWatcher> m_watcher;

    CCMD_HELPER;
};

#endif
