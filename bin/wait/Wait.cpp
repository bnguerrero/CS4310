/*

 * Copyright (C) 2009 Niek Linnenbank

 *

 * This program is free software: you can redistribute it and/or modify

 * it under the terms of the GNU General Public License as published by

 * the Free Software Foundation, either version 3 of the License, or

 * (at your option) any later version.

 *

 * This program is distributed in the hope that it will be useful,

 * but WITHOUT ANY WARRANTY; without even the implied warranty of

 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

 * GNU General Public License for more details.

 *

 * You should have received a copy of the GNU General Public License

 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <errno.h>

#include <unistd.h>

#include "Wait.h"

#include <ProcessClient.h>

Wait::Wait(int argc, char **argv)

    : POSIXApplication(argc, argv)

{

    parser().setDescription("Stop executing for some time");

    parser().registerPositional("PID", "Stop executing for the given number of seconds");
}

Wait::~Wait()

{
}

Wait::Result Wait::exec()

{

    int pid = atoi(arguments().get("PID"));

    const ProcessClient process;

    ProcessClient::Info info;

    const ProcessClient::Result result = process.processInfo(pid, info);

    if (result == ProcessClient::Success)
    {

        wait(pid);
    }

    else
    {

        ERROR("invalid process id: " << arguments().get("PID") << "'");

        return IOError;
    };

    // Sleep now

    // if (sleep(sec) != 0)

    // {

    //     ERROR("failed to wait: " << strerror(errno));

    //     return IOError;

    // }

    // Done

    return Success;
}