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
    SeatCount(tableGameCount * Seat::Seats),
    TableGameCount(tableGameCount),
    allPlayers(playerCount, Player(playerCount, perTableGameCount)),
    allTables(tableCount, Table(perTableGameCount)),
    playerGame(0),
    tableGame(0),
    seats(0)
{
    // Initialize all players
    //
    for (unsigned index = 0; index < playerCount; ++index)
    {
        allPlayers[index].Initialize(index + 1);
    }

    // Initialize all tables
    //
    for (unsigned index = 0; index < tableCount; ++index)
    {
        allTables[index].Initialize(index + 1);
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
        playerMax = std::min(TableCount * Seat::Seats, SeatCount - seats);
        unsigned tableMax = playerMax / Seat::Seats;

        // Select players for the game
        //
        Selector<Player*> players = SelectPlayersForGame();

        // Assign players to tables
        //
        for (unsigned i = 0; i < playerMax; ++i)
        {
            // Pick a random player
            //
            auto player = players.PickOne();

            // Calculate table penalty
            //
            unsigned currentPenalty = std::numeric_limits<unsigned>::max();
            for (unsigned tableNo = 0; tableNo < tableMax; ++tableNo)
            {
                Table* table = &allTables[tableNo];
                unsigned penalty = table->GetPenalty(tableGame, player);
                currentPenalty = std::min(penalty, currentPenalty);
            }

            // Choose table
            //
            Selector<Table*> tables;
            for (unsigned tableNo = 0; tableNo < tableMax; ++tableNo)
            {
                Table* table = &allTables[tableNo];
                unsigned penalty = table->GetPenalty(tableGame, player);
                if (penalty == currentPenalty)
                {
                    tables.push_back(table);
                }
            }

            // Assign the player to the table
            //
            Table* table = tables.PickOne();
            table->AssignSeat(tableGame, player);
            ++seats;
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

//----------------------------------------------------------------------
// Print table assignments
//
void Generator::PrintTables()
{
    // Print header 1
    //
    for (unsigned tableNo = 0; tableNo < TableCount; ++tableNo)
    {
        std::cout << "TABLE " << std::setw(2) << tableNo + 1 << "                                    ";
    }
    std::cout << std::endl;

    // Print header 2
    //
    for (unsigned tableNo = 0; tableNo < TableCount; ++tableNo)
    {
        for (unsigned seat = 0; seat < Seat::Seats; ++seat)
        {
            std::cout << std::setw(4) << seat + 1;
        }

        std::cout << "    ";
    }
    std::cout << std::endl;

    // Print header 3
    //
    for (unsigned tableNo = 0; tableNo < TableCount; ++tableNo)
    {                
        for (unsigned seat = 0; seat < Seat::Seats; ++seat)
        {
            std::cout << "----";
        }

        std::cout << "    ";
    }
    std::cout << std::endl;

    // Print assignments
    //
    for (unsigned game = 0; game < PerTableGameCount; ++game)
    {
        for (unsigned tableNo = 0; tableNo < TableCount; ++tableNo)
        {
            // Get table
            //
            Table& table = allTables[tableNo];

            // See if this table is empty (on the last game)
            //
            if (table[game][0] == nullptr)
            {
                break;
            }

            // Print assignments
            //
            for (unsigned seat = 0; seat < Seat::Seats; ++seat)
            {
                std::cout << std::setw(4) << table[game][seat]->GetId();
            }

            std::cout << "    ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

//----------------------------------------------------------------------
// Print player seats
//
void Generator::PrintPlayers()
{
    // Print header
    //
    std::cout << "     ";
    for (unsigned game = 0; game < PerTableGameCount; ++game)
    {
        std::cout << std::setw(6) << std::right << game + 1;
    }
    std::cout << std::endl;

    // Print seats
    //
    for (unsigned playerNo = 0; playerNo < PlayerCount; ++playerNo)
    {
        // Output player ID
        //
        Player& player = allPlayers[playerNo];
        std::cout << std::setw(4) << std::right << player.GetId() << "  ";

        for (unsigned game = 0; game < PerTableGameCount; ++game)
        {
            std::cout << player[game] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}
