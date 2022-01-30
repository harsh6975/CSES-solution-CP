#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <cstring>
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
    string s;
    cin >> s;
    int arr[26];
    memset(arr, 0, sizeof(arr));
    FOR0(i, s.size())
    {
        arr[s[i] - 'A']++;
    }
    int i = 0, j = s.size() - 1;
    string ans = s;
    int odd = 0;
    FOR0(k, 26)
    {
        if (arr[k] % 2 != 0)
        {
            odd++;
            continue;
        }
        while (arr[k] > 0)
        {
            ans[i] = k + 'A';
            arr[k]--;
            i++;
            ans[j] = k + 'A';
            arr[k]--;
            j--;
        }
    }
    if (odd > 1)
    {
        cout << "NO SOLUTION";
        return 0;
    }
    FOR0(k, 26)
    {
        while (arr[k] > 0)
        {
            ans[i] = k + 'A';
            arr[k]--;
            i++;
            if (arr[k])
            {
                ans[j] = k + 'A';
                arr[k]--;
                j--;
            }
        }
    }

    cout << ans;

    return 0;
}