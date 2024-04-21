#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "WeatherData.h"

using namespace std;

class RedBlackTree {
public:
    RedBlackTree(); // Constructor

    // Getter and Setter
    void addData(const string& county, const string& date, const WeatherData& data);
    WeatherData getData(const string& county, const string& date) const;

    // Tree Builder
    void buildTree();

private:
    map<pair<string, string>, WeatherData> weatherMap;

    bool isDouble(const string& str); // buildTree helper function
};
