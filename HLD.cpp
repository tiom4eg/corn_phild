#include <bits/stdc++.h>
// tiom4eg's precompiler options
// POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS
// IO settings
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0)
// Quick types
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair <int, int>
#define vi vector <int>
#define mi vector <vector <int>>
// Quick functions
#define endl "\n"
#define F first
#define S second
#define all(a) a.begin(), a.end()
#define sz(a) (int)(a.size())
#define pb push_back
#define mp make_pair
// Quick fors
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FORS(i, a, b, c) for (int i = a; i < b; i += c)
#define RFOR(i, a, b) for (int i = a; i >= b; --i)
#define EACH(e, a) for (auto& e : a)
// Pragmas
#ifndef TIOM4EG
#pragma GCC optimize("O3") // let the chaos begin!
#pragma GCC target("avx,tune=native")
#pragma GCC comment(linker, "/stack:200000000")
#endif
// PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>
#define ook order_of_key
#define fbo find_by_order
using namespace __gnu_pbds;
// POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS
using namespace std;
mt19937 rng(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
//#define int long long
const int INF = 1e9 + 7, MD = 998244353, MAX = 100007, R = 1 << 17, MOD = 1040015701, MOD2 = 1e9 + 9, LG = 20, B = 40;
const ll INFLL = 1e18 + 7;

int T, tin[MAX], tout[MAX], sub[MAX], up[LG][MAX], head[MAX];
vi g[MAX];

/// HLD PRECALC
int calc_size(int v = 0, int p = 0) {
    sub[v] = 1;
    EACH(u, g[v]) if (u != p) sub[v] += calc_size(u, v);
    return sub[v];
}

void build_hld(int v = 0, int p = 0, int hd = 0) {
    if (v) g[v].erase(remove(all(g[v]), p), g[v].end());
    head[v] = hd, tin[v] = T++;
    up[0][v] = p;
    FOR(i, 1, LG) up[i][v] = up[i - 1][up[i - 1][v]];
    if (!g[v].empty()) {
        FOR(i, 1, sz(g[v])) if (sub[g[v][i]] > sub[g[v][0]]) swap(g[v][0], g[v][i]);
        build_hld(g[v][0], v, hd);
        FOR(i, 1, sz(g[v])) build_hld(g[v][i], v, g[v][i]);
    }
    tout[v] = T;
}
/// LCA
int upper(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }
int lca(int u, int v) {
    if (upper(u, v)) return u;
    if (upper(v, u)) return v;
    int w = v;
    RFOR(i, LG - 1, 0) if (!upper(up[i][w], u)) w = up[i][w];
    return up[0][w];
}
/// SEGTREE
int t[2 * R];

void upd(int p, int x) {
    t[p += R] = x;
    while (p >>= 1) t[p] = max(t[2 * p], t[2 * p + 1]);
}

int get(int l, int r) {
    l += R, r += R;
    int v = 0;
    while (l < r) {
        if (l & 1) v = max(v, t[l++]);
        if (!(r & 1)) v = max(v, t[r--]);
        l >>= 1, r >>= 1;
    }
    if (l == r) v = max(v, t[l]);
    return v;
}
/// QUERY MANAGEMENT
int get_vert(int u, int v) {
    int r = 0;
    while (head[u] != head[v]) r = max(r, get(tin[head[u]], tin[u])), u = up[0][head[u]];
    r = max(r, get(tin[v], tin[u]));
    return r;
}

int get_path(int u, int v) {
    int w = lca(u, v);
    return max(get_vert(u, w), get_vert(v, w));
}

signed main() {
    fastIO;
    int n; cin >> n;
    vi a(n); EACH(e, a) cin >> e;
    FOR(i, 1, n) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    calc_size(), build_hld();
    FOR(i, 0, n) upd(tin[i], a[i]);
    int q; cin >> q;
    while (q--) {
        char op; int l, r; cin >> op >> l >> r;
        if (op == '?') cout << get_path(l - 1, r - 1) << endl;
        else upd(tin[l - 1], r);
    }
}
