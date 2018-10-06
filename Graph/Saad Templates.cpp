Global Mincut ( stoer Wagner N^3)

typedef long long ll;
const ll maxN = 305 ;
const ll inf = 0x3f3f3f3f ;
// Stoer-wagner algorithm, complexity: O(n^3)
// compute the global minimum cut with self-loop ignored.
ll n,m, g[maxN][maxN];
bool vis[maxN];
ll dis[maxN],v[maxN];
ll stoer_wagner() {
    ll i, j, now,ans=inf;
    for(i=0; i<n; i++)v[i]=i+1;
    while(n>1) {
        for(now=0,i=1; i<n; i++)dis[v[i]]=0;
        for(i=1; i<n; i++) {
            swap(v[now],v[i-1]);
            for(now=j=i; j<n; j++) {
                dis[v[j]]+=g[v[i-1]][v[j]];
                if(dis[v[now]]<dis[v[j]])now=j;
            }
        }
        ans=min(ans,dis[v[now]]);
        for(j=0; j<n; j++)
            g[v[j]][v[now-1]]=g[v[now-1]][v[j]]+=g[v[j]][v[now]] ;
        v[now]=v[--n];
    }
    return ans ;
}
*Stoer Wagner , O(NM*logN)
	
const int inf=1000000000;
// should be larger than max.possible mincut
#define MAXN 400
#define PB push_back
typedef pair<int,int> pii;
#define S second
#define F first
struct DisjointSet {
    int p[MAXN];
    DisjointSet(){

    }
    DisjointSet(int n) {
        iota(p,p+n,0);
    }
    void init(int n){
        iota(p,p+n,0);
    }
    int getpar(int u) {
        if(u==p[u])return u;
        return p[u]=getpar(p[u]);
    }
    void merge(int u,int v) {
        u=getpar(u);
        v=getpar(v);
        if(u!=v){
            p[u]=v;
        }
    }
};
class StoerWagner {
  public:
    int n,mc; // node id in [0,n-1]
    vector<int> adj[MAXN];
    int cost[MAXN][MAXN];
    int cs[MAXN];
    bool merged[MAXN],sel[MAXN];
    DisjointSet djs;
    vector<int> cut;
    //- 8<
    StoerWagner(int _n):n(_n),mc(inf) {
        djs.init(n);
        for(int i=0; i<n; i++)
            merged[i]=0;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                cost[i][j]=cost[j][i]=0;
    }
    void init(int _n){
        n=_n;
        mc=inf;
        cut.clear();
        djs.init(n);
        for(int i=0; i<n; i++)
            merged[i]=0,sel[i]=0,cs[i]=0,adj[i].clear();
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                cost[i][j]=cost[j][i]=0;
    }

    void append(int v,int u,int c) {
        if(v==u) return;
        if(!cost[v][u]&&c) {
            adj[v].PB(u);
            adj[u].PB(v);
        }
        cost[v][u]+=c;
        cost[u][v]+=c;
    }
    void merge(int v,int u) {
        merged[u]=1;
        for(int i=0; i<n; i++)
            append(v,i,cost[u][i]);
// include only if cut is explicitly needed
       djs.merge(v,u);
//

    }

    void phase() {
        priority_queue<pii> pq;
        for(int v=0; v<n; v++) {
            if(merged[v]) continue;
            cs[v]=0;
            sel[v]=0;
            pq.push({0,v});
        }
        int v,s,pv;

        while(pq.size()) {
            if(cs[pq.top().S]>pq.top().F) {
                pq.pop();
                continue;
            }
            pv=v;
            v=pq.top().S;
            s=pq.top().F;
            pq.pop();
            sel[v]=1;
            for(int i=0; i<adj[v].size(); i++) {
                int u=adj[v][i];
                if(merged[u]||sel[u]) continue;
                cs[u]+=cost[v][u];
                pq.push({cs[u],u});
            }
        }

        if(s<mc) {
            mc=s;
            //include only if cut is explicitly needed
            cut.clear();
            for(int i=0; i<n; i++)
                if(djs.getpar(i)==djs.getpar(v)) cut.PB(i);
        }
        merge(v,pv);
    }
    int mincut() {
        if(mc==inf)
            for(int t=0; t<n-1; t++)
                phase();

        return mc;
    }
    vector<int> getcut() { // return one side of the cut
        mincut();
        return cut;
    }
};


	

Max Flow (Dinic)

const int MAXN = 500+5 ;  const int INF = 1000000000 ;
struct edge{ int a, b, cap, flow , yo , x , y; };
struct Dinic{
   int s,t,d[MAXN] , ptr[MAXN] ;
   vector<edge>e; vector<int>g[MAXN];
   void init(){ e.clear();memset(d,0,sizeof(d)); for(int i = 0; i < MAXN ; i++)g[i].clear(); }
   void addEdge(int a,int b,int cap, int x = -1 , int y= -1){
    edge e1 = { a, b, cap, 0 , 1 , x , y } ; edge e2 = { b, a, 0  , 0 , 0 , x , y } ;
    g[a].push_back((int)e.size()); e.push_back(e1);  g[b].push_back((int)e.size()); e.push_back(e2);
   }
   bool bfs(){
       queue < int > Q ; Q.push(s); memset(d,-1,sizeof(d)); d[s]=0 ;
       while (!Q.empty()){
           int u=Q.front() ;  Q.pop() ;
           for(int i=0; i<g[u].size(); i++) {
               int id=g[u][i]; int v=e[id].b;
               if(d[v]==-1&&e[id].flow<e[id].cap) { Q.push(v) ;d[v]=d[u]+1 ;}
          }
      }
      return d[t]!=-1 ;
  }
  int dfs(int u,int flow){
     if (!flow)  return 0 ; if ( u==t )  return flow ;
     for(int& i = ptr[u] ; i<g[u].size(); i++){
          int id = g[u][i]; int v =  e[id].b ;
          if ( d[v] != d[u]+1 )  continue ;
          int pushed = dfs (v,min (flow,e[id].cap-e[id].flow)) ;
          if (pushed){  e [id].flow+=pushed ; e [id^1].flow-=pushed ; return pushed ;}
      }
      return 0 ;
  }
  int dinic(){
       int flow = 0 ;
       while(true){
          if(!bfs())  break ; memset(ptr, 0 , sizeof(ptr)) ;
          while ( int pushed = dfs(s,INF ) )  flow += pushed ;
        }
       return flow ;
    }
};

Bipartite Matching ( Kuhn )
class KuhnImplementation {
    public:
    int n, k; vector < vector<int> > g; vector<int> pairs_of_right, pairs_of_left; vector<bool> used;
    bool kuhn (int v) {
        if (used[v])  return false; used[v] = true;
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (pairs_of_right[to] == -1 || kuhn (pairs_of_right[to])) {
                pairs_of_right[to] = v; pairs_of_left[v] = to; return true;
            }
        }
        return false;
    }
    int find_max_matching(vector<vector<int> > &_g, int _n, int _k) {
        g = _g;
        n = _n;  //n is number of vertices in left part of graph
        k = _k;  //k is number of vertices in right part of graph
        pairs_of_right = vector<int> (k, -1);
        pairs_of_left = vector<int> (n, -1);
        //pairs_of_right[i] is a neighbor of vertex i from right part, on marked edge
        //pairs_of_left[i]  is a neighbor of vertex i from left part, on marked edge
        used = vector<bool> (n, false); bool path_found;
        do {
            fill(used.begin(), used.end(), false);
            path_found = false;
            //remember to start only from free vertices which are not visited yet
            for (int i = 0; i < n; ++i)
                if (pairs_of_left[i] < 0 && !used[i]) path_found |= kuhn (i);
        } while (path_found);
        int res = 0 ;
        for(int i = 0; i < k; i++) if(pairs_of_right[i] != -1) res++ ;
        return res;
    }
};






