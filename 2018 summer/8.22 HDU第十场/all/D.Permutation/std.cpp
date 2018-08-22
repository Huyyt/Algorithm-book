#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#define x first
#define y second
#define MP std::make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
using std::pair;
using std::vector;
using std::string;
typedef long long LL;
typedef pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b)
{
        return a < b ? a = b, true : false;
}
template<typename T> inline bool chkmin(T &a, T b)
{
        return b < a ? a = b, true : false;
}
// EOT

const int MAXN = 103;
int N, P;
inline void mod(int &x)
{
        x = (x >= P ? x - P : x);
}
void solve()
{
        static int f[MAXN][MAXN * MAXN], g[MAXN][MAXN * MAXN];
        memset(g, 0, sizeof(g));
        g[0][0] = g[1][0] = 1;
        for (int i = 1; i < N; ++i)
        {
                memcpy(f, g, sizeof(f));
                memset(g, 0, sizeof(g));
                for (int j = 0; j <= i; ++j)
                {
                        for (int k = 0; k <= i * i; ++k)
                        {
                                if (!f[j][k])
                                {
                                        continue;
                                }
                                mod(g[j][k + j] += (LL)(2 * j + 1) * f[j][k] % P);
                                if (j)
                                {
                                        mod(g[j - 1][k + j] += (LL)j * j * f[j][k] % P);
                                }
                                mod(g[j + 1][k + j] += f[j][k]);
                        }
                }
        }
        for (int i = 0; i < N * N; ++i)
        {
                int cur = i & 1 ? 0 : g[0][i / 2];
                printf("%d%c", cur, " \n"[i == N * N - 1]);
        }
}
int main()
{
        int T;
        scanf("%d", &T);
        while (T--)
        {
                scanf("%d%d", &N, &P);
                solve();
        }
        return 0;
}
