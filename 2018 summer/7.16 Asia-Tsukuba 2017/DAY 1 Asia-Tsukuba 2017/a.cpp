#include<iostream>
 
#define REP(i,s,n) for(int i=s;i<n;++i)
#define rep(i,n) REP(i,0,n)
 
using namespace std;
 
typedef long long ll;
ll arr[111][2];
 
int main() {
  int l,k;
  cin >> l >> k;
  arr[0][1] = 1LL;
  rep(i,l) {
    rep(j,2) {
      if( arr[i][j] ) {
    int v = ( j + 1 ) & 1;
    if( !v ) arr[i+k][v] += arr[i][j];
    arr[i+1][v] += arr[i][j];
      }
    }
  }
  ll ans = 0;
  REP(i,1,l+1) ans += arr[i][0];
  cout << ans << endl;
  return 0;
}