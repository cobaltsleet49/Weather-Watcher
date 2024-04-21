#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "RedBlackTree.h"

using namespace std;

int main() {
    RedBlackTree test;

    // NOAA only published data for January, February, and March
    for (int year = 2023; year <= 2024; year++) {
        for (int month = 1; month <= 3; month++) {
            stringstream date;
            date << year << "-" << month;
            string stringDate = date.str();

            stringstream filenameP, filenameT;
            filenameP << stringDate << "P.csv";
            filenameT << stringDate << "T.csv";

            ifstream precip(filenameP.str());
            ifstream temp(filenameT.str());
            if (!precip.is_open() || !temp.is_open()) {
                cerr << "Failed to open file." << endl;
            }

            string line1; // Read precipitation file
            string line2; // Read temperature file

            string county;
            double precipitation;
            double temperature;

            // Skip lines until we reach the 6th line
            for (int i = 0; i < 6; i++) {
                getline(precip, line1);
                getline(temp, line2);
            }

            stringstream ss1(line1);
            string token1; // Use token to iterate through each line

            // Skip to the county name
            getline(ss1, token1, ',');

            // Extract the county name
            getline(ss1, county, ',');

            // Skip to the value
            getline(ss1, token1, ',');

            // Extract the value
            getline(ss1, token1, ',');
            precipitation = stod(token1);

            // Repeat for the temperature
            stringstream ss2(line2);
            string token2; // Use token to iterate through each line

            for (int i = 0; i < 4; i++) {
                getline(ss2, token2, ',');
            }
            temperature = stod(token2);

            test.addData(county, stringDate, {precipitation, temperature});

            WeatherData testvals = test.getData(county, stringDate);
            cout << testvals.precipitation << endl;
            cout << testvals.temperature << endl;

        }
    }

    return 0;
}
