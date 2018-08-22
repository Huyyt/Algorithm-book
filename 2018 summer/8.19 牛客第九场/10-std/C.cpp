#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <map>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
const int N=5100;
struct point{
	int x,y;
	void scan(){
		scanf("%d%d",&x,&y);
		x*=2; y*=2;
	}
	long long h(){
		return 1ll*x*1000000000+y;
	}
}A[N];
point operator + (const point &k1,const point &k2){return (point){k1.x+k2.x,k1.y+k2.y};}
point operator - (const point &k1,const point &k2){return (point){k1.x-k2.x,k1.y-k2.y};}
point operator / (const point &k1,int k2){return (point){k1.x/k2,k1.y/k2};}
int operator == (const point &k1,const point &k2){return k1.x==k2.x&&k1.y==k2.y;}
point norm(point k1){
	while (k1.x<=0||(k1.x>0&&k1.y<0)){
		swap(k1.x,k1.y); k1.x=-k1.x;
	}
	return k1;
}
const int Mo=1e7+19,key=10007,M=7000000,mo=998244353,inv2=(mo+1)/2,inv4=748683265;
int *fir,len,*ne,n,*pd,sign,c,*f,C[N];
pair<point,point>* w;
int I[N],nI[N];
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo;
		k2>>=1; k1=1ll*k1*k1%mo;
	}
	return k3;
}
int getloc(pair<point,point> k1){
	int k=(k1.fi.h()%Mo*key+k1.se.h())%Mo;
	if (k<0) k+=Mo;
	if (pd[k]!=sign){
		pd[k]=sign; fir[k]=0;
	}
	for (int i=fir[k];i;i=ne[i])
		if (w[i]==k1) return i;
	len++; ne[len]=fir[k]; fir[k]=len; f[len]=0; w[len]=k1;
	return len;
}
void insert(point k1,point k2){
	int where=getloc(mp(k1,k2));
	f[where]+=2;
	if (f[where]==4){
		where=getloc(mp(k1,(point){0,0}));
		f[where]+=4;
	}
}
int ans;
int num[N][3];
int getw1(int size){
	return C[size];
}
int getw4(int size){
	//cout<<size<<" "<<2ll*C[size]<<" "<<C[(size>>1)+(size&1)]<<" "<<C[(size>>2)+(size&1)]<<endl;
	return (C[size]+C[(size>>1)+(size&1)]+2ll*C[(size>>2)+(size&1)])%mo*inv4%mo;
}
int getw2(int size){
	return (1ll*C[size]+C[(size>>1)+(size&1)])%mo*inv2%mo;
}
int CC(int k1,int k2){
	return 1ll*I[k1]*nI[k2]%mo*nI[k1-k2]%mo;
}
void calc4(int k1){
	int ans=0;
	for (int i=0;i<=(k1&1);i++)
		for (int j=0;j<=k1;j+=4)
			if (i+j>1){
				int way=CC(k1/4,j/4);
				num[i+j][2]=(num[i+j][2]+way)%mo;
				num[i+j][1]=(num[i+j][1]-way+mo)%mo;
			}
}
void calc2(int k1){
	for (int i=0;i<=(k1&1);i++)
		for (int j=0;j<=k1;j+=2)
			if (i+j>1){
				int way=CC(k1/2,j/2);
				num[i+j][1]=(num[i+j][1]+way)%mo;
				num[i+j][0]=(num[i+j][0]-way+mo)%mo;
			}
}
map<pair<int,int>,int>MM;
void solve(){
	scanf("%d%d",&n,&c); ans=0; C[0]=1;
	assert(1<=n&&n<=3000&&1<=c&&c<=1000000000);
	for (int i=1;i<=n;i++) C[i]=1ll*C[i-1]*c%mo;
	MM.clear();
	for (int i=1;i<=n;i++){
		A[i].scan(); assert(MM[make_pair(A[i].x,A[i].y)]==0);
		MM[make_pair(A[i].x,A[i].y)]=1;
	}
	len=0; sign++;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++){
			assert(A[i].x!=A[j].x||A[i].y!=A[j].y);
			point o=(A[i]+A[j])/2;
			point del=A[i]-o;
		//	cout<<i<<" "<<j<<" "<<o.x<<" "<<o.y<<" "<<norm(del).x<<" "<<norm(del).y<<endl;
			insert(o,norm(del));
		}
	for (int i=1;i<=n;i++){
		int where=getloc(mp(A[i],(point){0,0})); f[where]++;
	}
	int ans=0;
	memset(num,0x00,sizeof num);
	for (int i=1;i<=n;i++) num[i][0]=CC(n,i);
	for (int i=1;i<=len;i++)
		if (w[i].se==(point){0,0}) calc4(f[i]);
	len=0; sign++;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++){
			point o=(A[i]+A[j])/2;
			int where=getloc(mp(o,(point){0,0})); f[where]+=2;
		}
	for (int i=1;i<=n;i++){
		int where=getloc(mp(A[i],(point){0,0})); f[where]++;
	}
	for (int i=1;i<=len;i++) calc2(f[i]);
	/*for (int i=1;i<=n;i++){
		for (int j=0;j<3;j++) cout<<num[i][j]<<" "; cout<<endl;
	}*/
	for (int i=1;i<=n;i++)
		ans=(ans+1ll*getw1(i)*num[i][0]%mo+1ll*getw2(i)*num[i][1]%mo+1ll*getw4(i)*num[i][2])%mo;
	printf("%d\n",ans);
}
int main(){
	w=new pair<point,point>[M];
	fir=new int[Mo];
	ne=new int[M];
	pd=new int[Mo];
	f=new int[M];
	int t; scanf("%d",&t); assert(1<=t&&t<=3);
	I[0]=1;
	for (int i=1;i<=5000;i++) I[i]=1ll*I[i-1]*i%mo;
	for (int i=0;i<=5000;i++) nI[i]=quick(I[i],mo-2);
	for (;t;t--) solve();
	return 0;
}
