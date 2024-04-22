// This file contains two implementations of a Red-Black Tree
// The one commented out uses std::map, while the one currently active is written based of the lecture slides

#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "WeatherData.h"

using namespace std;

/*
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
*/

struct Node {
    // Key and values
    pair<string, string> key;
    WeatherData data;

    bool red; // true for red, false for black
    Node* parent;
    Node* left;
    Node* right;

    // Constructor
    Node(const pair<string, string>& key, const WeatherData& data) :
            key(key), data(data), red(true), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void insertHelper(Node* node, const pair<string, string>& key, const WeatherData& data);

    // Rotation and balancing
    void rotateLeft(Node*& node);
    void rotateRight(Node*& node);
    void balance(Node* node);

    bool isDouble(const string& str); // buildTree helper function

    void deleteTree(Node* node); // Destructor helper

public:
    // Constructor
    RedBlackTree() : root(nullptr) {}

    // Getter and Setter
    void insert(const pair<string, string>& key, const WeatherData& data);
    WeatherData getData(const pair<string, string>& key) const;

    // Tree Builder
    void buildTree();

    // Destructor
    ~RedBlackTree() { deleteTree(root); }
};

