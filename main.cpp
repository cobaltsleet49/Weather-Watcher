#include <chrono> // Used for timing
#include <iomanip> // Used to get a certain number of decimal places

#include "RedBlackTree.h"
#include "HashTable.h"

// You can add more data sets at https://www.ncei.noaa.gov/access/monitoring/climate-at-a-glance/county/mapping
// Format for the .csv files is "Year-MonthP/T", where P stands for precipitation and T for average temperature

using namespace std;

int main() {
    RedBlackTree tree;
    HashTable table;

    // Build the RedBlackTree and calculate the time it takes
    auto start = chrono::high_resolution_clock::now(); // Start the clock
    tree.buildTree(); // Build the Tree
    auto end = chrono::high_resolution_clock::now(); // Stop the clock
    chrono::duration<double> duration = end - start; // Calculate the duration
    cout << "Time taken to build the Red-Black Tree: " << duration.count() << " seconds" << endl; // Print the duration

    // Repeat for the HashTable
    start = chrono::high_resolution_clock::now();
    table.buildTable(); // Build the Table
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Time taken to build the Hash Table: " << duration.count() << " seconds" << endl;

    // Welcome Message
    cout << "\nWelcome to the Weather Watcher!\n"
            "-------------------------------\n";

    // Menu Selection
    int menuInput = -1;
    while (true) {
        cout << "\nWhat would you like to do today?\n"
                "--------------------------------\n"
                "0. Exit\n"
                "1. View Precipitation\n"
                "2. View Temperature\n"
                "\nEnter your menu selection: ";

        if (!(cin >> menuInput)) { // Check if the input is a valid integer
            cout << "Invalid Input - your input must be an integer. Please try again.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }
        cin.ignore();

        if (menuInput == 0) { // Exit condition
            cout << "\nThank you for using Weather Watcher and have a nice day!\n";
            break;
        }
        if (menuInput == 1 || menuInput == 2) { // Grab the county and date, choose the data structure, then conduct the search
            string county;
            string year;
            string month;

            cout << "Enter county name: ";
            getline(cin, county);
            cout << "Enter the year: ";
            getline(cin, year);
            cout << "Enter the month (either a 1 or 2-digit number): ";
            getline(cin, month);

            int dataStructure = -1;
            while (true) {
                cout << "\nWhat data structure would you like to use?\n"
                        "------------------------------------------\n"
                        "0. Red-Black Tree\n"
                        "1. Hash Table\n"
                        "\nEnter your menu selection: ";

                if (!(cin >> dataStructure)) { // Check if the input is a valid integer
                    cout << "Invalid Input - your input must be an integer. Please try again.\n";
                    cin.clear(); // Clear the fail state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    continue;
                }
                cin.ignore();

                if (dataStructure == 0 || dataStructure == 1) {
                    // Concatenate the year and month into the date form
                    stringstream date;
                    date << year << "-" << month;
                    string stringDate = date.str();

                    county += " County"; // Concatenate "County" to the county name

                    start = chrono::high_resolution_clock::now(); // Start the timer for the search

                    if (dataStructure == 0) {
                        WeatherData treeData = tree.getData({county, stringDate}); // Search the tree
                        // WeatherData treeData = tree.getData(county, stringDate); // std::map implementation

                        end = chrono::high_resolution_clock::now(); // Stop the timer
                        duration = end - start;
                        cout << "Time taken to search the Red-Black Tree: " << fixed << setprecision(10) << duration.count() << " seconds" << endl;

                        if (treeData.precipitation == -1.0) {
                            cout << "Sorry, we could not find the county/date you were looking for. Please try again.\n";
                            break;
                        }
                        else {
                            if (menuInput == 1) {
                                cout << "\nThe precipitation for " << county << " on " << stringDate << " was " << fixed << setprecision(2) << treeData.precipitation << " inches.\n";
                            }
                            if (menuInput == 2) {
                                cout << "\nThe average temperature for " << county << " on " << stringDate << " was " << fixed << setprecision(2) << treeData.temperature << " degrees Fahrenheit.\n";
                            }
                        }
                    }

                    if (dataStructure == 1) {
                        WeatherData tableData = table.getData(county, stringDate); // Search the tree

                        end = chrono::high_resolution_clock::now(); // Stop the timer
                        duration = end - start;
                        cout << "Time taken to search the Hash Table: " << fixed << setprecision(10) << duration.count() << " seconds" << endl;

                        if (tableData.precipitation == -1.0) {
                            cout << "Sorry, we could not find the county/date you were looking for. Please try again.\n";
                            break;
                        }
                        else {
                            if (menuInput == 1) {
                                cout << "\nThe precipitation for " << county << " on " << stringDate << " was " << fixed << setprecision(2)<< tableData.precipitation << " inches.\n";
                            }
                            if (menuInput == 2) {
                                cout << "\nThe average temperature for " << county << " on " << stringDate << " was " << fixed << setprecision(2) << tableData.temperature << " degrees Fahrenheit.\n";
                            }
                        }
                    }
                    break;
                }
                else {
                    cout << "Invalid Input - your input must be 0, 1, or 2. Please try again.";
                }
            }

        }
        else {
            cout << "Invalid Input - your input must be 0, 1, or 2. Please try again.";
        }
    }


    return 0;
}
