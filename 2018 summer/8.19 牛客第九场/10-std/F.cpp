#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
const int N=510,mo=998244353;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
int n,A[N],a[N][N],cur,pd[N],l[N][N];
long long d[N][N];
int compare(int k1,int k2){
	return d[cur][k1]<d[cur][k2];
}
void solve(){
	scanf("%d",&n); assert(1<=n&&n<=500);
	memset(d,0x3f,sizeof d);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) scanf("%lld",&d[i][j]),l[i][j]=d[i][j];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) assert(d[i][j]==d[j][i]);
	for (int i=1;i<=n;i++) assert(d[i][i]==0);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			assert(d[i][j]==d[j][i]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				d[j][k]=min(d[j][k],d[j][i]+d[i][k]);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) a[i][j]=j;
		cur=i;
		sort(a[i]+1,a[i]+n+1,compare);
	}
	int ans=0;
	for (int u=1;u<=n;u++)
		for (int v=u+1;v<=n;v++){
			memset(pd,0x00,sizeof pd);
			int k1=1,k2=1,len=0;
			while (k1<=n&&k2<=n){
				int now=0;
				if (d[u][a[u][k1]]<d[v][a[v][k2]]){
					now=a[u][k1]; k1++;
				} else now=a[v][k2],k2++;
				if (pd[now]==0){
					pd[now]=1; A[++len]=now;
				}
			}
			for (int i=k1;i<=n;i++){
				int now=a[u][i];
				if (pd[now]==0) pd[now]=1,A[++len]=now;
			}
			for (int i=k2;i<=n;i++){
				int now=a[v][i];
				if (pd[now]==0) pd[now]=1,A[++len]=now;
			}
		//	cout<<u<<" "<<v<<endl;
		//	for (int i=1;i<=n;i++) cout<<min(d[u][A[i]],d[v][A[i]])<<" "; cout<<endl;
			for (int i=n;i;i--) ans=(ans+min(d[u][A[i]],d[v][A[i]])%mo*(n-i))%mo;
		}
	int all=n*(n-1)/2;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			ans=(ans+1ll*(all-1)*l[i][j])%mo;
	printf("%d\n",ans);
}
int main(){
	int t; scanf("%d",&t); assert(1<=t&&t<=3);
	for (;t;t--) solve();
}
