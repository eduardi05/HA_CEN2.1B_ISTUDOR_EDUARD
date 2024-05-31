#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Structure to represent a node in the search tree
struct Node {
    vector<int> path; // Path taken so far
    int cost; // Cost of the current path
    int level; // Level of the node in the search tree
};

// Comparator for the priority queue to prioritize nodes with lower cost
struct Compare {
    bool operator()(Node const& n1, Node const& n2) {
        return n1.cost > n2.cost;
    }
};

// Function to calculate the Euclidean distance between two points
int calculateDistance(pair<int, int> point1, pair<int, int> point2) {
    int dx = point1.first - point2.first;
    int dy = point1.second - point2.second;
    return round(sqrt(dx * dx + dy * dy));
}

// Uniform Cost Search (UCS) algorithm to solve the Traveling Salesman Problem
int TSP_UCS(const vector<vector<int>>& dist) {
    int n = dist.size();
    priority_queue<Node, vector<Node>, Compare> pq;
    Node root;
    root.path.push_back(0); // Start from the first node
    root.cost = 0;
    root.level = 0;
    pq.push(root);
    int min_cost = INT_MAX;

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        // If all nodes are visited, check if this is the minimum cost
        if (node.level == n - 1) {
            node.path.push_back(0); // Return to the start node
            node.cost += dist[node.path[node.level]][0];
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
                child.cost += dist[node.path[node.level]][i];
                child.level++;
                pq.push(child);
            }
        }
    }
    return min_cost;
}

int main() {
    int n = 5; // Number of nodes
    vector<pair<int, int>> distances = {
        {0, 1},
        {1, 0},
        {2, 0},
        {2, 1},
        {1, 2}
    };

    // Compute the distance matrix
    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = calculateDistance(distances[i], distances[j]);
        }
    }

    // Measure the time taken by the TSP_UCS algorithm
    auto start = high_resolution_clock::now();
    int min_cost = TSP_UCS(dist);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // Output the results
    cout << "Minimum cost using UCS: " << min_cost << endl;
    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}
