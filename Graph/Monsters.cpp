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

bool safe(int x, int y, int n, int m)
{
    return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs(vvc &arr, vvl &dis, vector<vector<pair<pl, char>>> &par, char c)
{
    int n = arr.size(), m = arr[0].size();
    queue<pl> q;

    FOR0(i, n)
    {
        FOR0(j, m)
        {
            if (arr[i][j] == c)
            {
                q.push({i, j});
                dis[i][j] = 0;
            }
        }
    }
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    char dir[] = {'D', 'R', 'U', 'L'};
    while (!q.empty())
    {
        int sz = q.size();
        while (sz--)
        {
            auto curr = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int x = curr.first + dx[i];
                int y = curr.second + dy[i];
                if (safe(x, y, n, m) && arr[x][y] != '#' && dis[x][y] > dis[curr.first][curr.second] + 1)
                {
                    dis[x][y] = dis[curr.first][curr.second] + 1;
                    q.push({x, y});
                    if (c == 'A')
                    {
                        par[x][y] = {{curr.first, curr.second}, dir[i]};
                    }
                }
            }
        }
    }
}

pair<int, int> find(vvc &arr, vvl &disA, vvl &disM)
{
    int n = arr.size(), m = arr[0].size();
    int ex = -1, ey;
    int d = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i][0] != '#')
        {
            if (disA[i][0] < disM[i][0])
            {
                return {i, 0};
            }
        }
        if (arr[i][m - 1] != '#')
        {
            if (disA[i][m - 1] < disM[i][m - 1])
            {
                return {i, m - 1};
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        if (arr[0][i] != '#')
        {
            if (disA[0][i] < disM[0][i])
            {
                return {0, i};
            }
        }
        if (arr[n - 1][i] != '#')
        {
            if (disA[n - 1][i] < disM[n - 1][i])
            {
                return {n - 1, i};
            }
        }
    }
    return {-1, -1};
}

int main()
{
    // read the question correctly (ll vs int)
    fast_cin();
    ll n, m;
    cin >> n >> m;
    vvc arr(n, vc(m));
    vvl disA(n, vl(m, INT_MAX));
    vvl disM(n, vl(m, INT_MAX));
    vector<vector<pair<pl, char>>> par(n, vector<pair<pl, char>>(m));
    FOR0(i, n)
    {
        FOR0(j, m)
        {
            cin >> arr[i][j];
        }
    }

    bfs(arr, disA, par, 'A');
    bfs(arr, disM, par, 'M');   
   
    pair<int, int> e = find(arr, disA, disM);
    int x = e.first, y = e.second;
    if (e.first == -1)
    {
        cout << "NO";
        return 0;
    }

    cout << "YES" << '\n';
    cout << disA[e.first][e.second] << '\n';
    string ans = "";
    while (arr[x][y]!='A')
    {
        ans += par[x][y].second;
        int nx = par[x][y].first.first;
        int ny = par[x][y].first.second;
        x = nx;
        y = ny;
    }

    reverse(all(ans));
    cout << ans << '\n';

    return 0;
}