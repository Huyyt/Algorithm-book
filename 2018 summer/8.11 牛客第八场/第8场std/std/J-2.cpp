#include <bits/stdc++.h>

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

#ifdef __WIN32
#define LLFORMAT "I64"
#define Rand() ((rand() << 15) + rand())
#else
#define LLFORMAT "ll"
#define Rand() (rand())
#endif

using namespace std;

const int maxn = 2e6 + 10;

int n, m, k;
long long a[maxn], b[maxn];

long long extgcd(long long a, long long &x, long long b, long long &y) { // ax + by = gcd(a, b)
	if(!b) { x = 1; y = 0; return a; }
	long long c = a / b, d = extgcd(b, y, a - c * b, x);
	y -= c * x;
	return d;
}

int pow_mod(int x, int n, int m) { int y = 1; while(n) { if(n & 1) y = (long long) y * x % m; x = (long long) x * x % m; n >>= 1; } return y; }

int inv(int x, int mod) {
	long long s, t;
	extgcd(x, s, mod, t);
	return (s % mod + mod) % mod;
}

void div(int n, int p, int &s, int &t) {
	t = 0;
	while(n % p == 0) ++t, n /= p;
	s = n;
	return;
}

void work(int &res, int p, int q, int mod) {
	int x = 1, y = 0;
	for (int i = 0; i <= m + 10; ++i) {
		a[i] = (i <= n + 2 ? (long long) pow_mod(p, y, mod) * x % mod : 0);
		if(i + 1 <= n + 2) {
			int s, t;
			div(n + 2 - i, p, s, t);
			x = (long long) x * s % mod; y += t;
			div(i + 1, p, s, t);
			x = (long long) x * inv(s, mod) % mod; y -= t;
		}
	}
	--a[0];
	int inv2 = inv(2, mod);
	b[0] = (long long) a[1] * inv2 % mod;
	for (int i = 1; i <= m; ++i) b[i] = (long long) (a[i + 1] - b[i - 1]) * inv2 % mod;
	res = 0;
	for (int i = 0; i <= m; ++i) if(~i & 1) res = (res + b[i]) % mod;
	res = (res + mod) % mod;
	return;
}

void work2(int &res, int p, int q, int mod) {
	int x = 1, y = 0;
	for (int i = 0; i <= m + 100; ++i) {
		a[i] = (i <= n + 2 ? (long long) pow_mod(p, y, mod) * x % mod : 0);
		if(i + 1 <= n + 2) {
			int s, t;
			div(n + 2 - i, p, s, t);
			x = (long long) x * s % mod; y += t;
			div(i + 1, p, s, t);
			x = (long long) x * inv(s, mod) % mod; y -= t;
		}
	}
	--a[0];
	for (int i = 0; i <= m; ++i) {
		int t = 1;
		b[i] = 0;
		for (int j = i + 2; t; ++j, t = -2ll * t % mod) b[i] = ((long long) t * a[j] + b[i]) % mod;
	}
	res = 0;
	for (int i = 0; i <= m; ++i) if(~i & 1) res = (res + b[i]) % mod;
	res = (res + mod) % mod;
	return;
}

void crt(int &R1, int &M1, int R2, int M2) {
	long long r1 = R1, m1 = M1, r2 = R2, m2 = M2;
	long long x, y;
	extgcd(m1, x, m2, y);
	x = (x % m2 * (r2 - r1) % m2 + m2) % m2;
	y = M1 * M2;
	R1 = (x * m1 + R1) % y;
	M1 = y;
	return;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	if(n & 1) --n;
	int mod = 1, res = 0;
	for (int x = 2; x * x <= k; ++x) {
		if(k % x == 0) {
			int t = k, cnt = 0;
			while(k % x == 0) k /= x, ++cnt;
			int r, m = t / k;
			if(x == 2) work2(r, x, cnt, m);
			else work(r, x, cnt, m);
			crt(res, mod, r, m);
		}
	}
	if(k > 1) {
		int r, m = k;
		if(k == 2) work2(r, k, 1, m);
		else work(r, k, 1, m);
		crt(res, mod, r, m);
	}
	printf("%d\n", (res + mod) % mod);
	return 0;
}

