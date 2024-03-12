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
    t[i] = min(t[i*2],t[i*2+1]);
}
 
int range_query(int i, int l, int r, int ql, int qr){
    if(ql<=l&&r<=qr) return t[i];
    if(ql>r || qr<l) return INF;
    int LChild = range_query(i*2,l,m,ql,qr);
    int RChild = range_query(i*2+1,m+1,r,ql,qr);
    return min(LChild,RChild);
}
 
int32_t main(){
    int N,Q;
    cin >> N >> Q;
    for(int i=1;i<=N;i++) cin >> v[i];
    build(1,1,N);
    int a,b;
    while(Q--){
        cin >> a >> b;
        cout << range_query(1,1,N,a,b) << '\n';
    }
}