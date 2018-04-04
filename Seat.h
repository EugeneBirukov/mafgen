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
    static constexpr uint64_t Break = 0;

    // The number of seats:
    //
    static constexpr uint64_t Seats = 10;

    // The number of zones:
    // 1..3, 4..7, 8..10
    //
    static constexpr uint64_t Zones = 3;

    // Get zone number 
    //
    static uint64_t GetZoneNo(uint64_t seatNo);

    // Default constructor
    //
    Seat();
    
    // Constructor
    //
    Seat(uint64_t tableNo, uint64_t seatNo);

    // Destructor
    //
    ~Seat();

    // Get table
    //
    uint64_t GetTable() const;

    // Get seat
    //
    uint64_t GetSeat() const;

private:

    // Seat zones: 1..3, 4..7, 8..10
    //
    static uint64_t zone[1 + Seat::Seats];

    // Table No: Break, 1..tables
    //
    uint64_t table;

    // seat at the table: Break, 1..10
    //
    uint64_t seat;
};

// Output operator
//
std::ostream& operator<< (std::ostream& os, const Seat& seat);
