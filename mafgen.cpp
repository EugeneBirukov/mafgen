//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// The entry point for the console application.
//
#include "stdafx.h"

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
        srand(static_cast<unsigned>(config.GetSeed()));
        const uint64_t zeroes = config.GetMaxZeroes();

        uint64_t loop = 0;
        uint64_t minCount = ~0ull;
        while (true)
        {
            // Create the generator
            //
            Generator gen(
                config.GetPlayers(),
                config.GetTables(),
                config.GetPerTableGames(),
                config.GetTableGames(),
                config.GetPlayerGames());

            // Generate the tournament table
            //
            gen.Generate();

            uint64_t count = gen.CountZeroes();
            if (count > zeroes)
            {
                ++loop;
                minCount = std::min(count, minCount);
                continue;
            }

            uint64_t doubles = gen.CountDoubles();
            std::cout << "DOUBLES " << doubles << std::endl;
            if (doubles > 0)
            {
                ++loop;
                continue;
            }

            // Print table assignments
            //
            gen.PrintTables();

            // Print player seats
            //
            gen.PrintPlayers();

            // Print player seat penalties
            //
            gen.PrintSeatPenalties();

            // Print cross-player penalties
            //
            gen.PrintPlayerPenalties();

            // Done 
            //
            break;
        }
    }

    return result;
}



