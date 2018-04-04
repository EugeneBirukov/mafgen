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
    uint64_t playerCount,
    uint64_t tableCount,
    uint64_t perTableGameCount,
    uint64_t tableGameCount,
    uint64_t playerGameCount) :
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
    for (uint64_t index = 0; index < playerCount; ++index)
    {
        allPlayers[index].Initialize(index + 1);
    }

    // Initialize all tables
    //
    for (uint64_t index = 0; index < tableCount; ++index)
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
        uint64_t tableMax = playerMax / Seat::Seats;

        // Select players for the game
        //
        Selector<Player*> players = SelectPlayersForGame();

        // Assign players to tables
        //
        for (uint64_t i = 0; i < playerMax; ++i)
        {
            // Pick a random player
            //
            auto player = players.PickOne();

            // Calculate table penalty
            //
            uint64_t currentPenalty = std::numeric_limits<uint64_t>::max();
            for (uint64_t tableNo = 0; tableNo < tableMax; ++tableNo)
            {
                Table* table = &allTables[tableNo];
                uint64_t penalty = table->GetPenalty(tableGame, player);
                currentPenalty = std::min(penalty, currentPenalty);
            }

            // Choose table
            //
            Selector<Table*> tables;
            for (uint64_t tableNo = 0; tableNo < tableMax; ++tableNo)
            {
                Table* table = &allTables[tableNo];
                uint64_t penalty = table->GetPenalty(tableGame, player);
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
    for (uint64_t tableNo = 0; tableNo < TableCount; ++tableNo)
    {
        std::cout << "TABLE " << std::setw(2) << tableNo + 1 << "                                    ";
    }
    std::cout << std::endl;

    // Print header 2
    //
    for (uint64_t tableNo = 0; tableNo < TableCount; ++tableNo)
    {
        for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
        {
            std::cout << std::setw(4) << seat + 1;
        }

        std::cout << "    ";
    }
    std::cout << std::endl;

    // Print header 3
    //
    for (uint64_t tableNo = 0; tableNo < TableCount; ++tableNo)
    {                
        for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
        {
            std::cout << "----";
        }

        std::cout << "    ";
    }
    std::cout << std::endl;

    // Print assignments
    //
    for (uint64_t game = 0; game < PerTableGameCount; ++game)
    {
        for (uint64_t tableNo = 0; tableNo < TableCount; ++tableNo)
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
            for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
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
    std::cout << "PLAYER SCHEDULES" << std::endl;
    std::cout << "     |";
    for (uint64_t game = 0; game < PerTableGameCount; ++game)
    {
        std::cout << std::setw(6) << std::right << game + 1;
    }
    std::cout << std::endl;

    std::cout << "-----+";
    for (uint64_t game = 0; game < PerTableGameCount; ++game)
    {
        std::cout << "------";
    }
    std::cout << std::endl;

    // Print seats
    //
    for (uint64_t playerNo = 0; playerNo < PlayerCount; ++playerNo)
    {
        // Output player ID
        //
        const Player& player = allPlayers[playerNo];
        std::cout << std::setw(4) << std::right << player.GetId() << " | ";

        // Print seats
        //
        for (uint64_t game = 0; game < PerTableGameCount; ++game)
        {
            std::cout << player[game] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

//----------------------------------------------------------------------
// Print player seat penalties
//
void Generator::PrintSeatPenalties()
{
    // Print header
    //
    std::cout << "ZONE & SEAT FREQUENCY" << std::endl;
    std::cout << "     |   1..3  4..7 8..10 |      1     2     3     4     5     6     7     8     9    10" << std::endl;
    std::cout << "-----+--------------------+-------------------------------------------------------------" << std::endl;

    // Print zone and seat penalties
    //
    for (uint64_t playerNo = 0; playerNo < PlayerCount; ++playerNo)
    {
        // Output player ID
        //
        const Player& player = allPlayers[playerNo];
        std::cout << std::setw(4) << std::right << player.GetId() << " | ";

        // Print zone penalties
        //
        for (uint64_t zone = 0; zone < Seat::Zones; ++zone)
        {
            std::cout << std::setw(6) << std::right << player.GetZonePenalty(zone);
        }
        std::cout << " | ";

        // Print seat penalties
        //
        for (uint64_t seat = 0; seat < Seat::Seats; ++seat)
        {
            std::cout << std::setw(6) << std::right << player.GetSeatPenalty(seat);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

//----------------------------------------------------------------------
// Print cross-player penalties
//
void Generator::PrintPlayerPenalties()
{
    // Print header 1
    //
    std::cout << "CROSS-PLAYER FREQUENCY" << std::endl;
    std::cout << "     |";
    for (uint64_t cross = 0; cross < PlayerCount; ++cross)
    {
        std::cout << std::setw(4) << std::right << cross + 1;
    }
    std::cout << std::endl;

    // Print header 2
    //
    std::cout << "-----+";
    for (uint64_t cross = 0; cross < PlayerCount; ++cross)
    {
        std::cout << "----";
    }
    std::cout << std::endl;

    // Print penalties
    //
    for (uint64_t playerNo = 0; playerNo < PlayerCount; ++playerNo)
    {
        // Output player ID
        //
        const Player& player = allPlayers[playerNo];
        std::cout << std::setw(4) << std::right << player.GetId() << " |";

        // Print player penalties
        //
        for (uint64_t cross = 0; cross < PlayerCount; ++cross)
        {
            std::cout << std::setw(4) << std::right << player.GetPlayerPenalty(&allPlayers[cross]);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}
