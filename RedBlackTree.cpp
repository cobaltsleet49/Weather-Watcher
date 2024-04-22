// This file contains two implementations of a Red-Black Tree
// The one commented out uses std::map, while the one currently active is written based of the lecture slides

#include "RedBlackTree.h"
/*
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
*/

void RedBlackTree::rotateLeft(Node*& node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (!node->parent) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void RedBlackTree::rotateRight(Node*& node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (!node->parent) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

void RedBlackTree::insert(const pair<string, string>& key, const WeatherData& data) {
    insertHelper(root, key, data);
    root->red = false; // Ensure root is black
}

void RedBlackTree::insertHelper(Node* node, const pair<string, string>& key, const WeatherData& data) {
    // Create a new node
    Node* newNode = new Node(key, data);
    // Traverse down the tree using binary search and current/parent to keep track of position
    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // If the key already exists, update the data and return
            current->data = data;
            delete newNode; // Delete the new node since insertion isn't needed
            return;
        }
    }
    // Insert the new node
    newNode->parent = parent;
    if (!parent) {
        root = newNode; // If the tree is empty, set the new node as the root
    }
    else if (key < parent->key) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    // Balance the tree
    balance(newNode);
}

void RedBlackTree::balance(Node* node) { // Based off the pseudocode from Aman's slides
    if (!node->parent) {
        node->red = false;
        return;
    }
    if (!node->parent->red) {
        return;
    }

    Node* parent = node->parent;
    Node* grandparent = parent->parent;
    Node* uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;

    if (uncle && uncle->red) {
        parent->red = uncle->red = false;
        grandparent->red = true;
        balance(grandparent);
        return;
    }
    if (node == parent->right && parent == grandparent->left) {
        rotateLeft(parent);
        node = parent;
        parent = node->parent;
    }
    else if (node == parent->left && parent == grandparent->right) {
        rotateRight(parent);
        node = parent;
        parent = node->parent;
    }

    parent->red = false;
    grandparent->red = true;
    if (node == parent->left) {
        rotateRight(grandparent);
    }
    else {
        rotateLeft(grandparent);
    }
}

WeatherData RedBlackTree::getData(const pair<string, string>& key) const {
    Node* current = root;
    while (current != nullptr) {
        if (key == current->key) {
            return current->data;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return WeatherData{-1.0, -1.0};
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

                insert({county, stringDate}, {precipitation, temperature});

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

void RedBlackTree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
