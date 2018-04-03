//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A tournament table.
//
#include "stdafx.h"

//----------------------------------------------------------------------
// Constructor
//
Table::Table(unsigned perTableGameCount) :
    id(0),
    allGames(perTableGameCount)
{
}

//----------------------------------------------------------------------
// Destructor
//
Table::~Table()
{
}

//----------------------------------------------------------------------
// Initialize table
//
void Table::Initialize(unsigned newId)
{
    assert(id == 0);
    id = newId;
}

//----------------------------------------------------------------------
// Get penalty for placing the player at this table
//
unsigned Table::GetPenalty(unsigned tableGame, Player* player)
{
    unsigned penalty = 0;
    Game& game = allGames[tableGame];
    unsigned freeCount = 0;

    for (unsigned seat = 0; seat < 10; ++seat)
    {
        Player* p = game[seat];
        if (p != nullptr)
        {
            penalty += player->GetPlayerPenalty(p);
        }
        else
        {
            ++freeCount;
        }
    }

    return freeCount > 0 ? penalty : std::numeric_limits<unsigned>::max();
}

//----------------------------------------------------------------------
// Assign the player to the table
//
void Table::AssignSeat(unsigned tableGame, Player* player)
{
    Game& game = allGames[tableGame];

    // Scan current seats state
    //
    unsigned currentPenalty = std::numeric_limits<unsigned>::max();
    for (unsigned seat = 0; seat < 10; ++seat)
    {
        if (game[seat] == nullptr)
        {
            // Calculate minimal possible zone penalty
            //
            unsigned penalty = player->GetZonePenalty(seat);
            currentPenalty = std::min(penalty, currentPenalty);
        }
        else
        {
            // Adjust cross-player penalty
            //
            player->AddPlayerPenalty(game[seat]);
        }
    }

    // Collect possible seats
    //
    Selector<unsigned> seats;
    for (unsigned seat = 0; seat < 10; ++seat)
    {
        if (game[seat] == nullptr && currentPenalty == player->GetZonePenalty(seat))
        {
            seats.push_back(seat);
        }
    }

    // Assign the seat
    //
    unsigned seat = seats.PickOne();
    unsigned seatNo = seat + 1;
    player->AssignSeat(tableGame, id, seatNo);
    game[seat] = player;
}
