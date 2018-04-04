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
    Player*& operator[](unsigned seat);

    // Player accessor
    //
    const Player* operator[](unsigned seat) const;

private:

    // 10 players per game
    //
    Player* players[10];
};

