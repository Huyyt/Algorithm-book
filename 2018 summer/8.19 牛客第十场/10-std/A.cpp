#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
int A[110000];
const int mo=998244353;
int main(){
	int t; scanf("%d",&t);
	for (;t;t--){
		int n,m; scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) scanf("%d",&A[i]);
		for (int i=1;i<=n;i++) A[i]=(A[i]+A[i-1])%mo;
		int key=1;
		for (int i=1;i<=n;i++) key=key*2%mo;
		int key2=1;
		for (int i=1;i<=m;i++) key2=1ll*key*key2%mo;
		for (;m;m--){
			int k1,k2,k3; scanf("%d%d%d",&k1,&k2,&k3);
			if (k1==1) continue;
			else {
				int ans=1ll*(A[k3]-A[k2-1]+mo)*key2%mo;
				printf("%d\n",ans);
			}
		}
	}
}