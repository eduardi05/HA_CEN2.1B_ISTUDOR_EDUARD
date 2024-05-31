#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono> 

using namespace std;
using namespace std::chrono;

// Structure to represent a node in the search tree
struct Node {
    vector<int> path; // Path taken so far
    int cost; // Cost of the current path
    int level; // Level of the node in the search tree
};

// Function to calculate the distance between two points
int calculateDistance(pair<int, int> point1, pair<int, int> point2) {
    int dx = point1.first - point2.first;
    int dy = point1.second - point2.second;
    return round(sqrt(dx * dx + dy * dy));
}

// Function to get the distance from the distance matrix
int getDistance(const vector<vector<int>>& dist, int i, int j) {
    return dist[i][j];
}

// Breadth-First Search (BFS) algorithm to solve the Traveling Salesman Problem
int TSP_BFS(const vector<vector<int>>& dist, int n) {
    queue<Node> q;
    Node root;
    root.path.push_back(0); // Start from the first node
    root.cost = 0;
    root.level = 0;
    q.push(root);
    int min_cost = INT_MAX;

    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        // If all nodes are visited, check if this is the minimum cost
        if (node.level == n - 1) {
            node.path.push_back(0); // Return to the start node
            node.cost += getDistance(dist, node.path[node.level], 0);
            if (node.cost < min_cost) {
                min_cost = node.cost;
            }
            continue;
        }

        // Explore all unvisited nodes
        for (int i = 1; i < n; ++i) {
            if (find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                Node child = node;
                child.path.push_back(i);
                child.cost += getDistance(dist, node.path[node.level], i);
                child.level++;
                q.push(child);
            }
        }
    }
    return min_cost;
}

// Function to parse the TSP file and extract coordinates
vector<pair<int, int>> TSP_parseFile(const string& filename, int& n) {
    ifstream file(filename);
    string line;
    vector<pair<int, int>> coordinates;
    bool reading_nodes = false;

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(file, line)) {
        // Find the dimension of the problem
        if (line.find("DIMENSION") != string::npos) {
            istringstream iss(line);
            string token;
            while (iss >> token) {
                if (isdigit(token[0])) {
                    n = stoi(token);
                    break;
                }
            }
        }
        // Start reading node coordinates
        if (line.find("NODE_COORD_SECTION") != string::npos) {
            reading_nodes = true;
            continue;
        }
        // End of the file
        if (line.find("EOF") != string::npos) {
            break;
        }
        // Read node coordinates
        if (reading_nodes) {
            istringstream iss(line);
            int index, x, y;
            iss >> index >> x >> y;
            coordinates.emplace_back(x, y);
        }
    }

    file.close();
    return coordinates;
}

int main() {
    int n;
    string filename = "st70_9.tsp"; // File containing TSP problem data
    vector<pair<int, int>> distances = TSP_parseFile(filename, n);

    // Compute the distance matrix
    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = calculateDistance(distances[i], distances[j]);
        }
    }

    // Measure the time taken by the TSP_BFS algorithm
    auto start = high_resolution_clock::now();
    int min_cost = TSP_BFS(dist, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // Output the results
    cout << "Minimum cost using BFS: " << min_cost << endl;
    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}
