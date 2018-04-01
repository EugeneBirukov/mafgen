//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// Program configuration.
//
#include "stdafx.h"
#include "Configuration.h"

//----------------------------------------------------------------------
// The parser data
//
Configuration::Key Configuration::keys[] =
{
    {"-p", "--players", &Configuration::players, "The number of players"},
    {"-t", "--tables",  &Configuration::tables,  "The number of tables played simultaneously"},
    {"-g", "--games",   &Configuration::games,   "The number of games per tournament"},
    {"-s", "--seed",    &Configuration::seed,    "The random number seed"},
};

const size_t Configuration::KeyCount = sizeof(Configuration::keys) / sizeof(Configuration::keys[0]);

//----------------------------------------------------------------------
// Constructor
//
Configuration::Configuration()
{
    // Reasonablr default values
    //
    players = 10;
    tables = 1;
    games = 1;
    playerGames = 1;
    seed = static_cast<unsigned>(time(nullptr));
}

//----------------------------------------------------------------------
// Destructor
//
Configuration::~Configuration()
{
    // Empty
}

//----------------------------------------------------------------------
// Parse command line 
//
bool Configuration::Parse(int argc, char ** argv)
{
    // Assume success
    //
    bool result = true;

    // Parse command line
    //
    int argNo;
    for (argNo = 0; argNo < argc - 1; argNo += 2)
    {
        std::string key(argv[argNo]);
        std::string value(argv[argNo + 1]);

        // See if we can recognize the argument
        //
        bool found = false;
        for (int keyNo = 0; result && keyNo < KeyCount; ++keyNo)
        {
            if (key == keys[keyNo].shortKey || key == keys[keyNo].longKey)
            {
                std::istringstream(value) >> this->*keys[keyNo].field;
                found = true;
                break;
            }
        }

        if (!found)
        {
            std::cerr << "Error: cannot recognize argument " << key << std::endl;
            result = false;
        }
    }

    // Calculate the minimum number of games per player
    //
    unsigned minGames = players;
    unsigned minPlayerGames = 10;
    if (players % 2 == 0)
    {
        minGames /= 2;
        minPlayerGames /= 2;
    }
    if (players % 5 == 0)
    {
        minGames /= 5;
        minPlayerGames /= 5;
    }

    // Calculate the number of rounds and player games
    //
    unsigned rounds = games / minGames;
    playerGames = rounds * minPlayerGames;

    // Check sanity
    //
    if (argNo < argc)
    {
        std::cerr << "Error: cannot recognize argument " << argv[argNo] << std::endl;
        result = false;
    }
    if (tables == 0)
    {
        std::cerr << "Error: no tables" << std::endl;
        result = false;
    }
    if (players < tables * 10)
    {
        std::cerr << "Error: too few players " << players << " for " << tables << " tables" << std::endl;
        result = false;
    }       
    if (games % minGames != 0)
    {
        std::cerr << "Error: invalid number of games " << games << ". ";
        std::cerr << "Correct value would be " << (rounds + 1) * minGames << std::endl;
        result = false;
    }

    return result;
}

//----------------------------------------------------------------------
// Print usage
//
void Configuration::PrintUsage()
{
    std::cerr << std::endl << "Usage: " << std::endl;

    for (int keyNo = 0; keyNo < KeyCount; ++keyNo)
    {
        std::cerr << 
            "    " << 
            keys[keyNo].shortKey << 
            " | " << 
            std::setw(10) <<  
            std::left <<
            keys[keyNo].longKey << 
            " - " << 
            keys[keyNo].description << 
            std::endl;
    }
}

//----------------------------------------------------------------------
// Print configuration
//
void Configuration::PrintConfiguration()
{
    std::cout << "Configuration:" << std::endl;
    std::cout << "    Players:          " << std::setw(4) << std::right << players << std::endl;
    std::cout << "    Tables:           " << std::setw(4) << std::right << tables << std::endl;
    std::cout << "    Games:            " << std::setw(4) << std::right << games << std::endl;
    std::cout << "    Games per player: " << std::setw(4) << std::right << playerGames << std::endl;
    std::cout << "    RNG Seed:         " << seed << std::endl;
}
