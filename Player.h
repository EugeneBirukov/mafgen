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
    Player(uint64_t playerCount, uint64_t tableGameCount);

    // Destructor
    //
    ~Player();

    // Initialize player
    //
    void Initialize(uint64_t newId);

    // Assign a seat for a game
    //
    void AssignSeat(uint64_t gameNo, uint64_t tableNo, uint64_t seatNo);

    // Get seat and zone penalty for the seatNo
    //
    uint64_t GetZoneSeatPenalty(uint64_t seatNo) const;

    // Get cross-player penalty
    //
    uint64_t GetPlayerPenalty(Player* player) const;
            
    // Increment cross-player penalty
    //
    void AddPlayerPenalty(Player* player);

    // Get game count
    //
    uint64_t GetGameCount() const;

    // Get player ID
    //
    uint64_t GetId() const;

    const Seat& operator[](uint64_t game) const;

    // Get zone penalty
    //
    uint64_t GetZonePenalty(uint64_t zone) const;

    // Get seat penalty
    //
    uint64_t GetSeatPenalty(uint64_t seat) const;

private:

    // Player ID, starts from 1
    //
    uint64_t id;

    // Seat assignments for the tournament
    //
    std::vector<Seat> seats;

    // Accumulated cross-player penalty
    //
    std::vector<uint64_t> playerPenalty;

    // Accumulated zone penalty
    //
    uint64_t zonePenalty[Seat::Zones];

    // Accumulated seat penalty
    //
    uint64_t seatPenalty[Seat::Seats];

    // Games assigned
    //
    uint64_t gameCount;
};

