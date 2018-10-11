HeavyLightDecomposition

LazySegmentTree Tree ; 
int sz[MAX];
int in[MAX];
int rin[MAX];
int out[MAX];
int head[MAX];
int par[MAX];
vector<int>g[MAX];
void dfs_sz(int u,int p) {
    sz[u] = 1;
    par[u] = p;
    for(auto &v: g[u]) {
        if(v==p)continue;
        dfs_sz(v,u);
        sz[u] += sz[v];
        if(sz[v] > sz[g[u][0]])
            swap(v,g[u][0]);
    }
}
int t;
void dfs_hld(int u,int p) {
    in[u] = ++t;
    rin[in[u]] = u;
    for(auto v: g[u]) {
        if(v==p)continue;
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v,u);
    }
    out[u] = t;
}
bool isParent(int p,int u){
    return in[p]<=in[u]&&out[u]<=out[p];
}
int n ;
int pathQuery(int u,int v){
    int ret = -inf;
    while(true){
        if(isParent(head[u],v))break;
        ret=max(ret,Tree.queryRange(1,1,n,in[head[u]],in[u]));
        u=par[head[u]];
    }
    swap(u,v);
    while(true){
        if(isParent(head[u],v))break;
        ret=max(ret,Tree.queryRange(1,1,n,in[head[u]],in[u]));
        u=par[head[u]];
    }
    if(in[v]<in[u])swap(u,v);
    ret = max(ret,Tree.queryRange(1,1,n,in[u],in[v]));
    return ret;
}
void updateSubTree(int u,int val){
    Tree.updateRange(1,1,n,in[u],out[u],val);
}
void buildHLD(int root){
    dfs_sz(root,root);
    head[root]=root;
    dfs_hld(root,root);
}
// call buildHLD
