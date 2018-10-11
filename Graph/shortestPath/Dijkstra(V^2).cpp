#define maxN 1000
int n;
int dis[maxN],cost[maxN][maxN],par[maxN];
void Dijkstra (int start) { // v^2
    vector<int>found(n+1);
    dis[start] = 0;
    while (start != -1) {
        found[start] = true;
        int best = -1;
        for (int k = 1; k <= n; k++)
            if (!found[k]) {
                if (dis[k] > dis[start] + cost[start][k]) {
                    dis[k] = dis[start] + cost[start][k];
                    par[k] = start;
                }
                if (best==-1 || dis[k]<dis[best])best=k;
            }
        start = best;
    }
}
