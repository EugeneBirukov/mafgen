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
        unsigned perTableGames,
        unsigned tableGames,
        unsigned playerGames);
    
    // Destructor
    //
    ~Generator();

    // Generate the tournament table
    //
    void Generate();

    // Print table assignments
    //
    void PrintTables();

    // Print player seats
    //
    void PrintPlayers();

private:

    // The type for the list of players
    //
    using Players = std::vector<unsigned>;

    // Get players who has not played 'playerGame'
    //
    void GetPlayersForGame(Selector<Player *> &players);

    // Select players for one game at all tables
    //
    Selector<Player*> SelectPlayersForGame();

    // The list of players
    //
    std::vector<Player> allPlayers;

    // The list of all tables
    //
    std::vector<Table> allTables;

    // The number of players
    //
    const unsigned PlayerCount;

    // The number of tables
    //
    const unsigned TableCount;

    // The number of games per table
    // 
    const unsigned PerTableGameCount;

    // The number of table games
    //
    const unsigned TableGameCount;

    // The number of player games
    //
    const unsigned PlayerGameCount;

    // The number of seats to generate
    //
    const unsigned SeatCount;

    // Current seat
    //
    unsigned seats;

    // Current player's game being generated
    //
    unsigned playerGame;

    // Current per-table game being generated
    //
    unsigned tableGame;

    // The number of players to play simultaneously at all tables
    // Note: in the last game some tables may be inactive.
    //
    unsigned playerMax;
};

