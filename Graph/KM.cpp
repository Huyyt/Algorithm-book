//KM
�����ͼ�����ƥ����һ���ǳ�������㷨, ��������O(N ^ 3), �����KM�㷨�����㷨�������£�
1.����ѡ�񶥵������ٵ�ΪX������ʼʱ��X����ÿһ���������ö��꣬�����ֵΪ�õ���������ߵ�Ȩֵ��Y���Ķ��㶥��Ϊ0��
2.����X���е�ÿ�����㣬�������ͼ�������������㷨��һ������·�������û���ҵ������޸Ķ��꣬���������ͼ������������·������ÿ���㶼�ҵ�����·��ʱ����ʱ��ζ��ÿ���㶼��ƥ���У����ҵ��˶���ͼ���걸ƥ�䡣���걸ƥ�伴Ϊ����ͼ�����ƥ�䡣
ʲô�������ͼ�أ���Ϊÿ��������һ�����꣬�������ѡ���Ȩ�������˵�Ķ���֮�͵ıߣ�������ɵ�ͼ��Ϊ�����ͼ��
�����X���е�ĳ����Xi�����������ͼ��û���ҵ�����·��������������޸Ķ�����أ��������û���ҵ�����·����������һ���ҵ����������Xi������������X����ƥ�����δƥ��߽�����ֵ�·�������ҳ�֮Ϊ�����������ǽ���������X���Ķ��㶥���ȥһ��ֵd��������������Y���Ķ��㶥�����һ��ֵd�����ֵ����Ҫ������μ��㡣��ô���ǻᷢ�֣�
���˶��ڽ������еı�(i, j)���䶥���û�б仯��Ҳ����˵����ԭ�����������ͼ�����������������ͼ��
���˶����ڽ������еı�(i, j)���䶥��Ҳû�б仯��Ҳ����˵����ԭ�����ڣ������ڣ������ͼ�����������ڣ������ڣ������ͼ��
X�˲��ڽ������У�Y���ڽ������еı�(i, j)�����Ķ���ͻ�������ԭ�������������ͼ�������Բ����������ͼ��
X���ڽ������У�Y�˲��ڽ������еı�(i, j), ���Ķ���ͻ��С��Ҳ��˵����ԭ�������������ͼ�����ڿ��ܽ����������ͼ�����ʹ�����ͼ�õ�������
�����޸Ķ����Ŀ�ľ���Ҫ���������ͼ��Ϊ�˱�֤������һ���߽��������ͼ�����ǿ����ڽ������ı���Ѱ�Ҷ�������Ȩ֮����С�ı�, �����ǰ��˵��dֵ����������������X���Ķ����ȥd��������������Y���Ķ������d������Ա�֤������һ����������������ͼ��
3.��X�������ж��㶼�ҵ�������·�������ҵ����걸ƥ�䣬���걸ƥ�伴Ϊ���ƥ�䡣
�����ͼ����������
������ʱ�̣������ͼ�ϵ����Ȩƥ��һ��С�ڵ��������ͼ�Ķ���͡�
������ʱ�̣������ͼ�Ķ���ͼ�Ϊ���ж���Ķ���͡�
���������ͼ�������ͼ�Ķ���ͽ����С��
�������ͼ�����ƥ��Ϊԭͼ���걸ƥ��ʱ��ƥ��ߵ�Ȩֵ�͵������ж���Ķ���ͣ���ƥ�伴Ϊ���ƥ��
���Ͼ���KM�㷨�Ļ���˼·���������ص�ʵ�ַ�����ʱ�临�Ӷ�ΪO(n4)������Ҫ��O(n)������·��ÿ�����������Ҫ�޸�O(n)�ζ��꣬ÿ���޸Ķ���ʱ����Ҫö�ٱ�����dֵ�����Ӷ�ΪO(n2)��ʵ����KM�㷨�ĸ��Ӷ��ǿ�������O(n3)�ġ����Ǹ�ÿ��Y����һ�����ɳ���������slack��
ÿ�ο�ʼ������·ʱ��ʼ��Ϊ�������Ѱ������·�Ĺ����У�����(i, j)ʱ����������������ͼ�У�����slack[j]���ԭֵ�� A[i] + B[j] - w[i, j]�Ľ�Сֵ�����������޸Ķ���ʱ��ȡ���в��ڽ������е�Y�����slackֵ�е���Сֵ��Ϊdֵ���ɡ�����Ҫע��һ�㣺�� �Ķ����Ҫ�����в��ڽ������е�Y�����slackֵ����ȥd
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
using namespace std;
typedef long long ll;
const int maxn = 300 + 10;
const int INF = 0x3f3f3f3f;
int wx[maxn], wy[maxn];//ÿ����Ķ���ֵ����Ҫ���ݶ���ͼ���������
int cx[maxn], cy[maxn];//ÿ������ƥ��ĵ�
int visx[maxn], visy[maxn];//ÿ�����Ƿ��������·
int cntx, cnty;//�ֱ���X��Y�ĵ���
int Map[maxn][maxn];//����ͼ�ߵ�Ȩֵ
int slack[maxn];//��Ȩ�Ͷ�����С�Ĳ�ֵ
bool dfs(int u) { //����DFS�Ķ���X���ĵ�
        visx[u] = 1;//��ǽ�������·
        for (int v = 1; v <= cnty; v++) {
                if (!visy[v] && Map[u][v] != INF) { //���Y���ĵ㻹û��������·,���Ҵ���·��
                        int t = wx[u] + wy[v] - Map[u][v];
                        if (t == 0) { //tΪ0˵���������ͼ
                                visy[v] = 1;//��������·

                                //���Y���ĵ㻹δ����ƥ��
                                //�����Ѿ�������ƥ�䣬���Դ�ԭ����ƥ�䷴���ҵ�����·
                                //�ǾͿ��Խ���ƥ��
                                if (cy[v] == -1 || dfs(cy[v])) {
                                        cx[u] = v;
                                        cy[v] = u;//����ƥ��
                                        return 1;
                                }
                        } else if (t > 0) { //�˴�tһ���Ǵ���0����Ϊ����֮��һ��>=��Ȩ
                                slack[v] = min(slack[v], t);
                                //slack[v]�����Y���ĵ���Ҫ��������ͼ����ֵ��С���Ӷ���
                        }
                }
        }
        return false;
}
int KM() {
        memset(cx, -1, sizeof(cx));
        memset(cy, -1, sizeof(cy));
        memset(wx, 0, sizeof(wx));//wx�Ķ���Ϊ�õ����ӵıߵ����Ȩֵ
        memset(wy, 0, sizeof(wy));//wy�Ķ���Ϊ0
        for (int i = 1; i <= cntx; i++) { //Ԥ���������ֵ
                for (int j = 1; j <= cnty; j++) {
                        if (Map[i][j] == INF) {
                                continue;
                        }
                        wx[i] = max(wx[i], Map[i][j]);
                }
        }
        for (int i = 1; i <= cntx; i++) { //ö��X���ĵ�
                memset(slack, INF, sizeof(slack));
                while (1) {

                        memset(visx, 0, sizeof(visx));
                        memset(visy, 0, sizeof(visy));
                        if (dfs(i)) {
                                break;        //�Ѿ�ƥ����ȷ
                        }


                        int minz = INF;
                        for (int j = 1; j <= cnty; j++)
                                if (!visy[j] && minz > slack[j])
                                        //�ҳ���û�����ĵ��У���Ҫ��������ͼ����С�������ӵĶ���ֵ
                                {
                                        minz = slack[j];
                                }
                        //��ȫ�ֱ�����ͬ���ǣ�ȫ�ֱ�����ÿ��whileѭ���ж���Ҫ��ֵ��INF��ÿ������������е����Сֵ
                        //��slack������ÿ��while����ͳ�ʼ���ã�ÿ��whileѭ��slack�����ÿ��ֵ�����õ�
                        //��һ������·�������slackֵ���׼ȷ��ѭ��������ȫ�ֱ�������
                        //��δƥ�䣬��X���Ķ����ȥminz��Y���Ķ������minz
                        for (int j = 1; j <= cntx; j++)
                                if (visx[j]) {
                                        wx[j] -= minz;
                                }
                        for (int j = 1; j <= cnty; j++)
                                //�޸Ķ����Ҫ�����в��ڽ������е�Y�����slackֵ����ȥminz
                                if (visy[j]) {
                                        wy[j] += minz;
                                } else {
                                        slack[j] -= minz;
                                }
                }
        }

        int ans = 0;//����ͼ����ƥ��Ȩֵ
        for (int i = 1; i <= cntx; i++)
                if (cx[i] != -1) {
                        ans += Map[i][cx[i]];
                }
        return ans;
}
int n, k;
int main() {
        while (scanf("%d", &n) != EOF) {
                for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++) {
                                scanf("%d", &Map[i][j]);
                        }
                }
                cntx = cnty = n;
                printf("%d\n", KM());
        }
        return 0;
}

