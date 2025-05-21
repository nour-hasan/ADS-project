#include <iostream>
#include <limits>
#include "Graph.h"
#include <string>
#include <vector>
#include <chrono>

using namespace std;

void displayMenu() {
    cout << "\n===== AUC campus Navigation System =====\n";
    cout << "1. Find Shortest Path\n";
    cout << "2. Display Locations\n";
    cout << "3. Exit\n";
    cout << "================================\n";
    cout << "Enter your choice (1-3): ";
}

// Only show user-friendly locations
static const vector<string> userLocations = {
    "AUC Library",                                // 0
    "School of Sciences and Engineering",         // 1
    "Prince Alwaleed Bin Talal Hall",            // 2
    "Hatem and Janet Mostafa Core Center",        // 3
    "Graduate School of Education",               // 4
    "Administration Building",                    // 5
    "Research Centers Building",                  // 6
    "AUC Center for the Arts",                    // 7
    "Bassily Auditorium",                         // 8
    "Moataz Al Alfi Hall",                        // 9
    "Allam Amphitheater",                         //10
    "University Residences",                      //11
    "Campus Center",                              //12
    "Conference & Visitor Center",                //13
    "AUC Sports Center",                          //14
    "Paul and Charlotte Corddry Park",            //15
    "University Garden",                          //16
    "Bruce Ludwig Family Square",                 //17
    "Pepsi Entrance",                             //18
    "Bus Terminal"                                //19
};




void displayLocations() {
    cout << "\nAvailable Locations:\n";
    for (int i = 0; i < (int)userLocations.size(); ++i) {
        cout << i + 1 << ": " << userLocations[i] << endl;
    }
}

int getValidInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between "
                 << min << " and " << max << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

void findShortestPath(Graph& g) {
    displayLocations();
    cout << "\nChoose starting location (1-20): ";
    int srcLocation = getValidInput(1, 20);

    cout << "Choose destination location (1-20): ";
    int destLocation = getValidInput(1, 20);

    int srcNode = (srcLocation - 1);
    int destNode = (destLocation - 1);

    cout << "\nCalculating shortest path...\n";

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    g.dijkstra(srcNode, destNode);

    // End timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Algorithim runtime: " << duration.count() << " ms\n";
}


int main() {
    Graph g;
    cout << "Loading AUC Campus map...\n";
    g.createGraph("AUCcampus.txt");

    int choice;
    do {
        displayMenu();
        choice = getValidInput(1, 3);

        switch (choice) {
            case 1:
                findShortestPath(g);
                break;
            case 2:
                displayLocations();
                break;
            case 3:
                cout << "Exiting program. Goodbye!\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
