/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CCMD_INFO_H_
#define _CCMD_INFO_H_

#include "ccmd.h"

class CContext;
class CApplication;

// Info the context
class CCmdInfo : public CCmd
{
    Q_OBJECT

public:
    CCmdInfo(CApplication *application);
    virtual ~CCmdInfo();

public:
    int run();

private:
    void runContext(const CContext *context) const;

private:
    CApplication *m_application;

    CCMD_HELPER;
};

#endif
