/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "ctasksubcontext.h"

#include "ccontext.h"
#include "constants.h"
#include "ccmdswitch.h"

#include <iostream>

CTask *CTaskSubContext::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QString taskName;

    for (QDomNode n = root.firstChild(); !n.isNull(); n = n.nextSibling()) {
        if (!n.isElement())
            continue;

        QDomElement e = n.toElement();

        if (e.tagName() != C_TASK_SUBCONTEXT_SUBCONTEXT_TAG)
            continue;

        QString task = e.text();
        if (!task.isEmpty()) {
            taskName = task;
            break;
        }
    }

    return new CTaskSubContext(context, name, taskName);
}

bool CTaskSubContext::generator(const QFileInfo &file)
{
    return CTask::generator(file, C_TASK_SUBCONTEXT_TEMPLATE);
}

CTaskSubContext::CTaskSubContext(CContext *context, const QString &name, const QString &subContext) :
    CTask(context, name, C_TASK_SUBCONTEXT_NAME),
    m_context(context),
    m_subContext(subContext)
{
}

CTaskSubContext::~CTaskSubContext()
{
}

const QString CTaskSubContext::info() const
{
    return QString("Run a sub context");
}


int CTaskSubContext::run(const QString &context)
{
    Q_UNUSED(context);

    CCmdSwitch cmd(m_context->application(), m_subContext, false);
    cmd.run();

    return 0;
}
