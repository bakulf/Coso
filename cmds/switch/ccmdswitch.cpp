#include "ccmdswitch.h"

#include "capplication.h"
#include "ccontext.h"
#include "ctask.h"

#include <QStringList>
#include <iostream>

CCmd* CCmdSwitch::helper(CApplication *application, const QStringList &arguments)
{
    if (arguments.size() == 2 &&
        (arguments[0] == "switch" || arguments[0] == "sw"))
        return new CCmdSwitch(application, arguments[1]);

    return 0;
}

CCmdSwitch::CCmdSwitch(CApplication *application, const QString &context) :
    CCmd(application),
    m_application(application),
    m_context(context)
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
        if (task->run(context->name()))
            return 1;
    }

    return 0;
}
