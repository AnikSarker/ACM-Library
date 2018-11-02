typedef pair< pair<int,int> , pair<int,int> > que;
vector< que >query;

int S = sqrt(100005);
#define L first.first
#define R first.second
#define lca second.first
#define id second.second

bool cmp(const que &P,const que &Q){
    if(P.L/S!=Q.L/S)return P.L/S<Q.L/S;
    if((P.L/S)&1)return P.R>Q.R;
    return P.R<Q.R;
}

void insert(int u){}
void erase(int u){}

void up(int idx) {
  int u = node[idx];
  vis[u]?erase(u):insert(u);
  vis[u] ^= 1;
}

void addQuery(int u,int v){
    if(st[u]>st[v])swap(u,v);//st=dfs start time
    int lca = LCA(u,v);
    if(lca!=u)query.push_back({{en[u],st[v]},{st[lca],i}});
    else query.push_back({{st[u],st[v]},{-1,i}});
}

void solve(){
    sort(query.begin(),query.end(),cmp);
    l=1;
    r=0;
    
    for (auto q : query){
        while(l>q.L) up(--l);
        while(r<q.R) up(++r);
        while(l<q.L) up(l++);
        while(r>q.R) up(r--);
    }
    
    if(q.lca!=-1) up(lca);
    calc(ans);
    if(q.lca!=-1) up(lca);
}
