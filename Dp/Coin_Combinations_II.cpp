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

ll rec(int arr[], int n, int k, int i, vector<vector<int>> &dp)
{
    if (k == 0)
    {
        return 1;
    }
    if (i == n)
    {
        return 0;
    }
    if (dp[i][k] != -1)
    {
        return dp[i][k];
    }
    ll ans = 0;
    if (arr[i] <= k)
    {
        ans = rec(arr, n, k - arr[i], i, dp) + rec(arr, n, k, i + 1, dp);
        ans %= 1000000007;
    }
    else
    {
        ans = rec(arr, n, k, i + 1, dp);
        ans %= 1000000007;
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
    sort(arr, arr + n);
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
    // ll ans=rec(arr,n,k,0,dp);
    // cout<<ans;

    FOR0(i, n + 1)
    {
        dp[i][0] = 1;
    }
    FOR0(i, k + 1)
    {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (j - arr[i - 1] >= 0)
            {
                dp[i][j] = dp[i][j - arr[i - 1]] + dp[i - 1][j];
                dp[i][j] %= 1000000007;
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
                dp[i][j] %= 1000000007;
            }
        }
    }
    cout << dp[n][k];

    //  vector<int> dp(k+1,0);
    //  dp[0]=1;

    return 0;
}
