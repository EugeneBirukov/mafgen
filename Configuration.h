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
        uint64_t Configuration::* field;
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
    uint64_t GetPlayers() const;

    // Get the number of tables
    //
    uint64_t GetTables() const;

    // Get the number of table games
    //
    uint64_t GetTableGames() const;

    // Get the number of per-table games
    //
    uint64_t GetPerTableGames() const;

    // Get the number of player games
    //
    uint64_t GetPlayerGames() const;

    // Get RNG seed
    //
    uint64_t GetSeed() const;

private:

    uint64_t players;       // The number of players
    uint64_t tables;        // The number of tables played simultaneously
    uint64_t tableGames;    // The number of games
    uint64_t playerGames;   // The number of games per player
    uint64_t seed;          // The random number generator seed
    static Key keys[];      // The parser data
};

