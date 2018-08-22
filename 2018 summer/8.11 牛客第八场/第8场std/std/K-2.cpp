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

const int maxn = 15, mod = 998244353, maxm = 1 << maxn;

int F(vector<long long> a, long long x) {
	if(!a.size()) return x == 0;
	int i = 0, n = a.size();
	for (int j = 1; j < n; ++j) if(a[j] > a[i]) i = j;
	if(a[i] == 0) return x == 0;
	long long t = 1, y = x; while(t <= a[i]) t <<= 1, y >>= 1; t >>= 1;
	if(y) return 0;
	int f[2] = {1, 0};
	for (int j = 0; j < n; ++j) if(i != j) {
		long long x = min(t, a[j] + 1), y = a[j] + 1 - x;
		int g[2];
		x %= mod; y %= mod;
		g[0] = ((long long) f[0] * x + (long long) f[1] * y) % mod;
		g[1] = ((long long) f[1] * x + (long long) f[0] * y) % mod;
		memcpy(f, g, sizeof f);
	}
	int ret = f[(x & t) > 0];
	a[i] ^= t; x ^= t;
	ret = (ret + F(a, x)) % mod;
	return ret;
}

int n, m, S, ans;
long long a[maxn], x;
bool g[maxn][maxn];
int f[maxm], p[maxm][maxn], inv[maxn], col[maxn], Fpool[maxm], pw2[maxn], b[maxn], rem[maxn], s[maxn], invb[maxn], invf[maxm];

inline void upd(int &x, const int &y) { x += y; if(x >= mod) x -= mod; return; }
inline int pow_mod(int x, int n = mod - 2) { int y = 1; while(n) { if(n & 1) y = (long long) y * x % mod; x = (long long) x * x % mod; n >>= 1; } return y; }

inline int F(int &s) {
	int &t = Fpool[s];
	if(~t) return t;
	static vector<long long> a; a.clear();
	for (int i = 1; i <= n; ++i) if((s >> i) & 1) a.push_back(::a[i]);
	return t = F(a, x);
}

inline void chkmin(int &x, const int &y) { x = (!x || a[x] > a[y]) ? y : x; }

void dfs(int u = 1, int mx = 0, int cnt = 0, int t = 0, int coef = 1, int coef0 = 0) {
	if(u > n) {
		if(!coef0) ans = ((long long) coef * F(t) + ans) % mod;
		return;
	}
	int foo, bar, ncnt, nt, ncoef, ncoef0, fuck;
	for (int x = 1; x <= mx; ++x) {
		ncnt = cnt; nt = t; ncoef = coef; ncoef0 = coef0;
		foo = rem[x]; bar = s[x];

		if(ncnt & pw2[x]) nt ^= pw2[foo];
		else {
			fuck = invb[foo];
			if(!fuck) --ncoef0;
			else ncoef = (long long) ncoef * fuck % mod;
		}
		fuck = invf[bar];
		if(!fuck) --ncoef0;
		else ncoef = (long long) ncoef * fuck % mod;

		col[u] = x; chkmin(rem[x], u); s[x] |= pw2[u - 1];

		ncnt ^= pw2[x]; int &j = rem[x];
		if(ncnt & pw2[x]) nt |= pw2[j];
		else {
			fuck = b[j];
			if(!fuck) ++ncoef0;
			else ncoef = (long long) ncoef * fuck % mod;
		}
		fuck = f[s[x]];
		if(!fuck) ++ncoef0;
		else ncoef = (long long) ncoef * fuck % mod;
		if(!ncoef) {
			debug("%d %d\t%d %d\n", invb[foo], invf[bar], b[j], f[s[x]]);
			exit(0);
		}

		dfs(u + 1, mx, ncnt, nt, ncoef, ncoef0);
		rem[x] = foo; s[x] = bar;
	}
	col[u] = ++mx;
	foo = rem[mx]; bar = s[mx];
	chkmin(rem[mx], u); s[mx] |= pw2[u - 1];
	cnt ^= pw2[mx];
	int &j = rem[mx];
	if(cnt & pw2[mx]) t |= pw2[j];
	else {
		fuck = b[j];
		if(!fuck) ++coef0;
		else coef = (long long) coef * fuck % mod;
	}
	fuck = f[s[mx]];
	if(!fuck) ++coef0;
	else coef = (long long) coef * fuck % mod;
	dfs(u + 1, mx, cnt, t, coef, coef0);
	rem[mx] = foo; s[mx] = bar;
	return;
}

int main() {
	scanf("%d%d%"LLFORMAT"d", &n, &m, &x);
	memset(Fpool, -1, sizeof Fpool);
	for (int i = 0; i <= n; ++i) pw2[i] = 1 << i;
	for (int i = 1; i <= n; ++i) scanf("%"LLFORMAT"d", a + i), inv[i] = pow_mod(i), b[i] = (a[i] + 1) % mod, invb[i] = pow_mod(b[i]);
	for (int i = 0; i < m; ++i) { int u, v; scanf("%d%d", &u, &v); g[u][v] = g[v][u] = 1; }
	S = 1 << n;
	for (int s = 0; s < S; ++s) {
		int &f = ::f[s]; f = 1;
		for (int u = 1; u <= n; ++u) if((s >> u - 1) & 1) for (int v = 1; v < u; ++v) if((s >> v - 1) & 1) f &= (g[u][v] == 0);
	}
	for (int s = 0; s < S; ++s) p[s][__builtin_popcount(s)] = f[s];
	for (int hl = 1, l = 2; l <= S; hl = l, l <<= 1) for (int i = 0; i < S; i += l) for (int j = 0; j < hl; ++j) for (int k = 0; k <= n; ++k) upd(p[i + hl + j][k], p[i + j][k]);
	for (int s = 0; s < S; ++s) {
		static int f[maxn];
		for (int i = 0; i < n; ++i) f[i] = (long long) p[s][i + 1] * (i + 1) % mod; f[n] = 0;
		for (int i = 0; i <= n; ++i) for (int j = 1; j <= i; ++j) f[i] = ((long long) f[i] - (long long) p[s][j] * f[i - j]) % mod;
		p[s][0] = 0; for (int i = 1; i <= n; ++i) p[s][i] = ((long long) f[i - 1] * inv[i] % mod + mod) % mod;
	}
	for (int hl = 1, l = 2; l <= S; hl = l, l <<= 1) for (int i = 0; i < S; i += l) for (int j = 0; j < hl; ++j) for (int k = 0; k <= n; ++k) upd(p[i + hl + j][k], mod - p[i + j][k]);
	for (int s = 0; s < S; ++s) f[s] = p[s][__builtin_popcount(s)], invf[s] = pow_mod(f[s]);
	dfs();
	printf("%d\n", (ans + mod) % mod);
	return 0;
}
