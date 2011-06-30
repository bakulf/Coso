#include "ccmdswitch.h"

#include "capplication.h"
#include "ccontext.h"
#include "ctask.h"

#include <QStringList>
#include <iostream>

CCmd* CCmdSwitch::helper(CApplication *application, const QStringList &arguments)
{
    if (arguments.size() < 2 || arguments.size() > 3)
        return 0;

    if (arguments[0] != "switch" && arguments[0] != "sw")
        return 0;

    QString context;
    if (arguments.size() == 2)
        context = arguments[1];
    else {
        if (arguments[1] == "-v" || arguments[1] == "--verbose")
            return new CCmdSwitch(application, arguments[2], true);
        else if (arguments[2] == "-v" || arguments[2] == "--verbose")
            return new CCmdSwitch(application, arguments[1], true);
    }

    return 0;
}

CCmdSwitch::CCmdSwitch(CApplication *application, const QString &context, bool verbose) :
    CCmd(application),
    m_application(application),
    m_context(context),
    m_verbose(verbose)
{
}

CCmdSwitch::~CCmdSwitch()
{
}

int CCmdSwitch::run()
{
    foreach(const CContext *context, m_application->contexts()) {
        if (context->name() == m_context) {
            int ret(0);
            if (m_application->globalContext())
                ret = run(m_application->globalContext());

            if (ret == 0)
                ret = run(context);

            return ret;
        }
    }

    std::cerr << "This context doesn't exist." << std::endl;
    return 1;
}

int CCmdSwitch::run(const CContext *context)
{
    foreach(CTask *task, context->tasks()) {
        if (m_verbose)
            std::cerr << "Executing task '" << qPrintable(task->name()) << "`..." << std::endl;

        if (task->run(context->name()))
            return 1;
    }

    return 0;
}
