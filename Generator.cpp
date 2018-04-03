//======================================================================
// Mafia Tournament Table Generator
//
//  Copyright (c) Eugene Birukov, 2018
//
// The generator.
//
#include "stdafx.h"

//----------------------------------------------------------------------
// Constructor
//
Generator::Generator(
    unsigned playerCount,
    unsigned tableCount,
    unsigned perTableGameCount,
    unsigned tableGameCount,
    unsigned playerGameCount) :
    PlayerCount(playerCount),
    TableCount(tableCount),
    PerTableGameCount(perTableGameCount),
    PlayerGameCount(playerGameCount),
    SeatCount(tableGameCount * 10),
    TableGameCount(tableGameCount),
    allPlayers(playerCount, Player(playerCount, tableGameCount)),
    allTables(tableCount, Table(perTableGameCount)),
    playerGame(0),
    tableGame(0),
    seat(0)
{
    // Initialize all players
    //
    for (unsigned index = 0; index < playerCount; ++index)
    {
        allPlayers[index].Initialize(index + 1);
    }
}

//----------------------------------------------------------------------
// Destructor
//
Generator::~Generator()
{
}

//----------------------------------------------------------------------
// Generate the tournament table
//
void Generator::Generate()
{
    // Generate every round
    //
    while (tableGame < PerTableGameCount)
    {
        // The number of players to play simultaneously at all tables
        // Note: in the last game some tables may be inactive.
        //
        playerMax = std::min(TableCount * 10, SeatCount - seat);

        // Select players for the game
        //
        Selector<Player*> players = SelectPlayersForGame();

        // TODO:
        for (unsigned i = 0; i < playerMax; ++i)
        {
            auto player = players.PickOne();
            player->AssignSeat(tableGame, 1, 1);
            ++seat;
        }

        // Done, advance the counter
        //
        ++tableGame;
    }
}

//----------------------------------------------------------------------
// Get players who has not played 'playerGame'
//
void Generator::GetPlayersForGame(Selector<Player *> &players)
{
    for (auto& player : allPlayers)
    {
        if (player.GetGameCount() == playerGame)
        {
            // This player has not played the playerGame
            //
            players.push_back(&player);
        }
    }
}

//----------------------------------------------------------------------
// Select players for one game at all tables
//
Selector<Player*> Generator::SelectPlayersForGame()
{
    // Select candidates for this round
    //
    Selector<Player*> players;
    GetPlayersForGame(players);

    if (players.size() < playerMax)
    {
        // We have some room at the tables
        // Start a new game
        //
        ++playerGame;

        // Collect all remaining players
        //
        Selector<Player*> playersPlus;
        GetPlayersForGame(playersPlus);
        assert(players.size() + playersPlus.size() == allPlayers.size());

        // Pick a few players for the next game - just enough to fill the tables
        //
        for (size_t count = players.size(); count < playerMax; ++count)
        {
            auto player = playersPlus.PickOne();
            players.push_back(player);
        }
    }

    // Return it to the caller
    //
    return players;
}
