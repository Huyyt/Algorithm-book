#include <bits/stdc++.h>
#define N 200007
using namespace std;
int n,m,k,a[N],b[N],c[N];
int rt[N],l[N],r[N],npl[N],tag[N];
void pushdown(int x){
    if(l[x])c[l[x]]-=tag[x],tag[l[x]]+=tag[x];
    if(r[x])c[r[x]]-=tag[x],tag[r[x]]+=tag[x];
    tag[x]=0;
}
int Merge(int x,int y){
	if(!x)return y;
	if(!y)return x;
	if(c[x]>c[y])swap(x,y);
	if(tag[x])pushdown(x);
	r[x]=Merge(r[x],y);
	if(npl[l[x]]<npl[r[x]])swap(l[x],r[x]);
	npl[x]=npl[r[x]]+1;
	return x;
}
bool zr[N],vis[N];
int top,s[N],f[N];
int find(int x){return f[x]==x ? x:f[x]=find(f[x]);}
long long solve(int root){
    long long res=0;
    zr[root]=vis[root]=1,top=0;
    for(int i=1;i<=n;++i)f[i]=i;
    for(int i=1;i<=n;++i){
        if(vis[i])continue;
        for(int x=i;;){
            if(!vis[x])vis[x]=1,s[++top]=x;
            int e=rt[x];
            if(!e)return -1;
            res+=c[e],tag[e]+=c[e],c[e]=0;
            x=find(a[e]==x ? b[e]:a[e]);
            if(zr[x]){
                for(;top;--top)zr[s[top]]=1;
                break;
            }
            if(vis[x]){
                for(int y=s[top];y!=x;y=s[--top]){
                    if(tag[rt[x]])pushdown(rt[x]);
                    rt[f[y]=x]=Merge(rt[x],rt[y]);
                }
                while(rt[x] && find(a[rt[x]])==find(b[rt[x]])){
                    if(tag[rt[x]])pushdown(rt[x]);
                    rt[x]=Merge(l[rt[x]],r[rt[x]]);
                }
            }
        }
    }
    return res;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;++i){
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        rt[b[i]]=Merge(rt[b[i]],i);
    }
    printf("%lld",solve(k));
}















#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define fi first
#define se second
using namespace __gnu_pbds;
using namespace std;
typedef long long LL;
typedef pair<int, int> P;

const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;
const LL inf = 1e14 + 5;

template <class T>
inline bool In(T &ret) {
    char c = getchar();
    ret = 0;
    if(c == EOF) return false;
    T flag = 1;
    while (c != '-' && !isdigit(c)) c = getchar();
    if(c == '-') flag = -1, c = getchar();
    while (isdigit(c)) ret = ret * 10 + (c - '0'), c = getchar();
    ret *= flag;
    return true;
}

int p[maxn];
LL val[maxn], lz[maxn];
int ff(int x) {
    if(p[x] != x) {
        int w = ff(p[x]);
        val[x] += lz[p[x]];
        lz[x] += lz[p[x]];
        p[x] = w;
    }
    return p[x];
}

struct node {
    LL w;
    int u, v;
    node(LL _w = 0, int _u = 0, int _v = 0): w(_w), u(_u), v(_v) {};
};
struct cmp {
    bool operator()(node a, node b) {
        ff(a.v), ff(b.v);
        return val[a.v] + a.w > val[b.v] + b.w;
    }
};
__gnu_pbds::priority_queue<node, cmp, pairing_heap_tag> q[maxn];

int vis[maxn], fa[maxn];
node edge[maxn];
vector<int> son[maxn];
stack<int> st;
queue<int> cq;

LL DMST(int rt, int n) {
    int i, m = n, u, v;
    LL ret = 0;
    for(i = 0; i < n; i++) q[i].push(node(inf, (i + 1) % n, i));//额外加无穷大边,使图成为一个强联通
    st.push(0);
    while(true) {
        v = st.top();
        while(!q[v].empty() && ff(q[v].top().u) == v) q[v].pop();
        if(q[v].empty()) break;
        node e = q[v].top();
        ff(e.v);
        edge[v] = e;
        v = ff(e.u);
        if(vis[v]) {
            do {
                u = st.top();
                st.pop();
                fa[u] = p[u] = m;
                son[m].push_back(u);
                lz[u] -= edge[u].w + val[edge[u].v];
                val[u] -= edge[u].w + val[edge[u].v];
                q[m].join(q[u]);
            } while(u != v);
            v = m++;
        }
        st.push(v);
        vis[v] = 1;
    }
    cq.push(rt);
    while(!cq.empty()) {
        u = cq.front();
        cq.pop();
        while(fa[u] != -1) {
            for(auto e : son[fa[u]]) {
                if(e != u) {
                    fa[e] = -1;
                    if(son[e].size()) {
                        edge[edge[e].v] = edge[e];
                        cq.push(edge[e].v);
                    }
                }
            }
            u = fa[u];
        }
    }
    for(i = 0; i < n; i++) {
        if(i != rt) ret += edge[i].w;
    }
    if(ret > inf) ret = -1;
    return ret;
}

