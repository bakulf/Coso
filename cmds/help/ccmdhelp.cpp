#include "ccmdhelp.h"

#include "capplication.h"
#include "chelper.h"
#include "constants.h"

#include <iostream>

// This is the latest helper so it always returns a object:
CCmd* CCmdHelp::helper(CApplication *application, const QStringList &arguments)
{
    return new CCmdHelp(application, arguments);
}

CCmdHelp::CCmdHelp(CApplication *application, const QStringList &arguments)
  : CCmd(application)
{
    Q_UNUSED(arguments);
}

CCmdHelp::~CCmdHelp()
{
}

// Help is simple:
int CCmdHelp::run()
{
    std::cerr << C_PACKAGE << " " << C_VERSION << std::endl;
    std::cerr << std::endl;
    std::cerr << "Usage: " << C_PACKAGE << " <command> [params]" <<std::endl;
    std::cerr << std::endl;
    std::cerr << "List of commands:" << std::endl;

    for(int i = 0; CCmdHelpers[i].name; i++)
    {
        std::cerr << " . " << CCmdHelpers[i].name;

        for (int s = strlen(CCmdHelpers[i].name); s < 30; s++)
            std::cerr << ' ';

        std::cerr << CCmdHelpers[i].description << std::endl;
    }

    std::cerr << std::endl;

    return 1;
}
