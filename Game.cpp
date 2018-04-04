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
    for (uint64_t seat = 0; seat < 10; ++seat)
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
Player*& Game::operator[](uint64_t seat)
{
    return players[seat];
}

//----------------------------------------------------------------------
// Player accessor
//
const Player* Game::operator[](uint64_t seat) const
{
    return players[seat];
}
