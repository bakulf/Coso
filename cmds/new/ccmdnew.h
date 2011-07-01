#ifndef _CCMD_NEW_H_
#define _CCMD_NEW_H_

#include "ccmd.h"

#include <QStringList>

class CApplication;

class CCmdNew : public CCmd
{
    Q_OBJECT

public:
    CCmdNew(CApplication *application, const QStringList &arguments);
    virtual ~CCmdNew();

public:
    int run();

private:
   int runHelp();
   int runContext(const QString &context);
   int runTask(const QString &context, const QString &task, const QString &type);

public:
   static bool validateName(const QString &name);

private:
    CApplication *m_application;
    QStringList m_arguments;

    CCMD_HELPER;
};

#endif
