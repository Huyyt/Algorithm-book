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
int seed;
int getrand(){
	return seed=(1ll*seed*100000005+20150609)%998244353;
}
const int N=110000,M=40;
int n,m,x[N];
struct tree{
	int l,r,size;
}t[N*20];
int len,root[N],a[N],ra[N];
__int128 w[N];
int insert(int k1,int k2,int k3,int k4){
	int now=++len; t[now]=t[k1]; t[now].size+=1;
	int mid=(k2+k3)>>1; if (k2==k3) return now;
	if (mid>=k4) t[now].l=insert(t[k1].l,k2,mid,k4);
	else t[now].r=insert(t[k1].r,mid+1,k3,k4);
	return now;
}
pair<int,__int128> getall(int k1,int k2,int k3,int k4,int K){
	if (k3==k4){
		return mp(a[k3],w[a[k3]]);
	}
	int now=t[t[k1].l].size-t[t[k2].l].size,mid=(k3+k4)>>1;
	if (now>=K) return getall(t[k1].l,t[k2].l,k3,mid,K);
	else return getall(t[k1].r,t[k2].r,mid+1,k4,K-now);
}
__int128 get(int l,int len){
	return w[l]>>(M-len);
}
__int128 get(int s,int l,int r,int now){
	int k1=r-s+1,k2=now-k1;
	return (get(s,k1)<<k2)+get(l,k2);
}
int b[N];
void mysort(int k1,int k2,int l,int r,int d){
	if (k1>=k2) return;
	if (d==r-l+1){
		sort(b+k1,b+k2+1); return;
	}
	int M=k1-1;
	for (int i=k1;i<=k2;i++){
		int now=(b[i]-l+d)%(r-l+1)+l;
		if (x[now]==0){
			M++; swap(b[M],b[i]);
		}
	}
	mysort(k1,M,l,r,d+1);
	mysort(M+1,k2,l,r,d+1);
}
struct bwtgen{
	int l,r,mid,lim,nowK,s;
	vector<pair<int,__int128> >A;
	bwtgen(int _l,int _r){
		l=_l; r=_r; mid=r-M+1;
		if (mid>=l) lim=t[root[mid]].size-t[root[l-1]].size;
		else lim=0;
		int len=0;
		for (int i=max(l,mid+1);i<=r;i++) b[++len]=i;
		mysort(1,len,l,r,0); A.clear();
		for (int i=1;i<=len;i++) A.push_back(mp(b[i],get(b[i],l,r,min(r-l+1,M))));
		for (int i=1;i<(int)(A.size());i++) assert(A[i-1].se<=A[i].se);
		nowK=1; s=0;
	}
	int getnext(){
		pair<int,__int128> w1,w2,ans;
		if (s==(int)(A.size())) w1=mp(-1,0); else w1=A[s];
		if (nowK>lim) w2=mp(-1,0); else w2=getall(root[mid],root[l-1],1,n,nowK);
		if (w1.fi==-1&&w2.fi==-1) return -1;
		if (w1.fi==-1){
			nowK++; ans=w2;
		} else if (w2.fi==-1){
			s++; ans=w1;
		} else if (w1.se<w2.se||(w1.se==w2.se&&w1.fi<w2.fi)){
			s++; ans=w1;
		} else nowK++,ans=w2;
		if (ans.fi==l) return x[r]; else return x[ans.fi-1];
	}	
};
int ma=0;
int check(bwtgen k1,bwtgen k2){
	int t=0;
	while (1){
		t++; ma=max(ma,t);
		int w1=k1.getnext(),w2=k2.getnext();
		if (w1==-1&&w2==-1) return 0;
		if (w1==-1) return -1;
		if (w2==-1) return 1;
		if (w1<w2) return -1; else if (w1>w2) return 1;
	}
}
int compare(int k1,int k2) {
	return w[k1]<w[k2];
}
int checkcorrect(int l,int r){
	bwtgen w(l,r);
	vector<string>A;
	for (int i=l;i<=r;i++){
		string s=""; int now=i;
		for (int j=1;j<=r-l+1;j++){
			s+='0'+x[now];
			if (now==r) now=l; else now++;
		}
		A.push_back(s);
	}
	sort(A.begin(),A.end());
	// cout<<"fa "<<l<<" "<<r<<endl;
	for (int i=0;i<(int)(A.size());i++){
		int k1=w.getnext(),k2=A[i][r-l]-'0';
		// cout<<k1<<" "<<k2<<endl;
		assert(k1==k2);
	}
    return 0;
}
void solve(){
	scanf("%d%d%d",&n,&m,&seed);
	assert(1<=n&&n<=100000&&1<=m&&m<=100000&&0<=seed&&seed<=1000000000);
	for (int i=1;i<=n;i++) x[i]=getrand()%2;
	// for (int i=1;i<=n;i++) cerr<<x[i]; cerr<<endl;
	len=0;
	for (int i=1;i<=n;i++){
		w[i]=0;
		for (int j=1;j<=M;j++) w[i]=w[i]*2+x[i+j-1];
	}
	for (int i=1;i<=n;i++) a[i]=i;
	sort(a+1,a+n+1,compare);
	int pre=0;
	for (int i=1;i<=n;i++)
		if (a[i]<=n-M+1){
			if (pre) assert(w[a[i]]!=w[pre]);
			pre=a[i];
		}
	for (int i=1;i<=n;i++) ra[a[i]]=i;
	for (int i=1;i<=n;i++) root[i]=insert(root[i-1],1,n,ra[i]);
	int ti=0;
	for (;m;m--){
		ti++;
		int l1=getrand()%n+1,r1=getrand()%n+1,l2=getrand()%n+1,r2=getrand()%n+1;
		if (l1>r1) swap(l1,r1); if (l2>r2) swap(l2,r2);
		// cerr<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<endl;
		// checkcorrect(l1,r1); checkcorrect(l2,r2);
		bwtgen A(l1,r1),B(l2,r2);
		printf("%d\n",check(A,B));
	}
}
int main(){
	int t; scanf("%d",&t);
	assert(1<=t&&t<=3);
	for (;t;t--) solve();
	//cerr<<ma<<endl;
	return 0;
}
