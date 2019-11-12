#include <bits/stdc++.h>
using namespace std;
#define ll long long int

const int maxk = 105;
const int maxn = 10005;
const int maxX = 1000005;
const ll inf = 1e12;

struct Poly{
    vector<ll> co;
    Poly() {}
    void add(ll c) {co.push_back(c);}
    ll f(ll x){
        if(co.size() == 0) return inf;

        ll ans = 0;
        ll mul = 1;
        for(ll c : co) {ans += mul * c; mul = mul * x;}
        return ans;
    }
};

struct lc{
    Poly S;
    lc *lft, *rgt;

    lc() {lft = rgt = NULL; S = Poly();}

    void Del(){
        if(lft) lft->Del();
        if(rgt) rgt->Del();
        delete this;
    }

    void add(int lo, int hi, Poly upd){
        if(upd.f(lo) > S.f(lo) && upd.f(hi) > S.f(hi)) return;

        int mid = (lo + hi) / 2;
        bool bame  = upd.f(lo) < S.f(lo);
        bool majhe = upd.f(mid) < S.f(mid);
        if(majhe) swap(S, upd);
        if(lo == hi) return;

        if(bame != majhe){
            if(!lft) lft = new lc();
            lft->add(lo, mid, upd);
        }
        else{
            if(!rgt) rgt = new lc();
            rgt->add(mid+1, hi, upd);
        }
    }

    ll query(int lo, int hi, ll x){
        ll Curr = S.f(x);
        if(lo == hi) return Curr;
        int mid = (lo + hi) / 2;
        if(x <= mid) return min(Curr, lft ? lft->query(lo, mid, x) : inf);
        else return min(Curr, rgt ? rgt->query(mid+1, hi, x) : inf);
    }
};
