template <int MOD>
struct mint {
    int v;
    mint() : v(0) {}
    mint(int x) : v(x) {}
    void norm() { v = ((v % MOD) + MOD) % MOD; }
    mint operator+(const mint o) const { return mint(v + o.v - MOD * (v + o.v >= MOD)); }
    mint operator-(const mint o) const { return mint(v - o.v + MOD * (o.v > v)); }
    mint operator*(const mint o) const { return mint(v * 1LL * o.v % MOD); }
    mint operator^(int e) const {
        mint r(1), c(v);
        for (; e; e >>= 1, c = c * c) if (e & 1) r = r * c;
        return r;
    }
    mint inv() { return this->operator^(MOD - 2); }
    mint operator/(mint o) const { return this->operator*(o.inv()); }
    bool operator==(const mint o) const { return v == o.v; }
    bool operator!=(const mint o) const { return v != o.v; }
    bool operator<(const mint o) const { return v < o.v; }
    void operator+=(const mint& o) { *this = this->operator+(o); }
    void operator-=(const mint& o) { *this = this->operator-(o); }
    void operator*=(const mint& o) { *this = this->operator*(o); }
    void operator/=(const mint& o) { *this = this->operator/(o); }
    friend istream& operator>>(istream& in, mint& m) {
        in >> m.v;
        return in;
    }
    friend ostream& operator<<(ostream& out, const mint& m) {
        out << m.v;
        return out;
    }
};

template <typename M>
struct str_hash {
    vector <M> h, p;
    str_hash() : h(1), p(1, 1) {}
    str_hash(const string& s, M b) {
        h.resize(s.size() + 1);
        p.resize(s.size() + 1);
        p[0] = 1;
        for (int i = 0; i < s.size(); ++i) {
            h[i + 1] = h[i] * b + s[i];
            p[i + 1] = p[i] * b;
        }
    }
    M get(int l, int r) { return h[r] - h[l] * p[r - l]; }
};
