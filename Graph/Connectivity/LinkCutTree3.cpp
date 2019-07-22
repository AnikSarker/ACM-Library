#include <bits/stdc++.h>
using namespace std;

struct Node{
    int sz, label, w ;
    Node *p, *pp, *l, *r;
    Node() { p = pp = l = r = 0; }
};
void update(Node *x){
    x->sz = x->w;
    if(x->l) x->sz += x->l->sz;
    if(x->r) x->sz += x->r->sz;
}
void rotr(Node *x){
    Node *y, *z;
    y = x->p, z = y->p;
    if((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z)){
        if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void rotl(Node *x){
    Node *y, *z;
    y = x->p, z = y->p;
    if((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z)){
        if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void splay(Node *x){
    Node *y, *z;
    while(x->p){
        y = x->p;
        if(y->p == 0){
            if(x == y->l) rotr(x);
            else rotl(x);
        }
        else{
            z = y->p;
            if(y == z->l){
                if(x == y->l) rotr(y), rotr(x);
                else rotl(x), rotr(x);
            }
            else
            {
                if(x == y->r) rotl(y), rotl(x);
                else rotr(x), rotl(x);
            }
        }
    }
    update(x);
}

Node *access(Node *x){
    splay(x);
    if(x->r){
        x->r->pp = x;
        x->r->p = 0;
        x->r = 0;
        update(x);
    }

    Node *last = x;
    while(x->pp) {
        Node *y = x->pp;
        last = y;
        splay(y);
        if(y->r){
            y->r->pp = y;
            y->r->p = 0;
        }
        y->r = x;
        x->p = y;
        x->pp = 0;
        update(y);
        splay(x);
    }
    return last;
}

Node *root(Node *x){
    access(x);
    while(x->l) x = x->l;
    splay(x);
    return x;
}

void cut(Node *x){
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y){
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *lca(Node *x, Node *y){
    access(x);
    return access(y);
}

int depth(Node *x){
    access(x);
    return x->sz;
}

class LinkCut{
    Node *x;

    public:
    void initLinkCut(int n,int *vat){
        x = new Node[n+1];
        for(int i = 1; i <= n; i++){
            x[i].label = i;
            x[i].w = vat[i];
            update(&x[i]);
        }
    }
    virtual ~LinkCut(){   delete[] x;}

    void link(int u, int v){   ::link(&x[u], &x[v]);}

    void cut(int u){   ::cut(&x[u]);}

    int root(int u){   return ::root(&x[u])->label;}

    int depth(int u){   return ::depth(&x[u]);}

    int lca(int u, int v){   return ::lca(&x[u], &x[v])->label;}
};
LinkCut lct;
int vat[100005];
int cap;
void solve(int cs){
    int n , q ;
    cin>>n>>q;
    printf("Case %d:\n",cs);
    cap=1;
    for(int i=1;i<=n;i++)scanf("%d",&vat[i]);
    lct.initLinkCut(n,vat);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        lct.link(u,v);
    }
    for(int i=1;i<=q;i++){
        int type;
        scanf("%d",&type);
        int u , v ;
        if(type==1){
            scanf("%d",&u);
            lct.cut(u);
            lct.link(cap,u);
            cap=u;
            continue;
        }
        scanf("%d %d",&u,&v);
        int lca = lct.lca(u,v);
        int ans = lct.depth(u)+lct.depth(v)-2*lct.depth(lca)+vat[lca];
        printf("%d %d\n",lca,ans);
    }
}
int main()
{
    int t,cs=0;
    cin>>t;
    while(cs<t){
        cs++;
        solve(cs);
    }

    return 0;
}

/*


/*
4
5 5
1 2 3 4 5
2 1
3 1
4 2
5 2
2 4 5
1 2
2 1 5
1 5
2 1 5
5 5
1 2 3 4 5
2 1
3 1
4 2
5 2
2 4 5
1 2
2 1 5
1 5
2 1 5
5 5
1 2 3 4 5
2 1
3 1
4 2
5 2
2 4 5
1 2
2 1 5
1 5
2 1 5
5 5
1 2 3 4 5
2 1
3 1
4 2
5 2
2 4 5
1 2
2 1 5
1 5
2 1 5

*/
