// add , delete edge 
// online LCA
struct LinkCutTree{
    struct Node{
        Node*p=0, *pp=0, *c[2]={0, 0};
        int id;bool ev=0;
        Node(int _id=-1):id(_id){}
        void recalc(){for(int i:{0, 1})if(c[i]) c[i]->p=this;}
        void push(){
            if(ev){
                ev=0;swap(c[0], c[1]);
                for(int i:{0, 1})if(c[i]) c[i]->ev^=1;
            }
        }
        void unlink(int i){c[i]->p=0;c[i]=0;recalc();}
        int up(){return p?p->c[1]==this:-1;}
        void rot(){
            swap(pp, p->pp);
            int i = up(), j=p->up();
            p->c[i]=c[!i]; c[!i]=p; p=p->p;
            if(p) p->c[j]= this;c[!i]->recalc();
            recalc();if(p) p->recalc();
        }
        Node* splay(){
            for(push();p;){
                if(p->p) p->p->push();
                p->push(); push();
                if(p->up()==up())p->rot();
                rot();
            }
            return this;
        }
        Node*first(){push();return c[0]?c[0]->first():splay();}
    };
    vector<Node> g;
    LinkCutTree(size_t N){
        g.reserve(N);
        for(size_t i=0;i<N;++i)g.emplace_back(i);
    }
    bool connected(int u, int v){
        Node*x = access(&g[u])->first();
        Node*y = access(&g[v])->first();
        return x==y;
    }
    void link(int u, int p){
        if(connected(u, p)) return;
        make_root(&g[u]);g[u].pp=&g[p];
    }
    void cut_up(int u){Node*x = &g[u];access(x);x->unlink(0);}
    void cut(int u, int v){
        if(!connected(u, v)) return;
        Node*x = &g[u],*y=&g[v];make_root(x); make_root(y);
        x->splay();if(x->pp) x->pp=0;else x->unlink(0);
    }
    void make_root(Node*u){access(u);u->ev^=1;access(u);}
    Node*access(Node*x){
        Node*u = x; u->splay();
        while(Node*pp=u->pp){
            pp->splay();u->pp=0;
            if(pp->c[1])swap(pp->c[1]->p,pp->c[1]->pp);
            pp->c[1]=u;pp->recalc();u=pp;
        }
        x->splay();
        if(x->c[1]){x->c[1]->pp=x;x->unlink(1);}
        return u;
    }
    int lca(int u, int v){access(&g[u]);return access(&g[v])->id;}
};
