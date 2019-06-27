#define ll long long int
const int MAXN = 300005;
const int MAXQ = 300005;

int Sz;
ll currAns;
struct Query{
    int L,R,BeforeUpd,idx;
    Query() {}
    Query(int _L,int _R,int _upd,int _idx) {L=_L; R=_R; BeforeUpd=_upd; idx=_idx;}
    bool operator < (const Query other){
        int a = L/Sz; int b = other.L / Sz;
        int c = R/Sz; int d = other.R / Sz;
        if(a != b) return a < b;
        if(c != d) return c < d;
        return BeforeUpd < other.BeforeUpd;
    }
}OnlyQry[MAXQ];

vector <ll> forsort;
unordered_map <ll, ll> ID;

ll ans[MAXQ];
tuple<ll,ll,ll> AllQ[MAXQ], OnlyUpd[MAXQ];

bool vis[MAXN];
ll A[MAXN], Count[MAXN], dummy[MAXN], ValBeforeUpd[MAXN];

void DoUpdate(ll idx){
    int i = get<1>(OnlyUpd[idx]);
    ll Prv = get<2>(OnlyUpd[idx]);
    ll New = A[i]; A[i] = Prv;
    if(!vis[i]) return;
    if(New != -1) {Count[New]--;  if(Count[New] == 0) currAns -= forsort[New - 1];}
    if(Prv != -1) {Count[Prv]++;  if(Count[Prv] == 1) currAns += forsort[Prv - 1];}
}

void UnDoUpdate(ll idx){
    ll i = get<1>(OnlyUpd[idx]);
    ll Prv = ValBeforeUpd[idx];
    ll New = A[i]; A[i] = Prv;
    if(!vis[i]) return;
    if(New != -1) {Count[New]--; if(Count[New] == 0) currAns -= forsort[New - 1];}
    if(Prv != -1) {Count[Prv]++; if(Count[Prv] == 1) currAns += forsort[Prv - 1];}
}

void Add(ll x){
    if(A[x]==-1) return;
    if(Count[A[x]]==0) currAns += forsort[A[x]-1]; Count[A[x]]++;
}

void Remove(ll x){
    if(A[x]==-1) return;
    Count[A[x]]--; if(Count[A[x]]==0) currAns-=forsort[A[x]-1];
}

void Check(ll x){
    if(!vis[x]) Add(x);
    else Remove(x);
    vis[x] ^= 1;
}

int main(){
    int N,Q;
    scanf("%d %d",&N,&Q);
    Sz = N/cbrt(N);

    for(int i=1;i<=N;i++) {
        scanf("%lld",&A[i]);
        dummy[i] = A[i];
        if(ID[A[i]]) continue;
        ID[A[i]] = 1;
        forsort.push_back(A[i]);
    }

    int UpdNo = 0;
    int QryNo = 0;
    for(int i=1;i<=Q;i++){
        int tp,a,b;
        scanf("%d %d %d",&tp,&a,&b);
        AllQ[i] = make_tuple(tp,a,b);

        if(tp == 0){
            OnlyUpd[++UpdNo] = AllQ[i];
            if(ID[b]) continue;
            ID[b] = 1;
            forsort.push_back(b);
        }
        else OnlyQry[++QryNo] = Query(a,b,UpdNo,QryNo);
    }

    sort(forsort.begin(), forsort.end());
    for(int i=0;i<forsort.size();i++){
        if(forsort[i] % 3) ID[forsort[i]] = -1;
        else ID[forsort[i]] = i + 1;
    }

    for(int i=1;i<=N;i++) A[i] = ID[A[i]], dummy[i] = A[i];
    for(int i=1;i<=Q;i++) if(get<0>(AllQ[i]) == 0) get<2>(AllQ[i]) = ID[get<2>(AllQ[i])];
    for(int i=1;i<=UpdNo;i++) get<2>(OnlyUpd[i]) = ID[get<2>(OnlyUpd[i])];

    for(int i=1;i<=UpdNo;i++){
        ValBeforeUpd[i] = dummy[get<1>(OnlyUpd[i])];
        dummy[get<1>(OnlyUpd[i])] = get<2>(OnlyUpd[i]);
    }
    sort(OnlyQry+1, OnlyQry+QryNo+1);

    int left = 0;
    int right = left - 1;
    int currUpd = 0;
    for(int i=1;i<=QryNo;i++){
        int L = OnlyQry[i].L;
        int R = OnlyQry[i].R;
        int Upd = OnlyQry[i].BeforeUpd;

        while(currUpd < Upd) DoUpdate(++currUpd);
        while(currUpd > Upd) UnDoUpdate(currUpd--);

        while(left<L) Check(left++);
        while(left>L) Check(--left);
        while(right<R) Check(++right);
        while(right>R) Check(right--);
        ans[OnlyQry[i].idx] = currAns;
    }
    for(int i=1;i<=QryNo;i++) printf("%lld\n",ans[i]);
}
