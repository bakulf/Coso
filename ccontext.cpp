#include "ccontext.h"

#include "ctask.h"
#include "chelper.h"
#include "constants.h"

#include <QDir>
#include <QDomDocument>

#include <iostream>

CContext::CContext(CApplication *application, const QFileInfo &info) :
    QObject(application)
{
    m_name = info.fileName();

    QFileInfoList list(QDir(info.absoluteFilePath()).entryInfoList(QDir::Files, QDir::LocaleAware));
    foreach(const QFileInfo file, list) {
        readTask(file.absoluteFilePath());
    }
}

CContext::~CContext()
{
}

void CContext::readTask(const QFileInfo &file)
{
    QFile fd(file.absoluteFilePath());
    if (!fd.open(QIODevice::ReadOnly)) {
        std::cerr << "WARNING: Error opening the file '"
                  << qPrintable(file.absoluteFilePath())
                  << "`." << std::endl;
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&fd)) {
        std::cerr << "WARNING: Error parsing the file '"
                  << qPrintable(file.absoluteFilePath())
                  << "`." << std::endl;
       fd.close();
       return;
    }
 
    fd.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != C_TASK_ROOT_TAG)
    {
        std::cerr << "WARNING: The root task of the file '"
                  << qPrintable(file.absoluteFilePath())
                  << "` is not '" << C_TASK_ROOT_TAG
                  << "`." << std::endl;
        return;
    }

    QDomElement child = root.firstChildElement(C_TASK_TYPE_TAG);
    if (child.isNull()) {
        std::cerr << "WARNING: No type for the task of the file '"
                  << qPrintable(file.absoluteFilePath())
                  << "`." << std::endl;
        return;
    }

    QString type = child.text();
    for(int i = 0; CTaskHelpers[i].type; i++)
    {
        if (type == CTaskHelpers[i].type) {
            CTask *task(CTaskHelpers[i].helper(this, file.fileName(), root));
            if (task)
                m_tasks << task;
        }
    }
}
