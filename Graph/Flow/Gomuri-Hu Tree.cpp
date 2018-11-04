// ret = gomuri-hu tree
// edge e : i to ret[i].second with cost=ret[i].first 
Dinic dinic ;
struct edg{int s,e,x;};
vector<edg>edgs; // original graph

void clear(){edgs.clear();}
void add_edge(int s,int e,int x) {
    edgs.push_back({s,e,x});
}
#define maxn 1000
bool vis[maxn];
void dfs(int x) {
    if(vis[x])return;
    vis[x]=1;
    for(auto&i:dinic.g[x]) {
        if(dinic.e[i].cap-dinic.e[i].flow>0)
            dfs(dinic.e[i].b);
    }
}
vector<pair<int,int> >solve(int n) {
    vector<pair<int,int> >ret(n);
    for(int i=1; i<n; i++) {
        dinic.init();
        for(auto&j : edgs) {
            dinic.addEdge(j.s,j.e,j.x);
            dinic.addEdge(j.e,j.s,j.x);
        }
        dinic.s=i;
        dinic.t=ret[i].second;
        ret[i].first=dinic.dinic();
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
