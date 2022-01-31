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

int search(int a[], int n, int x)
{
    int l = 0, r = n - 1;
    int i = -1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (a[mid] == x)
        {
            i = mid;
            break;
        }
        else if (a[mid] > x)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    int ans;
    if (i == -1)
    {
        if (a[r] <= x)
        {
            ans = a[r];
            a[i] = INT_MAX;
        }
    }
    else
    {
        ans = a[i];
        a[i] = INT_MAX;
    }

    return ans;
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    ll n, m;
    cin >> n >> m;
    map<int, int> mp;
    ll b[m];
    FOR0(i, n)
    {
        int x;
        cin >> x;
        mp[x]++;
    }
    FOR0(i, m)
    {
        cin >> b[i];
    }
    FOR0(i, m)
    {
        if (mp.size() == 0)
        {
            cout << -1 << '\n';
            continue;
        }
        auto it = mp.lower_bound(b[i]);
        if (it == mp.end())
        {
            it--;
        }

        int ans = (*it).first;
        if (ans > b[i])
        {
            if (it == mp.begin())
            {
                ans = -1;
                cout << ans << '\n';
                continue;
            }
            else
            {
                it--;
                ans = (*it).first;
            }
        }
        cout << ans << '\n';
        if ((*it).second - 1 == 0)
        {
            mp.erase((*it).first);
        }
        else
        {
            mp[(*it).first]--;
        }
    }
    return 0;
}