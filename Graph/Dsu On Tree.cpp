#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int maxn=100010;
struct node{
    int to,nxt;
}t[maxn];int head[maxn],tot=0;
inline void addedge(int x,int y){
    t[++tot].to=y;
    t[tot].nxt=head[x];
    head[x]=tot;
}

int c[maxn],size[maxn],son[maxn],cnt[maxn],ans[maxn];
//  color   size       重儿子    计数器  

void dfs1(int x,int fa){
    size[x]=1;
    for(int i=head[x];i;i=t[i].nxt){
        int to=t[i].to;
        if(to!=fa){
            dfs1(to,x);
            size[x]+=size[to];
            if(size[to]>size[son[x]])
                son[x]=to;
        }
    }
}
//                    重儿子    保留答案
int dfs2(int u,int fa,int isson,int keep){
    if(keep){
        for(int i=head[u];i;i=t[i].nxt){
            int to=t[i].to;
            if(to!=fa&&to!=son[u]){
                dfs2(to,u,0,1);
            }
        }
    }
    int tmp=0;
    if(!keep&&son[u])tmp+=dfs2(son[u],u,1,0);
    else if(son[u]) tmp+=dfs2(son[u],u,1,1);
    for(int i=head[u];i;i=t[i].nxt){
        int v=t[i].to;
        if(v!=fa&&v!=son[u]){
            tmp+=dfs2(v,u,0,0);
        }
    }
    if(!cnt[c[u]]){
        tmp++;
    }
    cnt[c[u]]++;
    if(keep)ans[u]=tmp;
    if(keep&&!isson) memset(cnt,0,sizeof(cnt));
    return tmp;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(x,y);
        addedge(y,x);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&c[i]);
    }
    dfs1(1,0);
    dfs2(1,0,1,1);
    int m;
    scanf("%d",&m);
    while(m--){
        int x;
        cin>>x;
        cout<<ans[x]<<endl;
    }
    return 0;
}
