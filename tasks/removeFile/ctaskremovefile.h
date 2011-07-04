/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CTASK_REMOVE_FILE_H_
#define _CTASK_REMOVE_FILE_H_

#include "ctask.h"

class CContext;

class CTaskRemoveFile : public CTask
{
    Q_OBJECT

public:
    CTaskRemoveFile(CContext *context, const QString &name, const QString &file);
    virtual ~CTaskRemoveFile();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    QString m_file;

    CTASK_HELPER;
};

#endif
