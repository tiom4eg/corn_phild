// Example: https://atcoder.jp/contests/abc359/submissions/55232935

struct compressed_tree {
    int h, tt;
    vector <vector <int>> g;
    vector <int> tin, tout;
    vector <vector <int>> up;
    vector <bool> used;

    void add_edge_dir(int u, int v) { g[u].push_back(v); }
    void add_edge(int u, int v) { add_edge_dir(u, v), add_edge_dir(v, u); }

    bool upper(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }
    int lca(int u, int v) {
        if (upper(u, v)) return u;
        if (upper(v, u)) return v;
        for (int i = h - 1; i >= 0; --i) if (!upper(up[i][u], v)) u = up[i][u];
        return up[0][u];
    }

    void build(int v = 0, int p = 0) {
        tin[v] = tt++, up[0][v] = p;
        for (int i = 1; i < h; ++i) up[i][v] = up[i - 1][up[i - 1][v]];
        for (auto& u : g[v]) if (u != p) build(u, v);
        tout[v] = tt;
    }

    vector <pair <int, int>> compress(vector <int>& a) {
        vector <int> t(a);
        for (auto& v : a) used[v] = 1;
        sort(t.begin(), t.end(), [&](int u, int v) { return tin[u] < tin[v]; });
        for (int i = 1; i < a.size(); ++i) {
            int v = lca(t[i - 1], t[i]);
            if (!used[v]) {
                t.push_back(v);
                used[v] = 1;
            }
        }
        sort(t.begin(), t.end(), [&](int u, int v) { return tin[u] < tin[v]; });
        vector <int> st;
        vector <pair <int, int>> edg(t.size() - 1); // (parent, vertex)
        st.push_back(t[0]);
        for (int i = 1; i < t.size(); ++i) {
            while (tout[st.back()] <= tin[t[i]]) st.pop_back();
            edg[i - 1] = make_pair(st.back(), t[i]);
            st.push_back(t[i]);
        }
        for (auto& v : t) used[v] = 0;
        return edg;
    }

    compressed_tree() {}
    compressed_tree(int n) : h(__lg(n) + 1) {
        g.resize(n);
        tin.resize(n);
        tout.resize(n);
        up.assign(h, vector <int>(n));
        used.resize(n);
    }
};
