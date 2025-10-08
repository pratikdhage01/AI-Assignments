#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// Map of regions and their neighbors
unordered_map<string, vector<string>> adj = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q",  {"NT", "SA", "NSW"}},
    {"NSW",{"Q", "SA", "V"}},
    {"V",  {"SA", "NSW"}},
    {"T",  {}} // Tasmania has no neighbors
};

// Available colors
vector<string> colors = {"Red", "Green", "Blue"};

// Function to check if it's safe to assign a color to a region
bool isSafe(string region, string color, unordered_map<string,string>& assignment) {
    // Iterate through neighbors using traditional for loop
    for (int i = 0; i < adj[region].size(); i++) {
        string neighbor = adj[region][i];
        if (assignment[neighbor] == color) {
            return false; // Neighbor has the same color
        }
    }
    return true;
}

// Backtracking function to solve coloring
bool solve(vector<string>& regions, int idx, unordered_map<string,string>& assignment) {
    if (idx == regions.size()) 
        return true; // All regions colored

    string region = regions[idx];

    // Try all colors
    for (int i = 0; i < colors.size(); i++) {
        string color = colors[i];

        if (isSafe(region, color, assignment)) {
            assignment[region] = color; // Assign color

            // Recurse for the next region
            if (solve(regions, idx + 1, assignment)) 
                return true;

            // Backtrack
            assignment[region] = "";
        }
    }

    return false; // No valid color found
}

int main() {
    // Define regions
    vector<string> regions = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};
    unordered_map<string,string> assignment;

    // Initialize all regions with empty color
    for (int i = 0; i < regions.size(); i++) {
        assignment[regions[i]] = "";
    }

    // Solve map coloring
    if (solve(regions, 0, assignment)) {
        cout << "Map Coloring Solution:\n";

        // Print solution using traditional loop
        for (int i = 0; i < regions.size(); i++) {
            string region = regions[i];
            cout << region << " -> " << assignment[region] << "\n";
        }
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
