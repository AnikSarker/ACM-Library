//MinCostMaxFlow(Bellman Ford)
//Weighted Bipartite Matching

#define MAX_V 3777
#define INF INT_MAX
#define ll long long int

struct NODE{
    ll v,Cap,Cost,RevInd;
    NODE() {}
    NODE(ll a,ll b,ll c,ll d) {v=a; Cap=b; Cost=c; RevInd=d;}
};

vector<NODE>Edge[MAX_V+7];
int nV,SRC,TNK;
ll Par[MAX_V+7],PInd[MAX_V+7],SD[MAX_V+7];

void SetEdge( ll u,ll v,ll Cap,ll Cost){
    NODE U=NODE(v,Cap,Cost,Edge[v].size());
    NODE V=NODE(u,0,-Cost,Edge[u].size());
    Edge[u].push_back(U);
    Edge[v].push_back(V);
}

bool BFord(){
    for(int i=0;i<nV;i++){
        Par[i]=-1;
        SD[i]=INF;
    }
    bool IsChange=true;
    SD[SRC]=0;
    while(IsChange){
        IsChange =false;
        for(int u=SRC;u<=TNK;u++){
            for(int i=0; i<Edge[u].size(); i++){
                if(!Edge[u][i].Cap) continue;
                ll v=Edge[u][i].v;
                ll TD=SD[u]+Edge[u][i].Cost;

                if(SD[v]>TD){
                    SD[v]=TD;
                    Par[v]=u;
                    PInd[v]=i;
                    IsChange=true;
                }
            }
        }
    }
    return Par[TNK]!=-1;
}

ll FindVol(ll s,ll t){
    ll Cap=Edge[ Par[t]][ PInd[t]].Cap;
    if(s==Par[t]) return Cap;
    else return min(Cap,FindVol(s,Par[t]));
}

ll AugmentPath(ll s,ll t,ll V){
    if(s==t) return 0;
    ll Cost =Edge[Par[t]][PInd[t]].Cost*V;
    Edge[Par[t]][PInd[t]].Cap -=V;
    Edge[t][ Edge[Par[t]][PInd[t]].RevInd].Cap +=V;
    return Cost+AugmentPath( s,Par[t],V);
}

void MinCost(ll &Flow,ll &Cost){
    Flow=Cost=0;
    while(BFord())    {
        ll V=FindVol(SRC,TNK);
        Flow+=V;
        Cost+=AugmentPath(SRC,TNK,V);
    }
}

int ManX[MAX_V],ManY[MAX_V],HouseX[MAX_V],HouseY[MAX_V];
string s;

int main(){
    int n,m;
    scanf("%d %d",&n,&m);

    int CountH=0,CountM=0;
    for(int i=0;i<n;i++){
        cin>>s;
        for(int j=0;j<m;j++){
            if(s[j]=='m'){
                ManX[++CountM]=i;
                ManY[CountM]=j;
            }
            if(s[j]=='H'){
                HouseX[++CountH]=i;
                HouseY[CountH]=j;
            }
        }
    }

    SRC=0,TNK=2*CountM+1,nV=2*CountM+2;
    for(int i=0; i<nV; i++) Edge[i].clear();
    for(int i=1; i<=CountM; i++) SetEdge(SRC,i,1,0);
    for(int i=1; i<=CountH; i++) SetEdge(i+CountM,TNK,1,0);

    for(int i=1;i<=CountM;i++){
        for(int j=1; j<=CountH; j++){
            ll dist=abs(ManX[i]-HouseX[j])+abs(ManY[i]-HouseY[j]);
            SetEdge(i,j+CountM,1,dist);
        }
    }

    ll flow=0;
    ll Cost=0;
    MinCost(flow,Cost);
}
