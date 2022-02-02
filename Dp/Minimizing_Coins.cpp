#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pl;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef vector<vector<pl>> vvpl;
typedef vector<pl> vpl;
typedef vector<pi> vpi;
#define FOR0(i, n) for (ll i = 0; i < n; i++)
#define FORa(i, a, b) for (ll i = a; i < b; i++)
#define rFOR0(i, s) for (ll i = s; i >= 0; i--)
#define rFORa(i, s, e) for (ll i = s; i >= e; i--)
#define n1 'n'
#define PB push_back
#define F first
#define S second
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define T        \
    int test;    \
    cin >> test; \
    while (test--)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int rec(int arr[], int n, int i, int k, vector<vector<int>> &dp)
{
    if (k == 0)
    {
        return 0;
    }
    if (i == n)
    {
        return INT_MAX - 1;
    }
    int ans = 0;
    if (dp[i][k] != -1)
    {
        return dp[i][k];
    }
    if (arr[i] <= k)
    {
        int ans2, ans3;
        if (dp[i][k - arr[i]] != -1)
        {
            ans2 = dp[i][k - arr[i]];
        }
        else
        {
            ans2 = rec(arr, n, i, k - arr[i], dp);
        }
        if (dp[i + 1][k] != -1)
        {
            ans3 = dp[i + 1][k];
        }
        else
        {
            ans3 = rec(arr, n, i + 1, k, dp);
        }
        ans = min({1 + ans2, ans3});
    }
    else
    {
        ans = rec(arr, n, i + 1, k, dp);
    }
    return dp[i][k] = ans;
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    int n, k;
    cin >> n >> k;
    int arr[n];
    FOR0(i, n)
    {
        cin >> arr[i];
    }
    // vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
    // int ans = rec(arr, n, 0, k, dp);
    // if (ans == INT_MAX - 1)
    // {
    //     ans = -1;
    // }
    // cout << ans;

    // vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX));
    // for (int i = 0; i <= n; i++)
    // {
    //     dp[i][0] = 0;
    // }
    // for (int i = 0; i <= k; i++)
    // {
    //     dp[0][i] = INT_MAX - 1;
    // }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= k; j++)
    //     {
    //         if (j - arr[i - 1] >= 0)
    //         {
    //             dp[i][j] = min(dp[i][j - arr[i - 1]] + 1, dp[i - 1][j]);
    //         }
    //         else
    //         {
    //             dp[i][j] = dp[i - 1][j];
    //         }
    //     }
    // }
    // cout<<(dp[n][k]==INT_MAX-1?-1:dp[n][k]);

    vector<int> dp(k + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i - arr[j] >= 0 && dp[i - arr[j]] != INT_MAX)
            {
                dp[i] = min(dp[i], dp[i - arr[j]] + 1);
            }
        }
    }

    cout << (dp[k] == INT_MAX ? -1 : dp[k]);

    return 0;
}