/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

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

    if (arguments.size() == 2) {
        return new CCmdSwitch(application, arguments[1], false);
    } else {
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
                ret = run(m_application->globalContext(), m_context);

            if (ret == 0)
                ret = run(context, m_context);

            return ret;
        }
    }

    std::cerr << "This context doesn't exist." << std::endl;
    return 1;
}

int CCmdSwitch::run(const CContext *context, const QString &contextName)
{
    foreach(CTask *task, context->tasks()) {
        if (m_verbose)
            std::cerr << "Executing task '" << qPrintable(task->name()) << "`..." << std::endl;

        if (task->run(contextName))
            return 1;
    }

    return 0;
}
