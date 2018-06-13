//Articulation Point
vector<int>adj[MAX];
bool vis[MAX],art[MAX];
int d[MAX],low[MAX],par[MAX];
int Time;

int findArticulation(int u){
    Time++;
    vis[u]=true;
    d[u]=low[u]=Time;
    int child=0;

    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        child++;

        if(vis[v]==0){
            par[v]=u;
            findArticulation(v);
            low[u]=min(low[u],low[v]);
            if(child>1 && par[u]==-1) art[u]=true;
            if(par[u]!=-1 && low[v]>=d[u]) art[u]=true;
        }
        else{
            if(v!=par[u]) low[u]=min(low[u],d[v]);
        }
    }
}

int main(){
    int n,m,u,v;
    scanf("%d %d",&n,&m);

    for(int i=1;i<=n;i++) adj[i].clear();
    memset(par,-1,sizeof(par));
    memset(vis,0,sizeof(vis));
    memset(art,0,sizeof(art));
    Time=0;

    int Count=0;
    for(int i=0;i<m;i++)    {
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1; i<=n; i++) if(!vis[i]) findArticulation(i);
    for(int i=1; i<=n; i++) if(art[i]) Count++;
}
