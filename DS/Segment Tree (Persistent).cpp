//Persistent Segment Tree
struct node{
    node *left,*right; int val;
    node(){val=0;left=NULL;right=NULL;}
    node(int a,node *b,node *c){val=a,left=b,right=c;}

    void build(int lo, int hi) {
	if(lo==hi) return;
        left=new node();
        right=new node();
        int mid=(lo+hi)/2;
        left->build(lo,mid);
        right->build(mid+1,hi);
    }

    node *update(int lo,int hi,int i,int v){
        if(hi<i || lo>i) return this;
        if(lo==hi) {node *ret=new node(val,left,right); ret->val+=v; return ret;}
        int mid=(lo+hi)/2;
        node *ret=new node();
        ret->left=left->update(lo,mid,i,v);
        ret->right=right->update(mid+1,hi,i,v);
        ret->val=ret->left->val+ret->right-> val;
        return ret;
    }

    int query(int lo,int hi,int i,int j) {
        if(hi<i || lo>j) return 0;
        if(i<=lo && hi<=j) return val;
        int mid=(lo+hi)/2;
        return left->query(lo,mid,i,j)+right->query(mid+1,hi,i,j);
    }
};
int Size;
node* root[MAX];

//Searching kth minimum element in sorted order
int Search(node *a,node *b,node* c,node* d,int l,int r,int k){
    if(l==r) return l;
    int Count=a->left->val+b->left->val-c->left->val-d->left->val;
    int mid=(l+r)/2;
    if(Count>=k) return Search(a->left,b->left,c->left,d->left,l,mid,k);
    else return Search(a->right,b->right,c->right,d->right,mid+1,r,k-Count);
}

void dfs(int u,int p,int d){
    ......
    root[u]=root[p]->update(1,Size,w[u],1);
    ......
}

int main(){
    ......
    dfs(1,0,0);
    Size=Map.size();  //number of distinct elements after co-ordinate compression
    root[0]=new node();
    root[0]->build(1,Size);
    ......
}
