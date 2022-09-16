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
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
ll MOD = 1000000007;
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

int rec(vi &arr, int n, int m, int i, vi &dp)
{
    if (i == n)
        return 1;
    int ans = 0;
    if (dp[i] != -1)
    {
        return dp[i];
    }
    if (arr[i] == 0)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i == 0)
            {
                arr[i] = j;
                ans += rec(arr, n, m, i + 1, dp);
                arr[i] = 0;
            }
            else
            {
                if (abs(arr[i - 1] - j) <= 1)
                {
                    arr[i] = j;
                    ans += rec(arr, n, m, i + 1, dp);
                    arr[i] = 0;
                }
            }
        }
    }
    else
    {
        if (i != 0 && abs(arr[i] - arr[i - 1] > 1))
        {
            return 0;
        }
        ans = rec(arr, n, m, i + 1, dp);
    }
    return dp[i] = ans;
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    int n, m;
    cin >> n >> m;
    vi arr(n);
    FOR0(i, n)
    {
        cin >> arr[i];
    }
    vi dp(n + 1, -1);
    int ans = rec(arr, n, m, 0, dp);
    cout << ans;
    return 0;
}
