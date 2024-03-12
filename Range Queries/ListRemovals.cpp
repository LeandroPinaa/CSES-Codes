#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define MAXN 100005
#define ost tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
 
ost t;
vector<int>v;
 
int32_t main() {
    int N,x,p;
    cin >> N;
    for(int i=0;i<N;i++){
        cin >> x;
        t.insert(i);
        v.push_back(x);
    }
    for(int i=0;i<N;i++){
        cin >> p;
        p--;
        int p2 = *t.find_by_order(p);
        t.erase(p2);
        cout << v[p2] << " ";
    }
}