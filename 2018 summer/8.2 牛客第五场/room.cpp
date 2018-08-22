#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<iostream>
#include<assert.h>
#include<queue>
#include<string>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=205;
int x[N][4];
int y[N][4];
int n;
namespace cf{
	int head[N*2],np[N*N*10],p[N*N*10],flow[N*N*10],cost[N*N*10],tot;
	int S,T;
	void init(){
		tot=1;
	}
	void add(int a,int b,int f,int c){
		++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;flow[tot]=f;cost[tot]=c;
		++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;flow[tot]=0;cost[tot]=-c;
	}
	bool inq[N*2];
	int q[N*N*N*2];
	int dis[N*2];
	int pre[N*2];
	int preu[N*2];
	int spfa(){
		q[q[0]=1]=S;
		rep(i,1,T)dis[i]=-(1<<30),pre[i]=preu[i]=-1;
		dis[S]=0;inq[S]=1;
		rep(i,1,q[0]){
			int x=q[i];
			for(int u=head[x];u;u=np[u])if(flow[u])if(dis[p[u]]<dis[x]+cost[u]){
				dis[p[u]]=dis[x]+cost[u];
				pre[p[u]]=x;
				preu[p[u]]=u;
				if(!inq[p[u]]){
					inq[p[u]]=1;
					q[++q[0]]=p[u];
				}
			}
			inq[x]=0;
		}
		return pre[T];
	}
	int maxcostflow(){
		int ans=0;
		while(spfa()!=-1){
			int mi=1e9;
			for(int x=T;x!=S;x=pre[x])mi=min(mi,flow[preu[x]]);
			ans+=mi*dis[T];
			for(int x=T;x!=S;x=pre[x]){
				flow[preu[x]]-=mi;
				flow[preu[x]^1]+=mi;
			}
		}
		return ans;
	}
};
int get(int a,int b){
	int ans=0;
	rep(i,0,3){
		rep(j,0,3)if(x[a][i]==y[b][j]){
			++ans;
			break;
		}
	}
	return ans;
}
bool ct[405];
int main(){
	scanf("%d",&n);
	assert(1<=n&&n<=100);
	rep(i,1,n){
		rep(j,0,3){
			scanf("%d",&x[i][j]);
			assert(!ct[x[i][j]]);
			assert(1<=x[i][j]&&x[i][j]<=4*n);
			ct[x[i][j]]=1;
		}
	}
	memset(ct,0,sizeof ct);
	rep(i,1,n){
		rep(j,0,3){
			scanf("%d",&y[i][j]);
			assert(!ct[y[i][j]]);
			assert(1<=y[i][j]&&y[i][j]<=4*n);
			ct[y[i][j]]=1;
		}
	}
	cf::S=2*n+1;
	cf::T=2*n+2;
	cf::init();
	rep(i,1,n)cf::add(cf::S,i,1,0);
	rep(i,1,n)cf::add(i+n,cf::T,1,0);
	rep(i,1,n)rep(j,1,n)cf::add(i,j+n,1,get(i,j));
	printf("%d\n",4*n-cf::maxcostflow());
	return 0;
}






