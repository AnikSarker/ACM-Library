const int inf = 1e9;
const int N = 1e5;
int dis[N],n,m,k,p,g,t,a[N],par[N];
vector<int>adj[N],cost[N];
#define uu second
#define ww first
void dijkstra(int src ) { //VlogV+E
    priority_queue< pair < int, int > > pq ;
    pq.push( make_pair( 0, src ) ) ;
    for( int i = 0; i <= n ; i++ ) dis[i] = inf ;
    dis[src] = 0 ;
    while( !pq.empty() ) {
        pair<int,int>node = pq.top() ;
        int u = node.uu;
        pq.pop();
        if(dis[u]<-node.ww)continue;
        for( int i =0; i <adj[u].size() ; i++ ) {
            int v = adj[u][i] ;
            int w = cost[u][i] ;
            if(dis[u]+w<dis[v]) {
                dis[v]=dis[u]+w;
                par[v]=u;
                pq.push( make_pair( -dis[v], v ) ) ;
            }
        }
    }
}
