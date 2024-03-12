#include <bits/stdc++.h>
using namespace std;
#define NMAX 200005
#define INF 1e18
#define int long long
#define m (l+r)/2
 
int v[NMAX];
int t[NMAX<<2];
int lz[NMAX<<2];
 
void push(int i, int l, int r){
    if(lz[i]){
        t[i] += lz[i]*(r-l+1);
        if(l!=r){
            lz[i*2] += lz[i];
            lz[i*2+1] += lz[i];
        }
        lz[i] = 0;
    }
}
 
void build(int i, int l, int r){
    if(l==r){
        t[i] = v[l];
        return;
    }
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    t[i] = t[i*2] + t[i*2+1];
}
 
void range_update(int i, int l, int r, int ql, int qr, int x){
    push(i,l,r);
    if(ql<=l&&r<=qr){
        lz[i] += x;
        push(i,l,r);
        return;
    }
    if(ql>r || qr<l) return;
    range_update(i*2,l,m,ql,qr,x);
    range_update(i*2+1,m+1,r,ql,qr,x);
    t[i] = t[i*2] + t[i*2+1];
}
 
int range_query(int i, int l, int r, int ql, int qr){
    push(i,l,r);
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
    int op,a,b,c;
    while(Q--){
        cin >> op;
        if(op==1){
            cin >> a >> b >> c;
            range_update(1,1,N,a,b,c);  
        } 
        else{
            cin >> a;
            cout << range_query(1,1,N,a,a) << '\n';
        } 
    }
}