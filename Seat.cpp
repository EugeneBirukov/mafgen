//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A seat at a table.
//
#include "stdafx.h"

//----------------------------------------------------------------------
// Seat zones: 1..3, 4..7, 8..10
//
unsigned Seat::zone[Seat::Seats + 1] =
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

//----------------------------------------------------------------------
// Get table
//
unsigned Seat::GetTable() const
{
    return table;
}

//----------------------------------------------------------------------
// Get seat
//
unsigned Seat::GetSeat() const
{
    return seat;
}

//----------------------------------------------------------------------
// Output operator
//
std::ostream& operator<<(std::ostream& os, const Seat& seat)
{
    if (seat.GetTable() != 0)
    {
        os << std::setw(2) << std::right << seat.GetTable() << "/" << std::setw(2) << std::left << seat.GetSeat();
    }
    else
    {
        os << "Break";
    }

    return os;
}

