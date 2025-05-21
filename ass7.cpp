#include <iostream>
#include <vector>
using namespace std;

vector<int> bruteForceSearch(string txt, string pat)
{
    int N = txt.length(), M = pat.length();
    vector<int> result;

    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
        {
            if (txt[i + j] != pat[j])
                break;
        }
        if (j == M)
            result.push_back(i + 1); // one-based index
    }
    return result;
}
vector<int> rabinKarp(string txt, string pat, int q = 101)
{
    int d = 256; // Number of characters in ASCII
    int N = txt.length(), M = pat.length();
    int p = 0, t = 0, h = 1;
    vector<int> result;

    for (int i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (int i = 0; i <= N - M; i++)
    {
        if (p == t)
        {
            int j;
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M)
                result.push_back(i + 1);
        }
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t += q;
        }
    }
    return result;
}
vector<int> computeLPS(string pat)
{
    int M = pat.length();
    vector<int> lps(M, 0);
    int len = 0, i = 1;

    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
    return lps;
}

vector<int> KMPSearch(string txt, string pat)
{
    int N = txt.length(), M = pat.length();
    vector<int> lps = computeLPS(pat);
    vector<int> result;

    int i = 0, j = 0;
    while (i < N)
    {
        if (txt[i] == pat[j])
        {
            i++;
            j++;
        }

        if (j == M)
        {
            result.push_back(i - j + 1); // one-based index
            j = lps[j - 1];
        }
        else if (i < N && txt[i] != pat[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return result;
}
int main()
{
    string txt = "AABAACAADAABAABA";
    string pat = "AABA";

    vector<int> res1 = bruteForceSearch(txt, pat);
    vector<int> res2 = rabinKarp(txt, pat);
    vector<int> res3 = KMPSearch(txt, pat);

    cout << "Brute Force:\n";
    for (int idx : res1)
        cout << "Pattern found at index " << idx << endl;

    cout << "\nRabin-Karp:\n";
    for (int idx : res2)
        cout << "Pattern found at index " << idx << endl;

    cout << "\nKMP:\n";
    for (int idx : res3)
        cout << "Pattern found at index " << idx << endl;

    return 0;
}
