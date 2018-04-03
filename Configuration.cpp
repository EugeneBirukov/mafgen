//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// Program configuration.
//
#include "stdafx.h"

//----------------------------------------------------------------------
// The parser data
//
Configuration::Key Configuration::keys[] =
{
    {"-p", "--players", &Configuration::players, "The number of players"},
    {"-t", "--tables",  &Configuration::tables,  "The number of tables played simultaneously"},
    {"-g", "--games",   &Configuration::tableGames,   "The number of games per tournament"},
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
    tableGames = 1;
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
    unsigned rounds = tableGames / minGames;
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
    if (tableGames % minGames != 0)
    {
        std::cerr << "Error: invalid number of games " << tableGames << ". ";
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
// Get the number of players
//
unsigned Configuration::GetPlayers() const
{
    return players;
}

//----------------------------------------------------------------------
// Get the number of tables
//
unsigned Configuration::GetTables() const
{
    return tables;
}

//----------------------------------------------------------------------
// Get the number of table games
//
unsigned Configuration::GetTableGames() const
{
    return tableGames;
}

//----------------------------------------------------------------------
// Get the number of per-table games
//
unsigned Configuration::GetPerTableGames() const
{
    // Some tables might be empty during last game
    //
    return (tableGames + tables - 1) / tables;
}

//----------------------------------------------------------------------
// Get the number of per-table games
//
unsigned Configuration::GetPlayerGames() const
{
    return playerGames;
}

//----------------------------------------------------------------------
// Get RNG seed
//
unsigned Configuration::GetSeed() const
{
    return seed;
}

//----------------------------------------------------------------------
// Print configuration
//
void Configuration::PrintConfiguration()
{
    std::cout << "Configuration:" << std::endl;
    std::cout << "    Players:          " << std::setw(12) << std::right << players << std::endl;
    std::cout << "    Tables:           " << std::setw(12) << std::right << tables << std::endl;
    std::cout << "    Games:            " << std::setw(12) << std::right << tableGames << std::endl;
    std::cout << "    Games per player: " << std::setw(12) << std::right << playerGames << std::endl;
    std::cout << "    Games per table:  " << std::setw(12) << std::right << GetPerTableGames() << std::endl;
    std::cout << "    RNG Seed:         " << std::setw(12) << std::right << seed << std::endl;
}
