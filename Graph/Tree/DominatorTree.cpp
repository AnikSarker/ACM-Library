//construct DAG by dijkstra and then create dominator tree
#define uu second
typedef long long ll;
const int maxN = 100007;
const int inf=1e9;
struct DominatorTree {
    int ans[maxN],par[maxN][25], level[maxN],dis[maxN];
    vector<int>adj[maxN],cost[maxN],mama[maxN] ;
    vector<pair<int,int> >nodes ;
    void clr() {
        nodes.clear();
        for(int i = 0 ; i < maxN ; i++)adj[i].clear(),cost[i].clear(),mama[i].clear();
        memset(par,0,sizeof(par));
        memset(level,0,sizeof(level));
        memset(dis,0,sizeof(dis));
        memset(ans,0,sizeof(ans));
    }
    int lca(int u,int v) {
        if(level[u]< level[v])swap(u,v);
        int tmp=1;
        for(; (1<<tmp)<=level[u]; ++tmp);
        --tmp;
        for(int i=tmp; i>=0; --i) {
            if(level[u]-(1<<i)>=level[v])u=par[u][i];
        }
        if(u==v)return u ;
        for(int i = tmp ; i >= 0 ; --i) if(par[u][i]!=par[v][i])u=par[u][i],v=par[v][i] ;
        return par[u][0];
    }
    void dijkstra( int n, int src ) {
        priority_queue< pair < int, int > > pq ;
        pq.push( make_pair( 0, src ) ) ;
        for( int i = 0 ; i <= n ; i++ ) dis[i] = inf ;
        dis[src] = 0LL ;
        while( !pq.empty() ) {
            pair<int,int>node = pq.top() ;
            pq.pop();
            for( int i  = 0 ; i < adj[node.uu].size() ; i++  ) {
                int v = adj[node.uu][i] ;
                int w = cost[node.uu][i] ;
                if(dis[node.uu]+w<dis[v]) {
                    dis[v]=dis[node.uu]+w;
                    pq.push(make_pair(-dis[v], v) );
                }
            }
        }
    }
    void constructDag(int n, int src) {
        for(int i =1 ; i <=n; i++)
            nodes.push_back(make_pair(dis[i],i));
        sort(nodes.begin(),nodes.end());
        for(int i = 0 ; i < n ; i++) {
            int u = nodes[i].uu;
            for(int j=0; j < adj[u].size() ; j++ ) {
                int v = adj[u][j];
                int w = cost[u][j];
                if(dis[u]+w==dis[v])mama[v].push_back(u);
            }
        }
    }
    void dominatorTree(int n,int src) {
        dijkstra(n,src);
        constructDag(n,src);
        for(int i = 0; i<20; i++)par[1][i]=1;
        level[1]=1;
        n=nodes.size();
        for(int i =1; i < n ; i++) {
            int u = nodes[i].second ;
            if(mama[u].size()==0) {
                continue;
            }
            int sz = mama[u].size();
            int jaime = mama[u][0] ;
            int cur = 1 ;
            while(cur < sz ) {
                jaime = lca( jaime, mama[u][cur]) ;
                cur++;
            }
            par[u][0]=jaime;
            level[u]=1+level[jaime];
            for( int i = 1 ; i <20 ; i++ )par[u][i] = par[par[u][i-1]][i-1] ;
        }
    }
};
