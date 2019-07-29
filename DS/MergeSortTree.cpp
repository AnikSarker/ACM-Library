#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int A[MAXN];
vector<int>tree[MAXN*5];

#define Left (node*2)
#define Right (node*2+1)
#define mid ((lo+hi)/2)

void build(int node, int lo, int hi){
    if(lo==hi) {tree[node].push_back(A[lo]); return;}
    build(Left,lo,mid);
    build(Right,mid+1,hi);
    merge(tree[Left].begin(),tree[Left].end(),tree[Right].begin(),tree[Right].end(),back_inserter(tree[node]));
}

int query(int node, int lo, int hi, int i, int j, int x){
    if(i>hi || j<lo) return 0;
    if(lo>=i && hi<=j) return lower_bound(tree[node].begin(),tree[node].end(),x) - tree[node].begin();
    int p1 = query(Left,lo,mid,i,j,x);
    int p2 = query(Right,mid+1,hi,i,j,x);
    return p1+p2;
}
