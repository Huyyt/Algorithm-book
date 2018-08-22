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
int main(){
	int n,p2,p3;scanf("%d%d%d",&n,&p2,&p3);	
	assert(1<=n&&n<=1000000000);
	assert(1<=p2&&p2<=1000000000);
	assert(1<=p3&&p3<=1000000000);
	LL ans=1ll<<60;
	rep(i,0,10)ans=min(ans,i*1ll*p2+max(0,(n-i*2+2)/3)*1ll*p3);
	rep(i,0,10)ans=min(ans,i*1ll*p3+max(0,(n-i*3+1)/2)*1ll*p2);
	printf("%lld\n",ans);
	return 0;
}






