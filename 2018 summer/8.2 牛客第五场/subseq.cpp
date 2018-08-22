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
const int N=510000;
const LL inf=1200000000000000000ll;
int n;LL k;
struct atom{
	LL v;
	inline atom(LL w=0):v(w){}
};
inline atom operator +(const atom &a,const atom &b){return atom(min(a.v+b.v,inf));}
int a[N];
int tmp[N],m;

atom sum[N*30];
int root[N];
int cl[N*30],cr[N*30],tot;

atom segsum(int me,int l,int r,int x,int y){
	if(x>y)return atom(0);
	if(!me)return atom(0);
	if(x<=l&&r<=y)return sum[me];
	int mid=(l+r)>>1;
	atom res=atom(0);
	if(x<=mid)res=res+segsum(cl[me],l,mid,x,y);
	if(y>mid)res=res+segsum(cr[me],mid+1,r,x,y);
	return res;
}
void segadd(int &me,int l,int r,int x,atom v){
	++tot;
	sum[tot]=sum[me]+v;
	cl[tot]=cl[me];
	cr[tot]=cr[me];
	me=tot;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)segadd(cl[me],l,mid,x,v);
	else segadd(cr[me],mid+1,r,x,v);
}
vector<int> ans;
int main(){
	scanf("%d%lld",&n,&k);
	assert(1<=n&&n<=500000);
	assert(1<=k&&k<=1000000000000000000ll);
	rep(i,1,n){
		scanf("%d",&a[i]);
		assert(1<=a[i]&&a[i]<=1000000000);
		tmp[i]=a[i];
	}
	m=n;
	tmp[++m]=(1e9)+7;
	sort(tmp+1,tmp+1+m);
	m=unique(tmp+1,tmp+1+m)-tmp-1;
	rep(i,1,n)a[i]=lower_bound(tmp+1,tmp+1+m,a[i])-tmp;
	segadd(root[n+1],1,m,m,atom(1));
	per(i,n,1){
		root[i]=root[i+1];
		atom gt=segsum(root[i],1,m,a[i]+1,m);
		segadd(root[i],1,m,a[i],gt);
	}
	if(segsum(root[1],1,m,1,m-1).v<k){
		printf("-1\n");
		return 0;
	}
	if(k==1){
		printf("1\n");
		printf("1\n");
		return 0;
	}
	++k;
	ans.clear();
	int pre=0;
	rep(i,1,n)if(a[i]>pre){
		if(k==1)break;
		k--;
		atom gt=segsum(root[i+1],1,m,a[i]+1,m);
		//printf("%d %d %d %lld %lld\n",i,pre,a[i],k,gt.v);
		if(gt.v>=k){
			ans.pb(i);
			pre=a[i];
		}
		else{
			k-=gt.v-1;
		}
	}
	printf("%d\n",(int)ans.size());
	rep(i,0,ans.size()-1)printf("%d%c",ans[i],i+1==ans.size()?'\n':' ');
	return 0;
}



