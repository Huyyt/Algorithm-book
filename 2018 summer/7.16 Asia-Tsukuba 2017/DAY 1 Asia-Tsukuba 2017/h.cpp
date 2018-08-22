#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n, m, res = 1e9;
struct point {
    int b, e, ck;
    bool operator<(const point &p)const {
        return b < p.b;
    }
}w[410];
int D1[410][410], D2[410][410];
int main() {
    int i, RM = 0, j, k, MX = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &w[i].b, &w[i].e);
        if (i <= m)w[i].ck = 1;
        else w[i].ck = 2;
        MX = max(MX, w[i].e);
    }
    sort(w + 1, w + n + 1);
    priority_queue<int>PQ;
    int pv = 1;
    for (i = 1; i <= MX; i++) {
        while (pv <= n && w[pv].b == i) {
            PQ.push(-w[pv].e);
            pv++;
        }
        while (!PQ.empty() && -PQ.top() < i)PQ.pop();
        if (!PQ.empty())RM++, PQ.pop();
    }
    printf("%d\n", RM);
    for (i = 0; i <= MX; i++)for (j = 0; j <= MX; j++)D1[i][j] = 1e9, D2[i][j] = 1e9;
    D1[0][0] = D2[0][0] = 0;
    for (i = 0; i <= MX; i++) {
        for (j = 0; j <= i; j++) {
            if (D1[i][j] > 1e8 && D2[i][j] > 1e8)continue;
            int pv = 1;
            while (pv <= n && w[pv].b <= j)pv++;
            priority_queue<int>PQ2, PQ1;
            for (k = j + 1; k <= i; k++) {
                while (pv <= n && w[pv].b == k) {
                    if(w[pv].ck == 2) PQ2.push(-w[pv].e);
                    else PQ1.push(-w[pv].e);
                    pv++;
                }
            }
            int r2 = D1[i][j], r1 = D2[i][j];
            for (k = i + 1; k <= MX; k++){
                while (pv <= n && w[pv].b == k) {
                    if (w[pv].ck == 2) PQ2.push(-w[pv].e);
                    else PQ1.push(-w[pv].e);
                    pv++;
                }
                while (!PQ2.empty() && -PQ2.top() < k)PQ2.pop();
                while (!PQ1.empty() && -PQ1.top() < k)PQ1.pop();
                if (!PQ2.empty()) {
                    PQ2.pop();
                    r2++;
                }
                if(PQ2.empty())D2[k][i] = min(D2[k][i], r2);
                if (!PQ1.empty()) {
                    PQ1.pop();
                    r1++;
                }
                if (PQ1.empty())D1[k][i] = min(D1[k][i], r1);
                if (k == MX)res = min(res, min(r1,r2));
            }
        }
    }
    printf("%d\n", res);
}
