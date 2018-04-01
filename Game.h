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
    unsigned& operator[](unsigned seatNo)
    {
        // Seat numbering starts with 1
        //
        return player[seatNo - 1];
    }

private:

    // 10 players per game
    //
    unsigned player[10];
};

