// #include <iostream>
// #include <vector>
// using namespace std;

// #define V 5

// // Check if current vertex can be added at path[pos]
// bool isSafe(int v, bool graph[V][V], int path[], int pos)
// {
//     // Check adjacency
//     if (graph[path[pos - 1]][v] == 0)
//         return false;

//     // Check if already in path
//     for (int i = 0; i < pos; i++)
//         if (path[i] == v)
//             return false;

//     return true;
// }

// // Recursive utility function to solve Hamiltonian cycle problem
// bool hamCycleUtil(bool graph[V][V], int path[], int pos)
// {
//     // Base case: all vertices included
//     if (pos == V)
//     {
//         // Check if last vertex is connected to first
//         return graph[path[pos - 1]][path[0]] == 1;
//     }

//     // Try each vertex as next candidate
//     for (int v = 1; v < V; v++)
//     {
//         if (isSafe(v, graph, path, pos))
//         {
//             path[pos] = v;

//             if (hamCycleUtil(graph, path, pos + 1))
//                 return true;

//             path[pos] = -1; // Backtrack
//         }
//     }

//     return false;
// }

// // Function to solve the Hamiltonian Cycle problem
// bool hamCycle(bool graph[V][V])
// {
//     int path[V];
//     for (int i = 0; i < V; i++)
//         path[i] = -1;

//     path[0] = 0; // Start at vertex 0

//     if (!hamCycleUtil(graph, path, 1))
//     {
//         cout << "No Hamiltonian cycle exists\n";
//         return false;
//     }

//     cout << "Hamiltonian Cycle: ";
//     for (int i = 0; i < V; i++)
//         cout << path[i] << " ";
//     cout << path[0] << endl; // Return to starting point

//     return true;
// }

// int main()
// {
//     bool graph[V][V] = {
//         {0, 1, 0, 1, 0},
//         {1, 0, 1, 1, 1},
//         {0, 1, 0, 0, 1},
//         {1, 1, 0, 0, 1},
//         {0, 1, 1, 1, 0}};

//     hamCycle(graph);
//     return 0;
// }


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void kahnTopoSort(int V, vector<vector<int>> &adj)
{
    vector<int> in_degree(V, 0);
    for (int u = 0; u < V; u++)
    {
        for (int v : adj[u])
        {
            in_degree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++)
    {
        if (in_degree[i] == 0)
            q.push(i);
    }

    vector<int> topo_order;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (int v : adj[u])
        {
            in_degree[v]--;
            if (in_degree[v] == 0)
                q.push(v);
        }
    }

    if (topo_order.size() != V)
    {
        cout << "Cycle detected! No topological ordering exists.\n";
        return;
    }

    cout << "Topological Sort (Kahn's): ";
    for (int node : topo_order)
        cout << node << " ";
    cout << endl;
}

void dfsTopoSortUtil(int u, vector<bool> &visited, vector<vector<int>> &adj, vector<int> &result)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v])
            dfsTopoSortUtil(v, visited, adj, result);
    }
    result.push_back(u); // Add to result on return
}

void dfsTopoSort(int V, vector<vector<int>> &adj)
{
    vector<bool> visited(V, false);
    vector<int> result;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            dfsTopoSortUtil(i, visited, adj, result);
    }

    reverse(result.begin(), result.end());

    cout << "Topological Sort (DFS): ";
    for (int node : result)
        cout << node << " ";
    cout << endl;
}
int main()
{
    int V = 6;
    vector<vector<int>> adj(V);

    vector<pair<int, int>> edges = {
        {2, 3}, {3, 1}, {4, 0}, {4, 1}, {5, 0}, {5, 2}};

    for (auto e : edges)
        adj[e.first].push_back(e.second);

    kahnTopoSort(V, adj);
    dfsTopoSort(V, adj);

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <stack>
// using namespace std;

// // Step 1: DFS to fill order
// void dfsFillOrder(int u, vector<bool> &visited, stack<int> &Stack, const vector<vector<int>> &adj)
// {
//     visited[u] = true;
//     for (int v : adj[u])
//     {
//         if (!visited[v])
//             dfsFillOrder(v, visited, Stack, adj);
//     }
//     Stack.push(u); // Save finish time
// }

// // Step 2: Transpose the graph
// vector<vector<int>> getTranspose(int V, const vector<vector<int>> &adj)
// {
//     vector<vector<int>> transpose(V);
//     for (int u = 0; u < V; u++)
//     {
//         for (int v : adj[u])
//         {
//             transpose[v].push_back(u);
//         }
//     }
//     return transpose;
// }

// // Step 3: DFS on transposed graph to find SCC
// void dfsSCC(int u, vector<bool> &visited, const vector<vector<int>> &adj)
// {
//     visited[u] = true;
//     cout << u << " ";
//     for (int v : adj[u])
//     {
//         if (!visited[v])
//             dfsSCC(v, visited, adj);
//     }
// }

// // Kosaraju’s Main Function
// void kosarajuSCC(int V, const vector<vector<int>> &adj)
// {
//     stack<int> Stack;
//     vector<bool> visited(V, false);

//     // Step 1: Fill vertices in stack according to finishing time
//     for (int i = 0; i < V; i++)
//     {
//         if (!visited[i])
//             dfsFillOrder(i, visited, Stack, adj);
//     }

//     // Step 2: Get the transposed graph
//     vector<vector<int>> transpose = getTranspose(V, adj);

//     // Step 3: Do DFS in the order defined by the stack
//     fill(visited.begin(), visited.end(), false);

//     int sccCount = 0;
//     cout << "\nStrongly Connected Components are:\n";
//     while (!Stack.empty())
//     {
//         int v = Stack.top();
//         Stack.pop();

//         if (!visited[v])
//         {
//             dfsSCC(v, visited, transpose);
//             cout << endl;
//             sccCount++;
//         }
//     }

//     cout << "\nTotal SCCs: " << sccCount << endl;
// }
// int main()
// {
//     int V = 5;
//     vector<vector<int>> adj(V);

//     // Example graph with 3 SCCs
//     adj[0] = {2, 3};
//     adj[1] = {0};
//     adj[2] = {1};
//     adj[3] = {4};
//     adj[4] = {};

//     kosarajuSCC(V, adj);

//     return 0;
// }
