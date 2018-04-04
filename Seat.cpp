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
uint64_t Seat::zone[Seat::Seats + 1] =
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
Seat::Seat(uint64_t tableNo, uint64_t seatNo)
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
uint64_t Seat::GetZoneNo(uint64_t seatNo)
{
    return zone[seatNo];
}

//----------------------------------------------------------------------
// Get table
//
uint64_t Seat::GetTable() const
{
    return table;
}

//----------------------------------------------------------------------
// Get seat
//
uint64_t Seat::GetSeat() const
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
        os << "  -  ";
    }

    return os;
}

