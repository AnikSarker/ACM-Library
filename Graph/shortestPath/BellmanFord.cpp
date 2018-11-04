typedef double ll;
const int maxn = 105;
const int maxm = 10005;
const ll inf = 1e9;
ll d[maxn],w[maxm];
int u[maxm],v[maxm],n,m;
bool BellmanFord(){//1-indexed
    for(int i=1;i<=n;i++)d[i]=inf;
    d[1]=0;
    for(int i=1; i<=n; i++)
        for(int j=0; j<m; j++)
            if(d[u[j]]+w[j] < d[v[j]])
                d[v[j]]=d[u[j]]+w[j];
    bool negCycle = false;
    for(int j=0; j<m; j++)
        if(d[u[j]]+w[j] < d[v[j]]) {
            negCycle=true;
            break;
        }
    return negCycle;
}
