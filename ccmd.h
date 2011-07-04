/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CCMD_H_
#define _CCMD_H_

#include <QObject>

// Helper for the helper :)
#define CCMD_HELPER \
public: \
    static CCmd* helper(CApplication *application, \
                        const QStringList &arguments);

// Class for the command:
class CCmd : public QObject
{
    Q_OBJECT

public:
    CCmd(QObject *parent) : QObject(parent)
    {
    }

public:
    virtual int run() = 0;
};

#endif
