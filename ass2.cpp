#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second;
}

void activitySelection(vector<int> &start, vector<int> &finish)
{
    int n = start.size();
    vector<pair<int, int>> activities;
    for (int i = 0; i < n; i++)
        activities.push_back({start[i], finish[i]});

    sort(activities.begin(), activities.end(), compare);

    cout << "Selected activities:\n";
    int lastFinish = activities[0].second;
    cout << "(" << activities[0].first << ", " << activities[0].second << ")\n";

    for (int i = 1; i < n; i++)
    {
        if (activities[i].first >= lastFinish)
        {
            cout << "(" << activities[i].first << ", " << activities[i].second << ")\n";
            lastFinish = activities[i].second;
        }
    }
}

int main()
{
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> finish = {2, 4, 6, 7, 9, 9};
    activitySelection(start, finish);
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findPlatforms(vector<int> arr, vector<int> dep)
{
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int plat_needed = 1, result = 1;
    int i = 1, j = 0, n = arr.size();

    while (i < n && j < n)
    {
        if (arr[i] <= dep[j])
        {
            plat_needed++;
            i++;
        }
        else
        {
            plat_needed--;
            j++;
        }
        result = max(result, plat_needed);
    }
    return result;
}

int main()
{
    vector<int> arr = {900, 940, 950, 1100, 1500, 1800};
    vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};
    cout << "Minimum platforms needed: " << findPlatforms(arr, dep) << endl; // Output: 3
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job
{
    char id;
    int deadline;
    int profit;
};

bool compare(Job a, Job b)
{
    return a.profit > b.profit;
}

void jobScheduling(vector<Job> &jobs)
{
    sort(jobs.begin(), jobs.end(), compare);
    int n = jobs.size();
    vector<char> result(n, '-');
    vector<bool> slot(n, false);

    for (int i = 0; i < n; i++)
    {
        for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--)
        {
            if (!slot[j])
            {
                slot[j] = true;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    cout << "Scheduled Jobs: ";
    for (char job : result)
        if (job != '-')
            cout << job << " ";
    cout << endl;
}

int main()
{
    vector<Job> jobs = {{'a', 4, 20}, {'b', 1, 10}, {'c', 1, 40}, {'d', 1, 30}};
    jobScheduling(jobs); // Output: Scheduled Jobs: c a
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item
{
    int profit, weight;
};

bool compare(Item a, Item b)
{
    return (double)a.profit / a.weight > (double)b.profit / b.weight;
}

double fractionalKnapsack(int W, vector<Item> &items)
{
    sort(items.begin(), items.end(), compare);
    double totalValue = 0.0;

    for (auto &item : items)
    {
        if (W == 0)
            break;
        if (item.weight <= W)
        {
            totalValue += item.profit;
            W -= item.weight;
        }
        else
        {
            totalValue += (double)item.profit * W / item.weight;
            break;
        }
    }

    return totalValue;
}

int main()
{
    vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    int W = 50;
    cout << "Maximum profit: " << fractionalKnapsack(W, items) << endl; // Output: 240
    return 0;
}
