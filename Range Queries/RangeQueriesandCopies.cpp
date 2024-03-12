#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ost tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define int long long
#define NMAX 200005
#define COPIES 40
#define INF 1e18
#define pii pair<int,int>
#define m (l+r)/2
 
typedef struct{
    int lc,rc,s; //lc = left child, rc = right child, s = sum
}node;
node t[NMAX*COPIES]; //copies 50 é estimativa
int sts=1; //indices de cada array copia
int v[NMAX];
vector<int>c{0}; //copias
 
void point_update(int &i, int l, int r, int p, int x){
    //copia do nó
    t[sts].lc = t[i].lc;
    t[sts].rc = t[i].rc;
    t[sts].s = t[i].s + x;
    i = sts++;
    if(l==r) return; //nó folha
    if(p<=m) point_update(t[i].lc,l,m,p,x);
    else point_update(t[i].rc,m+1,r,p,x);
}
 
int range_query(int i, int l, int r, int ql, int qr){
    if(ql<=l&&r<=qr) return t[i].s;
    //if(ql>r || qr<l) return 0;
    int LChild = 0, RChild = 0;
    if(ql<=m) LChild = range_query(t[i].lc,l,m,ql,qr);
    if(qr>m) RChild = range_query(t[i].rc,m+1,r,ql,qr);
    return LChild + RChild;
}
 
int32_t main(){ faster
    int N,Q,op,k,a,b,x;
    cin >> N >> Q;
    for(int i=0;i<N;i++){
        cin >> v[i], point_update(c[0], 0, N-1, i, v[i]);
    }
    while(Q--){
        cin >> op;
        if(op==1){
            cin >> k >> a >> x, k--,a--; //ja que é indexado-0
            point_update(c[k], 0, N-1, a, x-range_query(c[k],0,N-1,a,a));
        }
        else if(op==2){
            cin >> k >> a >> b, k--, a--, b--;
            cout << range_query(c[k],0,N-1,a,b) << '\n';
        }
        else{
            cin >> k, k--;
            c.push_back(c[k]);
        }
    }
}
