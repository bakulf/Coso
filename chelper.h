#ifndef C_CMDHELPER_H
#define C_CMDHELPER_H

class CCmd;
class CTask;
class CContext;
class CApplication;

class QString;
class QStringList;
class QDomElement;

// Just a struct for the helpers:
struct CCmdHelper {
    const char *name;
    const char *description;

    CCmd *(*helper) (CApplication *application,
                     const QStringList& arguments);
};

// List of helpers:
extern CCmdHelper CCmdHelpers[];

// Just a struct for the task types
struct CTaskHelper {
    const char *type;
    CTask *(*helper) (CContext *context, const QString &name, const QDomElement &root);
};

extern CTaskHelper CTaskHelpers[];

#endif
