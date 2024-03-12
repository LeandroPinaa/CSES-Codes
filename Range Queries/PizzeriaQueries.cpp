#include <bits/stdc++.h>
using namespace std;
#define NMAX 200005
#define INF 1e18
#define int long long
#define m (l+r)/2
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
typedef pair<pair<int,int>,int>pii;
 
struct node{
    int value,ind;
};
 
int resp=-1;
int v[NMAX];
node t[NMAX<<2];
 
node combination(node a, node b){
    node resp;
    if(a.value < b.value){
        resp.value = a.value;
        resp.ind = a.ind;
    }
    else{
        resp.value = b.value;
        resp.ind = b.ind;
    }
    return resp;
}
 
void build(int i, int l, int r){
    if(l==r){
        t[i].value = v[l];
        t[i].ind = l;
        return;
    }
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    t[i] = combination(t[i*2],t[i*2+1]);
}
 
node emptynode(){
    node resp;
    resp.value = resp.ind = INF;
    return resp;
}
 
void point_update(int i, int l, int r, int p, int x){
    if(l==r){
        t[i].value = x;
        t[i].ind = p;
        return;
    }
    if(p<=m) point_update(i*2,l,m,p,x);
    else point_update(i*2+1,m+1,r,p,x);
    t[i] = combination(t[i*2],t[i*2+1]);
}
 
void query(int i, int l, int r, int x){
    //cout << "intervalos = " << l << " " << r << endl;
    if(l==r){
        resp = min(resp,t[i].value+abs(x-t[i].ind));
        return;
    }
    if( t[i*2].value < resp ){
        resp = min(resp,t[i*2].value+abs(x-t[i*2].ind));
        query(i*2,l,m,x);
    }
    if( t[i*2+1].value < resp ){
        resp = min(resp,t[i*2+1].value+abs(x-t[i*2+1].ind));
        query(i*2+1,m+1,r,x);
    }
}
 
int32_t main(){ faster
    int N,Q,op,x,y;
    pii before = {{-1,-1},-1};
    cin >> N >> Q;
    for(int i=1;i<=N;i++) cin >> v[i];
    build(1,1,N);
    while(Q--){
        cin >> op;
        if(op==1){
            cin >> x >> y;
            point_update(1,1,N,x,y);
            before.first.first = op;
        }
        else{
            cin >> x;
            if(before.first.first==op && before.first.second==x){
                cout << before.second << '\n';
                continue;
            } 
            resp = t[1].value + abs(x-t[1].ind);
            query(1,1,N,x);        
            before.first.first = op;
            before.first.second = x;
            before.second = resp;
            cout << resp << '\n';
        }
    }
}
/*
100 1000
80 69 91 47 74 75 94 22 100 43 50 82 47 40 51 90 27 98 85 47 14 55 82 52 9 65 90 86 45 52 52 95 40 85 3 46 77 16 59 32 22 41 87 89 78 59 78 34 26 71 9 82 68 80 74 100 6 10 53 84 80 7 87 3 82 26 26 14 37 26 58 96 73 41 2 79 43 56 74 30 71 6 100 72 93 83 40 28 79 24 68 68 68 24 100 85 7 96 64 91
2 95
correto: 9
*/