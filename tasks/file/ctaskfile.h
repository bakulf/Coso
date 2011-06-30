#ifndef _CTASK_FILE_H_
#define _CTASK_FILE_H_

#include "ctask.h"

class CContext;

// Class for the help menu:
class CTaskFile : public CTask
{
    Q_OBJECT

public:
    CTaskFile(CContext *context, const QString &name, const QString &fileInput, const QString &fileOutput);
    virtual ~CTaskFile();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    bool checkLine(const char *buffer, qint64 size, const QString &context);

private:
    QString m_fileInput;
    QString m_fileOutput;
    bool m_prevValue;
    bool m_in;

    CTASK_HELPER;
};

#endif
