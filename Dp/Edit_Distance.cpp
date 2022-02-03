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

int rec(string s, string s1, int i, int j, vvi &dp)
{
    if (i == s.size() && j == s1.size())
    {
        return 0;
    }
    if (i == s.size())
    {
        return s1.size() - j;
    }
    if (j == s1.size())
    {
        return s.size() - i;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    int ans = 0;
    if (s[i] == s1[j])
    {
        ans = rec(s, s1, i + 1, j + 1, dp);
    }
    else
    {
        ans = min({1 + rec(s, s1, i, j + 1, dp), 1 + rec(s, s1, i + 1, j, dp), 1 + rec(s, s1, i + 1, j + 1, dp)});
    }
    return dp[i][j] = ans;
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    string s, s1;
    cin >> s >> s1;
    // vvi dp(s.size() + 1, vi(s1.size() + 1, -1));
    // int ans = rec(s, s1, 0, 0, dp);
    // cout << ans;
    
    vvi dp(s.size() + 1, vi(s1.size() + 1, 0));
    FOR0(i, s.size()+1)
    {
        dp[i][0] = i;
    }
    FOR0(i, s1.size()+1)
    {
        dp[0][i] = i;
    }
    dp[0][0]=0;
    FORa(i, 1, s.size() + 1)
    {
        FORa(j, 1, s1.size() + 1)
        {
            if (s[i - 1] == s1[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min({1 + dp[i - 1][j], 1 + dp[i - 1][j - 1], 1 + dp[i][j - 1]});
            }
        }
    }
    cout << dp[s.size()][s1.size()];

    return 0;
}