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
const int N=1100000,inf=(int)(1e8);
char ch[N];
char s[N];
int ne[N][26];
int len,n;
int A[26];
void update(){
	for (int i=0;i<26;i++)
		if (A[i]){
			int pre=inf;
			for (int j=len;j>=0&&ne[j][i]>=inf;j--){
				ne[j][i]=pre;
				if (ch[j]-'a'==i) pre=j;
			}
		}
}
void solve(){
	scanf("%d",&n); assert(1<=n&&n<=1000000);
	scanf("%s",ch+1); len=strlen(ch+1);
	assert(1<=len&&len<=1000000);
	for (int i=1;i<=len;i++) assert(ch[i]>='a'&&ch[i]<='z');
	memset(ne,0x3f,sizeof ne);
	memset(A,0x00,sizeof A);
	for (int i=1;i<=len;i++) A[ch[i]-'a']=1;
	int totl=len;
	update(); n--;
	for (;n;n--){
		scanf("%s",s+1);
		memset(A,0x00,sizeof A);
		int now=0,k1=1,l=strlen(s+1); totl+=l;
		assert(1<=l&&l<=1000000);
		for (int i=1;i<=l;i++) assert(s[i]>='a'&&s[i]<='z');

		while (k1<=l&&ne[now][s[k1]-'a']<inf){
			now=ne[now][s[k1]-'a'];
			k1++;
		}
		while (k1<=l){
			ch[++len]=s[k1]; k1++;
		}
		for (int i=1;i<=l;i++) A[s[i]-'a']=1;
		update();
	}
	assert(totl<=1000000);
	for (int i=1;i<=len;i++) putchar(ch[i]);
	puts("");
}
int main(){
	int t; scanf("%d",&t); assert(1<=t&&t<=3);
	for (;t;t--) solve();
	return 0;
}