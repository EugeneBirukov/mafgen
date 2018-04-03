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
    Table(unsigned perTableGameCount);

    // Destructor
    //
    ~Table();

    // Initialize table
    //
    void Initialize(unsigned newId);

    // Get penalty for placing the player at this table
    //
    unsigned GetPenalty(unsigned tableGame, Player* player);

    // Assign the player to the table
    //
    void AssignSeat(unsigned tableGame, Player* player);

private:

    // table ID, starts from 1
    //
    unsigned id;

    // All the games at this table
    // Note: some tables may have last game empty 
    //
    std::vector<Game> allGames;
};

