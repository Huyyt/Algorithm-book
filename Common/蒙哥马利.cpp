#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
struct Mod64 {
    Mod64() : n_(0) {}
    Mod64(u64 n) : n_(init(n)) {}
    static u64 modulus() {
        return mod;
    }
    static u64 init(u64 w) {
        return reduce(u128(w) * r2);
    }
    static void set_mod(u64 m) {
        mod = m;
        assert(mod & 1);
        inv = m;
        for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
        r2 = -u128(m) % m;
    }
    static u64 reduce(u128 x) {
        u64 y = u64(x >> 64) - u64((u128(u64(x) * inv) * mod) >> 64);
        return i64(y) < 0 ? y + mod : y;
    }
    Mod64& operator += (Mod64 rhs) {
        n_ += rhs.n_ - mod;
        if (i64(n_) < 0) n_ += mod;
        return *this;
    }
    Mod64 operator + (Mod64 rhs) const {
        return Mod64(*this) += rhs;
    }
    Mod64& operator *= (Mod64 rhs) {
        n_ = reduce(u128(n_) * rhs.n_);
        return *this;
    }
    Mod64 operator * (Mod64 rhs) const {
        return Mod64(*this) *= rhs;
    }
    u64 get() const {
        return reduce(n_);
    }
    static u64 mod, inv, r2;
    u64 n_;
};
u64 Mod64::mod, Mod64::inv, Mod64::r2;
inline u64 mod128_64_small(u128 a, u64 b) {
    u64 q, r;
    __asm__ (
        "divq\t%4"
        : "=a"(q), "=d"(r)
        : "0"(u64(a)), "1"(u64(a >> 64)), "rm"(b)
    );
    return r;
}
Mod64 a[1000005];
int main() {
#ifdef CX_TEST
    freopen("E:\\program--GG\\test_in.txt", "r", stdin);
#endif
    int T;
    cin >> T;
    for(; T--;) {
        i64 m0, m1, a0, a1, c, k, mod;
        scanf("%lld%lld%lld%lld%lld%lld%lld", &a0, &a1, &m0, &m1, &c, &mod, &k);
        Mod64::set_mod(mod);
        Mod64 ret, M0 = Mod64(m0), M1 = Mod64(m1), C = Mod64(c);
        a[0] = Mod64(a0);
        a[1] = Mod64(a1);
        ret = a[0] * a[1];
        for(int i = 2; i <= k; i++) {
            a[i] = M0 * a[i - 1] + M1 * a[i - 2] + C;
            ret *= a[i];
        }
        printf("%llu\n", ret.get());
    }
}
