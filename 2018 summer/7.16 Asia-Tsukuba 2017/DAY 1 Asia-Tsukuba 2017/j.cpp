#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
int L, n, m, Q;
int Y[1010], H[1010];
char Res[1010];
int w[1010];
char p[1010];
map<int, char>Map[1010];
vector<int>G[1010];
int Loc(int x) {
    return (lower_bound(Y, Y + m + 2, x+1) - Y) - 1;
}
int main(){
    int i;
    scanf("%d%d%d%d", &L, &n, &m, &Q);
    for (i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        scanf("%s", p+i);
    }
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &Y[i],&H[i]);
    }
    Y[m + 1] = L + 1;
    for (i = 0; i <= m; i++)if (!H[i])H[i] = -L;
    for (i = 1; i <= n; i++) {
        int x = w[i];
        while (1) {
            int t = Loc(x);
            Map[t][x % (Y[t] - H[t])] = p[i];
            if (H[t] <= 0)break;
            x -= ((x - Y[t]) / (Y[t] - H[t]) + 1) * (Y[t] - H[t]);
        }
    }
    for (i = 1; i <= Q; i++) {
        int x;
        char u = '?';
        scanf("%d", &x);
        while (1) {
            int t = Loc(x);
            if (Map[t].count(x % (Y[t] - H[t]))) u = Map[t][x % (Y[t] - H[t])];
            if (H[t] <= 0)break;
            x -= ((x - Y[t]) / (Y[t] - H[t]) + 1) * (Y[t] - H[t]);
        }
        printf("%c", u);
    }
    printf("\n");
}
