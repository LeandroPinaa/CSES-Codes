#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define NMAX 200005
#define INF 1e18
#define int long long
#define m (l+r)/2
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
template <class T>
using Tree =
    tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
int v[NMAX];
Tree<int>t;
 
int32_t main(){
    int N,Q,a,b;
    char op;
    cin >> N >> Q;
    for(int i=1;i<=N;i++){
        cin >> v[i];
        t.insert(v[i]);
    }
    while(Q--){
        cin >> op >> a >> b;
        if(op=='!'){ //2 2 3 5 7
            t.erase(t.find_by_order(t.order_of_key(v[a])));
            v[a] = b;
            t.insert(v[a]);
        }
        else{
            cout << t.order_of_key(b+1) - t.order_of_key(a) << '\n';
        }
    }
}