//Treap
#define gn(o, d) node[node[o].c[d]]

struct Treap {int c[2]; int v,s,r,f;};
Treap node[MAX];
int sz;

void makeTree(int o) {node[o].s=gn(o,0).s+gn(o,1).s+1;}

void PushDown(int o){
    if(node[o].f){
        swap(node[o].c[0],node[o].c[1]);
        gn(o,0).f^=1;
        gn(o,1).f^=1;
        node[o].f=0;
    }
}

void Rotate(int &o, int d){
    int k=node[o].c[d^1];
    node[o].c[d^1]=node[k].c[d];
    node[k].c[d]=o;
    makeTree(o);
    makeTree(k);
    o=k;
}

void Init(int o, int v){
    Treap &n=node[o];
    n.v=v;
    n.r=rand();
    n.s=1;
    n.c[0]=n.c[1]=0;
    n.f=0;
}

void Insert(int &o, int p, int x){
    if(o==0) {o=sz++; Init(o,x);}
    else{
        int t=gn(o,0).s+1;
        int d=0;
        if(p>t) {p-=t; d=1;}
        Insert(node[o].c[d],p,x);
        if(gn(o,d).r>node[o].r) Rotate(o,d^1);
    }
    makeTree(o);
}

void Split(int o,int &l,int &r,int k){
    if(k==0) {l=0; r=o; return;}
    if(k==node[o].s) {l=o; r=0; return;}
    PushDown(o);

    if(k<=gn(o,0).s){
        PushDown(node[o].c[0]);
        r=o;
        Split(node[r].c[0],l,node[r].c[0],k);
        makeTree(r);
    }
    else{
        PushDown(node[o].c[1]);
        l=o;
        Split(node[l].c[1],node[l].c[1],r,k-gn(o,0).s-1);
        makeTree(l);
    }
}

void Merge(int &o,int l,int r){
    if(!l) o=r;
    else if(!r) o=l;
    else if(node[l].r>node[r].r){
        o=l;
        PushDown(o);
        Merge(node[o].c[1],node[o].c[1],r);
        makeTree(o);
    }
    else{
        o=r;
        PushDown(o);
        Merge(node[o].c[0],l,node[o].c[0]);
        makeTree(o);
    }
}

int A[MAX];
int Size=0;
void Print(int o){
    if(o){
        PushDown(o);
        Print(node[o].c[0]);
        A[++Size]=node[o].v;
        Print(node[o].c[1]);
    }
}

void Reverse(int &o, int l, int r){
    int lp,rp,mid;
    Split(o,lp,rp,l-1);
    Split(rp,mid,rp,r-l+1);
    node[mid].f^=1;
    Merge(o,lp,mid);
    Merge(o,o,rp);
}

//Circular Right Shift
void CRshift(int &o, int l, int r){
    int lp,rp,mid,MID;
    Split(o,lp,rp,l-1);
    Split(rp,mid,rp,r-l+1);
    Split(mid,MID,mid,r-l);

    Merge(mid,mid,MID);
    Merge(o,lp,mid);
    Merge(o,o,rp);
}

int main(){
    node[0].s=0;
    sz=1;
    int root=0;

    int n,q,m,p;
    scanf("%d %d %d",&n,&q,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&p);
        Insert(root,i,p);
    }

    while(q--){
        int cmd,l,r;
        scanf("%d %d %d",&cmd, &l, &r);
        if(cmd==1) CRshift(root,l,r);
        else Reverse(root, l, r);
    }
    Print(root);
}
