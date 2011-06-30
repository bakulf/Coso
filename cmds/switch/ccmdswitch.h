#ifndef _CCMD_SWITCH_H_
#define _CCMD_SWITCH_H_

#include "ccmd.h"

class CApplication;
class CContext;

// Switch the context
class CCmdSwitch : public CCmd
{
    Q_OBJECT

public:
    CCmdSwitch(CApplication *application, const QString &context);
    virtual ~CCmdSwitch();

public:
    int run();
    int run(const CContext *context);

private:
    CApplication *m_application;
    QString m_context;

    CCMD_HELPER;
};

#endif
