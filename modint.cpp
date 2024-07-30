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
};
