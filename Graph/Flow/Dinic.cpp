const int MAXN = 5000+5 ;
typedef long long T;
const T INF = 1e15 ;
const T eps = 0;
struct edge {
    int a, b;
    T cap,flow;
    int yo, x, y;
};
struct Dinic {
    int s,t,d[MAXN], ptr[MAXN] ;
    vector<edge>e;
    vector<int>g[MAXN];
    void init() {
        e.clear();
        memset(d,0,sizeof(d));
        for(int i = 0; i < MAXN ; i++)g[i].clear();
    }
    void addEdge(int a,int b,T cap, int x = -1, int y= -1) {
        edge e1 = { a, b, cap, 0, 1, x, y } ;
        edge e2 = { b, a, 0, 0, 0, x, y } ;
        g[a].push_back((int)e.size());
        e.push_back(e1);
        g[b].push_back((int)e.size());
        e.push_back(e2);
    }
    bool bfs() {
        queue < int > Q ;
        Q.push(s);
        memset(d,-1,sizeof(d));
        d[s]=0 ;
        while (!Q.empty()) {
            int u=Q.front() ;
            Q.pop() ;
            for(int i=0; i<g[u].size(); i++) {
                int id=g[u][i];
                int v=e[id].b;
              //  printf("%d %d %0.3lf %0.3lf\n",u,v,e[id].cap,e[id].flow);
                if(d[v]==-1&&e[id].flow<e[id].cap) {
                    Q.push(v) ;
                    d[v]=d[u]+1 ;
                }
            }
        }
        return d[t]!=-1 ;
    }
    T dfs(int u,T flow) {
        if (flow<=eps)  return 0 ;
        if ( u==t )  return flow ;
        for(int& i = ptr[u] ; i<g[u].size(); i++) {
            int id = g[u][i];
            int v =  e[id].b ;
            if ( d[v] != d[u]+1 )  continue ;
            T pushed = dfs (v,min (flow,e[id].cap-e[id].flow)) ;
            //cout << "pushed " << pushed << endl;
            if (pushed>eps) {
                e [id].flow+=pushed ;
                e [id^1].flow-=pushed ;
                return pushed ;
            }
        }
        return 0 ;
    }
    T dinic() {
        T flow = 0 ;
        while(true) {
            if(!bfs())  break ;
            memset(ptr, 0, sizeof(ptr)) ;
            while (true){
                T pushed = dfs(s,INF );
                if(pushed<=eps)break;
                flow += pushed ;
            }
        }
        return flow ;
    }
};
