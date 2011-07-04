/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CCMD_SWITCH_H_
#define _CCMD_SWITCH_H_

#include "ccmd.h"

class CApplication;
class CContext;

// Switch the context
class CCmdSwitch : public CCmd
{
    Q_OBJECT

public:
    CCmdSwitch(CApplication *application, const QString &context, bool verbose);
    virtual ~CCmdSwitch();

public:
    int run();
    int run(const CContext *context, const QString &contextName);

private:
    CApplication *m_application;
    QString m_context;
    bool m_verbose;

    CCMD_HELPER;
};

#endif
