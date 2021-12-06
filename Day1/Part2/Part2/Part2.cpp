// Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    std::cout << "Hello World!\n";

    ifstream myfile;
    myfile.open("D:/GitHub/AdventOfCode2021/Day1/input.txt", ios::in);

    int prevNum = -1;
    int num = 0;

    int numIncrements = 0;

    if (myfile.is_open())
    {
        string tp;
        while (getline(myfile, tp))
        {
            num = stoi(tp);

            if (prevNum > -1)
            {
                if (num > prevNum)
                {
                    numIncrements++;
                }
            }

            prevNum = num;
        }
        myfile.close();   //close the file object.

        cout << "Number of Increments: " << numIncrements;
    }
    else cout << "Unable to open file";
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
