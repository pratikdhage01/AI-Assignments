#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Class to represent a family tree using a knowledge base
class FamilyTree {
private:
    // Knowledge base stores parent -> list of children
    unordered_map<string, vector<string>> knowledgeBase;

public:
    // Function to add a parent-child relationship
    void addRelation(const string& parent, const string& child) {
        knowledgeBase[parent].push_back(child); // Append child to parent's list
    }

    // Function to get all children of a given parent
    vector<string> getChildren(const string& parent) {
        // Check if parent exists in the knowledge base
        if (knowledgeBase.find(parent) != knowledgeBase.end()) {
            return knowledgeBase[parent]; // Return the list of children
        }
        return {}; // Return empty vector if parent not found
    }

    // Function to get the parent of a given child
    string getParent(const string& child) {
        // Iterate through the knowledge base
        for (const auto& pair : knowledgeBase) {
            for (const auto& c : pair.second) {
                if (c == child) {
                    return pair.first; // Return parent if child matches
                }
            }
        }
        return "Unknown"; // Return "Unknown" if parent not found
    }

    // Function to display the entire family tree
    void displayFamilyTree() {
        for (const auto& pair : knowledgeBase) {
            cout << pair.first << " -> "; // Print parent
            for (const auto& child : pair.second) {
                cout << child << " "; // Print all children
            }
            cout << endl;
        }
    }
};

int main() {
    FamilyTree familyTree; // Create a FamilyTree object

    // Adding relations to the knowledge base
    familyTree.addRelation("John", "Alice");    // John is parent of Alice
    familyTree.addRelation("John", "Bob");      // John is parent of Bob
    familyTree.addRelation("Alice", "Charlie"); // Alice is parent of Charlie
    familyTree.addRelation("Alice", "Diana");   // Alice is parent of Diana

    // Display the family tree
    cout << "Family Tree:" << endl;
    familyTree.displayFamilyTree();

    // Querying the knowledge base
    string parent = "Alice";
    cout << "\nChildren of " << parent << ": ";
    for (const auto& child : familyTree.getChildren(parent)) {
        cout << child << " "; // Print children of Alice
    }
    cout << endl;

    string child = "Charlie";
    cout << "Parent of " << child << ": " << familyTree.getParent(child) << endl;

    return 0;
}
