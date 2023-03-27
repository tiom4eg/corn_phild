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
#pragma GCC optimize("O3,unroll-loops") // let the chaos begin!
#pragma GCC target("avx,avx2,tune=native")
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
const int INF = 1e9 + 7, MD = 998244353, MAX = 2007, R = 1 << 17, MOD = 1e9 + 7, MOD2 = MOD * MOD, LG = 15, B = 40;
const ll INFLL = 1e18 + 7;

/*
https://codeforces.com/group/n9yVVJUjBU/contest/431806/problem/G
Find any vertex cover in general graph with size <= k
*/

int n, m, k, cover[MAX];
vi g[MAX];

void brute(int v = 0, int r = k) {
	  if (v == n) {
		    for (int i = 0; r && i < n; ++i) if (!cover[i]) cover[i] = 1, --r;
		    cout << "Yes\n";
		    FOR(i, 0, n) if (cover[i]) cout << i + 1 << ' ';
		    exit(0);
    }
	  if (cover[v]) return brute(v + 1, r);
	  vi now;
	  EACH(u, g[v]) if (!cover[u]) now.pb(u), cover[u] = 1;
	  if (sz(now) <= r) brute(v + 1, r - sz(now));
	  EACH(u, now) cover[u] = 0;
	  if (r && sz(now) > 1) {
		    cover[v] = 1;
		    brute(v + 1, r - 1);
		    cover[v] = 0;
	  }
}

signed main() {
	fastIO;
	cin >> n >> m >> k;
    FOR(i, 0, m) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    brute();
    cout << "No";
}
