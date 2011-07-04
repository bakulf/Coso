/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ctaskremovefile.h"

#include "ccontext.h"
#include "constants.h"

#include <iostream>

CTask *CTaskRemoveFile::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QDomElement file = root.firstChildElement(C_TASK_REMOVEFILE_FILE_TAG);
    if (file.isNull()) {
        std::cerr << "WARNING: No file for the task '"
                  << qPrintable(name)
                  << "` (task ignored)." << std::endl;
        return 0;
    }

    return new CTaskRemoveFile(context, name, file.text());
}

bool CTaskRemoveFile::generator(const QFileInfo &file)
{
    return CTask::generator(file, C_TASK_REMOVEFILE_TEMPLATE);
}

CTaskRemoveFile::CTaskRemoveFile(CContext *context, const QString &name, const QString &file) :
    CTask(context, name, C_TASK_REMOVEFILE_NAME),
    m_file(file)
{
}

CTaskRemoveFile::~CTaskRemoveFile()
{
}

const QString CTaskRemoveFile::info() const
{
    return QString("Remove the file %1.").arg(m_file);
}


int CTaskRemoveFile::run(const QString &context)
{
    Q_UNUSED(context);

    if (!QFile::exists(m_file)) {
        std::cerr << "WARNING: the file '"
                  << qPrintable(m_file)
                  << "` doesn't exist." << std::endl;
        return 0;
    }

    if (!QFile::remove(m_file)) {
        std::cerr << "ERROR: Error removing file '"
                  << qPrintable(m_file)
                  << "`." << std::endl;
    }

    return 0;
}
