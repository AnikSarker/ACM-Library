typedef long long ll;
const int maxn = 2 * 100005;
struct TwoSat {
    int n;
    vector<int> G[maxn * 2];
    // i = x', i+n = x , x = variable , i = index
    bool mark[maxn * 2];//store actual value
    int S[maxn * 2],c;
    bool dfs(int x) {
        if(mark[x + n]) return false;
        if(mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for(int i = 0; i < G[x].size(); i++) {
            if(!dfs(G[x][i])) return false;
        }
        return true;
    }
    void init(int n) {
        this -> n = n;
        for(int i = 0; i < n * 2; i++) G[i].clear();
        memset(mark,0,sizeof(mark));
    }
    void add_clause(int x,int y) {
        G[x].push_back(y);
        //printf("%d ----- %d\n",x + 1,y + 1);
    }
    bool solve() {
        for(int i = 0; i < n; i ++) {
            if(!mark[i] && !mark[i + n]) {
                c = 0;
                if(!dfs(i)) {
                    while(c > 0) mark[S[--c]] = false;
                    if(!dfs(i + n)) return false;
                }
            }
        }
        return true;
    }
}sat;
