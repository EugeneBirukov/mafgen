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

    // The number of zones:
    // Break, 1..3, 4..7, 8..10
    //
    static constexpr unsigned Zones = 4;

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

private:

    // Seat zones: Break, 1..3, 4..7, 8..10
    //
    static unsigned zone[1 + 10];

    // Table No: Break, 1..tables
    //
    unsigned table;

    // seat at the table: Break, 1..10
    //
    unsigned seat;
};

