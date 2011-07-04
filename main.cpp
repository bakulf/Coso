/* *** This file is part of 'coso` ***
 *
 * Copyright (C) 2011 Andrea Marchesini <baku@ippolita.net>.
 *
 * This program is free software. It is released under the terms of
 * the BSD License. See license.txt for more details.
 */

#include "capplication.h"

int main (int argc, char ** argv)
{
    CApplication app(argc, argv);
    return app.exec();
}
