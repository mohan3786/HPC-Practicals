#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];  // Adjacency list to represent the graph
bool visited[MAX];       // Array to keep track of visited nodes

// Recursive function to perform parallel DFS using OpenMP tasks
void parallel_dfs(int node) {
    visited[node] = true;    // Mark the current node as visited
    cout << node << " ";     // Print the current node

    // Start parallel region
    #pragma omp parallel
    {
        // Ensure only one thread creates the tasks initially
        #pragma omp single nowait
        {
            // Traverse all adjacent nodes
            for (int i = 0; i < graph[node].size(); i++) {
                int adj_node = graph[node][i];
                
                // If the adjacent node is not visited
                if (!visited[adj_node]) {
                    // Create a new task for each unvisited adjacent node
                    #pragma omp task firstprivate(adj_node)
                    {
                        parallel_dfs(adj_node); // Recursive call
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
        graph[v].push_back(u);  // Add edge from v to u (undirected graph)
    }

    // Parallel initialization of visited array
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Start the parallel DFS from the given start node
    parallel_dfs(start_node);

    return 0;
}
