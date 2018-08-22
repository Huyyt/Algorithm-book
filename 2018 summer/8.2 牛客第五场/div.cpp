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
using namespace std;

char s[1005];
struct bign{
	int len,a[2005];
	bign(){
		len=0;memset(a,0,sizeof(a));
	}
	bool operator <(const bign &o)const{
		if(len!=o.len)return len<o.len;
		for(int i=len-1;i>=0;i--)if(a[i]!=o.a[i])return a[i]<o.a[i];
		return 0;
	}
	bign operator =(int x){
		memset(a,0,sizeof(a));
		for(len=0;x;x/=10,len++)a[len]=x%10;
		return *this;
	}
	void operator =(const bign &x){
		len=x.len;
		memcpy(a,x.a,sizeof(a));
	}
	void operator =(char *s){
		len=strlen(s);
		for(int i=0;i<len;i++)a[i]=s[len-1-i]-'0';
	}
	bign operator *(const int &x){
		bign ans;
		int g=0,l=len;
		for(int i=0;i<len;i++){
			int t=a[i]*x+g;
			ans.a[i]=t%10;
			g=t/10;
		}
		while(g)ans.a[l++]=g%10,g/=10;
		ans.len=l;
		return ans;	
	}	
	bign operator -(const bign &o){
		bign ans;
		assert(o<(*this));
		int g=0;
		for(int i=0;i<len;i++){
			int t=a[i]-o.a[i]-g;
			if(t<0)t+=10,g=1;else g=0;
			ans.a[i]=t;
		}
		int l=len;
		while(ans.a[l-1]==0)l--;
		ans.len=l;
		return ans;	
	}
	void print(){
		for(int i=len-1;i>=0;i--)printf("%d",a[i]);printf("\n");
	}
}a,u,v,ans;
int cnt=0;
void Main(){
	scanf("%s",s);a=s;
	u=0,v=2;
	while(v<a){
		bign w=v*6-u;
		u=v;v=w;
	}
	ans=v;
	u=0,v=6;
	while(v<a){
		bign w=v*14-u;
		u=v;v=w;
	}
	if(v<ans)ans=v;
	ans.print();
}
int main(){
	Main();
	return 0;
}
