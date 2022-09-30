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

class Node
{
public:
    ll sc, cost, x;
    Node(ll a, ll b, ll c)
    {
        sc = a;
        cost = b;
        x = c;
    }
};

class mysort
{
public:
    bool operator()(Node &a, Node &b)
    {
        if (a.cost == b.cost)
        {
            return a.x > b.x;
        }
        return a.cost > b.cost;
    }
};

vl dijkstra(vvpl &graph)
{
    ll n = graph.size();
    priority_queue<pl, vpl, greater<pl>> q;
    vl dis(n, 1e16), vis(n), count(n), mi(n, 1e16), mx(n);
    q.push({0, 0});
    dis[0] = 0;
    count[0] = 1;
    mi[0] = 0;
    mx[0] = 0;
    ll mod = 1e9 + 7;
    while (!q.empty())
    {
        auto curr = q.top();
        q.pop();
        if (vis[curr.second])
            continue;
        vis[curr.second] = 1;
        for (auto x : graph[curr.second])
        {
            if (dis[x.first] > curr.first + x.second)
            {
                dis[x.first] = curr.first + x.second;
                count[x.first] = count[curr.second];
                mx[x.first] = mx[curr.second] + 1;
                mi[x.first] = mi[curr.second] + 1;
                q.push({dis[x.first], x.first});
            }
            else if (dis[x.first] == curr.first + x.second)
            {
                count[x.first] = (count[x.first] + count[curr.second]) % mod;
                mx[x.first] = max(mx[curr.second] + 1, mx[x.first]);
                mi[x.first] = min(mi[curr.second] + 1, mi[x.first]);
            }
        }
    }
    return {dis[n - 1], count[n - 1], mi[n - 1], mx[n - 1]};
}

int main()
{
    // read the question correctly (ll vs int)
    ll n, m;
    cin >> n >> m;
    vvpl graph(n);
    FOR0(i, m)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        graph[a].push_back({b, c});
    }

    auto ans = dijkstra(graph);

    cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3];
    return 0;
}