//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A player.
//
#pragma once

//----------------------------------------------------------------------
//
class Player
{
public:

    // Constructor
    //
    Player(unsigned games);

    // Destructor
    //
    ~Player();

    // Assign a seat for a game
    //
    void AssignSeat(unsigned gameNo, unsigned tableNo, unsigned seatNo);

    // Get zone penalty for the seatNo
    //
    unsigned GetZonePenalty(unsigned seatNo);

    // Getters
    //
    unsigned GetGameCount();

private:

    // Seat assignments for the tournament
    //
    std::vector<Seat> seat;

    // Accumulated zone penalty
    //
    unsigned zonePenalty[Seat::Zones];

    // Games assigned
    //
    unsigned gameCount;
};

