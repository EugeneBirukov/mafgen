//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A seat at a table.
//
#include "stdafx.h"
#include "Seat.h"

//----------------------------------------------------------------------
// Seat zones: 1..3, 4..7, 8..10
//
unsigned Seat::zone[10 + 1] =
{
    0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3
};

//----------------------------------------------------------------------
// Default constructor
//
Seat::Seat()
{
    table = Break;
    seat = Break;
}

//----------------------------------------------------------------------
// Constructor
//
Seat::Seat(unsigned tableNo, unsigned seatNo)
{
    table = tableNo;
    seat = seatNo;
}

//----------------------------------------------------------------------
// Destructor
//
Seat::~Seat()
{
}

//----------------------------------------------------------------------
// Get zone number
//
unsigned Seat::GetZoneNo(unsigned seatNo)
{
    return zone[seatNo];
}
