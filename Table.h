//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// A tournament table.
//
#pragma once

//----------------------------------------------------------------------
//
class Table
{
public:

    // Constructor
    //
    Table(unsigned games);

    // Destructor
    //
    ~Table();

private:

    std::vector<Game> game;
};

