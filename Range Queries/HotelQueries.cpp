#include <bits/stdc++.h>
using namespace std;
#define NMAX 200005
#define INF 1e18
#define int long long
#define m (l+r)/2
 
int N;
int v[NMAX];
int t[NMAX<<2]; //max ST
 
void build(int i, int l, int r){
    if(l==r){
        t[i] = v[l];
        return;
    }
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    t[i] = max(t[i*2],t[i*2+1]);
}
 
void point_update(int i, int l, int r, int ql, int qr, int x){ //ql == qr
    if(ql<=l&&r<=qr){
        t[i] -= x;
        return;
    }
    if(ql>r || qr<l) return;
    point_update(i*2,l,m,ql,qr,x);
    point_update(i*2+1,m+1,r,ql,qr,x);
    t[i] = max(t[i*2],t[i*2+1]);
}
 
int smallest_index(int i, int l, int r, int x){
    if(l==r){
        point_update(1,1,N,l,l,x);
        return l; //retorna a posicao
    } 
    if(t[i*2]>=x) return smallest_index(i*2,l,m,x);
    else return smallest_index(i*2+1,m+1,r,x);
}
 
int32_t main(){
    int M,x;
    cin >> N >> M;
    for(int i=1;i<=N;i++) cin >> v[i];
    build(1,1,N);
    while(M--){
        cin >> x;
        if(x>t[1]) cout << 0 << " ";
        else cout << smallest_index(1,1,N,x) << " ";
    }
}
/*
8 5
3 2 4 1 5 5 2 6
2 4
 
4 4 7 1 1
resp: 3 5 0 1 1
*/