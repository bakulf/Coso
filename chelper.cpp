#include "chelper.h"

#include "ccmdswitch.h"
#include "ccmdinfo.h"
#include "ccmdhelp.h"

#include "ctaskfile.h"

// List of the commands:
CCmdHelper CCmdHelpers[] = {
    { "switch [contextName]", "change context", CCmdSwitch::helper  },
    { "info",                 "show the configuration of the contexts", CCmdInfo::helper  },

    // The letest helper:
    { "help",                 "this help", CCmdHelp::helper    },
    { 0,                      0,           0                   }
};

// List of the tasks types:
CTaskHelper CTaskHelpers[] = {
    { "file", CTaskFile::helper },
    { 0,      0 }
};
