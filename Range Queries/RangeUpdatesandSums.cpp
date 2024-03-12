#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define NMAX 200005
#define INF 1e18
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define m (l+r)/2
 
typedef struct{
    int sum,lz1,lz2;
    bool setAllValid;
}node;
node t[NMAX<<2];
int v[NMAX];
 
void distribute(int par, int child){
    if(t[par].setAllValid){
        t[child].setAllValid = 1;
        t[child].lz1 = t[par].lz1;
        t[child].lz2 = t[par].lz2;
    }
    else t[child].lz1 += t[par].lz1;
}
 
void push(int i, int l, int r){
    if(t[i].setAllValid)
        t[i].sum = t[i].lz2*(r-l+1);
    
    t[i].sum += t[i].lz1*(r-l+1);
    if(l!=r){
        distribute(i,i*2);
        distribute(i,i*2+1);
    }
    t[i].lz1 = 0;
    t[i].setAllValid = 0;
}
 
void build(int i, int l, int r){
    if(l==r){
        t[i].sum = v[l];
        return;
    }
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    t[i].sum = t[i*2].sum + t[i*2+1].sum;
}
 
void range_update1(int i, int l, int r, int ql, int qr, int x){
    push(i,l,r);
    if(ql<=l&&r<=qr){
        t[i].lz1 += x;
        push(i,l,r);
        return;
    }
    if(ql>r || qr<l) return;
    range_update1(i*2,l,m,ql,qr,x);
    range_update1(i*2+1,m+1,r,ql,qr,x);
    //tem que espalhar entre os filhos tb, em todos os casos, pra mudar os valores
    push(i*2,l,m);
    push(i*2+1,m+1,r);
    t[i].sum = t[i*2].sum + t[i*2+1].sum;
}
 
void range_update2(int i, int l, int r, int ql, int qr, int x){
    push(i,l,r);
    if(ql<=l&&r<=qr){
        t[i].lz2 = x;
        t[i].lz1 = 0;
        t[i].setAllValid = 1;
        return;
    }
    if(ql>r || qr<l) return;
    range_update2(i*2,l,m,ql,qr,x);
    range_update2(i*2+1,m+1,r,ql,qr,x);
    //tem que espalhar entre os filhos tb, em todos os casos, pra mudar os valores
    push(i*2,l,m);
    push(i*2+1,m+1,r);
    t[i].sum = t[i*2].sum + t[i*2+1].sum;
}
 
int range_query(int i, int l, int r, int ql, int qr){
    push(i,l,r);
    if(ql<=l&&r<=qr) return t[i].sum;
    if(ql>r || qr<l) return 0;
    int LChild=0,RChild=0;
    if(ql<=m) LChild = range_query(i*2,l,m,ql,qr);
    if(qr>m) RChild = range_query(i*2+1,m+1,r,ql,qr);
    return LChild + RChild;
}
 
int32_t main(){ faster
    int N,Q,op,a,b,c;
    cin >> N >> Q;
    for(int i=1;i<=N;i++) cin >> v[i];
    build(1,1,N);
    while(Q--){
        cin >> op;
        if(op==1){ //increment lz1
            cin >> a >> b >> c;
            range_update1(1,1,N,a,b,c);
        }
        else if(op==2){ //change lz2
            cin >> a >> b >> c;
            range_update2(1,1,N,a,b,c);
        }
        else{ //range query
            cin >> a >> b;
            cout << range_query(1,1,N,a,b) << endl;
        }
    }
}