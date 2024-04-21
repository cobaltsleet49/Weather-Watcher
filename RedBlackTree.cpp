#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {}

void RedBlackTree::addData(const string& county, const string& date, const WeatherData& data) {
    weatherMap[{county, date}] = data;
}

WeatherData RedBlackTree::getData(const string& county, const string& date) const {
    auto it = weatherMap.find({county, date});
    if (it != weatherMap.end()) {
        return it->second; // Return the pair of temperature and precipitation
    } else {
        return {-1.0, -1.0}; // Return a negative precipitation if not found
    }
}

void RedBlackTree::buildTree() {
    for (int year = 2021; year <= 2023; year++) {
        for (int month = 1; month <= 12; month++) {
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

            // Iterate for the 3107 counties
            for (int i = 0; i < 3107; i++) {
                stringstream ss1(line1);
                string token1; // Use token to iterate through each line for precip
                stringstream ss2(line2);
                string token2; // Use token to iterate through each line for temp

                // Skip to the county name
                getline(ss1, token1, ',');
                // Extract the county name
                getline(ss1, county, ',');
                // Skip to the value
                getline(ss1, token1, ',');

                // Extract the value
                while (!isDouble(token1)) { // Edge Case for Washington, D.C.
                    getline(ss1, token1, ',');
                }
                precipitation = stod(token1);

                // Repeat for the temperature
                for (int i = 0; i < 4; i++) {
                    getline(ss2, token2, ',');
                }
                while (!isDouble(token2)) { // Edge Case for Washington, D.C.
                    getline(ss1, token2, ',');
                }
                temperature = stod(token2);

                addData(county, stringDate, {precipitation, temperature});

                WeatherData testvals = getData(county, stringDate);
                cout << testvals.precipitation << endl;
                cout << testvals.temperature << endl;

                // Move to the next lines for both files
                getline(precip, line1);
                getline(temp, line2);
            }
        }
    }
}

bool RedBlackTree::isDouble(const string& str) { // Checks if the current token can be converted to a double or not
    stringstream ss(str);
    double d;
    ss >> d;
    return !ss.fail() && ss.eof();
}
