#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using pii = pair <int, int>;
using vi = vector <int>;
using pbds = tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>;
#define endl '\n'
#define F first
#define S second
#define all(a) a.begin(), a.end()
#define sz(a) (int)(a.size())
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FORS(i, a, b, c) for (int i = a; i < b; i += c)
#define RFOR(i, a, b) for (int i = a; i >= b; --i)
#define EACH(e, a) for (auto& e : a)
#ifdef ONLINE_JUDGE
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,tune=native")
#endif

mt19937 rng(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
constexpr int INF = 1e9 + 7, MD = 998244353, MAX = 200007, LG = 18, R = 1 << LG, MOD = 1000000007, B = 512;
const ll INFLL = 1e18 + 7;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
}
