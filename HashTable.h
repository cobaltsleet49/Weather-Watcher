#pragma once

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "WeatherData.h"

using namespace std;

// Define a custom hash function for pair<string, string>
// Inspiration: https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
namespace std {
    template <>
    struct hash<pair<string, string>> {
        size_t operator()(const pair<string, string>& p) const {
            // Get the hashes for both strings
            size_t hash1 = hash<string>{}(p.first);
            size_t hash2 = hash<string>{}(p.second);
            // Combine the hashes using bitwise operations
            return hash1 ^ (hash2 << 1);
        }
    };
}

class HashTable {
public:
    HashTable(); // Constructor

    // Getter and Setter
    void addData(const string& county, const string& date, const WeatherData& data);
    WeatherData getData(const string& county, const string& date) const;

    // Tree Builder
    void buildTable();

private:
    unordered_map<pair<string, string>, WeatherData> weatherMap;

    bool isDouble(const string& str); // buildTree helper function
};
