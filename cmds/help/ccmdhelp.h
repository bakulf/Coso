/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CCMD_HELP_H_
#define _CCMD_HELP_H_

#include "ccmd.h"

class CApplication;
class QStringList;

// Class for the help menu:
class CCmdHelp : public CCmd
{
    Q_OBJECT

public:
    CCmdHelp(CApplication *application, const QStringList &arguments);
    virtual ~CCmdHelp();

public:
    int run();

    CCMD_HELPER;
};

#endif
