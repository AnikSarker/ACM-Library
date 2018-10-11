//*for only perfect matching
struct MinimumWeightedMatching {
    static const int MN = 105 ;
    int n, edge[MN][MN];
    int match[MN],dis[MN],onstk[MN] ;
    vector<int>stk;
    void init(int _n) {
        n=_n;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                edge[i][j]=0;
    }
    void add_edge(int u,int v,int w) {
        edge[u][v]=edge[v][u]=w;
    }
    bool SPFA(int u) {
        if(onstk[u])return true;
        stk.push_back(u);
        onstk[u]=1;
        for(int v=0; v<n; v++) {
            if(v!=u&&match[u]!=v&&!onstk[v]) {
                int m = match[v];
                if(dis[m]>dis[u]-edge[v][m]+edge[u][v]) {
                    dis[m]=dis[u]-edge[v][m]+edge[u][v];
                    onstk[v]=1;
                    stk.push_back(v);
                    if(SPFA(m))return true;
                    stk.pop_back();
                    onstk[v]=0;
                }
            }
        }
        onstk[u]=0;
        stk.pop_back();
        return false;
    }
    int solve() {
        for(int i=0; i<n; i+=2) {
            match[i]=i+1;
            match[i+1]=i;
        }
        while(true) {
            int found=0;
            for(int i=0; i<n; i++)dis[i]=onstk[i]=0;
            for(int i=0; i<n; i++) {
                stk.clear();
                if(!onstk[i]&&SPFA(i)) {
                    found=1;
                    while((stk.size())>=2) {
                        int u = stk.back();
                        stk.pop_back();
                        int v = stk.back();
                        stk.pop_back();
                        match[v]=u;
                        match[u]=v;
                    }
                }
            }
            if(!found)break;
        }
        int ret = 0;
        for(int i=0; i<n; i++)ret+=edge[i][match[i]];
        ret /= 2;
        return ret ;
    }
};
