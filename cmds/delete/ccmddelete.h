#ifndef _CCMD_DELETE_H_
#define _CCMD_DELETE_H_

#include "ccmd.h"

#include <QStringList>

class CApplication;

class CCmdDelete : public CCmd
{
    Q_OBJECT

public:
    CCmdDelete(CApplication *application, const QStringList &arguments);
    virtual ~CCmdDelete();

public:
    int run();

private:
   int runHelp();
   int runContext(const QString &context);
   int runTask(const QString &context, const QString &task);

private:
    CApplication *m_application;
    QStringList m_arguments;

    CCMD_HELPER;
};

#endif
