#include <bits/stdc++.h>
using namespace std;
#define NMAX 200005
#define INF 999999999
#define int long long
#define m (l+r)/2
 
int v[NMAX];
int t[NMAX<<2];
 
void build(int i, int l, int r){
    if(l==r){
        t[i] = v[l];
        return;
    }
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    t[i] = t[i*2] + t[i*2+1];
}
 
void point_update(int i, int l, int r, int ql, int qr, int x){
    if(ql<=l&&r<=qr){
        t[i] = x;
        return;
    }
    if(ql>r || qr<l) return;
    point_update(i*2,l,m,ql,qr,x);
    point_update(i*2+1,m+1,r,ql,qr,x);
    t[i] = t[i*2] + t[i*2+1];
}
 
int range_query(int i, int l, int r, int ql, int qr){
    if(ql<=l&&r<=qr) return t[i];
    if(ql>r || qr<l) return 0;
    int LChild = range_query(i*2,l,m,ql,qr);
    int RChild = range_query(i*2+1,m+1,r,ql,qr);
    return LChild + RChild;
}
 
int32_t main(){
    int N,Q;
    cin >> N >> Q;
    for(int i=1;i<=N;i++) cin >> v[i];
    build(1,1,N);
    int op,a,b;
    while(Q--){
        cin >> op >> a >> b;
        if(op==1) point_update(1,1,N,a,a,b);
        else cout << range_query(1,1,N,a,b) << '\n';
    }
}