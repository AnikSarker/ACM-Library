typedef long long ll;

struct node {
    int prior, size;
    ll val, sum, lazy, rev;
    node *l, *r;
    node(int v = 0) {
        val = sum = v;
        lazy = 0; rev = 0;
        prior = rand();
        size = 1;
        l = r = NULL;
    }
} *root;
///If you initialize the root (root = new node()) then treap will be 1 based indexing and root will be the 0th index
///Otherwise it will be 0 based indexing, so decide carefully
typedef node* pnode;

int sz(pnode t) { return t ? t -> size : 0;}
void upd_sz(pnode t) { if(t) t -> size = sz(t -> l) + 1 + sz(t -> r);}

void push(pnode t) {
    if(!t) return;

    if(t->lazy){
        t -> val += t -> lazy;
        t -> sum += t -> lazy * sz(t);
        if(t -> l) t -> l -> lazy += t -> lazy;
        if(t -> r) t -> r -> lazy += t -> lazy;
        t -> lazy = 0;
    }
    //Reverse
    if(t->rev){
        swap(t->l,t->r);
        if(t -> l) t -> l -> rev ^= t -> rev;
        if(t -> r) t -> r -> rev ^= t -> rev;
        t -> rev = 0;
    }
}

void combine(pnode t) {
    // Note: This function should reset datas of t first (MUST!!)
    // Then update datas from l and r.
    if(!t) return;
    push(t -> l);
    push(t -> r);
    t -> sum = t -> val; // Reset
    if(t -> l) t -> sum += t -> l -> sum;
    if(t -> r) t -> sum += t -> r -> sum;
}

void split(pnode t, pnode &l, pnode &r, int pos, int add = 0) {
    if(!t) return void(l = r = NULL);
    push(t);
    int curr = sz(t -> l) + add;
    if(curr <= pos)
        split(t -> r, t -> r, r, pos, curr + 1), l = t;
    else split(t -> l, l, t -> l, pos, add), r = t;
    upd_sz(t);
    combine(t);
}

void merge(pnode &t, pnode l, pnode r) {
    push(l), push(r);
    if(!l || !r)
        t = l ? l : r;
    else if(l -> prior > r -> prior)
        merge(l -> r, l -> r, r), t = l;
    else merge(r -> l, l, r -> l), t = r;
    upd_sz(t);
    combine(t);
}

ll query(pnode t, int l, int r) {
    pnode L, mid, R;
    split(t, L, mid, l - 1);
    split(mid, t, R, r - l);
    ll ans = t -> sum;
    merge(mid, L, t);
    merge(t, mid, R);
    return ans;
}

void update(pnode t, int l, int r, ll v) {
    pnode L, mid, R;
    split(t, L, mid, l - 1);
    split(mid, t, R, r - l);
    t -> lazy += v;
    merge(mid, L, t);
    merge(t, mid, R);
}

void insert(pnode &t, int pos, int v) {
    pnode L, R, tmp, y = new node(v);
    split(t, L, R, pos - 1);
    merge(tmp, L, y);
    merge(t, tmp, R);
}

void Del(pnode &t, int pos) {
    pnode L, R, mid;
    split(t, L, mid, pos - 1);
    split(mid, t, R, 0);
    pnode tmp = t;
    merge(t, L, R);
    free(tmp);
}

void Reverse(pnode t, int l, int r) {
    pnode L, mid, R;
    split(t, L, mid, l - 1);
    split(mid, t, R, r - l);
    t -> rev ^= 1;
    merge(mid, L, t);
    merge(t, mid, R);
}
