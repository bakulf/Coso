/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ctask.h"

#include <QFileInfo>

#include <iostream>

bool CTask::generator(const QFileInfo &file, const char *str)
{
    QFile fd(file.absoluteFilePath());

    if (!fd.open(QIODevice::WriteOnly)) {
        std::cerr << "ERROR: Error opening the file '"
                  << qPrintable(file.absoluteFilePath())
                  << "\"." << std::endl;
        return false;
    }

    for (qint64 done = 0, size = strlen(str); done < size;) {
        qint64 ret = fd.write(str + done);
        if (ret <= 0) {
            std::cerr << "ERROR: Error writing in the file '"
                      << qPrintable(file.absoluteFilePath())
                      << "\"." << std::endl;
            break;
        }

        done += ret;
    }

    fd.close();
    return true;
}