Weighted Bipartite Matching ( Kuhn Munkress )
#define maxM 107
#define maxN 107
template<typename T>
struct KuhnMunkras { // n for left, m for right
  int n, m, match[maxM];
  T g[maxN][maxM], lx[maxN], ly[maxM], slack[maxM];
  bool vx[maxN], vy[maxM];
  void init(int n_, int m_) {memset(g,0,sizeof(g)); n = n_, m = m_;}
  void add(int u, int v, T w) { g[u][v] = w;}
  bool find(int x) {
    vx[x] = true;
    for (int y = 1; y <= m; ++y) {
      if (!vy[y]) {
        T delta = lx[x] + ly[y] - g[x][y];
        if (delta== T(0)) {
          vy[y] = true;
          if (match[y] == 0 || find(match[y])) { match[y] = x;return true; }
        }
        else slack[y] = min(slack[y], delta);
      }
    }
    return false;
  }

  T matching() { // maximum weight matching
    fill(lx + 1, lx + 1 + n, 0);
    memset(ly,0,sizeof(ly)); memset(match,0,sizeof(match));
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) lx[i] = max(lx[i], g[i][j]);
    }
    for (int k = 1; k <= n; ++k) {
      fill(slack + 1, slack + 1 + m, numeric_limits<T>::max());
      while (true) {
        memset(vx,0,sizeof(vx)); memset(vy,0,sizeof(vy));
        if (find(k)) break;
        else {
          T delta = numeric_limits<T>::max();
          for (int i = 1; i <= m; ++i) { if (!vy[i]) delta = min(delta, slack[i]); }
          for (int i = 1; i <= n; ++i) {if (vx[i]) lx[i] -= delta; }
          for (int i = 1; i <= m; ++i) {
            if (vy[i]) ly[i] += delta;  if (!vy[i]) slack[i] -= delta;
          }
        }
      }
    }
    T result = 0;
    for (int i = 1; i <= n; ++i) result += lx[i];
    for (int i = 1; i <= m; ++i) result += ly[i];
    return result;
  }
};


Weighted Bipartite Graph ( Hopcroft-karp )

#define mset0(x) memset(x,0,sizeof(x))
const int maxN = 50000 ;
const int maxM = 50000 ;
struct HopcroftKarp {
    int vis[maxN], level[maxN], ml[maxN], mr[maxM];
    vector<int> edge[maxN]; // constructing edges for left part only
    void init(int n) { for (int i = 1; i <= n; ++i) edge[i].clear();}
    void add(int u, int v) {edge[u].push_back(v); }
    bool dfs(int u) {
        vis[u] = true;
        for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
            int v = mr[*it];
            if (v == -1 || (!vis[v] && level[u] < level[v] && dfs(v))) {
                ml[u] = *it;
                mr[*it] = u;
                return true;
            }
        }
        return false;
    }
    int matching(int n) { // n for left
        mset0(vis);
        mset0(level);
        memset(ml, -1,sizeof(ml));
        memset(mr, -1,sizeof(mr));
        for (int match = 0;;) {
            queue<int> que;
            for (int i = 1; i <= n; ++i) {
                if (ml[i] == -1) {
                    level[i] = 0;
                    que.push(i);
                } else level[i] = -1;
            }
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
                    int v = mr[*it];
                    if (v != -1 && level[v] < 0) {
                        level[v] = level[u] + 1;
                        que.push(v);
                    }
                }
            }
            for (int i = 1; i <= n; ++i) vis[i] = false;
            int d = 0;
            for (int i = 1; i <= n; ++i) if (ml[i] == -1 && dfs(i)) ++d;
            if (d == 0) return match;
            match += d;
        }
    }
};



General Matching ( Edmond Blossom)

const int M=500;
struct struct_edge{int v;struct_edge* n;};
typedef struct_edge* edge;
struct_edge pool[M*M*2];edge top=pool,adj[M];
int V,E,match[M],qh,qt,q[M],father[M],base[M];
bool inq[M],inb[M],ed[M][M];
void add_edge(int u,int v){
  top→v=v,top→n=adj[u],adj[u]=top++; top->v=u,top->n=adj[v],adj[v]=top++;
}
int LCA(int root,int u,int v){
  static bool inp[M];
  memset(inp,0,sizeof(inp));
  while(1){ inp[u=base[u]]=true;  if (u==root) break; u=father[match[u]];  }
  while(1){  if (inp[v=base[v]]) return v;  else v=father[match[v]];  }
}
void mark_blossom(int lca,int u){
  while (base[u]!=lca){
      int v=match[u];  inb[base[u]]=inb[base[v]]=true; u=father[v];  if (base[u]!=lca) father[u]=v;
    }
}
void blossom_contraction(int s,int u,int v){
  int lca=LCA(s,u,v); memset(inb,0,sizeof(inb)); mark_blossom(lca,u); mark_blossom(lca,v);
  if (base[u]!=lca)  father[u]=v; if (base[v]!=lca) father[v]=u;
  for (int u=0;u<V;u++) if (inb[base[u]]){ base[u]=lca; if (!inq[u]) inq[q[++qt]=u]=true; }
}
int find_augmenting_path(int s){
  memset(inq,0,sizeof(inq)); memset(father,-1,sizeof(father));
  for (int i=0;i<V;i++) base[i]=i;  inq[q[qh=qt=0]=s]=true;
  while (qh<=qt){
      int u=q[qh++];
      for (edge e=adj[u];e;e=e->n){
	  int v=e→v;
              if (base[u]!=base[v]&&match[u]!=v)
	       if ((v==s)||(match[v]!=-1 && father[match[v]]!=-1)) blossom_contraction(s,u,v);
	       else if (father[v]==-1){
		father[v]=u;
                        if (match[v]==-1) return v;
		else if (!inq[match[v]]) inq[q[++qt]=match[v]]=true;
	      }
        }
    }
  return -1;
}
int augment_path(int s,int t){
  int u=t,v,w;
  while (u!=-1){ v=father[u]; w=match[v]; match[v]=u; match[u]=v; u=w; }
  return t!=-1;
}
int edmonds(){
  int matchc=0; memset(match,-1,sizeof(match));
  for (int u=0;u<V;u++) if (match[u]==-1) matchc+=augment_path(u,find_augmenting_path(u));
  return matchc;
}

Weighted General Matching
*for only perfect matching

struct MinimumWeightedMatching{
    static const int MN = 105 ;
    int n , edge[MN][MN];
    int match[MN],dis[MN],onstk[MN] ;
    vector<int>stk;
    void init(int _n){n=_n;for(int i=0;i<n;i++) for(int j=0;j<n;j++) edge[i][j]=0;}
    void add_edge(int u,int v,int w){ edge[u][v]=edge[v][u]=w;}
    bool SPFA(int u){
        if(onstk[u])return true;
        stk.push_back(u); onstk[u]=1;
        for(int v=0;v<n;v++){
            if(v!=u&&match[u]!=v&&!onstk[v]){
                int m = match[v];
                if(dis[m]>dis[u]-edge[v][m]+edge[u][v]){
                    dis[m]=dis[u]-edge[v][m]+edge[u][v];
                    onstk[v]=1; stk.push_back(v);
                    if(SPFA(m))return true;
                    stk.pop_back(); onstk[v]=0;
                }
            }
        }
        onstk[u]=0;
        stk.pop_back();
        return false;
    }
    int solve(){
        for(int i=0;i<n;i+=2){ match[i]=i+1;match[i+1]=i; }
        while(true){
            int found=0;
            for(int i=0;i<n;i++)dis[i]=onstk[i]=0;
            for(int i=0;i<n;i++){
                stk.clear();
                if(!onstk[i]&&SPFA(i)){
                    found=1;
                    while((stk.size())>=2){
                        int u = stk.back();stk.pop_back();
                        int v = stk.back();stk.pop_back();
                        match[v]=u; match[u]=v;
                    }
                }
            }
            if(!found)break;
        }
        int ret = 0;
        for(int i=0;i<n;i++)ret+=edge[i][match[i]];
        ret /= 2;
        return ret ;
    }
};





