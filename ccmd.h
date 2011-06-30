#ifndef _CCMD_H_
#define _CCMD_H_

#include <QObject>

// Helper for the helper :)
#define CCMD_HELPER \
public: \
    static CCmd* helper(CApplication *application, \
                        const QStringList &arguments);

// Class for the command:
class CCmd : public QObject
{
    Q_OBJECT

public:
    CCmd(QObject *parent) : QObject(parent)
    {
    }

public:
    virtual int run() = 0;
};

#endif
