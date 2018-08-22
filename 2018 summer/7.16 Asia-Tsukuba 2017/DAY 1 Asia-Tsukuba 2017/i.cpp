#include<cstdio>
#include<algorithm>
using namespace std;
int n, T = 100001;
struct point {
    int b, e;
}w[201000];
int S1[201000], S2[201000], S[201000], R1, R2;
int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &w[i].b, &w[i].e);
        S[w[i].b]++, S[w[i].e]--;
        S1[w[i].b]++;
        S2[w[i].e]++;
    }
    for (i = 1; i <= T; i++) {
        S[i] += S[i - 1];
        S1[i] += S1[i - 1];
        S2[i] += S2[i - 1];
        R2 = max(R2, S[i]);
    }
    for (i = 1; i <= n; i++) {
        R1 = max(R1, n - (n - S1[w[i].e - 1]) - S2[w[i].b]);
    }
    printf("%d %d\n", R1, R2);
}
