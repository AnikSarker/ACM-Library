#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int MAX_X = 100005;
//domain of f(x) = [1, MAX_X-1]

struct Poly{
    vector<ll> co;
    Poly(){}
    void add(ll c) {co.push_back(c);}
    ll f(ll x){
        ll ans = 0;
        ll mul = 1;
        for(ll c : co) {ans += mul * c; mul = mul * x;}
        return ans;
    }
};

#define Left (node*2)
#define Right (node*2+1)
#define mid ((lo+hi)/2)
Poly tree[4 * MAX_X];

void build(int node, int lo, int hi){
    tree[node].co.clear();
    tree[node].add(LLONG_MAX);
    if(lo == hi) return;
    build(Left, lo, mid);
    build(Right, mid+1, hi);
}

void addLine(int node, int lo, int hi, Poly upd){
    bool bame  = upd.f(lo) < tree[node].f(lo);
    bool majhe = upd.f(mid) < tree[node].f(mid);
    if(majhe) swap(tree[node], upd);

    if(lo == hi) return;
    if(bame != majhe) addLine(Left, lo, mid, upd);
    else addLine(Right, mid+1, hi, upd);
}

ll query(int node, int lo, int hi, ll x){
    ll Curr = tree[node].f(x);
    if(lo == hi) return Curr;
    if(x <= mid) return min(Curr, query(Left, lo, mid, x));
    else return min(Curr, query(Right, mid+1, hi, x));
}

// Comments :
// 1. Applies directly to lines in any domain space
// 2. In positive domain space, polynomials behave
// like lines after a certain threshold value MAGIC.
// Add a function as addLine(1,Magic,MAX_X-1, cur_poly)
// For query x < MAGIC, brute-force to calculate minimum
// For query x >= MAGIC, return query(1,Magic,MAX_X-1,x)
