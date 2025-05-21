#include <iostream>
#include <vector>
#include <cmath> // ✅ required for abs()
using namespace std;

// bool isSafe(int row, int col, vector<int> &board, int n)
// {
//     for (int i = 0; i < row; i++)
//     {
//         int placedCol = board[i];
//         if (placedCol == col || abs(row - i) == abs(col - placedCol))
//             return false;
//     }
//     return true;
// }

// void solveNQueens(int row, int n, vector<int> &board, vector<vector<int>> &solutions)
// {
//     if (row == n)
//     {
//         solutions.push_back(board);
//         return;
//     }

//     for (int col = 0; col < n; col++)
//     {
//         if (isSafe(row, col, board, n))
//         {
//             board[row] = col;
//             solveNQueens(row + 1, n, board, solutions);
//         }
//     }
// }

// void nQueens(int n)
// {
//     vector<int> board(n);
//     vector<vector<int>> solutions;
//     solveNQueens(0, n, board, solutions);

//     if (solutions.empty())
//     {
//         cout << "No solutions found.\n";
//     }
//     else
//     {
//         cout << "N-Queens Solutions:\n";
//         for (auto &sol : solutions)
//         {
//             cout << "[ ";
//             for (int val : sol)
//                 cout << val + 1 << " "; // Output in 1-based indexing
//             cout << "]\n";
//         }
//     }
// }

// int main()
// {
//     int n;
//     cout << "Enter number of queens: ";
//     cin >> n;
//     nQueens(n);
//     return 0;
// }

// #include <iostream>
// #include<vector>
// using namespace std;

// const int N = 9;

// bool isValid(int grid[N][N], int row, int col, int num)
// {
//     for (int x = 0; x < N; x++)
//     {
//         if (grid[row][x] == num || grid[x][col] == num)
//             return false;
//         if (grid[3 * (row / 3) + x / 3][3 * (col / 3) + x % 3] == num)
//             return false;
//     }
//     return true;
// }

// bool solveSudoku(int grid[N][N])
// {
//     for (int row = 0; row < N; row++)
//     {
//         for (int col = 0; col < N; col++)
//         {
//             if (grid[row][col] == 0)
//             {
//                 for (int num = 1; num <= 9; num++)
//                 {
//                     if (isValid(grid, row, col, num))
//                     {
//                         grid[row][col] = num;
//                         if (solveSudoku(grid))
//                             return true;
//                         grid[row][col] = 0;
//                     }
//                 }
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// void printSudoku(int grid[N][N])
// {
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//             cout << grid[i][j] << " ";
//         cout << endl;
//     }
// }

// int main()
// {
//     int grid[N][N] = {
//         {5, 3, 0, 0, 7, 0, 0, 0, 0},
//         {6, 0, 0, 1, 9, 5, 0, 0, 0},
//         {0, 9, 8, 0, 0, 0, 0, 6, 0},

//         {8, 0, 0, 0, 6, 0, 0, 0, 3},
//         {4, 0, 0, 8, 0, 3, 0, 0, 1},
//         {7, 0, 0, 0, 2, 0, 0, 0, 6},

//         {0, 6, 0, 0, 0, 0, 2, 8, 0},
//         {0, 0, 0, 4, 1, 9, 0, 0, 5},
//         {0, 0, 0, 0, 8, 0, 0, 7, 9}};

//     if (solveSudoku(grid))
//         printSudoku(grid);
//     else
//         cout << "No solution exists" << endl;

//     return 0;
// }

#define V 4

bool isColorSafe(int v, int graph[V][V], vector<int> &color, int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}

bool graphColoringUtil(int graph[V][V], int m, vector<int> &color, int v)
{
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++)
    {
        if (isColorSafe(v, graph, color, c))
        {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;
            color[v] = 0; // backtrack
        }
    }

    return false;
}

void graphColoring(int graph[V][V], int m)
{
    vector<int> color(V, 0);
    if (graphColoringUtil(graph, m, color, 0))
    {
        cout << "Solution Exists: Assigned colors: ";
        for (int c : color)
            cout << c << " ";
        cout << endl;
    }
    else
    {
        cout << "Solution does not exist\n";
    }
}
