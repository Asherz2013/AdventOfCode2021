// Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <array>
using namespace std;

int main()
{
    // How many bits are in each line
    const int bits = 12;
    // Bitset is a small class designed for holding BITS
    // Vector of these grabs all the reports from the text file
    vector<bitset<bits>> reports;

    ifstream myfile;
    myfile.open("D:/GitHub/AdventOfCode2021/Day3/input.txt", ios::in);

    // Grab all the data (this will be in STRING form
    if (myfile.is_open())
    {
        string line;
        while (getline(myfile, line))
        {
            // Convert the line to bits
            reports.push_back(bitset<bits>(line));
        }
        myfile.close();   //close the file object.

    }
    else
    {
        cout << "Unable to open file";
        return 1;
    }

    // Gamme and Epsilon need to also be the same size
    bitset<bits> oxygen_generator;
    bitset<bits> co2_scrubber;

    vector<bitset<bits>> most_common(reports);
    // Bitset stores the bits in the opposite way to the text file, so need to work backwards
    for (size_t i = bits - 1; most_common.size() > 1 && i >= 0; i--)
    {
        array<vector<bitset<bits>>, 2> filtered;
        // Go through all the reports
        for (auto report : most_common)
        {
            filtered[report[i]].push_back(report);
        }
        // The MOST common BIT goes towards Oxygen
        most_common = filtered[0].size() > filtered[1].size() ? filtered[0] : filtered[1];
    }
    oxygen_generator = most_common.at(0);

    vector<bitset<bits>> least_common(reports);
    // Bitset stores the bits in the opposite way to the text file, so need to work backwards
    for (size_t i = bits - 1; least_common.size() > 1 && i >= 0; i--)
    {
        array<vector<bitset<bits>>, 2> filtered;
        // Go through all the reports
        for (auto report : least_common)
        {
            filtered[report[i]].push_back(report);
        }
        // The MOST common BIT goes towards Oxygen
        least_common = filtered[0].size() > filtered[1].size() ? filtered[1] : filtered[0];
    }
    co2_scrubber = least_common.at(0);

    cout << "Oxygen: " << oxygen_generator.to_ulong() << endl;
    cout << "C02: " << co2_scrubber.to_ulong() << endl;
    cout << "Power consuption: " << oxygen_generator.to_ulong() * co2_scrubber.to_ulong() << endl;

    return 0;
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
