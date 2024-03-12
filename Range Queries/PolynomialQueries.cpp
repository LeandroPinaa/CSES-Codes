#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 200005
#define INF 1e18
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define int long long
#define m (l+r)/2
 
typedef struct{
    int sum;
    int lz1;
    int lz2;
}node;
node t[NMAX<<2];
 
int v[NMAX];
 
void build(int i, int l, int r){
    if(l==r){
        t[i].sum = v[l];
        return;
    }
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    t[i].sum = t[i*2].sum + t[i*2+1].sum;
}
 
void distribute(int par, int child){ //distribui os valores para os nós filhos
    t[child].lz1 += t[par].lz1;
    t[child].lz2 += t[par].lz2;
}
 
void push(int i, int l, int r){
    t[i].sum += t[i].lz1*(r-l+1) + t[i].lz2*((r+1)*r/2 - (l-1)*l/2);
    if(l!=r){
        distribute(i,i*2);
        distribute(i,i*2+1);
    }
    t[i].lz1 = 0;
    t[i].lz2 = 0;
}
 
void range_update(int i, int l, int r, int ql, int qr, int x, int x2){
    push(i,l,r);
    if(ql<=l&&r<=qr){
        t[i].lz1 += x;
        t[i].lz2 += x2;
        return;
    }
    if(ql>r || qr<l) return;
    range_update(i*2,l,m,ql,qr,x,x2);
    range_update(i*2+1,m+1,r,ql,qr,x,x2);
    push(i*2,l,m);
    push(i*2+1,m+1,r);
    t[i].sum = t[i*2].sum + t[i*2+1].sum;
}
 
int range_query(int i, int l, int r, int ql, int qr){
    push(i,l,r);
    if(ql<=l&&r<=qr) return t[i].sum;
    if(ql>r || qr<l) return 0;
    int LChild = range_query(i*2,l,m,ql,qr);
    int RChild = range_query(i*2+1,m+1,r,ql,qr);
    return LChild + RChild;
}
 
int32_t main(){ faster
    int N,Q;
    cin >> N >> Q;
    for(int i=1;i<=N;i++) cin >> v[i];
    build(1,1,N);
    int op,a,b,c;
    while(Q--){
        cin >> op;
        if(op==1){ //t[i].lz1 += x
            cin >> a >> b;
            range_update(1,1,N,a,b,1-a,1);
        }
        if(op==2){
            cin >> a >> b;
            cout << range_query(1,1,N,a,b) << '\n';
        }
    }
}