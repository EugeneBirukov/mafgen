//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// The generator.
//
#pragma once

//----------------------------------------------------------------------
//
class Generator
{
public:

    // Constructor
    //
    Generator(
        unsigned players,
        unsigned tables,
        unsigned games,
        unsigned playerGames);
    
    // Destructor
    //
    ~Generator();

private:

    // The list of players
    //
    std::vector<Player> player;

    // The table of cross-player penalty pretty much keeps the count
    // of how many times two players met at the same table.
    //
    // Note: In theory we need only one triangle of this table, but
    // in practice it is more convenient to have the full square.
    //
    std::vector<std::vector<unsigned>> crossPlayerPenalty;
};