#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int N = 210;
int val[N][N];
LL lx[N], ly[N];
int linky[N];
LL pre[N];
bool vis[N];
bool visx[N], visy[N];
LL slack[N];
int n;
void bfs(int k) {
        LL px, py = 0, yy = 0, d;
        memset(pre, 0, sizeof(LL) * (n + 2));
        memset(slack, inf, sizeof(LL) * (n + 2));
        linky[py] = k;
        do {
                px = linky[py], d = INF, vis[py] = 1;
                for (int i = 1; i <= n; i++)
                        if (!vis[i]) {
                                if (slack[i] > lx[px] + ly[i] - val[px][i]) {
                                        slack[i] = lx[px] + ly[i] - val[px][i], pre[i] = py;
                                }
                                if (slack[i] < d) {
                                        d = slack[i], yy = i;
                                }
                        }
                for (int i = 0; i <= n; i++)
                        if (vis[i]) {
                                lx[linky[i]] -= d, ly[i] += d;
                        } else {
                                slack[i] -= d;
                        }
                py = yy;
        } while (linky[py]);
        while (py) {
                linky[py] = linky[pre[py]], py = pre[py];
        }
}
void KM() {
        memset(lx, 0, sizeof(int) * (n + 2));
        memset(ly, 0, sizeof(int) * (n + 2));
        memset(linky, 0, sizeof(int) * (n + 2));
        for (int i = 1; i <= n; i++) {
                memset(vis, 0, sizeof(bool) * (n + 2)), bfs(i);
        }
}
int main() {
        int T;
        scanf("%d", &T);
        for (int _i = 1; _i <= T; _i++) {
                scanf("%d", &n);
                for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++) {
                                scanf("%d", &val[i][j]);
                                val[i][j] = -val[i][j];
                        }
                }
                KM();
                LL ans = 0;
                for (int i = 1; i <= n; ++i) {
                        ans += lx[i] + ly[i];
                }
                printf("Case #%d: %I64d\n", _i, -ans);
        }
        return 0;
}
