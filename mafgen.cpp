//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// The entry point for the console application.
//
#include "stdafx.h"
#include "Configuration.h"
#include "Seat.h"
#include "Player.h"
#include "Generator.h"

//----------------------------------------------------------------------
// Program entry point
//
int main(int argc, char** argv)
{
    int result = 0;

    // Parse the command line
    // Note: We skip the first argument which is the application name
    //
    Configuration config;
    bool ok = config.Parse(argc - 1, argv + 1);

    if (!ok)
    {
        // Print usage and exit
        //
        config.PrintUsage();
        result = 1;
    }
    else
    {
        // Print configuration
        //
        config.PrintConfiguration();

        // Initialize random number generator
        //
        srand(config.GetSeed());

        // Create the generator
        //
        Generator gen(
            config.GetPlayers(),
            config.GetTables(),
            config.GetGames(),
            config.GetPlayerGames());
    }

    return result;
}



