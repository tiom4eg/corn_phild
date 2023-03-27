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
https://codeforces.com/group/n9yVVJUjBU/contest/432816/problem/D
https://codeforces.com/group/n9yVVJUjBU/contest/432816/problem/E
https://codeforces.com/group/n9yVVJUjBU/contest/432816/problem/K
Set of most needed geometry primitives
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
ld sq(ld x) { return x * x; }

struct point {
    ld x, y;
    point() : x(), y() {}
    point(ld x_, ld y_) : x(x_), y(y_) {}
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
    ld len2() const { return sq(x) + sq(y); }
    ld len() const { return sqrt(len2()); }
    point norm() const {
        ld d = len();
        assert(sign(d));
        return point(x / d, y / d);
    }
    point ort() const { return point(-y, x); }
    void print() { cout << '(' << x << ',' << y << ')'; }
};

ld angle(const point& a, const point& b) { return atan2(a % b, a * b); }
ld area(const vector <point>& p) {
    int n = sz(p);
    ld s = 0;
    FOR(i, 0, n) s += p[i] % p[i == n - 1 ? 0 : i + 1];
    return abs(s) / 2;
}

struct line {
    ld a, b, c;
    line() : a(EPS), b(EPS), c(0) {}
    line(const point& x, const point& y) : a(y.y - x.y), b(x.x - y.x), c(y % x) {
        if (!sign(a)) a = EPS;
        if (!sign(b)) b = EPS;
        ld d = point(a, b).len();
        a /= d, b /= d, c /= d;
        if (sign(a) == -1) a = -a, b = -b, c = -c;
        else if (!sign(a) && sign(b) == -1) a = 0, b = -b, c = -c;
    }
    bool operator==(const line& oth) const { return !sign(a - oth.a) && !sign(b - oth.b) && !sign(c - oth.c); }
    point ort() const { return point(a, b); }
    ld get_x(const ld& y) const { return (-c - b * y) / a; }
    ld get_y(const ld& x) const { return (-c - a * x) / b; }
    void print() { cout << a << " * x + " << b << " * y + " << c << " = 0"; }
};

bool cross(const line& a, const line& b, point& res) {
    ld d = a.b * b.a - a.a * b.b;
    if (!sign(d)) return false;
    res = point((b.b * a.c - b.c * a.b) / d, (b.c * a.a - b.a * a.c) / d);
    return true;
}
ld dist(const point& a, const line& l) { return abs(l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b)); }
bool on_line(const point& a, const line& l) { return !sign(l.a * a.x + l.b * a.y + l.c); }
bool inside_convex(const point& a, const vector <point>& p) {
    int n = sz(p);
    ld s = 0;
    FOR(i, 0, n) s += (p[i] - a) % (p[i == n - 1 ? 0 : i + 1] - a);
    s = abs(s);
    FOR(i, 0, n) s -= abs((p[i] - a) % (p[i == n - 1 ? 0 : i + 1] - a));
    return !sign(s);
}
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
    stable_sort(p.begin() + 1, p.end(), cmp);
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

ld diameter(vector <point>& p) {
    int n = sz(p), c = 0;
    ld res = 0;
    FOR(i, 0, n) {
        while (dist(p[i], line(p[c % n], p[(c + 1) % n])) < dist(p[i], line(p[(c + 1) % n], p[(c + 2) % n]))) ++c;
        res = max({res, (p[c % n] - p[i]).len(), (p[(c + 1) % n] - p[i]).len()});
    }
    return res;
}

struct circle {
    point p;
    ld r;
    circle() {}
    circle(point p_, ld r_): p(p_), r(r_) {}
    circle(ld x, ld y, ld r_): p(point(x, y)), r(r_) {}
    circle(point a, point b, point c) {
        b = (a + b) * 0.5;
        c = (a + c) * 0.5;
        cross(line(b, b + (a - b).ort()), line(c, c + (a - c).ort()), p);
        r = (p - a).len();
    }
    bool operator==(const circle& oth) const { return (p == oth.p) && !sign(r - oth.r); }
    ld area() { return PI * r * r; }
    ld circumference() { return 2.0 * PI * r; }
};

circle minimum_enclosing_circle(vector <point>& p) {
    shuffle(all(p), rng);
    int n = sz(p);
    circle c(p[0], 0);
    FOR(i, 1, n) {
        if (sign((c.p - p[i]).len() - c.r) > 0) {
            c = circle(p[i], 0);
            FOR(j, 0, i) {
                if (sign((c.p - p[j]).len() - c.r) > 0) {
                    c = circle((p[i] + p[j]) * 0.5, (p[i] - p[j]).len() * 0.5);
                    FOR(k, 0, j) {
                        if (sign((c.p - p[k]).len() - c.r) > 0) {
                            c = circle(p[i], p[j], p[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}

int extreme_vertex(vector <point>& p, const point& z, const int top) {
    int n = sz(p), id = 0;
    if (n == 1) return 0;
    ld ans = p[0] * z;
    if (p[top] * z > ans) ans = p[top] * z, id = top;
    int l = 1, r = top - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (p[m + 1] * z >= p[m] * z) l = m + 1;
        else r = m;
    }
    if (p[l] * z > ans) ans = p[l] * z, id = l;
    l = top + 1, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (p[(m + 1) % n] * z >= p[m] * z) l = m + 1;
        else r = m;
    }
    l %= n;
    if (p[l] * z > ans) ans = p[l] * z, id = l;
    return id;
}

bool line_intersects_polygon(vector <point>& p, point a, point b, int top) {
	point orth = (b - a).ort();
	if (sign((b - a) % (p[0] - a)) == 1) orth = (a - b).ort();
	int id = extreme_vertex(p, orth, top);
	return ((p[id] - a) * orth >= 0);
}

signed main() {
    fastIO;
    cout << fixed << setprecision(12);
    int n, m; cin >> n >> m;
    vector <line> ls(n); EACH(e, ls) cin >> e.a >> e.b >> e.c;
    vector <point> f(m); EACH(e, f) cin >> e.x >> e.y;
    vector <point> h = convex_hull(f);
    int top = max_element(all(h)) - h.begin();
    vi ans;
    FOR(i, 0, n) {
        point p1, p2;
        if (!sign(ls[i].b)) p1 = point(ls[i].get_x(0), 0), p2 = point(ls[i].get_x(1), 1);
        else p1 = point(0, ls[i].get_y(0)), p2 = point(1, ls[i].get_y(1));
        if (line_intersects_polygon(h, p1, p2, top)) ans.pb(i);
    }
    cout << sz(ans) << endl;
    EACH(e, ans) cout << e + 1 << ' ';
}
