#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    string name;
    double g, h;
    Node* parent;

    Node(string name, double g = 0, double h = 0, Node* parent = nullptr)
        : name(name), g(g), h(h), parent(parent) {}

    double f() const { return g + h; }  // f = g + h
};

// Comparator for priority queue (min-heap based on f value)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f();
    }
};

/*
  Reconstructs the final path from goal back to start
  by following parent pointers.
 */
vector<string> reconstructPath(Node* node) {
    vector<string> path;
    while (node) {
        path.push_back(node->name);
        node = node->parent;
    }
    reverse(path.begin(), path.end());  // reverse to get Start → Goal
    return path;
}

/*
   - graph: adjacency list (node → [(neighbor, cost)])
   - heuristic: map of node → heuristic value
   - start: start node name
   - goal: goal node name

 Returns:
  - vector<string>: path from start to goal
 */
vector<string> aStar(
    unordered_map<string, vector<pair<string, int>>> &graph,
    unordered_map<string, int> &heuristic,
    string start, string goal
) {
    // Priority queue (min-heap by f = g+h)
    priority_queue<Node*, vector<Node*>, Compare> openSet;

    // All created nodes (used to avoid memory leaks & check g values)
    unordered_map<string, Node*> allNodes;

    // Stores the best g value found for each node
    unordered_map<string, double> gScore;

    // Start node
    Node* startNode = new Node(start, 0, heuristic[start]);
    openSet.push(startNode);
    allNodes[start] = startNode;
    gScore[start] = 0;

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        // Skip if this node is not the best version (outdated queue entry)
        if (current->g > gScore[current->name]) continue;

        // Goal test
        if (current->name == goal) {
            auto path = reconstructPath(current);
            for (auto& kv : allNodes) delete kv.second; // cleanup memory
            return path;
        }

        // Explore neighbors
        for (auto &neighbor : graph[current->name]) {
            string neighborName = neighbor.first;
            int weight = neighbor.second;

            double tentativeG = current->g + weight; // new g cost

            // If new path is better than any previous one
            if (!gScore.count(neighborName) || tentativeG < gScore[neighborName]) {
                gScore[neighborName] = tentativeG;

                Node* neighborNode = new Node(
                    neighborName,
                    tentativeG,
                    heuristic[neighborName],
                    current
                );

                openSet.push(neighborNode);
                allNodes[neighborName] = neighborNode;
            }
        }
    }

    // Cleanup in case no path is found
    for (auto& kv : allNodes) delete kv.second;
    return {};
}

int main() {
    // Graph edges with costs
    unordered_map<string, vector<pair<string, int>>> graph = {
        {"S", {{"A", 1}, {"B", 4}}},
        {"A", {{"B", 2}, {"C", 5}, {"D", 12}}},
        {"B", {{"C", 2}}},
        {"C", {{"D", 3}}},
        {"D", {}}
    };

    // Heuristic values (estimated distance to goal)
    unordered_map<string, int> heuristic = {
        {"S", 7}, {"A", 6}, {"B", 2}, {"C", 1}, {"D", 0}
    };

    string start = "S";
    string goal = "D";

    // Run A*
    vector<string> path = aStar(graph, heuristic, start, goal);

    // Output the result
    if (!path.empty()) {
        cout << "Optimal Path found: ";
        for (auto &node : path) cout << node << " ";
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
