//Max Flow
#define ll long long int
#define MAXN 255
#define INF 1000000000

struct edge {ll a,b,cap,flow;};
vector<ll>adj[MAXN];
int N,s,t,p;
ll d[MAXN],ptr[MAXN],q[MAXN];
vector<edge>E;
vector<ll>g[MAXN];

void add_edge(ll a,ll b,ll cap){
    edge e1={a,b,cap,0};
    edge e2={b,a,0,0};
    g[a].push_back((ll) E.size());
    E.push_back(e1);
    g[b].push_back((ll) E.size());
    E.push_back(e2);
}

bool bfs(){
    ll qh=0,qt=0;
    q[qt++]=s;
    memset(d,-1,sizeof(d));
    d[s]=0;
    while(qh<qt && d[t]==-1){
        ll v=q[qh++];
        for(int i=0;i<g[v].size();++i){
            ll id=g[v][i],
            ll to=E[id].b;
            if(d[to]==-1 && E[id].flow<E[id].cap){
                q[qt++]=to;
                d[to]=d[v]+1;
            }
        }
    }
    return d[t]!=-1;
}

ll dfs(ll v,ll flow){
    if(!flow) return 0;
    if(v==t) return flow;

    for(;ptr[v]<(ll)g[v].size();++ptr[v]){
        ll id=g[v][ptr[v]],
        ll to=E[id].b;

        if(d[to]!=d[v]+1) continue;
        ll pushed=dfs(to,min(flow,E[id].cap-E[id].flow));
        if(pushed){
            E[id].flow+=pushed;
            E[id^1].flow-=pushed;
            return pushed;
        }
    }
    return 0;
}

ll dinic(){
    ll flow=0;
    while(bfs()){
        memset(ptr,0,sizeof(ptr));
        while(ll pushed=dfs(s,INF)) flow+=pushed;
    }
    return flow;
}

int main(){
    scanf("%d",&N);
    s=0;
    t=2*N+1;

    E.clear();
    for(int i=s; i<=t; i++) g[i].clear();
    for(int i=1; i<=N; i++){
        scanf("%d",&p);
        add_edge(2*i-1,2*i,p);
        add_edge(2*i,2*i-1,p);
    }

    int e,a,b,cap;
    scanf("%d",&e);
    for(int i=1;i<=e;i++){
        scanf("%d %d %d",&a,&b,&cap);
        add_edge(2*a,2*b-1,cap);
    }

    int srcCount,sinkCount;
    scanf("%d %d",&srcCount,&sinkCount);
    for(int i=1;i<=srcCount;i++){
        scanf("%d",&p);
        add_edge(0,2*p-1,INF);
    }
    for(int i=1; i<=sinkCount; i++){
        scanf("%d",&p);
        add_edge(2*p,2*N+1,INF);
    }
    ll MaxFlow=dinic();
}
