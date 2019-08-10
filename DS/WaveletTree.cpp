//Tested : https://www.codechef.com/AUG19A/problems/CHGORAM

#include <bits/stdc++.h>
using namespace std;

struct WaveletTree{
    int lo, hi;
    WaveletTree *l, *r;
    vector<int> b;

    //from and to are array pointers
    //Build Wavelet Tree on A[from...to];
    //x <= A[j] <= y, for each from <= j <= to
    //Warning : Changes the original array A
    WaveletTree(int *from, int *to, int x, int y){
        lo = x, hi = y;
        if(lo == hi or from >= to) return;
        int mid = (lo+hi)/2;
        auto f = [mid](int x) {return x <= mid;};

        b.reserve(to - from + 1);
        b.push_back(0);

        for(auto it = from; it != to; it++)
            b.push_back(b.back() + f(*it));

        auto pivot = stable_partition(from, to, f);
        l = new WaveletTree(from, pivot, lo, mid);
        r = new WaveletTree(pivot, to, mid+1, hi);
    }

    //kth (1-indexed) smallest element in [l, r]
    int kth(int l, int r, int k){
        if(l > r) return 0;
        if(lo == hi) return lo;
        int inLeft = b[r] - b[l-1];
        int lb = b[l-1]; //amt of nos in first (l-1) nos that go in left
        int rb = b[r];   //amt of nos in first (r) nos that go in left
        if(k <= inLeft) return this->l->kth(lb+1, rb , k);
        return this->r->kth(l-lb, r-rb, k-inLeft);
    }

    //Count of numbers <= k in [l, r]
    int LTE(int l, int r, int k){
        if(l > r or k < lo) return 0;
        if(hi <= k) return r - l + 1;
        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
    }
};

const int MAXN = 100005;
const int MAXA = 1000005;
int A[MAXN];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++) scanf("%d",&A[i]);
    WaveletTree wt(A+1, A+n+1, 1, MAXA);
}