minimum cost Maximum Flow
*no negative cycle is allowed

typedef int LL;
const double eps = 0.005; const int maxn = 20100; const ll mod = 1e9+7; const int INF = 1e9;
struct Edge { int from, to, cap, flow, cost;};
struct MCMF {
    int n, m, s, t; vector<Edge> edges; vector<int> G[maxn];
    int inq[maxn], d[maxn], p[maxn], a[maxn];
    void init(int n) { this->n = n; for(int i = 0; i < n; i++) G[i].clear(); edges.clear(); }
    void AddEdge(int from, int to, int cap, int cost) {
        edges.push_back((Edge) {from, to, cap, 0, cost });
        edges.push_back((Edge) { to, from, 0, 0, -cost });
        m = edges.size(); G[from].push_back(m-2);G[to].push_back(m-1);
    }
    bool BellmanFord(int s, int t, LL& ans) {
        for(int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0;inq[s] = 1;
        p[s] = 0; a[s] = INF;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop(); inq[u] = 0;
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost; p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
                }
            }
        }
        if(d[t] == INF) return false;
        ans += (LL)d[t] * (LL)a[t];  int u = t;
        while(u != s) { edges[p[u]].flow += a[t]; edges[p[u]^1].flow -= a[t]; u = edges[p[u]].from; }
        return true;
     }
    LL Mincost(int s, int t) {
        LL cost = 0;
        while(BellmanFord(s, t, cost));
        return cost;
    }
};

Minimum Cost Maximum Flow
*negative cycle is allowed!

#define PB push_back
#define SZ size()
#define MAX 405
bool done[MAX];
template <class Tf, class Tc>
struct Edge {
   int from, to, next; Tf cap, flow; Tc cost;
   Edge(int from, int to, int next, Tf cap, Tc cost) {
      this->from = from; this->to = to; this->next = next;
      this->cap = cap; this->cost = cost;this->flow = 0;
   }
};
template <class Tf, class Tc>
struct MinCostFlow {
   typedef pair <Tc, int> Pti; const Tf infF; const Tc infC; const int nodes;
   int source, sink, nodeEnd[MAX], used[MAX]; Tc dist[MAX];
   vector < Edge <Tf, Tc> > edgeList;
   MinCostFlow(int n) : nodes(n), infF(numeric_limits<Tf>::max() / 4),   infC(numeric_limits<Tc>::max() / 4) { memset(nodeEnd, -1, n * sizeof(int)); }
   void addEdge(int u, int v, Tf cap = 1, Tc cost = 0) {
      edgeList.PB(Edge<Tf, Tc> (u, v, nodeEnd[u], cap, cost)); nodeEnd[u] = (int)edgeList.SZ-1;
      edgeList.PB(Edge<Tf, Tc> (v, u, nodeEnd[v], 0, -cost));  nodeEnd[v] = (int)edgeList.SZ-1;
   }
   // dijkstra
   bool augmentPath() {
      memset(used, -1, nodes*sizeof(int)); memset(done, 0, nodes*sizeof(bool));
      fill(dist, dist+nodes, infC); queue < int > que;
       que.push(source); dist[source] = 0;  done[source] = 1;
      while(!que.empty()) {
         int nd = que.front(); done[nd] = 0; que.pop();
         for(int i = nodeEnd[nd]; i != -1; i = edgeList[i].next) {
            int ch = edgeList[i].to; Tc pot = dist[nd];
            if(edgeList[i].cap > edgeList[i].flow && pot + edgeList[i].cost < dist[ch]) {
               dist[ch] = pot + edgeList[i].cost; used[ch] = i;
               if(!done[ch]) que.push(ch);
               done[ch] = 1;
            }
         }
      }
      return dist[sink] != infC;
   }
   pair <Tf, Tc> maxFlow(int src, int snk) {
      source = src, sink = snk;  Tf flow = 0; Tc cost = 0;
      while(augmentPath()) {
         // get blocking flow
         snk = sink; Tf bflow = infF;
         while(snk != source) {
            bflow = min(bflow, edgeList[ used[snk] ].cap - edgeList[ used[snk] ].flow);
            snk = edgeList[ used[snk] ].from;
         }
         // augment path
         snk = sink;
         while(snk != source) {
            edgeList[ used[snk] ].flow += bflow; edgeList[ used[snk] ^ 1 ].flow -= bflow;
            cost += edgeList[ used[snk] ].cost * bflow; snk = edgeList[ used[snk] ].from;
         }
         flow += bflow;
      }
      return make_pair(flow, cost);
   }
};

Articulation Point
#define MAX 100005
#define f first
#define s second
int cnt, d[MAX],md[MAX],vis[MAX]; bool is_cutpoint[MAX];
vector<vector<int> > graph(MAX);
int all_cutpoints(int now=0,int from=-1){
    d[now]=md[now]=cnt++; vis[now]=1;
    int i,total_child=0,is_cut=0;
    for(i=0;i<graph[now].size();i++){
        if(graph[now][i]==from) continue;
        if(vis[graph[now][i]]){ md[now]=min(md[now],d[graph[now][i]]); continue; }
        total_child++;
        md[now]=min(md[now],all_cutpoints(graph[now][i],now));
        if(md[graph[now][i]]>=d[now] ) is_cut=1;
    }
    if(from==-1 && total_child>=2)is_cutpoint[now]=true;
    else if(from!=-1 && is_cut) is_cutpoint[now]=true;
    else is_cutpoint[now]=false;
    return md[now];
}
Articulation Bridge
#define MAX 100005
#define f first
#define s second
int cnt;
vector<vector<int> > graph(MAX);
int d[MAX],md[MAX],vis[MAX];
map<pair<int,int>,int> bridges;
int all_bridges(int now,int from){
    d[now]=md[now]=cnt++;vis[now]=1;
    int i;
    for(i=0;i<graph[now].size();i++){
       if(graph[now][i]==from) continue;
       if(vis[graph[now][i]]){ md[now]=min(md[now],d[graph[now][i]]); continue;  }
       md[now]=min(md[now],all_bridges(graph[now][i],now));
       if(md[graph[now][i]]>d[now]) bridges[{min(now,graph[now][i]),max(now,graph[now][i])}]=1;
    }
    return md[now];
}

Directed MST
const int inf = 1e9 ;
struct edge { int u, v, w;
    edge() {}
    edge(int a,int b,int c) : u(a), v(b), w(c) {}
    bool operator < (const edge& o) const {
        if (u == o.u)
       	if (v == o.v)return w < o.w;
            else  return v < o.v;
        return u < o.u;
    }
};


