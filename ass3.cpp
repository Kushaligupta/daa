#include <iostream>
#include <vector>
#include <string>
using namespace std;

string lcs(string s1, string s2)
{
    int m = s1.length(), n = s2.length();
    vector<vector<string>> dp(m + 1, vector<string>(n + 1, ""));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
        {
            if (s1[i] == s2[j])
                dp[i + 1][j + 1] = dp[i][j] + s1[i];
            else
                dp[i + 1][j + 1] = (dp[i][j + 1].length() > dp[i + 1][j].length()) ? dp[i][j + 1] : dp[i + 1][j];
        }

    return dp[m][n];
}

int main()
{
    string s1 = "AGGTAB", s2 = "GXTXAYB";
    cout << "LCS: " << lcs(s1, s2) << endl; // Output: GTAB
    return 0;
}

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int matrixChainOrder(vector<int> &arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int l = 2; l < n; ++l)
    {
        for (int i = 1; i < n - l + 1; ++i)
        {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k)
            {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }
    return dp[1][n - 1];
}

int main()
{
    vector<int> arr = {2, 1, 3, 4};
    cout << "Minimum multiplications: " << matrixChainOrder(arr) << endl; // Output: 20
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

int knapsack(int W, vector<int> &wt, vector<int> &val, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i)
        for (int w = 0; w <= W; ++w)
            if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];

    return dp[n][W];
}

int main()
{
    int W = 7;
    vector<int> profit = {5, 3, 8, 6};
    vector<int> weight = {2, 3, 4, 5};
    int n = profit.size();
    cout << "Maximum Profit: " << knapsack(W, weight, profit, n) << endl; // Output: 13
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxSquare(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size(), maxSize = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i)
        dp[i][0] = mat[i][0];
    for (int j = 0; j < m; ++j)
        dp[0][j] = mat[0][j];

    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            if (mat[i][j] == 1)
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            maxSize = max(maxSize, dp[i][j]);

    return maxSize;
}

int main()
{
    vector<vector<int>> mat = {
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}};

    cout << "Maximum square size: " << maxSquare(mat) << endl; // Output: 3
    return 0;
}
