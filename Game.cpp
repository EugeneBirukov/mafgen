//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A tournament game.
//
#include "stdafx.h"

//----------------------------------------------------------------------
// Constructor
//
Game::Game()
{
    for (unsigned seat = 0; seat < 10; ++seat)
    {
        players[seat] = nullptr;
    }
}

//----------------------------------------------------------------------
// Destructor
//
Game::~Game()
{
}

//----------------------------------------------------------------------
// Player accessor
//
Player*& Game::operator[](unsigned seat)
{
    return players[seat];
}

//----------------------------------------------------------------------
// Player accessor
//
const Player* Game::operator[](unsigned seat) const
{
    return players[seat];
}
