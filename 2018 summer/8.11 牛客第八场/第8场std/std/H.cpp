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

const int maxn = (1 << 19) | 10;

int x, n, ans, a[maxn], c[maxn];
long long b[maxn];

template<typename T> void dft(T *a) { for (int hl = 1, l = 2; l <= n; hl = l, l <<= 1) for (T i = 0; i < n; i += l) for (register T t, j = 0, *x = a + i, *y = x + hl; j < hl; ++j, ++x, ++y) t = *x + *y, *y = *x - *y, *x = t; return; }

int main() {
	scanf("%d", &n);
	//assert(1 <= n && n <= 500000);
	for (int y, i = 0; i < n; ++i) assert(scanf("%d", &y) == 1), assert(y >= 0 && y <= 500000), c[y] = 1, x ^= y;
	//auto BEG = clock(); int m = n;
	ans = n; n = 1 << 19;
	//assert(scanf("%d", &n) == EOF); n = 1 << 19;
	dft(c); a[0] = 1;
	while(!a[x]) {
		--ans;
		dft(a);
		for (int i = 0; i < n; ++i) b[i] = (long long) a[i] * c[i];
		dft(b);
		for (int i = 0; i < n; ++i) a[i] = (b[i] > 0);
	}
	//debug("Time: %.12f\tdel %d\n", 1.0 * (clock() - BEG) / CLOCKS_PER_SEC, m - ans);
	printf("%d\n", ans);
	return 0;
}
