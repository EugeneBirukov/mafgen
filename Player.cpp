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
Player::Player(unsigned games) :
    seat(games),
    gameCount(0)
{
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
// Assign seat for a game
//
void Player::AssignSeat(unsigned gameNo, unsigned tableNo, unsigned seatNo)
{
    assert(seatNo != Seat::Break);

    // Assign seat
    //
    seat[gameNo] = Seat(tableNo, seatNo);
    
    // Add penalty for the seat zone
    //
    ++zonePenalty[Seat::GetZoneNo(seatNo)];
    ++gameCount;
}

//----------------------------------------------------------------------
// Get zone penalty for the seatNo
//
unsigned Player::GetZonePenalty(unsigned seatNo)
{
    return zonePenalty[Seat::GetZoneNo(seatNo)];
}

//----------------------------------------------------------------------
// Get game count
//
unsigned Player::GetGameCount()
{
    return gameCount;
}
