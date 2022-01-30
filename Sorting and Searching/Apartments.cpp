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
;
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

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    ll n, m, k;
    cin >> n >> m >> k;
    ll a[n], b[m];

    FOR0(i, n)
    {
        cin >> a[i];
    }
    FOR0(i, m)
    {
        cin >> b[i];
    }
    ll i = 0, j = 0;
    sort(a, a + n);
    sort(b, b + m);
    ll ans = 0;
    while (i < n && j < m)
    {
        if (b[j] + k >= a[i] && b[j] - k <= a[i])
        {
            ans++;
            i++;
            j++;
        }
        else if (b[j] < a[i])
        {
            j++;
        }
        else
        {
            i++;
        }
    }
    cout << ans;
    return 0;
}