/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#ifndef _CTASK_EDIT_FILE_H_
#define _CTASK_EDIT_FILE_H_

#include "ctask.h"

class CContext;

class CTaskEditFile : public CTask
{
    Q_OBJECT

public:
    CTaskEditFile(CContext *context, const QString &name, const QString &fileInput, const QString &fileOutput);
    virtual ~CTaskEditFile();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    bool checkLine(const char *buffer, qint64 size, const QString &context);

private:
    QString m_fileInput;
    QString m_fileOutput;
    bool m_prevValue;
    bool m_in;

    CTASK_HELPER;
};

#endif