void init(int n) {
    n *= 2;
    for(int i = 0; i < n; i++) p[i] = i;
    for(int i = 0; i < n; i++) son[i].clear();
    for(int i = 0; i < n; i++) q[i].clear();
    fill(val, val + n, 0);
    fill(lz, lz + n, 0);
    fill(vis, vis + n, 0);
    fill(fa, fa + n, -1);
    while(!st.empty()) st.pop();
}

int main() {
        int n, m, rt, i, u, v, w;
        In(n), In(m), In(rt);
        init(n);
        rt--;
        for(i = 0; i < m; i++) {
            In(u), In(v), In(w);
            u--, v--;
            q[v].push(node(w, u, v));
        }
        cout << DMST(rt, n) << endl;
    return 0;
}









//Directed_MST
#include<iostream>
using namespace std;
#include<cstdio>
#include<cstring>
#define MAXN 1005
#define INF 0x7f7f7f7f
typedef __int64 type;
struct node { //边的权和顶点
        int u, v;
        type w;
} edge[MAXN * MAXN];
int pre[MAXN], id[MAXN], vis[MAXN], n, m, pos;
type in[MAXN];//存最小入边权,pre[v]为该边的起点
type Directed_MST(int root, int V, int E) {
        type ret = 0;//存最小树形图总权值
        while (true) {
                int i;
                //1.找每个节点的最小入边
                for ( i = 0; i < V; i++) {
                        in[i] = INF;        //初始化为无穷大
                }
                for ( i = 0; i < E; i++) { //遍历每条边
                        int u = edge[i].u;
                        int v = edge[i].v;
                        if (edge[i].w < in[v] && u != v) { //说明顶点v有条权值较小的入边  记录之
                                pre[v] = u;//节点u指向v
                                in[v] = edge[i].w;//最小入边
                                if (u == root) { //这个点就是实际的起点
                                        pos = i;
                                }
                        }
                }
                for ( i = 0; i < V; i++) { //判断是否存在最小树形图
                        if (i == root) {
                                continue;
                        }
                        if (in[i] == INF) {
                                return -1;        //除了根以外有点没有入边,则根无法到达它  说明它是独立的点 一定不能构成树形图
                        }
                }
                //2.找环
                int cnt = 0;//记录环数
                memset(id, -1, sizeof(id));
                memset(vis, -1, sizeof(vis));
                in[root] = 0;
                for ( i = 0; i < V; i++) { //标记每个环
                        ret += in[i];//记录权值
                        int v = i;
                        while (vis[v] != i && id[v] == -1 && v != root) {
                                vis[v] = i;
                                v = pre[v];
                        }
                        if (v != root && id[v] == -1) {
                                for (int u = pre[v]; u != v; u = pre[u]) {
                                        id[u] = cnt;        //标记节点u为第几个环
                                }
                                id[v] = cnt++;
                        }
                }
                if (cnt == 0) {
                        break;        //无环   则break
                }
                for ( i = 0; i < V; i++)
                        if (id[i] == -1) {
                                id[i] = cnt++;
                        }
                //3.建立新图   缩点,重新标记
                for ( i = 0; i < E; i++) {
                        int u = edge[i].u;
                        int v = edge[i].v;
                        edge[i].u = id[u];
                        edge[i].v = id[v];
                        if (id[u] != id[v]) {
                                edge[i].w -= in[v];
                        }
                }
                V = cnt;
                root = id[root];
        }
        return ret;
}
int main() {
        int i;
        while (scanf("%d%d", &n, &m) != EOF) {
                type sum = 0;
                for ( i = 0; i < m; i++) {
                        scanf("%d%d%I64d", &edge[i].u, &edge[i].v, &edge[i].w);
                        edge[i].u++;
                        edge[i].v++;
                        sum += edge[i].w;
                }
                sum ++;
                for ( i = m; i < m + n; i++) { //增加超级节点0,节点0到其余各个节点的边权相同（此题中 边权要大于原图的总边权值）
                        edge[i].u = 0;
                        edge[i].v = i - m + 1;
                        edge[i].w = sum;
                }
                type ans = Directed_MST(0, n + 1, m + n);
                //n+1为总结点数,m+n为总边数
                //ans代表以超级节点0为根的最小树形图的总权值,
                //将ans减去sum,如果差值小于sum,说明节点0的出度只有1,说明原图是连通图
                //如果差值>=sum,那么说明节点0的出度不止为1,说明原图不是连通图
                if (ans == -1 || ans - sum >= sum) {
                        puts("impossible");
                } else {
                        printf("%I64d %d\n", ans - sum, pos - m);
                }
                puts("");
        }
        return 0;
}
