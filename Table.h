//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A tournament table.
//
#pragma once

//----------------------------------------------------------------------
//
class Table
{
public:

    // Constructor
    //
    Table(uint64_t perTableGameCount);

    // Destructor
    //
    ~Table();

    // Initialize table
    //
    void Initialize(uint64_t newId);

    // Get penalty for placing the player at this table
    //
    uint64_t GetPenalty(uint64_t tableGame, Player* player);

    // Assign the player to the table
    //
    void AssignSeat(uint64_t tableGame, Player* player);

    // Game accessor
    //
    const Game& operator[](uint64_t game);

private:

    // table ID, starts from 1
    //
    uint64_t id;

    // All the games at this table
    // Note: some tables may have last game empty 
    //
    std::vector<Game> allGames;
};

