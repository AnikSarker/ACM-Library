#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int A[MAXN];
int tree[MAXN*5];

#define Left (node*2)
#define Right (node*2+1)
#define mid ((lo+hi)/2)

void build(int node, int lo, int hi){
    if (lo==hi) {tree[node] = A[lo]; return;}
    build(Left,lo,mid);
    build(Right,mid+1,hi);
    tree[node] = tree[Left] + tree[Right];
}

int query(int node, int lo, int hi, int i, int j){
    if (i>hi || j<lo) return 0;
    if (lo>=i && hi<=j) return tree[node];
    int p1 = query(Left,lo,mid,i,j);
    int p2 = query(Right,mid+1,hi,i,j);
    return p1 + p2;
}

void update(int node, int lo, int hi, int i, int val){
    if (i>hi || i<lo) return;
    if (lo==hi)  {tree[node] = val; return;}
    update(Left,lo,mid,i,val);
    update(Right,mid+1,hi,i,val);
    tree[node] = tree[Left] + tree[Right];
}

/*
Lazy Propagation
1. Lets define a range update operation on segment tree OP. If there is a lazy
value x in some node u from some updates, its guaranteed that this lazy value
has been already propagated from each node v in the path from root to u. If
there is still some lazy value at in a node v in the path from root to u, then
that is from some later updates which has not been propagated up-to u yet.

2. Let there be multiple type of range updates. Build a struct called LazyStruct
and keep a lazy variable for each type of update. Note that,
a) for ASSIGN update, clear each other type of lazy variables.
b) while handling ADD/SUB/COUNT lazy in a node, first propagate down any ASSIGN
lazy it already has. This ensures the correct order of the updates.
*/

int lazy[MAXN*5];
void lazyPropagation(int node,int lo,int hi){
    if(lazy[node]){
        tree[node] += (hi-lo+1)*lazy[node];
        if(lo != hi) {lazy[Left] += lazy[node]; lazy[Right] += lazy[node];}
        lazy[node] = 0;
    }
}

void updateRange(int node, int lo, int hi, int i, int j, int val){
    lazyPropagation(node,lo,hi);
    if(lo>hi) return;
    else if(lo>j || hi<i) return;
    if(lo>=i && hi<=j) {lazy[node] += val; lazyPropagation(node,lo,hi); return;}
    updateRange(Left,lo,mid,i,j,val);
    updateRange(Right,mid+1,hi,i,j,val);
    tree[node] = tree[Left] + tree[Right];
}

int queryRange(int node,int lo,int hi,int i,int j){
    if(lo>hi) return 0;
    else if(lo>j || hi<i) return 0;
    lazyPropagation(node,lo,hi);
    if(lo>=i && hi <= j) return tree[node];
    int p1 = queryRange(Left,lo,mid,i,j);
    int p2 = queryRange(Right,mid+1,hi,i,j);
    return p1 + p2;
}
