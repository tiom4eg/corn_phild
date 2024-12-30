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

namespace std {
    template <int MOD>
    struct hash <mint <MOD>> {
        int operator()(const mint <MOD>& m) const { return m.v; }
    };
}

template <typename M>
struct seq_hash {
    vector <M> h, p;
    M b;
    seq_hash(M b) : h(1), p(1, 1), b(b) {}
    template <typename It>
    seq_hash(It beg, It end, M b) : b(b) {
        h.resize(distance(beg, end) + 1); // std::distance should exists for all adequate iterators
        p.resize(distance(beg, end) + 1);
        p[0] = 1;
        for (size_t i = 0; beg != end; ++i, ++beg) {
            h[i + 1] = h[i] * b + M(*beg);
            p[i + 1] = p[i] * b;
        }
    }
    template <typename T>
    void operator+=(const T x) {
        h.push_back(h.back() * b + M(x));
        p.push_back(p.back() * b);
    }
    M get(size_t l, size_t r) { return h[r] - h[l] * p[r - l]; }
};
