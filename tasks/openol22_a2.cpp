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
https://codeforces.com/group/n9yVVJUjBU/contest/432816/problem/I
Given a set of points and queries with parameter a.
For each query find diameter of the new version of set, where every x-coordinate is multiplied by a.

This problem requires usage of Minkowski sum, convex hull building and CHT for minimum.
*/

const ld EPS = 1e-9, PI = 3.1415926535897;

int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
int sign(ld x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}
int sq(int x) { return x * x; }
ld sq(ld x) { return x * x; }

struct point {
    int x, y;
    point() : x(), y() {}
    point(int x_, int y_) : x(x_), y(y_) {}
    point operator-(point oth) const { return point(x - oth.x, y - oth.y); }
    point operator+(point oth) const { return point(x + oth.x, y + oth.y); }
    point operator*(ld a) const { return point(x * a, y * a); }
    ld operator*(point oth) const { return x * oth.x + y * oth.y; }
    ld operator%(point oth) const { return x * oth.y - y * oth.x; }
    bool operator<(point oth) const {
        if (sign(x - oth.x)) return x < oth.x;
        if (sign(y - oth.y)) return y < oth.y;
        return false;
    }
    bool operator==(const point& oth) const { return !sign(x - oth.x) && !sign(y - oth.y);  }
    int len2() const { return sq(x) + sq(y); }
    ld len() const { return sqrt(len2()); }
    point norm() const {
        ld d = len();
        assert(sign(d));
        return point(x / d, y / d);
    }
    point ort() const { return point(-y, x); }
    void print() { cout << '(' << x << ',' << y << ')'; }
};

bool cmp(const point& a, const point& b) {
    int s = sign(a % b);
    if (s) return s == 1;
    return sign(b.len2() - a.len2()) == 1;
}
vector <point> convex_hull(vector <point> p) {
    if (p.empty()) return {};
    int pos = min_element(all(p)) - p.begin();
    swap(p[0], p[pos]);
    FOR(i, 1, sz(p)) p[i] = p[i] - p[0];
    stable_sort(1 + all(p), cmp);
    FOR(i, 1, sz(p)) p[i] = p[i] + p[0];
    vector <point> hull;
    for (auto& u : p) {
        while (sz(hull) > 1) {
            int last = sz(hull) - 1;
            point v1 = hull[last] - hull[last - 1], v2 = u - hull[last];
            if (sign(v1 % v2) == 1) break;
            hull.pop_back();
        }
        hull.pb(u);
    }
    return hull;
}

vector <point> minkowski(const vector <point>& f1, const vector <point>& f2) {
	int p1 = 0, p2 = 0;
	point now = f1[0] + f2[0];
	vector <point> ms = {now};
	while (p1 < sz(f1) || p2 < sz(f2)) {
		point sh;
		int nx1 = (p1 == sz(f1) - 1 ? 0 : p1 + 1), nx2 = (p2 == sz(f2) - 1 ? 0 : p2 + 1);
		if (p1 == sz(f1) || (p2 != sz(f2) && (f1[nx1] - f1[p1]) % (f2[nx2] - f2[p2]) < 0)) sh = f2[nx2] - f2[p2++];
		else sh = f1[nx1] - f1[p1++];
		ms.pb(now = now + sh);
	}
	return ms;
}

struct line {
    int k, b;
    line(int x = 0, int y = -INFLL) : k(x), b(y) {}
    bool operator<(const line& o) const { return (k == o.k) ? (b < o.b) : (k < o.k); }
    ld operator()(ld x) const { return k * x + b; }
    ld operator/(const line& o) const { return (ld)(b - o.b) / (o.k - k); }
};
struct CHT : vector <line> {
    void add(line x) {
        while (!empty() && x.k == back().k) x.b = max(x.b, back().b), pop_back();
        while (size() > 1 && x / at(size() - 2) < at(size() - 1) / at(size() - 2)) pop_back();
        pb(x);
    }
    ld get(ld x) const {
        int l = -1, r = size() - 1;
        while (l < r - 1) {
            int m = (l + r) / 2;
            ((at(m) / at(m + 1) < x) ? l : r) = m;
        }
        return at(r)(x);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector <point> f(n);
    EACH(e, f) cin >> e.x >> e.y;
    vector <point> h = convex_hull(f);
    vector <point> ih(sz(h));
    FOR(i, 0, sz(h)) ih[i] = h[i] * -1;
    rotate(h.begin(), min_element(all(h)), h.end());
    rotate(ih.begin(), min_element(all(ih)), ih.end());
    vector <point> ms = minkowski(h, ih);
    vector <line> ls;
    EACH(e, ms) ls.pb(line(e.x * e.x, e.y * e.y));
    sort(all(ls));
    CHT cht;
    EACH(e, ls) cht.add(e);
    while (q--) {
        ld a; cin >> a;
        cout << sqrt(cht.get(a * a)) << endl;
    }
}

signed main() {
    fastIO;
    cout << fixed << setprecision(9);
    int t, g; cin >> t >> g;
    while (t--) solve();
}
