//MST (Kruskal)
#define f first
#define s second
#define mp make_pair
#define pii pair<int,int>
#define piii pair<int,pii>

int n,e;
int par[MAX];
piii edge[MAX];
 
int Find(int x){
    if(x!=par[x]) par[x]=Find(par[x]);
    return par[x];
}
 
int Kruskal(){
    sort(edge,edge+e);
 
    int cost=0;
    int takenEdges=0;
    for(int i=0;i<e;i++){
        int pu=Find(edge[i].s.f);
        int pv=Find(edge[i].s.s);
        if(pu!=pv){
            cost+=edge[i].f;
            par[pu]=par[pv];
            takenEdges++;
        }
    }
	
  if(takenEdges!=n-1) return -1;                 //No spanning tree
  else return cost;
}
