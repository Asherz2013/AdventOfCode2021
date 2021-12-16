// Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Holds 1 coordinate (x,y)
struct Point
{
    int x;
    int y;
};

// Holds a "line" of points
struct LineSegment
{
    Point start;
    Point end;
};

int main()
{
    ifstream myfile;
    //myfile.open("D:/GitHub/AdventOfCode2021/Day5/sample.txt", ios::in);
    myfile.open("D:/GitHub/AdventOfCode2021/Day5/input.txt", ios::in);

    vector<LineSegment> lineSegments;

    int max_x = 0;
    int max_y = 0;

    // Grab all the data
    if (myfile.is_open())
    {
        string line;
        while (getline(myfile, line))
        {
            // Put the line into a new stream for easier manipulation
            auto iss = istringstream(line);

            int x1;
            int y1;
            int x2;
            int y2;

            char dead;

            iss >> x1 >> dead >> y1 >> dead >> dead >> x2 >> dead >> y2;

            Point start;
            start.x = x1;
            start.y = y1;

            Point end;
            end.x = x2;
            end.y = y2;

            LineSegment lineSegment;
            lineSegment.start = start;
            lineSegment.end = end;

            lineSegments.push_back(lineSegment);

            max_x = max(max_x, max(x1, x2));
            max_y = max(max_y, max(y1, y2));
        }
        myfile.close();   //close the file object.

        max_x++;
        max_y++;

        cout << "Max X: " << max_x << endl;
        cout << "Max Y: " << max_y << endl;

        vector<int> map;
        map.resize(max_x * max_y);

        cout << "Map size: " << map.size() << endl;

        for (auto line : lineSegments)
        {
            Point cursor = line.start;

            bool is_at_end = false;

            while (!is_at_end)
            {
                is_at_end = (cursor.x == line.end.x) && (cursor.y == line.end.y);

                /*
                Formula:
                x + (y * width)

                0 1 2
                3 4 5

                (1,0)
                1 + (0 * 3) = 1

                (0,1)
                0 + (1 * 3) = 3

                (2,1)
                2 + (1 * 3) = 5
                */

                int map_i = cursor.x + (cursor.y * max_x);
                map[map_i]++;

                // Move the cursor towards the end
                if (cursor.x < line.end.x)
                {
                    cursor.x++;
                }
                else if (cursor.x > line.end.x)
                {
                    cursor.x--;
                }
                if (cursor.y < line.end.y)
                {
                    cursor.y++;
                }
                else if (cursor.y > line.end.y)
                {
                    cursor.y--;
                }
            }
        }

        // Print out the map
        /*for (int y = 0; y < max_y; y++)
        {
            for (int x = 0; x < max_x; x++)
            {
                int count = map[x + (y * max_x)];
                if (count == 0)
                {
                    cout << ".";
                }
                else
                {
                    cout << count;
                }
            }
            cout << endl;
        }*/

        int number_of_intersections = 0;
        for (int spot : map)
        {
            if (spot >= 2)
            {
                number_of_intersections++;
            }
        }

        cout << "We have " << number_of_intersections << " points greater than 1";
    }
    else
    {
        cout << "Unable to open file";
        return 1;
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
