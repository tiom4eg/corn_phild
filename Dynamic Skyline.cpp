#include <bits/stdc++.h>
// tiom4eg's precompiler options
// POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS
// IO settings
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0)
// Quick types
#define ll long long
#define ld long double
//#define ull unsigned long long
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
#pragma GCC target("avx,avx2,tune=native")
#pragma GCC comment(linker, "/stack:200000000")
#endif
// PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define pbds tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>
using namespace __gnu_pbds;
// POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS POGGERS
using namespace std;
mt19937 rng(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
//#define int long long
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 400007, LG = 19, R = 1 << LG, MOD = 1000000007, MOD2 = 1e9 + 9, B = 256;
const ll INFLL = 1e18 + 7;

// Problem link: https://codeforces.com/group/n9yVVJUjBU/contest/434487/problem/H
// Solution: li-chao with rollbacks using deletions in T(n) log n trick

// 50000**4 + 1e18 < 7.3e18 so if we put (25000; 7.3e18) as default, it wouldn't overflow ll and it will actually be > than worst possible func everywhere
struct line {
    ll a, b; // (x - a)^4 + b
    line() : a(25000), b(7300000000000000000LL) {} //
    line(ll x, ll y): a(x), b(y) {}
    ll operator()(ll x) {
        ll s = (x - a) * (x - a);
        return s * s + b;
    }
};

struct rollback_lichao {
    vector <line> t;
    stack <vector <pair <int, line>>> st;
    vector <pair <int, line>> upd;
    int R;

    void add(line x, int v, int l, int r) {
        int m = (l + r) / 2;
        bool dl = x(l) < t[v](l), dm = x(m) < t[v](m);
        if (dm) {
            upd.pb({v, t[v]});
            swap(x, t[v]);
        }
        if (l + 1 == r) return;
        if (dl == dm) add(x, 2 * v + 1, m, r);
        else add(x, 2 * v, l, m);
    }
    void add(line x) {
        upd.clear();
        add(x, 1, 0, R);
        st.push(upd);
    }

    ll get(int p) {
        int v = 1, l = 0, r = R;
        ll s = t[v](p);
        while (l < r - 1) {
            int m = (l + r) / 2;
            if (p < m) {
                v = 2 * v, r = m;
                s = min(s, t[v](p));
            }
            else {
                v = 2 * v + 1, l = m;
                s = min(s, t[v](p));
            }
        }
        return s;
    }

    void undo() {
        if (st.empty()) return;
        upd = st.top();
        st.pop();
        EACH(u, upd) t[u.F] = u.S;
    }

    rollback_lichao() {}
    rollback_lichao(int n) : R(1) {
        while (R < n) R <<= 1;
        t.resize(2 * R);
    }
};

struct query_tree {
    vector <vector <line>> t;
    vi qs;
    rollback_lichao ds;
    int R;

    void add_upd(int ql, int qr, line& x, int v, int nl, int nr) {
        if (ql == nl && qr == nr) {
            t[v].pb(x);
            return;
        }
        int nm = (nl + nr) / 2;
        if (qr <= nm) return add_upd(ql, qr, x, 2 * v, nl, nm);
        if (ql >= nm) return add_upd(ql, qr, x, 2 * v + 1, nm, nr);
        add_upd(ql, nm, x, 2 * v, nl, nm), add_upd(nm, qr, x, 2 * v + 1, nm, nr);
    }
    void add_upd(int l, int r, line& x) { add_upd(l, r, x, 1, 0, R); }

    void add_get(int p, int x) { qs[p] = x; }

    void dfs(int v, int nl, int nr, vector <ll>& ans) {
        EACH(x, t[v]) ds.add(x);
        if (nl + 1 == nr) {
            if (qs[nl]) {
                ll s = ds.get(qs[nl]);
                ans.pb(s >= 7300000000000000000LL ? -1 : s);
            }
        }
        else {
            int nm = (nl + nr) / 2;
            dfs(2 * v, nl, nm, ans), dfs(2 * v + 1, nm, nr, ans);
        }
        FOR(i, 0, sz(t[v])) ds.undo();
    }

    vector <ll> solve() {
        vector <ll> ans;
        dfs(1, 0, R, ans);
        return ans;
    }

    query_tree() {}
    query_tree(int n, int q) : R(1) {
        while (R < q) R <<= 1;
        t.resize(2 * R), qs.resize(R);
        ds = rollback_lichao(n);
    }
};


void solve() {
    int n, q; cin >> n >> q;
    query_tree qt(50001, q + 1);
    vector <pair <int, line>> ls;
    FOR(i, 0, n) {
        ll a, b; cin >> a >> b;
        ls.pb({0, line(a, b)});
    }
    FOR(i, 1, q + 1) {
        int op; cin >> op;
        if (op == 1) {
            ll a, b; cin >> a >> b;
            ls.pb({i, line(a, b)});
        }
        else if (op == 2) {
            int p; cin >> p, --p;
            qt.add_upd(ls[p].F, i, ls[p].S);
            ls[p].F = -1;
        }
        else {
            int x; cin >> x;
            qt.add_get(i, x);
        }
    }
    EACH(p, ls) if (p.F >= 0) qt.add_upd(p.F, q + 1, p.S);
    vector <ll> ans = qt.solve();
    EACH(e, ans) cout << e << endl;
}

signed main() {
    fastIO;
    int tc = 1; cin >> tc;
    while (tc--) solve();
}
