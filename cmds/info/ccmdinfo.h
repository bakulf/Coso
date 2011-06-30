#ifndef _CCMD_INFO_H_
#define _CCMD_INFO_H_

#include "ccmd.h"

class CApplication;

// Info the context
class CCmdInfo : public CCmd
{
    Q_OBJECT

public:
    CCmdInfo(CApplication *application);
    virtual ~CCmdInfo();

public:
    int run();

private:
    CApplication *m_application;

    CCMD_HELPER;
};

#endif
