template <typename T>
void permute(vector <T>& a, vi p) {
    FOR(i, 0, sz(p)) {
        while (p[i] != i) {
            swap(a[i], a[p[i]]);
            swap(p[i], p[p[i]]);
        }
    }
}

template <typename T, typename U>
struct hld_forest {
    vector <vi> g;
    vi sub, tin, tout, head, par, dep;
    int tt;
    vector <T> val;
    segtree <T, U> t;

    void add_edge(int u, int v) { g[u].pb(v), g[v].pb(u); }

    void pre(int v, int p = -1) {
        sub[v] = 1, par[v] = p;
        EACH(u, g[v]) if (u != p) {
            dep[u] = dep[v] + 1;
            pre(u, v);
            sub[v] += sub[u];
        }
    }
    void hld(int v, int h, int p = -1) {
        tin[v] = tt++, head[v] = h;
        if (~p) g[v].erase(find(g[v].begin(), g[v].end(), p));
        if (!g[v].empty()) {
            swap(g[v][0], *max_element(g[v].begin(), g[v].end(), [&](int u, int v) { return sub[u] < sub[v]; }));
            hld(g[v][0], h, v);
            FOR(i, 1, sz(g[v])) hld(g[v][i], g[v][i], v);
        }
        tout[v] = tt;
    }
    void build(int v = 0) {
        tt = 0;
        dep[v] = 0;
        pre(v);
        hld(v, v);
        permute(val, tin);
        t = segtree <T, U>(val);
    }

    bool upper(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }
    int lca(int u, int v) {
        for (; head[u] != head[v]; u = par[head[u]]) if (dep[head[u]] < dep[head[v]]) swap(u, v);
        return dep[u] < dep[v] ? u : v;
    }

    T get_vertex(int v) { return t.get(tin[v], tin[v] + 1); }
    T get_path(int u, int v) {
        T s{};
        for (; head[u] != head[v]; s += t.get(tin[head[u]], tin[u] + 1), u = par[head[u]]) if (dep[head[u]] < dep[head[v]]) swap(u, v);
        return s + (dep[u] < dep[v] ? t.get(tin[u], tin[v] + 1) : t.get(tin[v], tin[u] + 1));
    }
    T get_subtree(int v) { return t.get(tin[v], tout[v]); }

    void upd_vertex(int v, U x) { t.upd(tin[v], tin[v] + 1, x); }
    void upd_path(int u, int v, U x) {
        for (; head[u] != head[v]; t.upd(tin[head[u]], tin[u] + 1, x), u = par[head[u]]) if (dep[head[u]] < dep[head[v]]) swap(u, v);
        dep[u] < dep[v] ? t.upd(tin[u], tin[v] + 1, x) : t.upd(tin[v], tin[u] + 1, x);
    }
    void upd_subtree(int v, U x) { t.upd(tin[v], tout[v], x);}

    hld_forest() {}
    hld_forest(int n) {
        g.resize(n), sub.resize(n), tin.resize(n), tout.resize(n), head.resize(n), val.resize(n), par.resize(n), dep.resize(n);
    }
    hld_forest(vector <T>& a) {
        g.resize(sz(a)), sub.resize(sz(a)), tin.resize(sz(a)), tout.resize(sz(a)), head.resize(sz(a)), par.resize(sz(a)), dep.resize(sz(a));
        val = a;
    }
};
