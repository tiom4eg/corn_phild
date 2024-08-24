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
#define int long long
const int INF = 1e9 + 7, MD = 998244353, MAX = 200007, R = 1 << 19, MOD = 1040015701, MOD2 = 1e9 + 9, LG = 20, B = 40;
const ll INFLL = 1e18 + 7;

/*
https://codeforces.com/group/n9yVVJUjBU/contest/430845/problem/N
Every vertex in tree has color 0 or 1, there are queries of two types:
1) Change color of vertex v
2) Find sum of distances between every pair of vertices with color c
*/

int used[MAX], cent_par[MAX], sub[MAX], depth[MAX], dist[LG][MAX], color[MAX], cnt[2][MAX], sum[2][MAX], only[2][MAX];
vi g[MAX];

int find_centroid(int v, int p, int s) {
    EACH(u, g[v]) if (!used[u] && u != p && sub[u] > s / 2) return find_centroid(u, v, s);
    return v;
}

int calc_size(int v, int p) {
    sub[v] = 1;
    EACH(u, g[v]) if (!used[u] && u != p) sub[v] += calc_size(u, v);
    return sub[v];
}

void calc_centroid(int v, int p, int l, int c, int cc) {
    dist[depth[c]][v] = l, sum[0][c] += l, only[0][cc] += l;
    EACH(u, g[v]) if (!used[u] && u != p) calc_centroid(u, v, l + 1, c, cc);
}

void build_centroid(int v, int p, int l) {
    int s = calc_size(v, -1), c = find_centroid(v, -1, s);
    used[c] = 1, cent_par[c] = p, depth[c] = l;
    cnt[0][c] = s;
    EACH(u, g[c]) if (!used[u]) {
        int su = calc_size(u, -1), cu = find_centroid(u, -1, su);
        calc_centroid(u, c, 1, c, cu);
    }
    EACH(u, g[c]) if (!used[u]) build_centroid(u, c, l + 1);
}

void upd(int v) {
    --cnt[color[v]][v], ++cnt[!color[v]][v];
    for (int pr = v, c = cent_par[v]; c != -1; pr = c, c = cent_par[c]) {
        --cnt[color[v]][c], ++cnt[!color[v]][c];
        only[color[v]][pr] -= dist[depth[c]][v], only[!color[v]][pr] += dist[depth[c]][v];
        sum[color[v]][c] -= dist[depth[c]][v], sum[!color[v]][c] += dist[depth[c]][v];
    }
    color[v] = !color[v];
}

int get(int v) {
    int s = sum[color[v]][v];
    for (int pr = v, c = cent_par[v]; c != -1; pr = c, c = cent_par[c]) {
        s += (sum[color[v]][c] - only[color[v]][pr]) + dist[depth[c]][v] * (cnt[color[v]][c] - cnt[color[v]][pr]);
    }
    return s;
}

signed main() {
    fastIO;
    int n, q; cin >> n >> q;
    FOR(i, 1, n) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    build_centroid(0, -1, 0);
    while (q--) {
        int t, v; cin >> t >> v, --v;
        if (t == 1) upd(v);
        else cout << get(v) << endl;
    }
}
