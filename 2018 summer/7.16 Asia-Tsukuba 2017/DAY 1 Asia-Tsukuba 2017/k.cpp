#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
 
int n,m;
vector<int> G[100001];
vector<int> mdfG[100001];
bool useless[100001];
int cutted[100001];
bool used[100001];
vector<int> route;
int cmp[100001];
int all=0;
int ans=0;
 
set<deque<int> > se;
 
void dfs(int v,int p){
    used[v]=true;
    route.push_back(v);
    for(int i=0;i<mdfG[v].size();i++){
        int next=mdfG[v][i];
        if(p!=next){
            if(!used[next]){
                dfs(next,v);
            }else{
                deque<int> tmp;
                int si=route.size()-1;
                while(route[si]!=next){
                    tmp.push_back(route[si]);
                    si--;
                }
                tmp.push_back(next);
                int best=next;
                for(int j=0;j<tmp.size();j++){
                    best=min(best,tmp[j]);
                }
                while(best!=tmp[0]){
                    int tp=tmp.front();
                    tmp.pop_front();
                    tmp.push_back(tp);
                }
                se.insert(tmp);
            }
        }
    }
    used[v]=false;
    route.pop_back();
}
 
int main(void){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    if(m==n-1){
        printf("0\n");
    }else if(m==n){
        printf("1\n");
    }else{
        queue<int> que;
        memset(cmp,-1,sizeof(cmp));
        for(int i=0;i<n;i++){
            if(G[i].size()==1){
                que.push(i);
                useless[i]=true;
            }
        }
        while(que.size()){
            int v=que.front();
            que.pop();
            for(int i=0;i<G[v].size();i++){
                int next=G[v][i];
                cutted[next]++;
                if(!useless[next] && G[next].size()==cutted[next]+1){
                    useless[next]=true;
                    que.push(next);
                }
            }
        }
        for(int i=0;i<n;i++){
            if(G[i].size()-cutted[i]>=3){
                cmp[i]=all++;
                for(int j=0;j<G[i].size();j++){
                    int next=G[i][j];
                    if(useless[next])continue;
                    if(G[next].size()-cutted[next]<=2){
                        if(cmp[next]==-1){
                            cmp[next]=all++;
                            que.push(next);
                        }
                    }
                }
            }
        }
        if(que.size()==0){
            for(int i=0;i<n;i++){
                if(!useless[i]){
                    que.push(i);
                    cmp[i]=0;
                    all++;
                    break;
                }
            }
        }
        while(que.size()){
            int v=que.front();
            que.pop();
            for(int i=0;i<G[v].size();i++){
                if(cmp[G[v][i]]==-1 && !useless[G[v][i]]){
                    cmp[G[v][i]]=cmp[v];
                    que.push(G[v][i]);
                }
            }
        }
        for(int i=0;i<n;i++){
            if(useless[i])continue;
            for(int j=0;j<G[i].size();j++){
                if(cmp[i]!=cmp[G[i][j]] && !useless[G[i][j]])mdfG[cmp[i]].push_back(cmp[G[i][j]]);
            }
        }
        for(int i=0;i<all;i++){
            sort(mdfG[i].begin(),mdfG[i].end());
            mdfG[i].erase(unique(mdfG[i].begin(),mdfG[i].end()),mdfG[i].end());
        }
        dfs(0,-1);
        printf("%d\n",se.size()/2);
    }
    return 0;
}
