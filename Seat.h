//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A seat at a table.
//
#pragma once

//----------------------------------------------------------------------
//
class Seat
{
public:

    // Sentinel table/seat number which means the player has a break
    //
    static constexpr unsigned Break = 0;

    // The number of seats:
    //
    static constexpr unsigned Seats = 10;

    // The number of zones:
    // 1..3, 4..7, 8..10
    //
    static constexpr unsigned Zones = 3;

    // Get zone number 
    //
    static unsigned GetZoneNo(unsigned seatNo);

    // Default constructor
    //
    Seat();
    
    // Constructor
    //
    Seat(unsigned tableNo, unsigned seatNo);

    // Destructor
    //
    ~Seat();

    // Get table
    //
    unsigned GetTable() const;

    // Get seat
    //
    unsigned GetSeat() const;

private:

    // Seat zones: 1..3, 4..7, 8..10
    //
    static unsigned zone[1 + Seat::Seats];

    // Table No: Break, 1..tables
    //
    unsigned table;

    // seat at the table: Break, 1..10
    //
    unsigned seat;
};

// Output operator
//
std::ostream& operator<< (std::ostream& os, const Seat& seat);
