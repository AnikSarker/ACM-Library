#define MAX 1000000005
#define mid (lo+(hi-lo)/2) //Be careful about overflow

struct item{
    int value, lazy;
    item *Left, *Right ;
    item(){value=0; lazy=0; Left=Right=NULL;}
};
item* root;

int query(item* node, int lo, int hi, int i, int j){
    if (!node || i>hi || j<lo) return 0;
    if (lo>=i && hi<=j) return node->value;
    int p1=query(node->Left,lo,mid,i,j);
    int p2=query(node->Right,mid+1,hi,i,j);
    return p1+p2;
}

void update(item* node, int lo, int hi, int i, int val){
    if (i>hi || i<lo) return;
    if (lo==hi) {node->value=val; return;}
    if(lo!=hi && !node->Left) node->Left=new item();
    if(lo!=hi && !node->Right) node->Right=new item();

    update(node->Left,lo,mid,i,val);
    update(node->Right,mid+1,hi,i,val);
    node->value=node->Left->value + node->Right->value;
}

//lazy propagation
void lazyPropagation(item* node,int lo,int hi){
    if(node->lazy){
        node->value+=(hi-lo+1)*node->lazy;
        if(lo != hi) {node->Left->lazy+=node->lazy; node->Right->lazy+=node->lazy;}
        node->lazy=0;
    }
}

void updateRange(item* node, int lo, int hi, int i, int j, ll val){
    if(!node->Left)  node->Left=new item();
    if(!node->Right) node->Right=new item();
    lazyPropagation(node,lo,hi);

    if(lo>hi) return;
    else if(lo>j || hi<i) return;
    if(lo>=i && hi<=j) {node->lazy+=val;  lazyPropagation(node,lo,hi);  return;}

    updateRange(node->Left,lo,mid,i,j,val);
    updateRange(node->Right,mid+1,hi,i,j,val);
    node->value=node->Left->value + node->Right->value;
}

ll queryRange(item* node,int lo,int hi,int i,int j){
    if(lo>hi) return 0;
    else if(lo>j || hi<i) return 0;
    
    if(!node->Left) node->Left=new item();
    if(!node->Right) node->Right=new item();
    lazyPropagation(node,lo,hi);
    
    if(lo>=i && hi <= j) return node->value;
    ll p1=queryRange(node->Left,lo,mid,i,j);
    ll p2=queryRange(node->Right,mid+1,hi,i,j);
    return p1+p2;
}


//Free each node of the tree after each test case
void Free(item* node){
    if(node->Left) Free(node->Left);
    if(node->Right) Free(node->Right);
    free(node);
}

int main() {root=new item();}
