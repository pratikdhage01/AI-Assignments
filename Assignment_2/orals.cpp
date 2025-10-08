#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class CountryGraph {
public:
    unordered_map<string, vector<string>> adjList;
    unordered_map<string, string> colors;
    unordered_map<string, vector<string>> domains;

    CountryGraph() {
        domains["NT"] = {"R", "G", "B"};
        domains["AU"] = {"R", "G", "B"};
        domains["IN"] = {"R", "G", "B"};
        domains["SA"] = {"R", "G", "B"};
        domains["CA"] = {"R", "G", "B"};
    }

    void addEdge(const string& country1, const string& country2) {
        adjList[country1].push_back(country2);
        adjList[country2].push_back(country1);
    }

    bool isValid(const string& country, const string& color) {
        for (const string& neighbor : adjList[country]) {
            if (colors.find(neighbor) != colors.end() && colors[neighbor] == color) {
                return false;
            }
        }
        return true;
    }

    bool solve(vector<string>& countries, int index) {
        if (index == countries.size()) {
            return true;
        }

        string country = countries[index];

        for (const string& color : domains[country]) {
            if (isValid(country, color)) {
                colors[country] = color;

                if (solve(countries, index + 1)) {
                    return true;
                }

                colors.erase(country);
            }
        }

        return false;
    }

    void printSolution() {
        for (const auto& kv : colors) {
            cout << kv.first << " -> " << kv.second << endl;
        }
    }
};

int main() {
    CountryGraph g;

    g.addEdge("NT", "AU");
    g.addEdge("NT", "IN");
    g.addEdge("AU", "IN");
    g.addEdge("IN", "SA");
    g.addEdge("SA", "CA");

    vector<string> countries = {"NT", "AU", "IN", "SA", "CA"};

    if (g.solve(countries, 0)) {
        cout << "Solution Found!";
        g.printSolution();
    } else {
        cout << "No solution exists.";
    }

    return 0;
}
