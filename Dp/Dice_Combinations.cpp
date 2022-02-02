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

ll rec(int n, ll sum, vector<ll> &dp)
{
    if (sum == n)
    {
        return 1;
    }
    ll ans = 0;
    if (dp[sum] != -1)
    {
        return dp[sum] % 1000000007;
    }
    for (int i = 1; i <= 6; i++)
    {
        if (sum + i <= n)
        {
            ans += rec(n, sum + i, dp);
            ans %= 1000000007;
        }
    }
    return dp[sum] = ans % 1000000007;
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    int n;
    cin >> n;
    vector<ll> dp(n + 1, 0);
    //ll ans = rec(n, 0, dp);

    //cout << ans;
    dp[0]=1;
    FORa(i,1,n+1){
        FORa(j,1,7){
            if(i-j>=0){
                dp[i]+=dp[i-j];
                dp[i]%=1000000007;
            }
        }
    }
    cout<<dp[n];
    return 0;
}
