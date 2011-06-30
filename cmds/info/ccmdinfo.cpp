#include "ccmdinfo.h"

#include "capplication.h"
#include "ccontext.h"
#include "ctask.h"

#include <QStringList>
#include <iostream>

CCmd* CCmdInfo::helper(CApplication *application, const QStringList &arguments)
{
    if (arguments.size() == 1 &&
        (arguments[0] == "info" || arguments[0] == "i"))
        return new CCmdInfo(application);

    return 0;
}

CCmdInfo::CCmdInfo(CApplication *application) :
    CCmd(application),
    m_application(application)
{
}

CCmdInfo::~CCmdInfo()
{
}

int CCmdInfo::run()
{
    const CContext *context = m_application->globalContext();
    if (context) {
        std::cout << "Global Context" << std::endl;
        runContext(context);
    }

    foreach(const CContext *context, m_application->contexts()) {
        std::cout << "Context: " << qPrintable(context->name()) << std::endl;
        runContext(context);
    }

    return 0;
}

void CCmdInfo::runContext(const CContext *context) const
{
    foreach(const CTask *task, context->tasks()) {
        std::cout << "\tTask: " << qPrintable(task->name()) << std::endl;
        std::cout << "\t\tType: " << qPrintable(task->type()) << std::endl;
        std::cout << "\t\tDescription: " << qPrintable(task->info()) << std::endl;
    }
}
