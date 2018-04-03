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
    Player(unsigned playerCount, unsigned tableGameCount);

    // Destructor
    //
    ~Player();

    // Initialize player
    //
    void Initialize(unsigned newId);

    // Assign a seat for a game
    //
    void AssignSeat(unsigned gameNo, unsigned tableNo, unsigned seatNo);

    // Get zone penalty for the seatNo
    //
    unsigned GetZonePenalty(unsigned seatNo) const
    {
        return zonePenalty[Seat::GetZoneNo(seatNo)];
    }

    // Get cross-player penalty
    //
    unsigned GetPlayerPenalty(unsigned playerId) const
    {
        return playerPenalty[playerId];
    }
            
    // Get game count
    //
    unsigned GetGameCount() const
    {
        return gameCount;
    }

    // Get player ID
    //
    unsigned GetId() const
    {
        return id;
    }

private:

    // Player ID
    //
    unsigned id;

    // Seat assignments for the tournament
    //
    std::vector<Seat> seats;

    // Accumulated cross-player penalty
    //
    std::vector<unsigned> playerPenalty;

    // Accumulated zone penalty
    //
    unsigned zonePenalty[Seat::Zones];

    // Games assigned
    //
    unsigned gameCount;
};

