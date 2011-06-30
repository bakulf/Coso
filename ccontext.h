#ifndef _C_CONTEXT_H_
#define _C_CONTEXT_H_

#include  <QFileInfo>

class CTask;
class CApplication;

class CContext : public QObject
{
    Q_OBJECT

public:
    CContext(CApplication *application, const QFileInfo &info);
    virtual ~CContext();

public:
    const QString name() const { return m_name; }

    const QList<CTask*> tasks() const { return m_tasks; }

private:
    void readTask(const QFileInfo &file);

private:
    QString m_name;
    QList<CTask*> m_tasks;
};

#endif
