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
Table::Table(uint64_t perTableGameCount) :
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
void Table::Initialize(uint64_t newId)
{
    assert(id == 0);
    id = newId;
}

//----------------------------------------------------------------------
// Get penalty for placing the player at this table
//
uint64_t Table::GetPenalty(uint64_t tableGame, Player* player)
{
    uint64_t penalty = 0;
    Game& game = allGames[tableGame];
    uint64_t freeCount = 0;

    for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
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

    return freeCount > 0 ? penalty : std::numeric_limits<uint64_t>::max();
}

//----------------------------------------------------------------------
// Assign the player to the table
//
void Table::AssignSeat(uint64_t tableGame, Player* player)
{
    Game& game = allGames[tableGame];

    // Scan current seats state
    //
    uint64_t currentPenalty = std::numeric_limits<uint64_t>::max();
    for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
    {
        if (game[seat] == nullptr)
        {
            // Calculate minimal possible zone penalty
            //
            uint64_t penalty = player->GetZoneSeatPenalty(seat);
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
    Selector<uint64_t> seats;
    for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
    {
        if (game[seat] == nullptr && currentPenalty == player->GetZoneSeatPenalty(seat))
        {
            seats.push_back(seat);
        }
    }

    // Assign the seat
    //
    uint64_t seat = seats.PickOne();
    uint64_t seatNo = seat + 1;
    player->AssignSeat(tableGame, id, seatNo);
    game[seat] = player;
}

//----------------------------------------------------------------------
// Game accessor
//
const Game& Table::operator[](uint64_t game)
{
    return allGames[game];
}