int dmst(vector<edge> &edges, int root, int n) {
    int ans = 0;  int cur_nodes = n;
    while (true) {
        vector<int> lo(cur_nodes, inf), pi(cur_nodes, inf);
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            if (w < lo[v] and u != v) {
                lo[v] = w; pi[v] = u;
            }
        }
        lo[root] = 0;
        for (int i = 0; i < lo.size(); ++i) {
            if (i == root) continue;
            if (lo[i] == inf) return -1;
        }
        int cur_id = 0;
        vector<int> id(cur_nodes, -1), mark(cur_nodes, -1);
        for (int i = 0; i < cur_nodes; ++i) {
            ans += lo[i]; int u = i;
            while (u != root and id[u] < 0 and mark[u] != i) {mark[u] = i;  u = pi[u]; }
            if (u != root and id[u] < 0) { // Cycle
                for (int v = pi[u]; v != u; v = pi[v]) id[v] = cur_id; id[u] = cur_id++;
            }
        }
        if (cur_id == 0) break;
        for (int i = 0; i < cur_nodes; ++i) if (id[i] < 0) id[i] = cur_id++;
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            edges[i].u = id[u]; edges[i].v = id[v];
            if (id[u] != id[v]) edges[i].w -= lo[v];
        }
        cur_nodes = cur_id;  root = id[root];
    }
    return ans;
}

*Directed MST solution 

const int INF = 1029384756;
#define MAXN 1000
#define FOR(i,x) for(auto i :x )
struct edge_t {
    int u,v,w;
    set< pair<int,int> > add, sub;
    edge_t() : u(-1), v(-1), w(0) {}
    edge_t(int _u, int _v, int _w) {
        u = _u;
        v = _v;
        w = _w;
        add.insert({u, v});
    }
    edge_t& operator += (const edge_t& obj) {
        w += obj.w;
        for (auto it : obj.add) {
            if (!sub.count(it)) add.insert(it);
            else sub.erase(it);
        }
        for (auto it : obj.sub) {
            if (!add.count(it)) sub.insert(it);
            else add.erase(it);
        }
        return *this;
    }
    edge_t& operator -= (const edge_t& obj) {
        w -= obj.w;
        for (auto it : obj.sub) {
            if (!sub.count(it)) add.insert(it);
            else sub.erase(it);
        }
        for (auto it : obj.add) {
            if (!add.count(it)) sub.insert(it);
            else add.erase(it);
        }
        return *this;
    }
} eg[MAXN*MAXN],prv[MAXN],EDGE_INF(-1,-1,INF);
int N,M;
int cid,incyc[MAXN],contracted[MAXN];
vector<int> E[MAXN];

edge_t dmst(int rt) {
    edge_t cost;
    for (int i=0; i<N; i++) {
        contracted[i] = incyc[i] = 0;
        prv[i] = EDGE_INF;
    }
    cid = 0;
    int u,v;
    while (true) {
        for (v=0; v<N; v++) {
            if (v != rt && !contracted[v] && prv[v].w == INF)
                break;
        }
        if (v >= N) break; // end
        for (int i=0; i<M; i++) {
            if (eg[i].v == v && eg[i] .w < prv[v].w)
                prv[v] = eg[i];
        }
        if (prv[v].w == INF) // not connected
            return EDGE_INF;
        cost += prv[v];
        for (u=prv[v].u; u!=v && u!=-1; u=prv[u].u);
        if (u == -1) continue;
        incyc[v] = ++cid;
        for (u=prv[v].u; u!=v; u=prv[u].u) {
            contracted[u] = 1;
            incyc[u] = cid;
        }
        for (int i=0; i<M; i++) {
            if (incyc[eg[i].u] != cid && incyc[eg[i].v] ==
                    cid) {
                eg[i] -= prv[eg[i].v];
            }
        }
        for (int i=0; i<M; i++) {
            if (incyc[eg[i].u] == cid) eg[i].u = v;
            if (incyc[eg[i].v] == cid) eg[i].v = v;
            if (eg[i].u == eg[i].v) eg[i--] = eg[--M];
        }
        for (int i=0; i<N; i++) {
            if (contracted[i]) continue;
            if (prv[i].u>=0 && incyc[prv[i].u] == cid)
                prv[i].u = v;
        }
        prv[v] = EDGE_INF;
    }
    return cost;
}
#define F first
#define S second
void solve() {
    edge_t cost = dmst(0);
    for (auto it : cost.add) { // find a solution
        E[it.F].push_back(it.S);
        prv[it.S] = edge_t(it.F,it.S,0);
    }
}


MST : Prim’s Algorithm

initial distance of all nodes are INFINITE except the starting node , which distance is 0.
and all nodes are marked as non-visited.
Now until all nodes are visited, pick the non-visited node u which distance is lowest than all other non-visited nodes.After picking any nodes, update its all adjacent node v’s distance if dis[u]+edgeCost(u,v)<dis[v] .  

MST : Borukuva’s Algorithm
*all edge cost must be distinct.
initially all nodes are individual components.
While there is more than one components,
	for each components	
		find the smallest edge which connects this component to any other component. And 		then add this edge.
These edges are the edges of minimum spanning tree.

2SAT
const int N = 100005;
struct twoSAT{
 int Ans , n, m, s[N] ,x,y,ck[2*N], up[2*N] ;
 vector < int >ans, bro[2*N],orb[2*N],scc[2*N], graph[2*N] ; stack < int > Stack ;
 void addEdge(int u, int v ) {
    int ux,vx,uy,vy;
    if(u>0)ux=2*u-1,uy=ux-1;else uy=2*(-u)-1,ux=uy-1;
    if(v>0)vx=2*v-1,vy=vx-1;else vy=2*(-v)-1,vx=vy-1;
    bro[uy].push_back(vx) ;bro[vy].push_back(ux) ;
   orb[vx].push_back(uy) ;orb[ux].push_back(vy) ;
 }
 void go(int u) {
    if(ck[u]!=-1)return;ck[u]=0; for(int i=0;i<bro[u].size();i++ )go(bro[u][i]) ;Stack.push(u) ;
}
 void go(int u, int id) {
    if(ck[u]!=0)return;ck[u] = id ; scc[id].push_back(u);
    for(int i=0;i<orb[u].size();i++)go(orb[u][i],id);
 }
void graph_compression(){
    int r = 2*m ;
    for(int u =0;u<r;u++)for(int i=0;i<bro[u].size();i++){
            int v = bro[u][i];graph[ck[u]].push_back(ck[v]) ;
        }
}
int theLastCalc(int u ) {
    if(ck[u]!=0) return up[u];ck[u]=1;
    for( int i=0;i<graph[u].size();i++){up[u]|=theLastCalc(graph[u][i]);}
    for( int i=0;i<scc[u].size();i++){
        int ux =scc[u][i]|1; ux =(ux+1)>>1 ;
        if(s[ux]!=-1&&(scc[u][i]&1)!=s[ux]){up[u]=1;break;}
    }
    for(int i =0;i<scc[u].size();i++){int ux=scc[u][i]|1;ux=(ux+1)>>1;s[ux]=up[u]^(scc[u][i]&1);}
    return up[u] ;
}
void clr(){
    ans.clear();Ans=0;memset(s,-1,sizeof(s));memset(ck,-1,sizeof(ck));
    for( int i=0;i<N*2;i++)graph[i].clear(),bro[i].clear(),orb[i].clear(),scc[i].clear() ;
}
void solve(){
        scanf("%d %d",&n, &m ) ;
        for( int i = 0 ; i < n ; i++ ) {scanf("%d %d",&x,&y) ;addEdge(x,y) ;}
        int r = 2*m ; for( int i = 0 ; i < r ; i++ )go(i) ; int cnt = 0 ;
        while(!Stack.empty()) {
            int u = Stack.top() ; Stack.pop() ; if(ck[u] == 0 ) {++cnt ; go(u,cnt) ;}
         }
        Ans = 1 ;
        for( int i = 0 ; i < r ; i+=2 ) if(ck[i]==ck[i+1] ){Ans = 0;break ;}
        //only if solution is needed to show
        if(Ans == 1 ) {
            graph_compression();memset(ck,0,sizeof(ck)) ;memset(up,0,sizeof(up)) ;
            for(int i = 1 ; i <= cnt ; i++) theLastCalc(i) ;
            for( int i = 1 ; i <= m ; i++ ) if(s[i] == 1 )ans.push_back(i);
        }
}
};
      
