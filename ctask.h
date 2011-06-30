#ifndef _C_TASK_H_
#define _C_TASK_H_

#include <QObject>
#include <QFileInfo>
#include <QDomElement>

// Helper for the helper :)
#define CTASK_HELPER \
public: \
    static CTask* helper(CContext *context, \
                         const QString &name, \
                         const QDomElement &root);

class CTask : public QObject
{
    Q_OBJECT

public:
    CTask(QObject *parent, const QString &name, const QString &type) :
        QObject(parent),
        m_name(name),
        m_type(type)
    {
    }

public:
    const QString name() const { return m_name; }
    const QString type() const { return m_type; }
    virtual const QString info() const = 0;

public:
    virtual int run(const QString &context) = 0;

private:
    QString m_name;
    QString m_type;
};

#endif
