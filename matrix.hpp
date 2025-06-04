#include <vector>
#include <utility>
#include "tensor.hpp"

using u32 = uint32_t;

template <class T>
class matrix {
    matrix() {}
    matrix(int r, int c) : val(tensor <T, 2>(r, c)) {}
    matrix(tensor <T, 1>& a, bool hori = false) { // hori = true if 1 * n; n * 1 otherwise
        if (hori) {
            val = tensor <T, 2>(std::array{1, a.size()});
            for (u32 i = 0; i < a.dim(0); ++i) {
                val[0][i] = a[i];
            }
        } else {
            val = tensor <T, 2>(std::array{a.size(), 1});
            for (u32 i = 0; i < a.dim(0); ++i) {
                val[i][0] = a[i];
            }
        }
    }
    matrix(tensor <T, 2>& a) : val(a) {}

    friend matrix operator+(const matrix& self, const matrix& other) {
        assert(self.val.dim(0) == other.val.dim(0) && self.val.dim(1) == self.val.dim(1));
        matrix <T> result(self.val.dim(0), self.val.dim(1));
        for (u32 i = 0; i < self.val.dim(0); ++i) {
            for (u32 j = 0; j < self.val.dim(1); ++j) {
                result.val[i][j] = self.val[i][j] + other.val[i][j];
            }
        }
        return result;
    }

    friend matrix operator-(const matrix& self, const matrix& other) {
        assert(self.val.dim(0) == other.val.dim(0) && self.val.dim(1) == self.val.dim(1));
        matrix <T> result(self.val.dim(0), self.val.dim(1));
        for (u32 i = 0; i < self.val.dim(0); ++i) {
            for (u32 j = 0; j < self.val.dim(1); ++j) {
                result.val[i][j] = self.val[i][j] - other.val[i][j];
            }
        }
        return result;
    }

    friend matrix operator*(const matrix& self, const matrix& other) {
        assert(self.val.dim(1) == other.val.dim(0));
        matrix <T> result(self.val.dim(0), other.val.dim(1));
        for (u32 i = 0; i < self.val.dim(0); ++i) {
            for (u32 j = 0; j < other.val.dim(1); ++j) {
                for (u32 k = 0; k < self.val.dim(1); ++k) {
                    result.val[i][j] = result.val[i][j] + (self.val[i][k] * other.val[k][j]);
                }
            }
        }
        return result;
    }

    friend matrix operator+=(matrix& self, const matrix& other) {
        assert(self.val.dim(0) == other.val.dim(0) && self.val.dim(1) == self.val.dim(1));
        for (u32 i = 0; i < self.val.dim(0); ++i) {
            for (u32 j = 0; j < self.val.dim(1); ++j) {
                self.val[i][j] = self.val[i][j] + other.val[i][j];
            }
        }
        return self;
    }

    friend matrix operator+=(matrix& self, const matrix& other) {
        assert(self.val.dim(0) == other.val.dim(0) && self.val.dim(1) == self.val.dim(1));
        for (u32 i = 0; i < self.val.dim(0); ++i) {
            for (u32 j = 0; j < self.val.dim(1); ++j) {
                self.val[i][j] = self.val[i][j] - other.val[i][j];
            }
        }
        return self;
    }

    friend matrix operator*=(matrix& self, const matrix& other) {
        assert(self.val.dim(1) == other.val.dim(0));
        tensor <T, 2> result(std::array{self.val.dim(0), other.val.dim(1)});
        for (u32 i = 0; i < self.val.dim(0); ++i) {
            for (u32 j = 0; j < other.val.dim(1); ++j) {
                for (u32 k = 0; k < self.val.dim(1); ++k) {
                    result.val[i][j] = result.val[i][j] + (self.val[i][k] * other.val[k][j]);
                }
            }
        }
        self.val = result;
        return self;
    }

    T& operator[](std::pair <u32, u32> idx) { return val[idx.first][idx.second]; }
	const T& operator[](std::pair <u32, u32> idx) const { return val[idx.first][idx.second]; }

private:
    tensor <T, 2> val;
};
