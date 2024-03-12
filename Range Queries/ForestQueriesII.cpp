#include <bits/stdc++.h>
using namespace std;
#define NMAX 1025
#define INF 999999999
#define int long long
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
int b[NMAX][NMAX];
char vv[NMAX][NMAX];
 
int qry(int x, int y){
    int sum = 0;
    for(; x >= 0; x = (x & (x + 1)) - 1){
        for(int yy = y; yy >= 0; yy = (yy & (yy + 1)) - 1)
            sum += b[x][yy];
    }
    return sum;
}
 
void add(int x, int y, int v){
    for(; x < NMAX; x = x | (x + 1)){
        for(int yy = y; yy < NMAX; yy = yy | (yy + 1))
        b[x][yy] += v;
    }
}
 
int qry2(int x1, int y1, int x2, int y2){
    return qry(x2, y2) - qry(x2, y1 - 1) - qry(x1 - 1, y2) + qry(x1 - 1, y1 - 1);
}
 
void add2(int x1, int y1, int x2, int y2, int v){
    add(x1, y1, v);
    add(x1, y2 + 1, -v);
    add(x2 + 1, y1, -v);
    add(x2 + 1, y2 + 1, v);
}
int32_t main(){ faster
    int N,M;
    cin >> N >> M;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> vv[i][j];
            if(vv[i][j]=='*'){
                add(i,j,1);
            } 
        }
    }
    while(M--){
        int op,x1,x2,y1,y2;
        cin >> op;
        if(op==1){
            cin >> x1 >> y1;
            x1--; y1--;
            if(vv[x1][y1]=='*'){
                vv[x1][y1] = '.';
                add(x1,y1,-1);
            }
            else{
                vv[x1][y1] = '*';
                add(x1,y1,1);
            }
        }
        else{
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; x2--; y1--; y2--;
            cout << qry2(x1,y1,x2,y2) << '\n';
        }
        
    }
}