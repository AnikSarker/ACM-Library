#define MAX 100005
#define f first
#define s second
int cnt, d[MAX],md[MAX],vis[MAX];
bool is_cutpoint[MAX];
vector<vector<int> > graph(MAX);
int all_cutpoints(int now=0,int from=-1) {
    d[now]=md[now]=cnt++;
    vis[now]=1;
    int i,total_child=0,is_cut=0;
    for(i=0; i<graph[now].size(); i++) {
        if(graph[now][i]==from) continue;
        if(vis[graph[now][i]]) {
            md[now]=min(md[now],d[graph[now][i]]);
            continue;
        }
        total_child++;
        md[now]=min(md[now],all_cutpoints(graph[now][i],now));
        if(md[graph[now][i]]>=d[now] ) is_cut=1;
    }
    if(from==-1 && total_child>=2)is_cutpoint[now]=true;
    else if(from!=-1 && is_cut) is_cutpoint[now]=true;
    else is_cutpoint[now]=false;
    return md[now];
}
