// Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
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
    else cout << "Unable to open file";

    // Gamme and Epsilon need to also be the same size
    bitset<bits> gammaRate;
    bitset<bits> epsilonRate;

    // Bitset stores the bits in the opposite way to the text file, so need to work backwards
    for (int i = bits - 1; i >= 0; i--)
    {
        // Array to hold how many 0's and 1's there are
        int counts[2] { 0,0 };
        // Go through all the reports
        for (auto report : reports)
        {
            // Incremement either Counts index 0 or index 1 based on the BIT we are currently looking at.
            counts[report[i]]++;
        }
        // Gamma uses the MOST common BIT
        gammaRate[i] = counts[0] > counts[1] ? 0 : 1;
    }
    // Since the Epsilon Rate use Least Common BIT, we can just flip the gamma
    epsilonRate = bitset<bits>(gammaRate).flip();

    cout << "Gamma Rate: " << gammaRate.to_ulong() << endl;
    cout << "Epsilon Rate: " << epsilonRate.to_ulong() << endl;
    cout << "Power consuption: " << gammaRate.to_ulong() * epsilonRate.to_ulong()  << endl;
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
