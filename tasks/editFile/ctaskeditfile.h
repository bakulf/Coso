#ifndef _CTASK_EDIT_FILE_H_
#define _CTASK_EDIT_FILE_H_

#include "ctask.h"

class CContext;

class CTaskEditFile : public CTask
{
    Q_OBJECT

public:
    CTaskEditFile(CContext *context, const QString &name, const QString &fileInput, const QString &fileOutput);
    virtual ~CTaskEditFile();

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
