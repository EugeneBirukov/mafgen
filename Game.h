//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A tournament game.
//
#pragma once

//----------------------------------------------------------------------
//
class Game
{
public:

    // Constructor
    //
    Game();

    // Destructor
    //
    ~Game();

    // Player accessor
    //
    Player*& operator[](uint64_t seat);

    // Player accessor
    //
    const Player* operator[](uint64_t seat) const;

private:

    // 10 players per game
    //
    Player* players[10];
};

