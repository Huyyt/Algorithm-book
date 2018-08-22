//by yjz
#include<bits/stdc++.h>
using namespace std;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
#define bged(v) (v).begin(),(v).end()
#define foreach(it,s) for(__typeof((s).begin()) it=(s).begin();it!=(s).end();it++)
typedef long long ll;
const int Imx=2147483647;
const ll Lbig=2e18;
const int mod=1e9+7;
int Tn,n,m,K;
int main()
{
	cin>>Tn;
	while(Tn--)
	{
		cin>>n>>m>>K;
		bool f=n%2==1&&m%2==1;
		for(int i=0;i<K;i++)
		{
			int px,py,qx,qy;
			cin>>px>>py>>qx>>qy;
			if((px+py)%2==0&&(qx+qy)%2==0&&(px!=qx||py!=qy))
			{
				f=0;
			}
		}
		cout<<n*m+f<<endl;
	}
	return 0;
}

