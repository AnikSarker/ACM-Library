vector<pair<int,int> >adj[maxn];
vector<pair<int,int> >edge[maxn];
int __cnt ;
#define vv first
#define ww second
inline void addEdge(int u, int v, int w){
    edge[u].push_back({v,w});
    edge[v].push_back({u,w});
}
namespace Compress{
// make all node's degree at most 3
    void dfs(int u, int p=0){
        int cu = u ;
        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if(v==p)continue;
            dfs(v,u);
            if(i<2)addEdge(u,v,w);
            else{
                addEdge(cu,++__cnt,0);
                cu = __cnt ;
                addEdge(cu,v,w);
            }
        }
    }
}
namespace CD{
    int lvl[maxn], sub[maxn], p[maxn], vis[maxn] ;
    int total = 0;
    void calc(int u, int par) {
        p[u] = par ;
        sub[u] = 1;
        for(auto e : edge[u]) if(e.vv - par && !vis[e.vv])
            calc(e.vv, u), sub[u] += sub[e.vv];
    }
    int centroid(int u, int par, int r) {
        for(auto e : edge[u]) if(e.vv - par && !vis[e.vv])
            if(sub[e.vv] >= r) return centroid(e.vv, u, r);
        return u;
    }
    void calc2(int u){
        //cout << " yo yo " << u << endl;
    }
    void decompose(int u, int par) {
        calc(u, 0);
        total += sub[u];
        if(sub[u]==1)return ;
        int c = centroid(u,0,(sub[u]+2)/3);
        int pp = p[c] ;
        vis[pp] = 1 ; decompose(c,0) ; vis[pp]= 0;
        vis[c]= 1; decompose(pp,0); vis[c] = 0 ;
        //calc2(pp);
        //calc2(c);
    }
}
//Compress::dfs(1);
//CD::decompose(1,0);
