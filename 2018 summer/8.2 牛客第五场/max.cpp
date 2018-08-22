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
	int c,n;scanf("%d%d",&c,&n);
	assert(1<=c&&c<=1000000000);
	assert(1<=n&&n<=1000000000);
	if(n<c){
		printf("-1\n");
		return 0;
	}	
	int d=n/c;
	if(d==1)printf("%lld\n",c*1ll*c);
	else printf("%lld\n",c*1ll*c*(d*1ll*(d-1)));
	return 0;
}

