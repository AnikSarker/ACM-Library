//MO on Tree
int Time = 0;
int Euler[2*MAXN];
vector<int> adj[MAXN];
int Par[MAXN], D[MAXN], st[MAXN], en[MAXN];

void dfs(int u,int p){
    st[u] = ++Time; Euler[Time] = u;
    Par[u] = p;
    D[u] = D[p] + 1;
    
    for(int v : adj[u]){
        if(v == p) continue;
        dfs(v,u);
    }
    en[u] = ++Time; Euler[Time] = u;
}
using namespace MO;
using namespace LCA;

int main(){
    int N,Q;
    scanf("%d %d",&N,&Q);

    //Input
    Time = 0;
    dfs(1,0);
    BuildSparse(N);

    for(int i=1;i<=Q;i++){
        int u,v;
        scanf("%d %d",&u,&v);

        if(st[u]>st[v]) swap(u,v);
        int lca = LCA(u,v);
        if(lca == u) qry[i] = Query(st[u],st[v],i);   //Case 1 : range(st[u],st[v])
        else qry[i] = Query(en[u],st[v],i);           //Case 2 : range(en[u],st[v]) and LCA(u,v)
    }

    Sz = sqrt(N);
    sort(qry+1,qry+Q+1);

    int left = qry[1].L;
    int right = left-1;
    for(int i=1;i<=Q;i++){
        Query now = qry[i];
        while(left<now.L)  Check(Euler[left++]);
        while(left>now.L)  Check(Euler[--left]);
        while(right<now.R) Check(Euler[++right]);
        while(right>now.R) Check(Euler[right--]);

        int lca = LCA(Euler[left],Euler[right]);
        if(Euler[left]!=lca && Euler[right]!=lca) Check(lca); //Adding LCA(u,v) for Case 2
        Ans[now.id]=MaxFreq;
        if(Euler[left]!=lca && Euler[right]!=lca) Check(lca); //Discarding the Addition
    }
}
