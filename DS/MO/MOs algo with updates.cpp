#define ll long long int
const int MAXN = 300005;
const int MAXQ = 300005;

int Sz;
ll currAns;
struct Query{
    int L,R,t,id;
    Query() {}
    Query(int _L,int _R,int _upd,int _id) {L=_L; R=_R; t=_upd; id=_id;}
    bool operator < (const Query o){
        if(L/Sz != o.L/Sz) return L < o.L;
        if(R/Sz != o.R/Sz) return R < o.R;
        return t < o.t;
    }
}OnlyQry[MAXQ];

ll ans[MAXQ];
tuple<int,int,int> AllQ[MAXQ], OnlyUpd[MAXQ];

vector <int> forsort;
unordered_map <int, int> ID;

bool vis[MAXN];
int A[MAXN], Count[MAXN];
int dummy[MAXN], ValBeforeUpd[MAXN];

void DoUpdate(int idx){
    int i = get<1>(OnlyUpd[idx]);
    int Prv = get<2>(OnlyUpd[idx]);
    int New = A[i]; A[i] = Prv;
    if(!vis[i]) return;
    if(New != -1) {Count[New]--;  if(Count[New] == 0) currAns -= forsort[New - 1];}
    if(Prv != -1) {Count[Prv]++;  if(Count[Prv] == 1) currAns += forsort[Prv - 1];}
}

void UnDoUpdate(int idx){
    int i = get<1>(OnlyUpd[idx]);
    int Prv = ValBeforeUpd[idx];
    int New = A[i]; A[i] = Prv;
    if(!vis[i]) return;
    if(New != -1) {Count[New]--; if(Count[New] == 0) currAns -= forsort[New - 1];}
    if(Prv != -1) {Count[Prv]++; if(Count[Prv] == 1) currAns += forsort[Prv - 1];}
}

void Add(int x){
    if(A[x] == -1) return;
    if(Count[A[x]]==0) currAns += forsort[A[x]-1]; Count[A[x]]++;
}

void Remove(int x){
    if(A[x] == -1) return;
    Count[A[x]]--; if(Count[A[x]]==0) currAns -= forsort[A[x]-1];
}

void Check(int x){
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
    int Cnt = 0;
    for(int x : forsort){
        Cnt++;
        if(x % 3) ID[x] = -1;
        else ID[x] = Cnt;
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
        int Upd = OnlyQry[i].t;

        while(currUpd < Upd) DoUpdate(++currUpd);
        while(currUpd > Upd) UnDoUpdate(currUpd--);

        while(left<L) Check(left++);
        while(left>L) Check(--left);
        while(right<R) Check(++right);
        while(right>R) Check(right--);
        ans[OnlyQry[i].id] = currAns;
    }
    for(int i=1;i<=QryNo;i++) printf("%lld\n",ans[i]);
}