Dijkstra        
const int inf = 1e9; const int N = 1e5;
int dis[N],n,m,k,p,g,t,a[N],par[N];
vector<int>adj[N],cost[N];
void dijkstra(int src ){ //VlogV+E
    priority_queue< pair < int, int > > pq ;pq.push( make_pair( 0, src ) ) ;
    for( int i = 0; i <= n ; i++ ) dis[i] = inf ; dis[src] = 0 ;
    while( !pq.empty() ){
        pair<int,int>node = pq.top() ;int u = node.second; pq.pop();
        if(dis[u]<-node.first)continue;
        for( int i =0;i <adj[u].size() ; i++ ){
            int v = adj[u][i] ;int w = cost[u][i] ;
            if(dis[u]+w<dis[v]){
                dis[v] dis[u]+w;par[v]=u; pq.push( make_pair( -dis[v], v ) ) ;
            }
        }
    }
}
void Dijkstra (int start){ // v^2
       vector<int> found (n+1); dis[start] = 0;
       while (start != -1){
              found[start] = true;
              int best = -1;
              for (int k = 1; k <= n; k++)
            	if (!found[k]){
                   	    if (dis[k] > dis[start] + cost[start][k]){
                                dis[k] = dis[start] + cost[start][k];
                                par[k] = start;
                            }
                            if (best==-1 || dis[k]<dis[best])best=k;
                       }
              start = best;    
        }
}

BellmenFord
void BellmanFord(){
       for(ll i=1;i<=n;i++)for(ll j=0;j<m;j++)
             if(d[u[j]]+w[j] < d[v[j]])d[v[j]]=d[u[j]]+w[j],ck[v[j]]=cs;
       bool negCycle = false;
       for(ll j=0;j<m;j++)if(d[u[j]]+w[j] < d[v[j]]){negCycle=true; break;}
}

FloydWarshall
void floydWarshall{
	for(int k=1;k<=n;k++)
	    for(int i=1;i<=n;i++)
                     for(int j=1;j<=n;j++)
		dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}




DSU

