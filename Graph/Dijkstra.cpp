//Dijkstra
#define MAX 100005
#define ll long long int

struct EDGE{
    int dest; ll cost;
    EDGE(int b,ll c){dest=b;cost=c;}
};

struct NODE{
    int ID; ll Dist;
    NODE(int u,int d){ID=u;Dist=d;}
    bool operator <(const NODE& other) const{
        return Dist>other.Dist;    //This is how pq works - reverse
    }
};

vector<EDGE>adj[MAX];
priority_queue<NODE>pq;
ll dist[MAX];
int n;

void dijkstra(ll u){
    for(int i=1;i<=n;i++) dist[i]=INT_MAX;
    dist[u]=0;
    pq.push(NODE(u,0));
	
    while(!pq.empty()){
        NODE now=pq.top();
        int v=now.ID;
        pq.pop();
        ## if(dist[v]<now.Dist) continue;

        for(ll i=0;i<adj[v].size();i++){
            EDGE w=adj[v][i];
            if(dist[w.dest]>dist[v]+w.cost){
                dist[w.dest]=dist[v]+w.cost;
                pq.push(NODE(w.dest,dist[w.dest]));
            }
        }
    }
}
