//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A player.
//
#include "stdafx.h"
#include "Seat.h"
#include "Player.h"

//----------------------------------------------------------------------
// Constructor
//
Player::Player(unsigned playerCount, unsigned perTableGameCount) :
    seats(perTableGameCount),
    id(0),
    gameCount(0),
    playerPenalty(playerCount, 0)
{
    // Initialize zonePenalty array
    //
    for (unsigned zoneNo = 0; zoneNo < Seat::Zones; ++zoneNo)
    {
        zonePenalty[zoneNo] = 0;
    }
}

//----------------------------------------------------------------------
// Destructor
//
Player::~Player()
{
}

//----------------------------------------------------------------------
// Initialize player
//
void Player::Initialize(unsigned newId)
{
    assert(id == 0);
    id = newId;
}

//----------------------------------------------------------------------
// Assign seat for a game
//
void Player::AssignSeat(unsigned game, unsigned tableNo, unsigned seatNo)
{
    assert(seatNo != Seat::Break);

    // Assign seat
    //
    seats[game] = Seat(tableNo, seatNo);
    
    // Add penalty for the seat zone
    //
    ++zonePenalty[Seat::GetZoneNo(seatNo) - 1];
    ++gameCount;
}

//----------------------------------------------------------------------
// Get zone penalty for the seatNo
//
unsigned Player::GetZonePenalty(unsigned seat) const
{
    unsigned seatNo = seat + 1;
    unsigned zoneNo = Seat::GetZoneNo(seatNo);
    return zonePenalty[zoneNo - 1];
}

//----------------------------------------------------------------------
// Get cross-player penalty
//
unsigned Player::GetPlayerPenalty(Player* player) const
{
    return playerPenalty[player->GetId() - 1];
}

//----------------------------------------------------------------------
// Increment cross-player penalty
//
void Player::AddPlayerPenalty(Player* player)
{
    ++playerPenalty[player->GetId() - 1];
    ++player->playerPenalty[GetId() - 1];
}

//----------------------------------------------------------------------
// Get game count
//
unsigned Player::GetGameCount() const
{
    return gameCount;
}

//----------------------------------------------------------------------
// Get player ID
//
unsigned Player::GetId() const
{
    return id;
}
