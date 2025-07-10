/*
BigInt for poor (numbers of small length)
Supports +, -, *, %, <<, >> and fast division by 2, * and % work in O(nm), where n, m - lenghts of operands
TODO: in-place operators, /, test for correctness
*/

static constexpr int LEN = 9, BASE = 1000000000;

using u32 = uint32_t;
using u64 = uint64_t;

struct poor_bigint {
    vector <u32> a;
    bool neg;

    poor_bigint() : a(1, 0), neg(0) {}
    poor_bigint(ll x) : neg(0) {
        if (x < 0) neg = 1, x = -x;
        while (x) {
            a.push_back(x % BASE);
            x /= BASE;
        }
    }

    bool is_zero() const {
        return sz(a) == 1 && a[0] == 0;
    }

    void div_by_2() {
        if (is_zero()) return;
        u32 carry = 0;
        for (int i = 0; i < sz(a); ++i) {
            if (i && a[i] & 1) {
                a[i - 1] += BASE >> 1;
            }
            a[i] >>= 1;
        }
    }

    poor_bigint add_impl(const poor_bigint& o) const {
        poor_bigint res;
        res.a.resize(max(sz(a), sz(o.a)));
        bool carry = 0;
        for (int i = 0; i < max(sz(a), sz(o.a)); ++i) {
            u32 cur = (i < sz(a) ? a[i] : 0) + (i < sz(o.a) ? o.a[i] : 0) + carry;
            if (cur >= BASE) {
                cur -= BASE;
                carry = 1;
            } else {
                carry = 0;
            }
            res.a[i] = cur;
        }
        if (carry) {
            res.a.push_back(1);
        }
        return res;
    }

    poor_bigint sub_impl(const poor_bigint& o) const {
        poor_bigint res;
        res.a.resize(sz(a));
        bool borrow = 0;
        for (int i = 0; i < sz(a); ++i) {
            u32 cur = a[i] - (i < sz(o.a) ? o.a[i] : 0) - borrow;
            if (cur < 0) {
                cur += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res.a[i] = cur;
        }
        while (sz(res.a) > 1 && res.a.back() == 0) res.a.pop_back();
        return res;
    }

    bool cmp_impl(const poor_bigint& o) {
        if (sz(a) != sz(o.a)) return sz(a) < sz(o.a);
        for (int i = sz(a) - 1; i >= 0; --i) {
            if (a[i] != o.a[i]) return a[i] < o.a[i];
        }
        return false;
    }

    bool eq_impl(const poor_bigint& o) const {
        if (sz(a) != sz(o.a)) return false;
        for (int i = 0; i < sz(a); ++i) {
            if (a[i] != o.a[i]) return false;
        }
        return true;
    }

    poor_bigint mul_impl(const poor_bigint& o) {
        poor_bigint res;
        res.a.resize(sz(a) + sz(o.a), 0);
        for (int i = 0; i < sz(a); ++i) {
            u64 carry = 0;
            for (int j = 0; j < sz(o.a); ++j) {
                u64 cur = (u64)a[i] * o.a[j] + res.a[i + j] + carry;
                res.a[i + j] = cur % BASE;
                carry = cur / BASE;
            }
            res.a[i + sz(o.a)] += carry;
        }
        while (sz(res.a) > 1 && res.a.back() == 0) {
            res.a.pop_back();
        }
        return res;
    }

    poor_bigint shift_right(int k) const {
        poor_bigint res;
        res.a.resize(sz(a) + k);
        for (int i = 0; i < sz(a); ++i) {
            res.a[i + k] = a[i];
        }
        res.neg = neg;
        return res;
    }

    // This looks really sus, should check it ASAP
    poor_bigint mod_impl(const poor_bigint& o) {
        poor_bigint rem = *this;
        while (!rem.cmp_impl(o)) {
            if (o.a.back() < rem.a.back()) {
                poor_bigint shifted = o.shift_right(sz(rem.a) - sz(o.a));
                rem = rem - shifted;
            } else {
                poor_bigint shifted = o.shift_right(sz(rem.a) - sz(o.a) - 1);
                u32 coeff = ((u64)rem.a.back() * BASE + rem.a[sz(rem.a) - 2] - 1) / o.a.back();
                rem = rem - shifted * poor_bigint(coeff - 1);
            }
        }
        return rem;
    }

    poor_bigint operator+(const poor_bigint& o) {
        if (neg == o.neg) {
            poor_bigint res = add_impl(o);
            res.neg = neg;
            return res;
        } else {
            if (cmp_impl(o)) {
                poor_bigint res = o.sub_impl(*this);
                res.neg = o.neg;
                return res;
            } else {
                poor_bigint res = sub_impl(o);
                res.neg = (res.is_zero() ? 0 : neg);
                return res;
            }
        }
    }

    poor_bigint operator-(const poor_bigint& o) {
        if (neg != o.neg) {
            poor_bigint res = add_impl(o);
            res.neg = neg;
            return res;
        } else {
            if (cmp_impl(o)) {
                poor_bigint res = o.sub_impl(*this);
                res.neg = !neg;
                return res;
            } else {
                poor_bigint res = sub_impl(o);
                res.neg = (res.is_zero() ? 0 : neg);
                return res;
            }
        }
    }

    poor_bigint operator*(const poor_bigint& o) {
        poor_bigint res = this->mul_impl(o);
        res.neg = this->neg ^ o.neg;
        return res;
    }

    poor_bigint operator%(const poor_bigint& o) {
        assert(!o.neg);
        return mod_impl(o);
    }

    istream& operator>>(istream& in) {
        string s; in >> s;
        a.clear();
        neg = s[0] == '-';
        for (int i = sz(s) - 1; i >= neg; i -= LEN) {
            u32 cur = 0;
            for (int j = i; j >= max((int)neg, i - LEN + 1); --j) {
                cur = cur * 10 + (s[j] - '0');
            }
            a.push_back(cur);
        }
        return in;
    }

    ostream& operator<<(ostream& out) const {
        if (neg) out << '-';
        out << a.back();
        for (int i = sz(a) - 2; i >= 0; --i) {
            out << setw(LEN) << setfill('0') << a[i];
        }
        return out;
    }
};
