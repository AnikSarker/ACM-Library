int ara[MAX];
int tree[MAX*5];
#define Left (node*2)
#define Right (node*2+1)
#define mid ((lo+hi)/2)

void build(int node, int lo, int hi){
    if (lo==hi) {tree[node]=ara[lo]; return;}
    build(Left,lo,mid);
    build(Right,mid+1,hi);
    tree[node]=tree[Left]+tree[Right];
}

int query(int node, int lo, int hi, int i, int j){
    if (i>hi || j<lo) return 0;
    if (lo>=i && hi<=j) return tree[node];
    int p1=query(Left,lo,mid,i,j);
    int p2=query(Right,mid+1,hi,i,j);
    return p1+p2;
}

void update(int node, int lo, int hi, int i, int val){
    if (i>hi || i<lo) return;
    if (lo==hi)  {tree[node]=val; return;}
    update(Left,lo,mid,i,val);
    update(Right,mid+1,hi,i,val);
    tree[node]=tree[Left]+tree[Right];
}

//lazy propagation
int lazy[MAX*5];
void lazyPropagation(int node,int lo,int hi){
    if(lazy[node]){
        tree[node]+=(hi-lo+1)*lazy[node];
        if(lo != hi) {lazy[Left] += lazy[node]; lazy[Right] += lazy[node];}
        lazy[node] = 0;
    }
}

void updateRange(int node, int lo, int hi, int i, int j, int val){
    lazyPropagation(node,lo,hi);
    if(lo>hi) return;
    else if(lo>j || hi<i) return;
    if(lo>=i && hi<=j) {lazy[node]+=val;  lazyPropagation(node,lo,hi);  return;}
    updateRange(Left,lo,mid,i,j,val);
    updateRange(Right,mid+1,hi,i,j,val);
    tree[node]=tree[Left]+tree[Right];
}

int queryRange(int node,int lo,int hi,int i,int j){
    if(lo>hi) return 0;
    else if(lo>j || hi<i) return 0;
    lazyPropagation(node,lo,hi);
    if(lo>=i && hi <= j) return tree[node];
    int p1=queryRange(Left,lo,mid,i,j);
    int p2=queryRange(Right,mid+1,hi,i,j);
    return p1+p2;
}
