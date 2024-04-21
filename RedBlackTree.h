#pragma once

#include <map>
#include <string>

using namespace std;

struct WeatherData {
    double temperature;
    double precipitation;
};

class RedBlackTree {
public:
    RedBlackTree(); // Constructor

    // Getter and Setter
    void addData(const string& county, const string& date, const WeatherData& data);
    WeatherData getData(const string& county, const string& date) const;

private:
    map<pair<string, string>, WeatherData> weatherMap;
};
