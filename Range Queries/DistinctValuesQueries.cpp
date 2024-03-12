#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 200005
#define INF 1e18
#define int long long
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define m (l+r)/2
 
vector<int>t[NMAX<<2];
int a[NMAX],b[NMAX]; //a = vetor original, b = vetor dos indices ocorrencia do visto
map<int,int>seen; //seen[a[i]] = i, ou seja, em qual indice um X elemento apareceu, e assim por diante
 
void build(int i, int l, int r){
    if(l==r){
        t[i].push_back(b[l]);
        return;
    }
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    merge(t[i*2].begin(),t[i*2].end(),t[i*2+1].begin(),t[i*2+1].end(),back_inserter(t[i]));
}
 
int range_query(int i, int l, int r, int ql, int qr){
    if(ql<=l&&r<=qr){
        return (int)(upper_bound(t[i].begin(),t[i].end(),INF) - lower_bound(t[i].begin(),t[i].end(),qr+1));
    }
    if(ql>r || qr<l) return 0;
    int LChild = range_query(i*2,l,m,ql,qr);
    int RChild = range_query(i*2+1,m+1,r,ql,qr);
    return LChild + RChild; //soma os valores distintos de cada array segmento
}
 
int32_t main(){ faster
    int N,Q;
    cin >> N >> Q;
    for(int i=1;i<=N;i++) cin >> a[i];
    for(int i=N;i>=1;i--){
        if(seen.count(a[i])) b[i] = seen[a[i]];
        else b[i] = INF; //se n foi visto, será apenas N+1
        seen[a[i]] = i;
    }
    build(1,1,N);
    while(Q--){
        int x,y;
        cin >> x >> y;
        cout << range_query(1,1,N,x,y) << '\n';
    }
}
/*
a[i] = {3,2,3,1,2}
 
construção b:
b[i] = {3,5,6,6,6}
tem valor N+1 (no caso, 6) a primeira ocorrência daquele elemento
depois, para o caso do elemento 2 que se repete na posição 2 do a[i](indexado-1), ele indica
a posição anterior que é 5
depois, para o caso do elemento 3 que se repete na posição 1 do a[i](indexado-1), ele indica
a posição anterior que é 3
e assim por diante
 
com isso, basta verificar os elementos do intervalo ql qr que são > R
logo, que pertencem a: [a+1,INF], logo:
upperbound(INF)-lowerbound(a+1)
*/