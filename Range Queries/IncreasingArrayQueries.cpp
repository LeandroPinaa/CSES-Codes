#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 200005
#define INF 1e18
#define ll long long
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define m (l+r)/2

int n, q;
ll x[NMAX], pref[NMAX], ans[NMAX];
ll contrib[NMAX], bit[NMAX];
vector<pair<int, int>> bckt[NMAX];
 
void update(int pos, ll val){
	for(; pos <= n; pos += pos & -pos) bit[pos] += val;
}
 
ll query(int a, int b){
	ll ans = 0;
	for(; b; b -= b & -b) ans += bit[b];
	for(a--; a; a -= a & -a) ans -= bit[a];
	return ans;
}
 
int main(){ faster
	cin >> n >> q;
	for(int i=1;i<=n;i++){
		cin >> x[i];
		pref[i] = pref[i - 1] + x[i];
	}
	x[n + 1] = -INF;
	pref[n + 1] = pref[n] + x[n + 1];
	for(int i=1;i<=q;i++){
		int a, b;
		cin >> a >> b;
		bckt[a].push_back({b, i});
	}
	deque<int> stck = {n + 1};
	for(int i=n;i;i--){
		while(stck.size() && x[i] >= x[stck.front()]){
			update(stck.front(), -contrib[stck.front()]);
			stck.pop_front();
		}
		contrib[i] = (stck.front() - 1 - i) * x[i] - (pref[stck.front() - 1] - pref[i]);
		update(i, contrib[i]);
		stck.push_front(i);
		for(pair<int, int> j : bckt[i]){
			int pos = upper_bound(stck.begin(), stck.end(), j.first) - stck.begin() - 1;
			ans[j.second] = (pos ? query(i, stck[pos - 1]) : 0) + (j.first - stck[pos]) * x[stck[pos]] - (pref[j.first] - pref[stck[pos]]);
		}
	}
	for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}