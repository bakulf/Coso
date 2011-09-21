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

class CApplication;
class CContext;

class QSystemTrayIcon;

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

private:
    CApplication *m_application;
    QSystemTrayIcon *m_sysTray;

    CCMD_HELPER;
};

#endif
