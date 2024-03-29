template <typename T, typename U>
struct segtree {
    vector <T> t;
    vector <U> u;
    int R;

    void pull(int v) { t[v] = t[2 * v] + t[2 * v + 1]; }
    void push(int v) {
        t[2 * v] += u[v], t[2 * v + 1] += u[v];
        u[2 * v] += u[v], u[2 * v + 1] += u[v];
        u[v] = U();
    }

    void upd(int ql, int qr, U x, int v, int nl, int nr) {
        if (ql == nl && qr == nr) {
            t[v] += x, u[v] += x;
            return;
        }
        push(v);
        int nm = (nl + nr) / 2;
        if (qr <= nm) upd(ql, qr, x, 2 * v, nl, nm);
        else if (ql >= nm) upd(ql, qr, x, 2 * v + 1, nm, nr);
        else upd(ql, nm, x, 2 * v, nl, nm), upd(nm, qr, x, 2 * v + 1, nm, nr);
        pull(v);
    }
    void upd(int l, int r, U x) { upd(l, r, x, 1, 0, R); }
    T get(int ql, int qr, int v, int nl, int nr) {
        if (ql == nl && qr == nr) return t[v];
        push(v);
        int nm = (nl + nr) / 2;
        if (qr <= nm) return get(ql, qr, 2 * v, nl, nm);
        if (ql >= nm) return get(ql, qr, 2 * v + 1, nm, nr);
        return get(ql, nm, 2 * v, nl, nm) + get(nm, qr, 2 * v + 1, nm, nr);
    }
    T get(int l, int r) { return get(l, r, 1, 0, R); }

    segtree() {}
    segtree(int n) : R(1) {
        while (R < n) R <<= 1;
        t.resize(2 * R), u.resize(2 * R);
        RFOR(i, R - 1, 1) pull(i);
    }
    segtree(vector <T>& a) : R(1) {
        while (R < sz(a)) R <<= 1;
        t.resize(2 * R), u.resize(2 * R);
        FOR(i, 0, sz(a)) t[R + i] = a[i];
        RFOR(i, R - 1, 1) pull(i);
    }
};



// Example of usage
struct info {
    unsigned ll v;
    ll c;
    info() : v(0), c(0) {}
    info(unsigned ll x) : v(x), c(1) {}
    info(unsigned ll a, ll b) : v(a), c(b) {}
};
struct lazy {
    ll v;
    lazy() : v(0) {}
    lazy(ll x) : v(x) {}
};

info operator+(const info a, const info b) { return info(a.v + b.v, a.c + b.c); }
info& operator+=(info& a, const info b) { return a = a + b; }
info operator+(const info a, const lazy b) { return info(a.v + b.v * a.c, a.c); }
info& operator+=(info& a, const lazy b) { return a = a + b; }
lazy operator+(const lazy a, const lazy b) { return lazy(a.v + b.v); }
lazy& operator+=(lazy& a, const lazy b) { return a = a + b; }
