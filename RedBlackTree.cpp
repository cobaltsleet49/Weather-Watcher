#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {}

void RedBlackTree::addData(const std::string& county, const std::string& date, const WeatherData& data) {
    weatherMap[{county, date}] = data;
}

WeatherData RedBlackTree::getData(const std::string& county, const std::string& date) const {
    auto it = weatherMap.find({county, date});
    if (it != weatherMap.end()) {
        return it->second; // Return the pair of temperature and precipitation
    } else {
        return {-1.0, -1.0}; // Return a negative precipitation if not found
    }
}
