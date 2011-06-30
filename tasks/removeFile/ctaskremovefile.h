#ifndef _CTASK_REMOVE_FILE_H_
#define _CTASK_REMOVE_FILE_H_

#include "ctask.h"

class CContext;

class CTaskRemoveFile : public CTask
{
    Q_OBJECT

public:
    CTaskRemoveFile(CContext *context, const QString &name, const QString &file);
    virtual ~CTaskRemoveFile();

public:
    virtual const QString info() const;

public:
    int run(const QString &context);

private:
    QString m_file;

    CTASK_HELPER;
};

#endif
