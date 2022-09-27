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

bool safe(int &x, int &y, int &n, int &m)
{
    return x >= 0 && x < n && y >= 0 && y < m;
}

string bfs(vvc &arr, ll a, ll b)
{
    int n = arr.size(), m = arr[0].size();
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    char dir[] = {'D', 'R', 'U', 'L'};
    vector<vector<pair<pl, char>>> par(n, vector<pair<pl, char>>(m));
    vvl dis(n, vl(m, INT_MAX));
    queue<pl> q;
    q.push({a, b});
    dis[a][b] = 1;
    int sx=-1, sy;
    while (!q.empty())
    {
        int sz = q.size();
        bool ok = false;
        while (sz--)
        {
            auto curr = q.front();
            q.pop();
            if (arr[curr.first][curr.second] == 'B')
            {
                sx = curr.first;
                sy = curr.second;
                ok = true;
                break;
            }
            for (int i = 0; i < 4; i++)
            {
                int x = curr.first + dx[i];
                int y = curr.second + dy[i];
                if (safe(x, y, n, m) && dis[x][y] > dis[curr.first][curr.second] + 1 && arr[x][y] != '#')
                {
                    dis[x][y] = dis[curr.first][curr.second] + 1;
                    q.push({x, y});
                    par[x][y] = {{curr.first, curr.second}, dir[i]};
                }
            }
        }
        if(ok)break;
    }

    string ans = "";
    if (sx==-1)
        return ans;
    while(arr[sx][sy]!='A')
    {
        ans += par[sx][sy].second;
        int nsx = par[sx][sy].first.first;
        int nsy = par[sx][sy].first.second;
        sx=nsx;
        sy=nsy;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    // read the question correctly (ll vs int)
    ll n, m;
    cin >> n >> m;
    vvc arr(n, vc(m));
    int si=-1, sj;
    FOR0(i, n)
    {
        FOR0(j, m)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 'A')
            {
                si = i;
                sj = j;
            }
        }
    }
    if(si==-1){
        std::cout << "NO" << '\n';
        return 0;
    }
    string ans = bfs(arr, si, sj);
    if (ans.size() == 0)
    {
        std::cout << "NO" << '\n';
        return 0;
    }

    std::cout << "YES" << '\n';
    std::cout << ans.size() << '\n';
    std::cout << ans << '\n';
    return 0;
}
