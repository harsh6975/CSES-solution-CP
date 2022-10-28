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

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
bool safe(int x, int y, int n, int m)
{
    return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(vvl &graph, vl &startTime, vl &endTime, int sc, int par, int &time)
{
    startTime[sc] = time++;
    for (auto child : graph[sc])
    {
        if (child != par)
        {
            dfs(graph, startTime, endTime, child, sc, time);
        }
    }
    endTime[sc] = time++;
}

void BinaryLift(vvl &lift, vl &par)
{
    for (int i = 0; i < sz(par); i++)
    {
        lift[i][0] = par[i];
    }

    for (int j = 1; j < 20; j++)
    {
        for (int i = 0; i < sz(par); i++)
        {
            if (lift[i][j - 1] == -1)
            {
                lift[i][j] = -1;
            }
            else
            {
                lift[i][j] = lift[lift[i][j - 1]][j - 1];
            }
        }
    }
}

bool isAnc(vl &startTime, vl &endTime, int u, int v)
{
    return startTime[u] <= startTime[v] && endTime[v] <= endTime[u];
}

int LCA(vvl &lift, int u, int v, vl &startTime, vl &endTime)
{
    if (isAnc(startTime, endTime, u, v))
        return u;
    if (isAnc(startTime, endTime, v, u))
        return v;

    for (int i = 19; i >= 0 && v != -1; i--)
    {
        int x = lift[u][i];
        if (x!=-1 && !isAnc(startTime, endTime, x, v))
            u = x;
    }
    return lift[u][0];
}

int main()
{
    fast_cin();
    ll n, q;
    cin >> n >> q;

    vl par(n), startTime(n), endTime(n);
    vvl lift(n, vl(20)), graph(n);
    par[0] = -1;
    FOR0(i, n - 1)
    {
        cin >> par[i + 1];
        par[i + 1]--;
    }

    for (int i = 0; i < n; i++)
    {
        if (par[i] == -1)
            continue;
        graph[par[i]].push_back(i);
        graph[i].push_back(par[i]);
    }
    int time = 0;
    dfs(graph, startTime, endTime, 0, -1, time);

    BinaryLift(lift, par);

    while (q--)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        cout << LCA(lift, u, v, startTime, endTime)+1 << '\n';
    }

    return 0;
}
