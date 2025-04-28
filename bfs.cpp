#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];  // Adjacency list representation
bool visited[MAX];       // To keep track of visited nodes

// Function to perform parallel BFS using OpenMP
void parallel_bfs(int start_node) {
    queue<int> q; // Standard BFS queue

    visited[start_node] = true; // Mark start node as visited
    q.push(start_node);         // Enqueue start node

    while (!q.empty()) {
        int size = q.size(); // Number of nodes at current level

        // Process all nodes at the current BFS level in parallel
        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int curr_node;

            // Use critical section to safely access queue
            #pragma omp critical
            {
                if (!q.empty()) {
                    curr_node = q.front();
                    q.pop();
                }
            }

            cout << curr_node << " "; // Print the node

            // Visit all adjacent nodes
            for (int j = 0; j < graph[curr_node].size(); j++) {
                int adj_node = graph[curr_node][j];

                // Use atomic operation to prevent race condition
                if (!visited[adj_node]) {
                    bool expected = false;
                    // Only one thread should mark and enqueue
                    #pragma omp critical
                    {
                        if (!visited[adj_node]) {
                            visited[adj_node] = true;
                            q.push(adj_node);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n, m, start_node;
    cout << "Enter No of Nodes, Edges, and Start Node: ";
    cin >> n >> m >> start_node;

    cout << "Enter Pairs of Edges:\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);  // Add edge from u to v
        graph[v].push_back(u);  // Add edge from v to u (undirected)
    }

    // Parallel initialization of visited array
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Start the parallel BFS from the given start node
    parallel_bfs(start_node);

    return 0;
}

