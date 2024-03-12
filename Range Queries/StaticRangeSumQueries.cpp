#include <bits/stdc++.h>
using namespace std;
#define NMAX 200100
 
long long int v[NMAX],sum[NMAX];
 
int main(){
    long long int N,Q,l,r,i;
    cin >> N >> Q;
    for(i=1;i<=N;i++) cin >> v[i];
    for(i=1;i<=N;i++){
        sum[i] = sum[i-1]+v[i];
    }
    while(Q--){
        cin >> l >> r;
        cout << sum[r]-sum[l-1] << endl;
    }
}