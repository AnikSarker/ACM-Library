// can be used as online minimum spanning tree
// dynamic add edge & cut edge
// check the size of connected component
// check whether two node is connected
const int MAXN = 100005;
const int MAXM = 300005;

struct node {
    node *l, *r, *p, *m; int f, v, w, s, id;
    node(int v, int w, int id) : l(), r(), p(),
    m(this), f(), v(v), w(w), s(w), id(id) {}
};

inline bool is_root(node *n){return n->p==NULL||n->p->l!=n&&n->p->r!=n;}
inline bool left(node *n){return n == n -> p -> l;}
inline int sum(node *n){return n ? n -> s : 0;}
inline node* max(node *n){return n ? n -> m : NULL;}
inline node* max(node *a, node *b) {
    if(a == NULL || b == NULL) return a ? a : b;
    return a -> v > b -> v ? a : b;
}
inline void push(node *n) {
    if(!n -> f) return;n -> f = 0;swap(n -> l, n -> r);
    if(n -> l) n -> l -> f ^= 1;if(n -> r) n -> r -> f ^= 1;
}
inline void pull(node *n) {
    n -> m = max(max(max(n -> l), max(n -> r)), n);
    n -> s = sum(n -> l) + sum(n -> r) + n -> w;
}
inline void connect(node *n, node *p, bool l) {
    (l ? p -> l : p -> r) = n; if(n) n -> p = p;
}
inline void rotate(node *n) {
    node *p = n -> p, *g = p -> p; bool l = left(n);
    connect(l ? n -> r : n -> l, p, l);
    if(!is_root(p)) connect(n, g, left(p)); else n -> p = g;
    connect(p, n, !l);pull(p), pull(n);
}
inline void splay(node *n) {
    while(!is_root(n)) {
        node *p = n -> p;
        if(!is_root(p)) push(p -> p);
        push(p), push(n);
        if(!is_root(p)) rotate(left(n) ^ left(p) ? n : p);
        rotate(n);
    }
    push(n);
}
inline void expose(node *n) {
    node *last = NULL;
    for(node *m = n; m; m = m -> p) {
        splay(m);
        m -> w -= sum(last); m -> w += sum(m -> r);
        m -> r = last; last = m; pull(m);
    }
    splay(n);
}
inline void evert(node *n){expose(n);n -> f ^= 1;}
inline void link(node *m,node *n){evert(m);expose(n);m->p=n;n->w+=sum(m);}
inline void cut(node *m,node *n){evert(m);expose(n);n->l=n->l->p=NULL;}
inline node* path_max(node *m,node *n){evert(m);expose(n);return n->m;}
inline int size(node *n){evert(n);return sum(n);}
bool connected(node *m,node *n){expose(m);expose(n);return m->p!=NULL;}
struct edge {
    int a, b, w, id;
    bool operator<(const edge e) const {return w != e.w ? w > e.w : id > e.id;}
};
int n, m, o;
node *v[MAXN],*ev[MAXM];
vector<edge> ed;
set<edge> s;
void delete_edge(edge e){cut(v[e.a],ev[e.id]);cut(v[e.b],ev[e.id]);}
void add_edge(edge e) {link(v[e.a],ev[e.id]);link(v[e.b],ev[e.id]);}
void new_edge(int a, int b, int w) {
    int id = ed.size();
    edge e = {a, b, w, id};
    ed.push_back(e);
    ev[id] = new node(w, 0, id);
    if(connected(v[a], v[b])) {
        node* m = path_max(v[a], v[b]);
        if(m -> v <= w) return;
        delete_edge(ed[m -> id]);
        s.erase(ed[m -> id]);
    }
    add_edge(e);
    s.insert(e);
}
void init(){for(int i=1;i<=n;i++){v[i]=new node(0,1,-i);}}

