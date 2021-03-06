/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef C_CMDHELPER_H
#define C_CMDHELPER_H

class CCmd;
class CTask;
class CContext;
class CApplication;

class QString;
class QFileInfo;
class QStringList;
class QDomElement;

// Just a struct for the helpers:
struct CCmdHelper {
    const char *name;
    const char *description;

    CCmd *(*helper) (CApplication *application,
                     const QStringList& arguments);
};

// List of helpers:
extern CCmdHelper CCmdHelpers[];

// Just a struct for the task types
struct CTaskHelper {
    const char *type;
    const char *description;

    CTask *(*helper) (CContext *context,
                      const QString &name,
                      const QDomElement &root);

    bool (*generator) (const QFileInfo &file);
};

extern CTaskHelper CTaskHelpers[];

#endif
