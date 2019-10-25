struct edge{
    int t , v;
    edge(int t=0 ,int v=0):t(t),v(v){}
};
 // f[u][v]   = shortest Path between u to v
 // D[r][mask] = minimum cost stainer tree with root r and covering all the nodes in the mask. 
 
struct StreinerTree{
    int n;
    int f[maxn][maxn] , d[maxn][1<<maxk];
    void init(int n) {
        this->n = n;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j] = INF;
    }
    
    void addEdge(int ff , int t , int v) {
        f[ff][t] = min(v , f[ff][t]);
        f[t][ff] = min(v , f[t][ff]);
    }
    
    void floyd() {
        for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
            f[i][j] = min(f[i][j] , f[i][k]+f[k][j]);
    }
    
    void mincostST(vector<int> s) {
        for(int i=1;i<=n;i++) for(int j=0;j<(1<<s.size());j++) d[i][j] = INF;
        for(int i=0;i<s.size();i++) d[s[i]][1<<i] = 0;
        for(int i=1;i<(1<<s.size());i++) {
            for(int j=1;j<=n;j++) for(int ii = (i-1)&i;ii>0;ii = (ii-1)&i)
                d[j][i] = min(d[j][i] , d[j][ii]+d[j][i-ii]);           
            for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) d[j][i] = min(d[j][i] , d[k][i]+f[j][k]);
        }
    }
};
