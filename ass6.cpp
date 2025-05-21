#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

#define V 6 // Total number of vertices (0 to 5)

// 1. Find if there is an augmenting path using BFS
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, false, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++)
        {
            // If residual capacity exists and v is not visited
            if (!visited[v] && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // Return true if there is a path from source to sink
    return visited[t];
}

// 2. Main Ford-Fulkerson Algorithm
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;

    // Create residual graph and initialize it as original graph
    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];    // Array to store the augmenting path
    int max_flow = 0; // No flow initially

    // 3. Augment the flow while there is a path from s to t
    while (bfs(rGraph, s, t, parent))
    {
        int path_flow = INT_MAX;

        // Find minimum residual capacity in the path
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // 4. Update residual capacities and reverse edges
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow; // Add reverse edge
        }

        // 5. Add path flow to overall flow
        max_flow += path_flow;
    }

    return max_flow;
}

// 6. Driver code to use the algorithm with your graph
int main()
{
    // Graph from your example (Adjacency Matrix)
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}};

    int source = 0, sink = 5;

    cout << "The maximum possible flow is: " << fordFulkerson(graph, source, sink) << endl;
    return 0;
}
