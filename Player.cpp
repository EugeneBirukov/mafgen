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
Player::Player(unsigned playerCount, unsigned tableGameCount) :
    seats(tableGameCount),
    id(0),
    gameCount(0),
    playerPenalty(playerCount + 1, 0)
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
void Player::AssignSeat(unsigned gameNo, unsigned tableNo, unsigned seatNo)
{
    assert(seatNo != Seat::Break);

    // Assign seat
    //
    seats[gameNo] = Seat(tableNo, seatNo);
    
    // Add penalty for the seat zone
    //
    ++zonePenalty[Seat::GetZoneNo(seatNo)];
    ++gameCount;
}

