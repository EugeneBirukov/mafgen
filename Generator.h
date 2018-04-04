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
        uint64_t players,
        uint64_t tables,
        uint64_t perTableGames,
        uint64_t tableGames,
        uint64_t playerGames);
    
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

    // Print player seat penalties
    //
    void PrintSeatPenalties();

    // Print cross-player penalties
    //
    void PrintPlayerPenalties();

private:

    // The type for the list of players
    //
    using Players = std::vector<uint64_t>;

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
    const uint64_t PlayerCount;

    // The number of tables
    //
    const uint64_t TableCount;

    // The number of games per table
    // 
    const uint64_t PerTableGameCount;

    // The number of table games
    //
    const uint64_t TableGameCount;

    // The number of player games
    //
    const uint64_t PlayerGameCount;

    // The number of seats to generate
    //
    const uint64_t SeatCount;

    // Current seat
    //
    uint64_t seats;

    // Current player's game being generated
    //
    uint64_t playerGame;

    // Current per-table game being generated
    //
    uint64_t tableGame;

    // The number of players to play simultaneously at all tables
    // Note: in the last game some tables may be inactive.
    //
    uint64_t playerMax;
};

