int n;
int tree[MAX*2];

//point update, range query
//initial elements at tree[n]....tree[2*n-1]
void build(){
    for(int i=n-1;i>=1;i--) 
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

void update(int p,int value){
    for(tree[p+=n]=value; p>1; p>>=1)
        tree[p>>1]=max(tree[p],tree[p^1]);
}

//outputs max(l,r-1)
int query(int l,int r){
    int res=0;
    for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if(l&1) res=max(res,tree[l++]);
        if(r&1) res=max(res,tree[--r]);
    }
    return res;
}
