#define clr(ar) memset(ar, 0, sizeof(ar))
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))
/// Min-cost Max-flow using SPFA (Shortest Path Faster Algorithm)
/// 0 Based indexed for directed weighted graphs (for undirected graphs, just add two directed edges)
namespace mcmf{
    const int MAX = 1000010;
    const long long INF = 1LL << 60;
    long long cap[MAX], flow[MAX], cost[MAX], dis[MAX];
    int n, m, s, t, Q[10000010], adj[MAX], link[MAX], last[MAX], from[MAX], visited[MAX];
    void init(int nodes, int source, int sink){
        m = 0, n = nodes, s = source, t = sink;
        for (int i = 0; i <= n; i++) last[i] = -1;
    }
    void addEdge(int u, int v, long long c, long long w){
        adj[m] = v, cap[m] = c, flow[m] = 0, cost[m] = +w, link[m] = last[u], last[u] = m++;
        adj[m] = u, cap[m] = 0, flow[m] = 0, cost[m] = -w, link[m] = last[v], last[v] = m++;
    }
    bool spfa(){
        int i, j, x, f = 0, l = 0;
        for (i = 0; i <= n; i++) visited[i] = 0, dis[i] = INF;
        dis[s] = 0, Q[l++] = s;
        while (f < l){
            i = Q[f++];
            for (j = last[i]; j != -1; j = link[j]){
                if (flow[j] < cap[j]){
                    x = adj[j];
                    if (dis[x] > dis[i] + cost[j]){
                        dis[x] = dis[i] + cost[j], from[x] = j;
                        if (!visited[x]){
                            visited[x] = 1;
                            if (f && rand() & 7) Q[--f] = x;
                            else Q[l++] = x;
                        }
                    }
                }
            }
            visited[i] = 0;
        }
        return (dis[t] != INF);
    }
    pair <long long, long long> solve(){
        int i, j;
        long long mincost = 0, maxflow = 0;

        while (spfa()){
            long long aug = INF;
            for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]){
                aug = min(aug, cap[j] - flow[j]);
            }
            for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]){
                flow[j] += aug, flow[j ^ 1] -= aug;
            }
            maxflow += aug, mincost += aug * dis[t];
        }
        return make_pair(mincost, maxflow);
    }
}
