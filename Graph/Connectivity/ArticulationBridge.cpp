#define MAX 100005
#define f first
#define s second
int cnt;
vector<vector<int> > graph(MAX);
int d[MAX],md[MAX],vis[MAX];
map<pair<int,int>,int> bridges;
int all_bridges(int now,int from) {
    d[now]=md[now]=cnt++;
    vis[now]=1;
    int i;
    for(i=0; i<graph[now].size(); i++) {
        if(graph[now][i]==from) continue;
        if(vis[graph[now][i]]) {
            md[now]=min(md[now],d[graph[now][i]]);
            continue;
        }
        md[now]=min(md[now],all_bridges(graph[now][i],now));
        if(md[graph[now][i]]>d[now])
            bridges[{min(now,graph[now][i]),max(now,graph[now][i])}]=1;
    }
    return md[now];
}
