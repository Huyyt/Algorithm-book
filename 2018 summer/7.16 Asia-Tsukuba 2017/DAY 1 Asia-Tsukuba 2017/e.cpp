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
 
 
#define NUM 2147483647
 
int N;
int* table;
 
void init(int first_N){
    while(N < first_N)N *= 2;
}
 
void update(int loc,int value){
    loc += N-1;
 
    table[loc] = value;
 
    if(N == 1)return;
 
    int parent = (loc-1)/2;
 
    while(true){
        table[parent] = min(table[2*parent+1],table[2*parent+2]);
 
        if(parent == 0)break;
        else{
            parent = (parent-1)/2;
        }
    }
}
 
 
int query(int search_left,int search_right,int node_id,int node_left,int node_right){
 
    if(search_right < node_left || search_left > node_right)return NUM;
 
    if(search_left <= node_left && search_right >= node_right){
        return table[node_id];
    }
 
    int left_min = query(search_left,search_right,2*node_id+1,node_left,(node_left+node_right)/2);
    int right_min = query(search_left,search_right,2*node_id+2,(node_left+node_right)/2+1,node_right);
 
    return min(left_min,right_min);
}
 
char start[500001],goal[500001];
 
int main(){
 
    int first_N,K;
    scanf("%d %d",&first_N,&K);
 
    N = 1;
    init(first_N+1);
 
    table = new int[2*N-1];
 
    for(int i = 0; i <= 2*N-2; i++)table[i] = NUM;
 
    scanf("%s",start);
    scanf("%s",goal);
 
    int* change_ruisekiwa = new int[first_N+1];
 
    change_ruisekiwa[0] = 0;
    for(int i = 0; i < first_N; i++){
        if(goal[i] == goal[i+1]){
            change_ruisekiwa[i+1] = change_ruisekiwa[i];
        }else{
            change_ruisekiwa[i+1] = change_ruisekiwa[i]+1;
        }
    }
 
    int* dp = new int[first_N+1];
 
    dp[0] = 0;
    update(0,0);
 
    for(int i = 1; i <= first_N; i++){
        if(start[i-1] == goal[i-1]){
            dp[i] = dp[i-1];
 
        }else{
 
            dp[i] = (query(max(0,i-K),i-1,0,0,N-1)+change_ruisekiwa[i-1]+3)/2;
        }
        update(i,2*dp[i]-change_ruisekiwa[i]);
    }
 
    printf("%d\n",dp[first_N]);
 
    return 0;
}
