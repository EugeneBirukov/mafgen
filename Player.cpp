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
Player::Player(uint64_t playerCount, uint64_t perTableGameCount) :
    seats(perTableGameCount),
    id(0),
    gameCount(0),
    playerPenalty(playerCount, 0)
{
    // Initialize zonePenalty array
    //
    for (uint64_t zone = 0; zone < Seat::Zones; ++zone)
    {
        zonePenalty[zone] = 0;
    }

    // Initialize seatPenalty array
    //
    for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
    {
        seatPenalty[seat] = 0;
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
void Player::Initialize(uint64_t newId)
{
    assert(id == 0);
    id = newId;
}

//----------------------------------------------------------------------
// Assign seat for a game
//
void Player::AssignSeat(uint64_t game, uint64_t tableNo, uint64_t seatNo)
{
    assert(seatNo != Seat::Break);

    // Assign seat
    //
    seats[game] = Seat(tableNo, seatNo);
    
    // Add penalty for the seat and zone
    //
    zonePenalty[Seat::GetZoneNo(seatNo) - 1] += 4;
    ++seatPenalty[seatNo - 1];

    // Done with this game
    //
    ++gameCount;
}

//----------------------------------------------------------------------
// Get zone penalty for the seatNo
//
uint64_t Player::GetZoneSeatPenalty(uint64_t seat) const
{
    uint64_t seatNo = seat + 1;
    uint64_t zoneNo = Seat::GetZoneNo(seatNo);
    return zonePenalty[zoneNo - 1] + seatPenalty[seatNo - 1];
}

//----------------------------------------------------------------------
// Get cross-player penalty
//
uint64_t Player::GetPlayerPenalty(Player* player) const
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
uint64_t Player::GetGameCount() const
{
    return gameCount;
}

//----------------------------------------------------------------------
// Get player ID
//
uint64_t Player::GetId() const
{
    return id;
}

//----------------------------------------------------------------------
// Seat accessor
//
const Seat& Player::operator[](uint64_t game) const
{
    return seats[game];
}

//----------------------------------------------------------------------
// Get zone penalty for the seat
//
uint64_t Player::GetZonePenalty(uint64_t zone) const
{
    return zonePenalty[zone];
}

//----------------------------------------------------------------------
// Get seat penalty for the seat
//
uint64_t Player::GetSeatPenalty(uint64_t seat) const
{
    return seatPenalty[seat];
}
