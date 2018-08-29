#include<bits/stdc++.h>
using namespace std;

#define MAX 1000005
typedef long long ll;

struct node {
    int prior, size;
    ll val, sum;
    node *l, *r;
    node(int v = 0) {
        val = sum = v;
        prior = rand();
        size = 1;
        l = r = NULL;
    }
};

node* root[1000005];
typedef node* pnode;

int sz(pnode t) {return t ? t -> size : 0;}
void upd_sz(pnode t) {if(t) t -> size = sz(t -> l) + 1 + sz(t -> r);}

void combine(pnode t) {
    // Note: This function should reset datas of t first (MUST!!)
    // Then update datas from l and r.
    if(!t) return;
    t -> sum = t -> val; // Reset
    if(t -> l) t -> sum += t -> l -> sum;
    if(t -> r) t -> sum += t -> r -> sum;
}

void split(pnode t, pnode &l, pnode &r, int pos, int add = 0) {
    if(!t) return void(l = r = NULL);
    node* cn = new node();
    *cn = *t;

    int curr = sz(cn -> l) + add;
    if(curr <= pos) split(cn -> r, cn -> r, r, pos, curr + 1), l = cn;
    else split(cn -> l, l, cn -> l, pos, add), r = cn;

    upd_sz(cn);
    combine(cn);
}

void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r) {t = l ? l : r; return;}
    node* cn = new node();

    if(l -> prior > r -> prior) {*cn = *l; merge(cn -> r, cn -> r, r);}
    else {*cn = *r; merge(cn -> l, l, cn -> l);}
    t = cn;

    upd_sz(t);
    combine(t);
}

//Important to use pnode &t here
//Because this is a non-persistent operation
void insert(pnode &t, int pos, int v){
    pnode L, R, tmp, y = new node(v);
    split(t, L, R, pos - 1);
    merge(tmp, L, y);
    merge(t, tmp, R);
}

//Important to use pnode &t here
//Because this is a non-persistent operation
void Replace(pnode &t,int x, int val){
    pnode L, R, mid;
    split(t,L,mid,x);
    split(L,t,R,x-1);

    R->val = R->sum = val;

    merge(L,t,R);
    merge(t,L,mid);
}

//Important to use pnode t here (no &)
//Because this is a persistent operation
ll Query(pnode t, int pos1, int pos2){
    pnode L, R, mid, tmp;
    split(t, L, R, pos2);
    split(L, mid, tmp, pos1 - 1);
    return tmp->sum;
}
