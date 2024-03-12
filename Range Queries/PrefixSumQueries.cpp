#include <bits/stdc++.h>
using namespace std;
#define NMAX 200005
#define INF 999999999
#define m (l+r)/2
#define int long long
 
typedef struct{
	int sum,left,right,maxsum;
}node;
int v[NMAX];
node t[NMAX<<2];
 
node emptynode(){
	node resp;
	resp.left = resp.right = resp.sum = resp.maxsum = 0;
	return resp;
}
 
node combination(node a, node b){
	node resp;
	resp.sum = a.sum + b.sum;
	resp.left = max(a.left,a.sum+b.left);
	resp.right = max(b.right,b.sum+a.right);
	resp.maxsum = max(max(a.maxsum,b.maxsum),a.right+b.left);
	return resp;
}
 
void build(int i, int l, int r){
	if(l==r){
		t[i].sum = t[i].left = t[i].right = t[i].maxsum = v[l];
		return;
	}
	build(i*2,l,m);
	build(i*2+1,m+1,r);
	t[i] = combination(t[i*2],t[i*2+1]);
}
 
node range_query(int i, int l, int r, int ql, int qr){
	if(ql<=l&&r<=qr) return t[i];
	if(ql>r || qr<l) return emptynode();
	node LChild = range_query(i*2,l,m,ql,qr);
	node RChild = range_query(i*2+1,m+1,r,ql,qr);
	return combination(LChild,RChild);
}
 
void point_update(int i, int l, int r, int p, int x){
	if(l==r){
		t[i].sum = t[i].left = t[i].right = t[i].maxsum = x;
		return;
	}
	if(p<=m) point_update(i*2,l,m,p,x);
	else point_update(i*2+1,m+1,r,p,x);
	t[i] = combination(t[i*2],t[i*2+1]);
}
 
int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N,Q,i;
	cin >> N >> Q;
	for(i=1;i<=N;i++) cin >> v[i];
	build(1,1,N);
	int op,x,y;
	while(Q--){
		cin >> op >> x >> y;
		if(op==1){
			point_update(1,1,N,x,y);
		}
		else{
			node resp;
			resp = range_query(1,1,N,x,y);
            if(resp.left<0) cout << "0\n";
            else cout << resp.left << '\n';
		}
    }
}