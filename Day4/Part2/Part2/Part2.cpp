// Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

bool checkForBingo(vector<int> card)
{
    // Check if we have a winner
    int sum = 0;
    for (int loop = 0; loop < 5; loop++)
    {
        sum = 0;
        // Check Rows
        for (int row = 0; row < 5; row++)
        {
            int value = card[loop * 5 + row];
            sum += value;
        }
        if (sum == -5)
        {
            return true;
        }

        sum = 0;
        // Check Columns
        for (int col = 0; col < 5; col++)
        {
            int value = card[loop + col * 5];
            sum += value;
        }
        if (sum == -5)
        {
            return true;
        }
    }
    return false;
}

int getUnMarkedNumbers(vector<int> card)
{
    int sum = 0;

    for (int value : card)
    {
        if (value != -1)
        {
            sum += value;
        }
    }

    return sum;
}

bool alreadyWinner(vector<int> winners, int cardIndex)
{
    auto it = find(winners.begin(), winners.end(), cardIndex);

    if (it != winners.end())
    {
        return true;
    }

    return false;
}

int main()
{
    ifstream myfile;
    myfile.open("D:/GitHub/AdventOfCode2021/Day4/input.txt", ios::in);

    bool read_numbers = false;

    vector<int> bingo_calls;

    vector<vector<int>> bingocards;
    vector<int> card;

    // Grab all the data
    if (myfile.is_open())
    {
        string line;
        while (getline(myfile, line))
        {
            // Empty lines denote new cards are next to come.
            if (line.empty())
            {
                card.clear();
                continue;
            }

            // Copy the line into a new stream, this allows us to manipulate it a bit better.
            istringstream iss(line);
            string val;

            /*
            * Grab the Calling numbers
            */
            if (!read_numbers)
            {
                // This is a commar seperated list, so can break it up that way.
                while (getline(iss, val, ','))
                {
                    bingo_calls.push_back(stoi(val));
                }

                read_numbers = true;
            }
            else
            {
                /*
                * Create the cards
                */

                while (iss >> val)
                {
                    card.push_back(stoi(val));
                }
                // If the size of the card is 25 (5 x 5 grid) then push it onto the BOARDS vector
                if (card.size() == 25)
                {
                    bingocards.push_back(card);
                }
            }
        }
        myfile.close();   //close the file object.
    }
    else
    {
        cout << "Unable to open file";
        return 1;
    }

    vector<int> winningboards;

    // For each of the calls
    for (int index = 0; index < bingo_calls.size(); index++)
    {
        int call = bingo_calls[index];

        // Go through each of the cards
        for (int cardIndex = 0; cardIndex < bingocards.size(); cardIndex++)
        {
            // Grab the board
            // Make it a pointer so we once we manipulate the values using replace it will update the board rather in memory rather than a copy of it.
            auto* board = &bingocards[cardIndex];

            // Check to see if we are already a winner and move on
            if (alreadyWinner(winningboards, cardIndex))
            {
                continue;
            }

            // Replace the calling number with -1 to denote it being found
            replace(board->begin(), board->end(), call, -1);

            // Run the board through the checker..
            // Dereference the pointer
            if (checkForBingo(*board))
            {
                // If the next loop is out last board, then we have out "Last Card"
                if (winningboards.size() == bingocards.size() - 1)
                {
                    cout << "Call: " << call << endl;
                    int unmarkedsum = getUnMarkedNumbers(*board);
                    cout << "Unmarked Sum: " << unmarkedsum << endl;
                    cout << "Score (Unamrked Sum * call): " << unmarkedsum * call << endl;
                }
                winningboards.push_back(cardIndex);
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
