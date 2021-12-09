// Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    std::cout << "Hello World!\n";

    ifstream myfile;
    myfile.open("D:/GitHub/AdventOfCode2021/Day1/input.txt", ios::in);

    int prevNum = -1;
    int num = 0;

    int numIncrements = 0;

    vector<int> numbers;

    if (myfile.is_open())
    {
        string tp;
        while (getline(myfile, tp))
        {
            numbers.push_back(stoi(tp));
        }
        myfile.close();   //close the file object.
    }
    else cout << "Unable to open file";

    if (!numbers.empty())
    {
        // Find the first 3 numbers
        for (int iter = 0; iter < 3; iter++)
        {
            num += numbers[iter];
        }

        int oldIndex = 0;
        // Loop through from 3
        for (int newIndex=3; newIndex < numbers.size(); newIndex++)
        {
            // To get the new value, we can ake the current value, add the new index, and remove the "first" index
            /*
            1   A
            2   A   B
            3   A   B   C
            4       B   C   D
            5           C   D
            6               D
            */
            int newValue = num + numbers[newIndex] - numbers[oldIndex];
            if (newValue > num)
            {
                numIncrements++;
            }
            oldIndex++;
        }

        cout << "Increments: " << numIncrements;
    }
    else
    {
        cout << "Array was empty??";
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
