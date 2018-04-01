//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// The generator.
//
#include "stdafx.h"
#include "Seat.h"
#include "Player.h"
#include "Generator.h"

//----------------------------------------------------------------------
// Constructor
//
Generator::Generator(
    unsigned players,
    unsigned tables,
    unsigned games,
    unsigned playerGames) :
    player(players, Player(games)),
    crossPlayerPenalty(players, std::vector<unsigned>(players))
{
}

//----------------------------------------------------------------------
// Destructor
//
Generator::~Generator()
{
}
