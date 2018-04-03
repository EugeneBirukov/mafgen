//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// Program configuration.
//
#pragma once

//----------------------------------------------------------------------
//
class Configuration
{
private:

    // Helper struct for parser
    //
    struct Key
    {
        std::string               shortKey;
        std::string               longKey;
        unsigned Configuration::* field;
        std::string               description;
    };

    static const size_t KeyCount;

public:

    // Constructor
    //
    Configuration();

    // Destructor
    //
    ~Configuration();

    // Parse command line
    //
    bool Parse(int argc, char** argv);

    // Print usage
    //
    void PrintUsage();

    // Print resulting configuration
    //
    void PrintConfiguration();

    // Get the number of players
    //
    unsigned GetPlayers() const;

    // Get the number of tables
    //
    unsigned GetTables() const;

    // Get the number of table games
    //
    unsigned GetTableGames() const;

    // Get the number of per-table games
    //
    unsigned GetPerTableGames() const;

    // Get the number of player games
    //
    unsigned GetPlayerGames() const;

    // Get RNG seed
    //
    unsigned GetSeed() const;

private:

    unsigned players;       // The number of players
    unsigned tables;        // The number of tables played simultaneously
    unsigned tableGames;    // The number of games
    unsigned playerGames;   // The number of games per player
    unsigned seed;          // The random number generator seed
    static Key keys[];      // The parser data
};

