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
const int N=110000;
const int P=998244353;
int n;
pii a[N];
inline bool cmpy(const pii &x,const pii &y){
	if(x.se!=y.se)return x.se<y.se;
	return x.fi<y.fi;
}
int tmp[N*2],m;
int cnt[N];
void add(int x){
	for(;x<=m;x+=(x&(-x)))cnt[x]++;
}
int ask(int x){
	int ans=0;
	for(;x;x-=(x&(-x)))ans+=cnt[x];
	return ans;
}
int pre[N],suf[N];
map<pii,bool>hv;
int main(){
	scanf("%d",&n);
	assert(1<=n&&n<=100000);
	rep(i,1,n){
		scanf("%d%d",&a[i].fi,&a[i].se);
		assert(1<=a[i].fi&&a[i].fi<=1000000000);
		assert(1<=a[i].se&&a[i].se<=1000000000);
		assert(!hv[a[i]]);
		hv[a[i]]=1;
		tmp[++m]=a[i].fi;
	}
	sort(tmp+1,tmp+1+m);
	m=unique(tmp+1,tmp+1+m)-tmp-1;
	rep(i,1,n){
		a[i].fi=lower_bound(tmp+1,tmp+1+m,a[i].fi)-tmp;
	}
	sort(a+1,a+1+n,cmpy);
	int ans=n;
	rep(i,1,n){
		int j=i;
		while(j<n&&a[j+1].se==a[i].se)++j;
		ans=(ans+(j-i+1)*1ll*(i-1))%P;
		rep(k,i,j){
			pre[k]=ask((m-a[k].fi+1)-1);
		}
		rep(k,i,j)add(m-a[k].fi+1);
		i=j;
	}
	memset(cnt,0,sizeof cnt);
	per(i,n,1){
		int j=i;
		while(j>1&&a[j-1].se==a[i].se)--j;
		rep(k,j,i){
			suf[k]=ask(m-a[k].fi+1-1);
		}
		rep(k,j,i)add(m-a[k].fi+1);
		i=j;
	}
	rep(i,1,n)ans=(ans+pre[i]*1ll*suf[i])%P;
	printf("%d\n",ans);
	return 0;
}