typedef int ll;
map<int,int>ck[1000006];
int id[1000006];
set<pair<int,int> >s[1000006];
int x, y, n , ans[1000006], offset[1000006];
vector<int>adj[1000006];
void go(int u,int p){
    ck[id[u]][0]=1;
    s[id[u]].insert({-1,0});
    for(int v : adj[u]){
         if(v==p)continue;
        go(v,u);
        if(s[id[v]].size()>s[id[u]].size()){
            for(auto p : s[id[u]]){
                int ki = p.second-1+offset[id[u]]-offset[id[v]];
                int koyta = ck[id[v]][ki];
                if(koyta!=0)s[id[v]].erase(s[id[v]].find({-koyta,ki}));
                koyta -= p.first ;
                s[id[v]].insert({-koyta,ki});
                ck[id[v]][ki] = koyta ;
            }
            offset[id[v]]++; swap(id[u],id[v]);
        }
        else{
            for(auto p : s[id[v]]){
                int ki = p.second+1+offset[id[v]]-offset[id[u]];
                int koyta = ck[id[u]][ki];
                if(koyta!=0)s[id[u]].erase(s[id[u]].find({-koyta,ki}));
                koyta -= p.first ;
                s[id[u]].insert({-koyta,ki});
                ck[id[u]][ki] = koyta ;
            }
        }
    }
    auto it = *(s[id[u]].begin());
    ans[u] = it.second + offset[id[u]] ;
}
int main(){
    cin>>n;
    for(int i = 1; i < n ; i++){
        scanf("%d %d",&x,&y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for(int i = 1 ; i <= n ; i++)id[i]=i;
    go(1,1);
    for(int i = 1 ; i <= n ; i++)printf("%d\n",ans[i]);
    return 0 ;
}





Manhattan MST

struct point {
  int x, y, index;
  bool operator<(const point &p) const { return x == p.x ? y < p.y : x < p.x; }
} p[maxN];
struct node {
  int value, p;
} T[maxN];

int query(int x) {
  int r = maxint, p = -1;
  for (; x <= n; x += (x & -x)) if (T[x].value < r) r = T[x].value, p = T[x].p;
  return p;
}

void modify(int x, int w, int p) {
  for (; x > 0; x -= (x & -x)) if (T[x].value > w) T[x].value = w, T[x].p = p;
}

// impl add & kruskal
int manhattan() {
  for (int i = 1; i <= n; ++i) p[i].index = i;
  for (int dir = 1; dir <= 4; ++dir) {
    if (dir == 2 || dir == 4) {
      for (int i = 1; i <= n; ++i) swap(p[i].x, p[i].y);
    } else if (dir == 3) {
      for (int i = 1; i <= n; ++i) p[i].x = -p[i].x;
    }
    sort(p + 1, p + 1 + n);
    vector<int> v; static int a[maxN];
    for (int i = 1; i <= n; ++i) a[i] = p[i].y - p[i].x, v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    for (int i = 1; i <= n; ++i) T[i].value = maxint, T[i].p = -1;
    for (int i = n; i >= 1; --i) {
      int pos = query(a[i]);
      if (pos != -1) add(p[i].index, p[pos].index, dist(p[i], p[pos]));
      modify(a[i], p[i].x + p[i].y, i);
    }
  }
  return kruskal();
}











Dominator Tree
construct DAG by dijkstra and then create dominator tree

#define uu second
typedef long long ll;const int maxN = 100007;const int inf=1e9;
struct DominatorTree {
    int ans[maxN] ,par[maxN][25], level[maxN],dis[maxN];
    vector<int>adj[maxN],cost[maxN],mama[maxN] ; vector<pair<int,int> >nodes ;
    void clr() {
        nodes.clear(); for(int i = 0 ; i < maxN ; i++)adj[i].clear(),cost[i].clear(),mama[i].clear();
        memset(par,0,sizeof(par));memset(level,0,sizeof(level));
        memset(dis,0,sizeof(dis));memset(ans,0,sizeof(ans));
    }
    int lca(int u,int v) {
        if(level[u]< level[v])swap(u,v); int tmp=1; for(; (1<<tmp)<=level[u];++tmp);  --tmp;
        for(int i=tmp; i>=0; --i) { if(level[u]-(1<<i)>=level[v])u=par[u][i];} if(u==v)return u ;
        for(int i = tmp ; i >= 0 ; --i) if(par[u][i]!=par[v][i])u=par[u][i],v=par[v][i] ; return par[u][0];
    }
    void dijkstra( int n, int src ) {
        priority_queue< pair < int, int > > pq ;pq.push( make_pair( 0, src ) ) ;
        for( int i = 0 ; i <= n ; i++ ) dis[i] = inf ;dis[src] = 0LL ;
        while( !pq.empty() ) {
            pair<int,int>node = pq.top() ;pq.pop();
            for( int i  = 0 ; i < adj[node.uu].size() ; i++  ) {
                 int v = adj[node.uu][i] ;int w = cost[node.uu][i] ;
                 if(  dis[node.uu]+w<dis[v]){dis[v]=dis[node.uu]+w;pq.push(make_pair(-dis[v], v) );
                }
            }
        }
    }
    void constructDag(int n, int src) {
        for(int i =1 ; i <=n; i++)nodes.push_back(make_pair(dis[i],i)); sort(nodes.begin(),nodes.end());
        for(int i = 0 ; i < n ; i++) {
            int u = nodes[i].uu;
            for(int j=0; j < adj[u].size() ; j++ ) {
                int v = adj[u][j];int w = cost[u][j]; if(dis[v]+w==dis[u])mama[u].push_back(v);
            }
        }
    }
    void dominatorTree(int n,int src) {
        dijkstra(n,src);constructDag(n,src);for(int i = 0 ; i < 20 ; i++ )par[1][i]=1; level[1]=1;
        n=nodes.size();
        for(int i =1; i < n ; i++) {
            int u = nodes[i].second ;if(mama[u].size()==0) {continue;}int sz = mama[u].size();
            int jaime = mama[u][0] ; int cur = 1 ;
            while(cur < sz ) {jaime = lca( jaime, mama[u][cur]) ;cur++;}
            par[u][0]=jaime;level[u]=1+level[jaime];
            for( int i = 1 ; i <20 ; i++ )par[u][i] = par[par[u][i-1]][i-1] ;
        }
    }

};




Dominator Tree
for any directed Graph

struct DominatorTree {
    vector <int> g[Max], tree[Max],bucket[Max],rg[Max];
    int sdom[Max],dom[Max],par[Max],dsu[Max],label[Max],arr[Max],rev[Max],T;
    int papa[Max] ; // papa te osbar dominator node save kora ache
    int ed[Max][2], n,m;
    int Find(int u,int x=0) {
        if(u == dsu[u])return x ? -1 : u;
        int v = Find(dsu[u],x+1); if(v < 0)return u;
        if(sdom[ label[ dsu[u] ] ] < sdom[ label[u] ]) label[u] = label[ dsu[u] ];
        dsu[u] = v;
        return x ? v : label[u];
    }
    void Union(int u,int v) {dsu[v] = u;}
    void dfs0(int u) {
        ++T;arr[u] = T;rev[T] = u;sdom[T] = T;label[T] = T; dsu[T] = T;
        for(int i = 0; i < sz(g[u]); i++) {
            int w = g[u][i]; if( !arr[w] )dfs0(w), par[ arr[w] ] = arr[u];  rg[ arr[w] ].pb( arr[u] );
        }
    }
    void dominator_tree_init() {
        dfs0(1);
        for(int i = T; i >= 1; i--) {
            for(int j = 0; j<sz(rg[i]); j++)
                sdom[i] = min(sdom[i],sdom[ Find(rg[i][j]) ]);
            if(i > 1)bucket[ sdom[i] ].pb(i);
            for(int j = 0; j < sz(bucket[i]); j++) {
                int w = bucket[i][j]; int v = Find(w);
                if( sdom[w] == sdom[v] )dom[w] = sdom[w];
                else dom[w] = v;
            }
            if(i > 1)Union(par[i],i);
        }
        for(int i = 2; i <= T; i++) {
            if(dom[i] != sdom[i])dom[i] = dom[ dom[i] ];
            tree[ rev[ dom[i] ] ].pb(rev[i]);
            tree[ rev[i] ].pb(rev[ dom[i] ]);
            papa[rev[i]]=rev[dom[i]];
            //cout << rev[dom[i]] << " -> " <<  rev[i] << endl ;
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
};

Centroid Decomposition of Tree

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100007 ;
struct centroidDecompostion {
    vector<int> tree[MAXN], centroidTree[MAXN];
    int par[MAXN] ;
    bool centroidMarked[MAXN];
    void addEdge(int u, int v) {
        tree[u].push_back(v); tree[v].push_back(u);
    }
    void DFS(int src, bool visited[], int subtree_size[], int* n) {
        visited[src] = true; *n += 1;
        subtree_size[src] = 1; vector<int>::iterator it;
        for (it = tree[src].begin(); it!=tree[src].end(); it++)
            if (!visited[*it] && !centroidMarked[*it]) {
                DFS(*it, visited, subtree_size, n); subtree_size[src]+=subtree_size[*it];
            }
    }
    int getCentroid(int src, bool visited[], int subtree_size[], int n) {
        bool is_centroid = true;  visited[src] = true;
        int heaviest_child = 0;  vector<int>::iterator it;
        for (it = tree[src].begin(); it!=tree[src].end(); it++)
            if (!visited[*it] && !centroidMarked[*it]) {
                if (subtree_size[*it]>n/2) is_centroid=false;
                if (heaviest_child==0 ||subtree_size[*it]>subtree_size[heaviest_child])
                    heaviest_child = *it;
            }
        if (is_centroid && n-subtree_size[src]<=n/2) return src;
        return getCentroid(heaviest_child, visited, subtree_size, n);
    }
    int getCentroid(int src) {
        bool visited[MAXN];int subtree_size[MAXN];
        memset(visited, false, sizeof visited); memset(subtree_size, 0, sizeof subtree_size);
        int n = 0;DFS(src, visited, subtree_size, &n);
        for (int i=1; i<MAXN; i++) visited[i] = false;
        int centroid = getCentroid(src, visited, subtree_size, n);
        centroidMarked[centroid]=true;
        return centroid;
    }
    int decomposeTree(int root) {
        int cend_tree = getCentroid(root);
        vector<int>::iterator it;
        for (it=tree[cend_tree].begin(); it!=tree[cend_tree].end(); it++) {
            if (!centroidMarked[*it]) {
                int cend_subtree = decomposeTree(*it);
                centroidTree[cend_tree].push_back(cend_subtree);
                par[cend_subtree] = cend_tree ;
            }
        }
        return cend_tree;
    }
};


 *  LCA , O(|V| log |V| + Q)
 
typedef vector<pair<int,int> > vpi; typedef vector<vpi> graph; typedef long long ll ;
int sz(graph& C){  return C.size();}
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) {
		int N = V.size(), on = 1, depth = 1;
		while (on < V.size() ) on *= 2, depth++; jmp.assign(depth, V);
		for(int i=0; i<depth-1;i++)  for(int j=0;j<N;j++)
                            jmp[i+1][j] = min(jmp[i][j], jmp[i][min(N - 1, j + (1 << i))]);
	}
	T query(int a, int b) {
                 assert(a < b); // or return inf if a == b
	     int dep = 31 - __builtin_clz(b – a);return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
struct LCA {
	vector<int> time; vector<long long> dist; RMQ<pair<int,int> > rmq;
	LCA(graph& C) : time(sz(C), -99), dist(sz(C)), rmq(dfs(C)) {}
	vpi dfs(graph& C) {
		vector<tuple<int, int, int, ll>> q(1); vector<pair<int,int> > ret; int T = 0, v, p, d; ll di;
		while (!q.empty()) {
			tie(v, p, d, di) = q.back();q.pop_back(); if (d) ret.emplace_back(d, p);
			time[v] = T++; dist[v] = di;
			for(auto &e: C[v]) if (e.first != p)
				q.emplace_back(e.first, v, d+1, di + e.second);
		}
		return ret;
	}
	int query(int a, int b) {
	    if (a == b) return a;a = time[a], b = time[b];return rmq.query(min(a, b), max(a, b)).second;
	}
	long long distance(int a, int b) {int lca = query(a, b);return dist[a] + dist[b] - 2 * dist[lca]; }
};

CompressTree , 0-rooted with specific nodes

vpi compressTree(LCA& lca, const vector<int>& subset) {
	static vector<int> rev; rev.resize(lca.dist.size()); vector<int> li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; }; sort(li.begin(),li.end(), cmp);
	int m = li.size()-1;
	for(int i=0;i<m;i++) {
		int a = li[i], b = li[i+1]; li.push_back(lca.query(a, b));
	}
	sort(li.begin(),li.end(), cmp); li.erase(unique(li.begin(),li.end()), li.end());
	for(int i=0;i<li.size();i++) rev[li[i]] = i;   vpi ret = {pair<int,int>(0, li[0])};
	for(int i=0;i<li.size()-1;i++) {
		int a = li[i], b = li[i+1];ret.emplace_back(rev[lca.query(a, b)], b);
	}
	return ret;
}



Link Cut Tree
/* Represents a forest of unrooted trees. You can add and remove edges (as long as the result is still a forest), and check whether two nodes are in the same tree.Time: O(\log N).*/
struct Node { // Splay tree. Root's pp contains tree's parent.
	Node *p = 0, *pp = 0, *c[2];bool flip = 0;
	Node() { c[0] = c[1] = 0; fix(); }
	void fix() {
		if (c[0]) c[0]->p = this;if (c[1]) c[1]->p = this;
		// (+ update sum of subtree elements etc. if wanted)
	}
	void push_flip() {
	     if (!flip) return; flip = 0; swap(c[0], c[1]);if (c[0]) c[0]->flip ^= 1;if (c[1]) c[1]->flip ^= 1;
	}
	int up() { return p ? p->c[1] == this : -1; }
	void rot(int i, int b) {
		int h = i ^ b; Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
		if ((y->p = p)) p->c[up()] = y;  c[i] = z->c[i ^ 1];
		if (b < 2) { x->c[h] = y->c[h ^ 1];z->c[h ^ 1] = b ? x : this;}
		y->c[i ^ 1] = b ? this : x; fix(); x->fix(); y->fix();if (p) p->fix(); swap(pp, y->pp);
	}
	void splay() { /// Splay this up to the root. Always finishes without flip set.
	         for (push_flip(); p; ) {
		   if (p->p) p->p->push_flip();p->push_flip(); push_flip(); int c1 = up(), c2 = p→up();
                          if (c2 == -1) p->rot(c1, 2);else p->p->rot(c2, c1 != c2);
	         }
	}
	Node* first() { /// Return the min element of the subtree rooted at this, splayed to the top.
		push_flip(); return c[0] ? c[0]->first() : (splay(), this);
	}
};
struct LinkCut {
	vector<Node> node;
	LinkCut(int N) : node(N) {}
	void link(int u, int v) { // add an edge (u, v)
		assert(!connected(u, v));make_root(&node[u]);node[u].pp = &node[v];
	}
	void cut(int u, int v) { // remove an edge (u, v)
		Node *x = &node[u], *top = &node[v]; make_root(top); x->splay();
		assert(top == (x->pp ?: x->c[0]));
		if (x->pp) x->pp = 0;else {x->c[0] = top->p = 0;x->fix();}
	}
	bool connected(int u, int v) { // are u, v in the same tree?
		Node* nu = access(&node[u])->first(); return nu == access(&node[v])->first();
	}
	void make_root(Node* u) { /// Move u to root of represented tree.
	        access(u); u->splay();
	        if(u->c[0]) {u->c[0]->p = 0;u->c[0]->flip ^= 1;u->c[0]->pp = u;u->c[0] = 0;u->fix();}
	}
	Node* access(Node* u) { /// Move u to root aux tree. Return the root of the root aux tree.
		u->splay();
		while (Node* pp = u->pp) {
			pp->splay(); u->pp = 0;if (pp->c[1]) {pp->c[1]->p = 0; pp->c[1]->pp = pp; }
			pp->c[1] = u; pp->fix(); u = pp;
		}
		return u;
	}
};
Stable Marriage
/* Numbered from 0
 * For man i, L[i] = list of women in order of decreasing preference
 * For women j, R[j][i] = index of man i in j-th women's list of preference
 * OUTPUTS:
 *      - L2R[]:    the mate of man i (always between 0 and n-1)
 *      - R2L[]:    the mate of woman j (or -1 if single)
 * COMPLEXITY: M^2
 */

#define MAXM 1024
#define MAXW 1024
int m;
int L[MAXM][MAXW], R[MAXW][MAXM];
int L2R[MAXM], R2L[MAXW];
int p[MAXM];
void stableMarriage(){
    static int p[128];
    memset(R2L, -1, sizeof R2L);
    memset(p, 0, sizeof p);
    // Each man proposes...
    for(int i = 0; i < m; i++) {
        int man = i;
        while (man >= 0) { // propose until success
            int wom;
            while (1) {
                wom = L[man][p[man]++];
                if (R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]]) break;
            }
            int hubby = R2L[wom];
            R2L[L2R[man] = wom] = man;
            man = hubby; // remarry the dumped guy
        }
    }
}

Minimum Mean Cycle

int dp[maxN][maxN]; // minimum mean cycle(allow negative weight)
double mmc(int n) {
  for (int i = 0; i < n; ++i) {
    memset(dp[i + 1], 0x7f, sizeof(dp[i + 1]));
    for (int j = 1; j <= ec; ++j) {
      int u = edge[j].u, v = edge[j].v, w = edge[j].w;
      if (dp[i][u] != maxint) dp[i + 1][v] = min(dp[i + 1][v], dp[i][u] + w);
    }
  }
  double res = maxdbl;
  for (int i = 1; i <= n; ++i) {
    if (dp[n][i] == maxint) continue; double value = -maxdbl;
    for (int j = 0; j < n; ++j) {value = max(value, double(dp[n][i] - dp[j][i]) / (n - j));}
    res = min(res, value);
  }
  return res;
}

Block-CutVertex tree

struct graph {
    int n;
    vector<vector<int>> adj;
    graph(int n) : n(n), adj(n) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int add_node() {
        adj.push_back({});
        return n++;
    }
    vector<int>& operator[](int u) {
        return adj[u];
    }
};

int node_id[500005];
int comp_id[500005];
int art[500005];
// tree = block cut tree
// return BCCs
vector<vector<int>> biconnected_components(graph &adj,graph&tree ) {
    int n = adj.n;
    vector<int> num(n), low(n), stk;
    vector<vector<int>> comps;
    function<void(int, int, int&)> dfs = [&](int u, int p, int &t) {
        num[u] = low[u] = ++t;
        stk.push_back(u);
        for (int v : adj[u]) if (v != p) {
                if (!num[v]) {
                    dfs(v, u, t);
                    low[u] = min(low[u], low[v]);
                    if (low[v] >= num[u]) {
                        art[u] = (num[u] > 1 || num[v] > 2);
                        comps.push_back({u});
                        while (comps.back().back() != v)
                            comps.back().push_back(stk.back()), stk.pop_back();
                    }
                } else low[u] = min(low[u], num[v]);
            }
    };
    for (int u = 0, t; u < n; ++u)if (!num[u]) dfs(u, -1, t = 0);
    for (int u = 0; u < n; ++u)if (art[u]) node_id[u] = tree.add_node();
    int cmpi = 0;
    for (auto &comp : comps) {
        int node = tree.add_node();
        comp_id[cmpi++]=node;
        for (int u : comp)
            if (!art[u]) node_id[u] = node;
            else tree.add_edge(node, node_id[u]);
    }
    return comps;
}

// MO ON Tree

#include <bits/stdc++.h>
using namespace std ;
int a[100005];
int p[200005],m[200005];
int pp[200005],mm[200005],ex[200005];
int n ;
vector<int>y;
vector<int>adj[100005];
int st[100005];
int en[100005];
int tim;
int par[20][100005];
int level[100005];
void go(int u,int p) {
    st[u]=++tim;
    par[0][u]=p;
    level[u]=1+level[p];
    for(int i=1; i<20; i++)par[i][u]=par[i-1][par[i-1][u]];
    for(int v:adj[u])
        if(v!=p)
            go(v,u);
    en[u]=++tim;
}

int LCA(int u,int v) {
    if(level[u]< level[v])swap(u,v);
    int tmp=1;
    for(; (1<<tmp)<=level[u]; ++tmp);
    --tmp;
    for(int i=tmp; i>=0; --i) {
        if(level[u]-(1<<i)>=level[v])u=par[i][u];
    }
    if(u==v)return u ;
    for(int i = tmp ; i >= 0 ; --i) if(par[i][u]!=par[i][v])u=par[i][u],v=par[i][v] ;
    if(par[0][u]==0)par[0][u]=1;
    return par[0][u];
}
typedef pair<pair<int,int>,pair<int,int> > que;
vector<que >query;
int S=sqrt(100005);
#define L first.first
#define R first.second
#define O second.first
#define ID second.second
bool cmp(const que &P,const que &Q){
    if(P.L/S!=Q.L/S)return P.L/S<Q.L/S;
    if((P.L/S)&1)return P.R>Q.R;
    return P.R<Q.R;
}
typedef long long ll;
ll ans[100005];
ll ml[100005];
ll fl[100005];
ll res;
void sub(int idx){
    //cout << "sub"<<endl;
    //cout << idx << " pi " << p[idx] << endl;
    res -= ml[p[idx]]*fl[p[idx]] ;
    if(m[idx]==0)fl[p[idx]]--;
    else ml[p[idx]]--;
    res += ml[p[idx]]*fl[p[idx]] ;
}
void add(int idx){
    //cout << "add"<<endl;
    //cout << idx << " pi " << p[idx] << endl;
    res -= ml[p[idx]]*fl[p[idx]] ;
    if(m[idx]==0)fl[p[idx]]++;
    else ml[p[idx]]++;
    res += ml[p[idx]]*fl[p[idx]] ;

}
int l, r;
void up(int& x,int d,int type){
    //cout <<".....\n"<< x << " " ;
    if(type==0){ // R
      //  cout << "R "<<endl;
        if(d==1){//inc
        //    cout << "inc\n";
            x++;
            if(x<ex[x])add(x);
            else if(ex[x]<l)add(x);
            else sub(x);
        }
        else{
          //  cout << "dec\n";
            if(x<ex[x])sub(x);
            else if(ex[x]<l)sub(x);
            else add(x);
            x--;
        }

    }
    else{//L
       // cout << "L "<<endl;
        if(d==1){//inc
            //cout << "inc\n";
            if(ex[x]<x)sub(x);
            else if(ex[x]>r)sub(x);
            else add(x);
            x++;
        }
        else{
            //cout << "dec\n";
            x--;
            if(ex[x]<x)add(x);
            else if(ex[x]>r)add(x);
            else sub(x);
        }
    }
   // cout << x << " " << res << endl<<endl;
}
ll check(int idx){
   if(idx==0)return res ;
    ll ret = res;
    ret -= ml[p[idx]]*fl[p[idx]] ;
    if(m[idx]==0)fl[p[idx]]++;
    else ml[p[idx]]++;
    ret += ml[p[idx]]*fl[p[idx]] ;
    if(m[idx]==0)fl[p[idx]]--;
    else ml[p[idx]]--;
    return ret;
}
int main() {
    cin>>n;
    for(int i=1; i<=n; i++)scanf("%d",&mm[i]);
    for(int i=1; i<=n; i++) {
        scanf("%d",&pp[i]);
        y.push_back(pp[i]);
    }
    sort(y.begin(),y.end());
    y.resize(unique(y.begin(),y.end())-y.begin());
    for (int i=1; i<=n; ++i)pp[i]=lower_bound(y.begin(),y.end(),pp[i])-y.begin();
    int u,v;
    for(int i=1; i<n; i++) {
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    go(1,1);
    for(int i=1; i<=n; i++) {
        p[st[i]]=p[en[i]]=pp[i];
        m[st[i]]=m[en[i]]=mm[i];
        ex[st[i]]=en[i];
        ex[en[i]]=st[i];
    }
    int q;
    cin>>q;
    for(int i=0; i<q; i++) {
        scanf("%d %d",&u,&v);
        if(st[u]>st[v])swap(u,v);
        int lca = LCA(u,v);
        if(lca!=u)query.push_back({{en[u],st[v]},{st[lca],i}});
        else query.push_back({{st[u],st[v]},{0,i}});
    }
    sort(query.begin(),query.end(),cmp);
    l=1;
    r=0;
    for(auto q : query){
        while(l>q.L)up(l,-1,1);
        while(r<q.R)up(r,1,0);
        while(l<q.L)up(l,1,1);
        while(r>q.R)up(r,-1,0);
        ans[q.ID]=check(q.O);
    }
    for(int i=0;i<q;i++)printf("%lld\n",ans[i]);

    return 0 ;
}


GomuriHu Tree

Dinic mf ;
struct edg {
    int s,e,x;
};
vector<edg>edgs;

void clear() {
    edgs.clear();
}
void add_edge(int s,int e,int x) {
    edgs.push_back({s,e,x});
}
#define maxn 1000
bool vis[maxn];
void dfs(int x) {
    if(vis[x])return;
    vis[x]=1;
    for(auto&i:mf.g[x]){
        if(mf.e[i].cap-mf.e[i].flow>0)
            dfs(mf.e[i].b);
    }
}
vector<pair<int,int> >solve(int n) {
    vector<pair<int,int> >ret(n);
    for(int i=1; i<n; i++) {
        mf.init();
        for(auto&j : edgs) {
            mf.addEdge(j.s,j.e,j.x);
            mf.addEdge(j.e,j.s,j.x);
        }
        mf.s=i;
        mf.t=ret[i].second;
        ret[i].first=mf.dinic();
        memset(vis,0,sizeof vis);
        dfs(i);
        for(int j=i+1; j<n; j++) {
            if(ret[j].second==ret[i].second&&vis[j]) {
                ret[j].second=i;
            }

        }
    }
    return ret;
}




// minimum cost circulation

#define MAXN 70
struct cost_circ {
    struct edg {
        int pos, cap, rev, cost;
    };
    vector<edg> gph[MAXN];
    void clear() {
        for(int i=0; i<MAXN; i++) gph[i].clear();
    }
    void add_edge(int s, int e, int x, int c) {
        gph[s].push_back({e, x, (int)gph[e].size(), c});
        gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
    }

    int dist[MAXN], par[MAXN], pae[MAXN];
    int negative_cycle(int n) {
        bool mark[MAXN] = {};
        memset(dist, 0, sizeof(dist));
        int upd = -1;
        for(int i=0; i<=n; i++) {
            for(int j=0; j<n; j++) {
                int idx = 0;
                for(auto &k : gph[j]) {
                    if(k.cap > 0 && dist[k.pos] > dist[j] + k.cost) {
                        dist[k.pos] = dist[j] + k.cost;
                        par[k.pos] = j;
                        pae[k.pos] = idx;
                        if(i == n) {
                            upd = j;
                            while(!mark[upd]) {
                                mark[upd] = 1;
                                upd = par[upd];
                            }
                            return upd;
                        }
                    }
                    idx++;
                }
            }
        }

        return -1;
    }
    typedef pair<int,int> pi ;
    int match(int n) {
        int rt = -1;
        int ans = 0;
        while(~(rt = negative_cycle(n))) {
            bool mark[MAXN] = {};
            vector<pi > cyc;
            while(!mark[rt]) {
                cyc.push_back(pi(par[rt], pae[rt]));
                mark[rt] = 1;
                rt = par[rt];
            }
            reverse(cyc.begin(), cyc.end());
            int capv = 1e9;
            for(auto &i : cyc) {
                auto e = &gph[i.first][i.second];
                capv = min(capv, e->cap);
            }
            for(auto &i : cyc) {
                auto e = &gph[i.first][i.second];
                e->cap -= capv;
                gph[e->pos][e->rev].cap += capv;
                ans += e->cost * capv;
            }
        }
        return ans;
    }
} circ;

