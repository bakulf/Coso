#ifndef _CTASK_CREATE_FILE_H_
#define _CTASK_CREATE_FILE_H_

#include "ctask.h"

class CContext;

class CTaskCreateFile : public CTask
{
    Q_OBJECT

public:
    CTaskCreateFile(CContext *context, const QString &name, const QString &fileInput,const QString &fileOutput);
    virtual ~CTaskCreateFile();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    QString m_fileInput;
    QString m_fileOutput;

    CTASK_HELPER;
};

#endif
