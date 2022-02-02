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

int rec(int n, vector<int> &dp)
{
    if (n == 0)
    {
        return 0;
    }
    if (dp[n] != -1)
    {
        return dp[n];
    }
    vector<int> v;
    int x = n;
    while (x)
    {
        v.push_back(x % 10);
        x /= 10;
    }
    int ans = INT_MAX, ans1 = 0;
    for (int j = 0; j < v.size(); j++)
    {
        if (n >= v[j] && v[j] != 0)
        {
            ans1 = 1 + rec(n - v[j], dp);
            ans = min(ans, ans1);
        }
    }
    return dp[n] = ans;
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    int n;
    cin >> n;
    //  vector<int> dp(n + 1, -1);
    //  int ans = rec(n, dp);
    //  cout << ans;
    vector<int> dp(n + 1, INT_MAX);

    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        while (x)
        {
            int rem = x % 10;
            if (i - rem >= 0 && rem != 0)
            {
                dp[i] = min(1 + dp[i - x % 10], dp[i]);
            }
            x /= 10;
        }
    }

    cout << dp[n];

    return 0;
}
