//SCC
bool vis[MAX];
vector<int>adj[MAX];
vector<int>rev[MAX];
stack<int>stk;

//Normal DFS
int dfs1(int u){
    vis[u]=true;
    for (int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(vis[v]==false) dfs1(v);
    }
    stk.push(u);
}

int cnt;
int comp[MAX],minOfComp[MAX],sizeOfComp[MAX];

//Transpose DFS
int dfs2(int u){
    vis[u]=true;
    comp[u]=cnt;
    sizeOfComp[cnt]++;
    minOfComp[cnt]=min(u,minOfComp[cnt]);
    for(int i=0;i<rev[u].size();i++){
        int v=rev[u][i];
        if(vis[v]==false) dfs2(v);
    }
}

int main(){
    int n,a,b;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) {adj[i].clear(); rev[i].clear(); scc[i].clear(); vis[i]=false;}

    for(int i=1;i<=n;i++){
        scanf("%d %d",&a,&b);
        adj[a].push_back(b);
        rev[b].push_back(a);
    }

    for(int i=1;i<=n;i++) if(vis[i]==false) dfs1(i);
    for(int i=1;i<=n;i++) vis[i]=false;

    cnt=0;
    while(!stk.empty()){
        int u=stk.top();
        stk.pop();
        if(vis[u]==false){
            cnt++;
            minOfComp[cnt]=u;
            sizeOfComp[cnt]=0;
            dfs2(u);
        }
    }

    //Forming SCC DAG
    for(int u=1;u<=n;u++){
        for(int i=0;i<adj[u].size();i++){
            int v=adj[u][i];
            if(comp[u]!=comp[v]) scc[comp[u]].pb(comp[v]);
        }
    }
}
