#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cfloat>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <time.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;
 
 
ll table[100001],calc_table[100001];
 
int main(){
 
    int N;
    ll T;
    scanf("%d %lld",&N,&T);
 
    table[0] = 0;
    for(int i = 1; i <= N; i++){
        scanf("%lld",&table[i]);
        table[i] += table[i-1];
    }
 
    printf("%lld\n",T/table[1]+1);
 
    if(N == 1){
        return 0;
    }
 
    calc_table[0] = 0;
    calc_table[1] = 2*table[1];
 
    ll diff;
 
    for(int i = 2; i <= N; i++){
        if(calc_table[i-1] >= table[i]){
            calc_table[i] = calc_table[i-1]+(table[i]-table[i-1]);
        }else{
            calc_table[i] = table[i]+(table[i]-table[i-1]);
        }
        if(table[i] > T){
            printf("1\n");
            continue;
        }
 
        diff = calc_table[i]-table[i];
        printf("%lld\n",(T-table[i])/diff+2);
    }
 
    return 0;
}
