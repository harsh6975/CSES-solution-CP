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

class UnionFind
{
    vl par, rank;
    ll sz, mx;

public:
    UnionFind(int n)
    {
        mx = 1;
        sz = n;
        par.resize(n);
        rank.resize(n);
        FOR0(i, n)
        {
            par[i] = i;
            rank[i] = 1;
        }
    }
    ll find(ll n)
    {
        if (par[n] == n)
            return n;
        return par[n] = find(par[n]);
    }

    void merge(ll a, ll b)
    {
        ll p1 = find(a);
        ll p2 = find(b);

        if (p1 != p2)
            sz--;
        else
            return;

        if (rank[p1] < rank[p2])
        {
            par[p1] = p2;
            rank[p2] += rank[p1];
            mx = max(mx, rank[p2]);
        }
        else if (rank[p1] > rank[p2])
        {
            par[p2] = p1;
            rank[p1] += rank[p2];
            mx = max(mx, rank[p1]);
        }
        else
        {
            par[p1] = p2;
            rank[p2] += rank[p1];
            mx = max(mx, rank[p2]);
        }
    }

    int comp()
    {
        return sz;
    }

    int maxComp()
    {
        return mx;
    }
};

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    ll n, m;
    cin >> n >> m;
    UnionFind uf(n);
    vvl edge;
    FOR0(i, m)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        edge.push_back({c, a - 1, b - 1});
    }

    sort(all(edge));
    ll ans = 0;
    for (auto v : edge)
    {
        ll p1 = uf.find(v[1]);
        ll p2 = uf.find(v[2]);
        if (p1 != p2)
        {
            uf.merge(p1, p2);
            ans += v[0];
        }
    }
    ll p = uf.find(0);
    bool ok = true;
    FORa(i, 1, n)
    {
        ll x = uf.find(i);
        if (x != p)
        {
            ok = false;
        }
    }
    if (!ok)
    {
        cout << "IMPOSSIBLE";
    }
    else
    {
        cout << ans << '\n';
    }

    return 0;
}