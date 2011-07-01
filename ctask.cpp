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
