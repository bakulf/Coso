#include "chelper.h"

#include "ccmdswitch.h"
#include "ccmdinfo.h"
#include "ccmdnew.h"
#include "ccmdhelp.h"

#include "ctaskeditfile.h"
#include "ctaskremovefile.h"
#include "ctaskcreatefile.h"

// List of the commands:
CCmdHelper CCmdHelpers[] = {
    { "switch|sw [contextName] <--verbose|-v>", "change context",                         CCmdSwitch::helper  },
    { "info|i",                                 "show the configuration of the contexts", CCmdInfo::helper    },
    { "new|n <options>",                        "create a new context or a task",         CCmdNew::helper     },

    // The letest helper:
    { "help",                                   "this help",                              CCmdHelp::helper    },
    { 0,                                        0,                                        0                   }
};

// List of the tasks types:
CTaskHelper CTaskHelpers[] = {
    { "editFile",   "Edit a file (you must create a template)", CTaskEditFile::helper,   CTaskEditFile::generator   },
    { "removeFile", "Remove a file",                            CTaskRemoveFile::helper, CTaskRemoveFile::generator },
    { "createFile", "Create a file",                            CTaskCreateFile::helper, CTaskCreateFile::generator },
    { 0,            0,                                          0,                       0                          }
};
