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

const int MAX = 400005;

ll segTree[4 * MAX], euler[MAX], startIndex[MAX], endIndex[MAX];
vl value;
void EulerTour(vvl &graph, int sc, int par, int &index)
{
    startIndex[sc] = index;
    euler[index] = value[sc];
    index++;
    for (auto child : graph[sc])
    {
        if (child != par)
        {
            EulerTour(graph, child, sc, index);
        }
    }
    endIndex[sc] = index;
    euler[index] = -value[sc];
    index++;
}

void build(int root, int l, int r)
{
    if (l == r)
    {
        segTree[root] = euler[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * root, l, mid);
    build(2 * root + 1, mid + 1, r);
    segTree[root] = segTree[2 * root] + segTree[2 * root + 1];
}

void update(int root, int l, int r, int index, ll val)
{
    if (l == r)
    {
        segTree[root] = val;
        euler[index] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (index <= mid)
    {
        update(2 * root, l, mid, index, val);
    }
    else
    {
        update(2 * root + 1, mid + 1, r, index, val);
    }
    segTree[root] = segTree[2 * root] + segTree[2 * root + 1];
}

ll find(int root, int l, int r, int lq, int rq)
{
    if (lq <= l && r <= rq)
    {
        return segTree[root];
    }
    int mid = (l + r) / 2;
    if (mid < lq)
    {
        return find(2 * root + 1, mid + 1, r, lq, rq);
    }
    if (mid + 1 > rq)
    {
        return find(2 * root, l, mid, lq, rq);
    }

    return find(2 * root + 1, mid + 1, r, lq, rq) + find(2 * root, l, mid, lq, rq);
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    ll n, q;
    cin >> n >> q;
    vvl graph(n);
    value = vl(n);
    FOR0(i, n)
    {
        cin >> value[i];
    }

    FOR0(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
    int index = 0;
    EulerTour(graph, 0, -1, index);
    build(1, 0, 2 * n - 1);

    while (q--)
    {
        int x, a, b;
        cin >> x >> a;
        a--;
        if (x == 1)
        {
            cin >> b;
            update(1, 0, 2 * n - 1, startIndex[a], b);
            update(1, 0, 2 * n - 1, endIndex[a], -b);
        }
        else
        {
            cout << find(1, 0, 2 * n - 1, startIndex[0], startIndex[a]) << '\n';
        }
    }

    return 0;
}