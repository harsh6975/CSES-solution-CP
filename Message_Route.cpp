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
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pl;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef vector<vector<pl>> vvpl;
typedef vector<pl> vpl;
typedef vector<pi> vpi;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
typedef vector<vector<string>> vvs;
typedef vector<vector<char>> vvc;
ll MOD = 1000000007;
#define FOR0(i, n) for (ll i = 0; i < n; i++)
#define FORa(i, a, b) for (ll i = a; i < b; i++)
#define rFOR0(i, s) for (ll i = s; i >= 0; i--)
#define rFORa(i, s, e) for (ll i = s; i >= e; i--)
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
#define allr(x) (x).rbegin(), (x).rend()
#define sz(x) ((ll)(x).size())

ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

ll merge(ll x, ll y)
{
    return x + y;
}
void buildSegTree(vl &v, vl &segTree, ll root, ll l, ll r)
{
    if (l == r)
    {
        segTree[root] = v[l];
        return;
    }
    ll mid = (l + r) / 2;
    buildSegTree(v, segTree, 2 * root, l, mid);
    buildSegTree(v, segTree, 2 * root + 1, mid + 1, r);
    segTree[root] = merge(segTree[2 * root], segTree[2 * root + 1]);
}
void updateSegTree(vl &segTree, ll root, ll l, ll r, ll index, ll val)
{
    if (l == r)
    {
        segTree[root] = val;
        return;
    }
    ll mid = (l + r) / 2;
    if (index <= mid)
    {
        updateSegTree(segTree, 2 * root, l, mid, index, val);
    }
    else
    {
        updateSegTree(segTree, 2 * root + 1, mid + 1, r, index, val);
    }
    segTree[root] = merge(segTree[2 * root], segTree[2 * root + 1]);
}
int findQuery(vl &segTree, ll root, ll l, ll r, ll lq, ll rq)
{
    if (lq <= l && r <= rq)
    {
        return segTree[root];
    }
    ll mid = (l + r) / 2;
    if (mid < lq)
    {
        return findQuery(segTree, 2 * root + 1, mid + 1, r, lq, rq);
    }
    if (mid + 1 > rq)
    {
        return findQuery(segTree, 2 * root, l, mid, lq, rq);
    }
    auto left = findQuery(segTree, 2 * root, l, mid, lq, rq);
    auto right = findQuery(segTree, 2 * root + 1, mid + 1, r, lq, rq);
    return merge(left, right);
}
void RangeUpdateSegTree(vl &segTree, ll root, ll l, ll r, ll lq, ll rq, ll val)
{
    if (r < lq || l > rq)
        return;
    if (lq <= l && r <= rq)
    {
        segTree[root] += val;
        return;
    }
    ll mid = (l + r) / 2;
    RangeUpdateSegTree(segTree, 2 * root, l, mid, lq, rq, val);
    RangeUpdateSegTree(segTree, 2 * root + 1, mid + 1, r, lq, rq, val);
}
ll pointFindQuery(vl &segTree, ll root, ll l, ll r, ll index)
{
    if (l == r)
    {
        return segTree[root];
    }
    int mid = (l + r) / 2;
    if (index <= mid)
    {
        return segTree[root] + pointFindQuery(segTree, 2 * root, l, mid, index);
    }
    else
    {
        return segTree[root] + pointFindQuery(segTree, 2 * root + 1, mid + 1, r, index);
    }
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    ll n, m;
    cin >> n >> m;
    queue<ll> q;
    vvl graph(n);
    FOR0(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> dis(n, INT_MAX), par(n);
    dis[0] = 1;
    q.push(0);

    while (!q.empty())
    {
        bool ok = false;
        int sz = q.size();
        while (sz--)
        {
            auto curr = q.front();
            q.pop();
            if (curr == n - 1)
            {
                ok = true;
                break;
            }
            for (auto x : graph[curr])
            {
                if (dis[x] > dis[curr] + 1)
                {
                    q.push(x);
                    dis[x] = 1 + dis[curr];
                    par[x] = curr;
                }
            }
        }
        if (ok)
            break;
    }
    if (dis[n - 1] == INT_MAX)
    {
        cout << "IMPOSSIBLE" << '\n';
        return 0;
    }
    cout << dis[n - 1] << '\n';
    vector<ll> ans(dis[n - 1]);
    int y=n-1;
    FOR0(i, dis[n - 1])
    {
        ans[i]=y;
        y=par[y];
    }

    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i]+1<<" ";
    }
    return 0;
}