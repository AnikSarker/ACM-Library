#define Max 1000000
#define sz(u) u.size()
#define pb push_back
struct DominatorTree {
    vector <int> g[Max], tree[Max],bucket[Max],rg[Max];
    int sdom[Max],dom[Max],label[Max],arr[Max],rev[Max],T;
    int papa[Max]; //store u's dominator in papa[u]
    int n,m,par[Max],dsu[Max];
    int Find(int u,int x=0) {
        if(u == dsu[u])return x ? -1 : u;
        int v = Find(dsu[u],x+1);
        if(v<0)return u;
        if(sdom[label[dsu[u]]]<sdom[label[u]])
            label[u] = label[ dsu[u] ];
        dsu[u] = v;
        return x ? v : label[u];
    }
    void Union(int u,int v) {dsu[v] = u;}
    void dfs0(int u) {
        ++T;
        rev[T]=u;
        arr[u]=sdom[T]=label[T]=dsu[T]=T;
        for(int i = 0; i < sz(g[u]); i++) {
            int w = g[u][i];
            if(!arr[w])dfs0(w),par[arr[w]]=arr[u];
            rg[arr[w]].pb(arr[u]);
        }
    }
    void dominator_tree_init() {
        dfs0(1);
        for(int i = T; i >= 1; i--) {
            for(int j = 0; j<sz(rg[i]); j++)
                sdom[i] = min(sdom[i],sdom[ Find(rg[i][j]) ]);
            if(i > 1)bucket[ sdom[i] ].pb(i);
            for(int j = 0; j < sz(bucket[i]); j++) {
                int w = bucket[i][j];
                int v = Find(w);
                if( sdom[w] == sdom[v] )dom[w] = sdom[w];
                else dom[w] = v;
            }
            if(i > 1)Union(par[i],i);
        }
        for(int i = 2; i <= T; i++) {
            if(dom[i] != sdom[i])dom[i] = dom[ dom[i] ];
            tree[ rev[ dom[i] ] ].pb(rev[i]);
            papa[rev[i]]=rev[dom[i]];
            //here rev[dom[i]] dominates rev[i]
        }
    }
    void Clear() {
        for(int i = 1; i <= n; i++) {
            arr[i] =  sdom[i] = dom[i] = par[i] = dsu[i] = label[i] = rev[i] = 0;
            tree[i].clear();
            g[i].clear();
            rg[i].clear();
            bucket[i].clear();
        }
        T=0;
    }
} dtree;
//dree.g[u].pb(v)&then call dominator_tree_init()
