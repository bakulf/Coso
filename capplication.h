#ifndef _C_APPLICATION_H_
#define _C_APPLICATION_H_

#include <QCoreApplication>
#include <QStringList>

class CContext;

// Main class for this application:
class CApplication : public QCoreApplication
{
    Q_OBJECT

public:
    CApplication(int argc, char **argv);
    virtual ~CApplication();

public:
    int exec();

public: // For Tasks:
    const QList<CContext*> contexts() const { return m_contexts; }

private:
    void readContexts();

private:
    QStringList m_arguments;
    QList<CContext*> m_contexts;
};

#endif
