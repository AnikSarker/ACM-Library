#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 300005
ll m, n, x, y, z, block, currAns, currR, currL, currUPDT;

typedef struct _info{
    ll L, R;
    ll BeforeUpd;
    ll IDx;
}QUERY;

QUERY OnlyQry[MAX];
unordered_map < ll, ll > ID;
vector < ll > forsort;
pair < ll, pair < ll, ll > > AllQ[MAX], OnlyUpd[MAX];
ll A[MAX], Count[MAX],ans[MAX], dummy[MAX], ValBeforeUpd[MAX];
bool vis[MAX];
bool cmp(const QUERY &a, const QUERY &b){
    if((a.L / block) != (b.L / block)) return (a.L / block) < (b.L / block);
    if((a.R / block) != (b.R / block)) return (a.R / block) < (b.R / block);
    return a.BeforeUpd < b.BeforeUpd;
}

void DoUpdate(ll IDx){
    ll i = OnlyUpd[IDx].second.first;
    ll Prv = OnlyUpd[IDx].second.second;
    ll New = A[i]; A[i] = Prv;
    if(!vis[i]) return;
    if(New != -1) {Count[New]--;  if(Count[New] == 0) currAns -= forsort[New - 1];}
    if(Prv != -1) {Count[Prv]++;  if(Count[Prv] == 1) currAns += forsort[Prv - 1];}
}

void UndoUpdate(ll IDx){
    ll i = OnlyUpd[IDx].second.first;
    ll Prv = ValBeforeUpd[IDx];
    ll New = A[i]; A[i] = Prv;
    if(!vis[i]) return;
    if(New != -1) {Count[New]--; if(Count[New] == 0) currAns -= forsort[New - 1];}
    if(Prv != -1) {Count[Prv]++; if(Count[Prv] == 1) currAns += forsort[Prv - 1];}
}

void Add(ll x){
    if(A[x]==-1) return;
    if(Count[A[x]]==0) currAns+=forsort[A[x]-1]; Count[A[x]]++;
}

void Remove(ll x){
    if(A[x]==-1) return;
    Count[A[x]]--; if(Count[A[x]]==0) currAns-=forsort[A[x]-1];
}
void Up(ll x){
    if(!vis[x])Add(x);
    else Remove(x);
    vis[x]^=1;
}
int main(){
    cin >> n >> m;
    block = n/cbrt(n);

    for(ll i = 1; i <= n; i++) {
        scanf("%lld", &A[i]);
        dummy[i] = A[i];
        if(ID[A[i]]) continue;
        ID[A[i]] = 1;
        forsort.push_back(A[i]);
    }

    ll updtno = 0, qu = 0;
    for(ll i = 1; i <= m; i++){
        scanf("%lld %lld %lld", &AllQ[i].first, &AllQ[i].second.first, &AllQ[i].second.second);

        if(AllQ[i].first == 0){
            OnlyUpd[updtno] = AllQ[i]; updtno++;
            if(ID[AllQ[i].second.second])continue;
            ID[AllQ[i].second.second] = 1;
            forsort.push_back(AllQ[i].second.second);
        }
        else{
            OnlyQry[qu].BeforeUpd = updtno;
            OnlyQry[qu].L = AllQ[i].second.first;
            OnlyQry[qu].R = AllQ[i].second.second;
            OnlyQry[qu].IDx = qu;
            qu++;
        }
    }

    sort(forsort.begin(), forsort.end());

    for(ll i = 0; i < forsort.size(); i++){
        if(forsort[i] % 3) ID[forsort[i]] = -1;
        else ID[forsort[i]] = i + 1;
    }

    for(ll i = 1; i <= n; i++) A[i] = ID[A[i]], dummy[i] = A[i];
    for(ll i = 1; i <= m; i++) if(AllQ[i].first == 0) AllQ[i].second.second = ID[AllQ[i].second.second];
    for(ll i = 0; i < updtno; i++) OnlyUpd[i].second.second = ID[OnlyUpd[i].second.second];

    for(ll i = 0; i < updtno; i++){
        ValBeforeUpd[i] = dummy[OnlyUpd[i].second.first];
        dummy[OnlyUpd[i].second.first] = OnlyUpd[i].second.second;
    }
    sort(OnlyQry, OnlyQry + qu, cmp);

    currR = 0, currL = 0, currUPDT = 0;

    for(ll i = 0; i < qu; i++){
        ll L = OnlyQry[i].L, R = OnlyQry[i].R, UPDT = OnlyQry[i].BeforeUpd;

        while(currUPDT < UPDT) DoUpdate(currUPDT++);
        while(currUPDT > UPDT) UndoUpdate(--currUPDT);

        while(currL<L)   Up(currL++);
        while(currL>L)   Up(--currL);
        while(currR<=R)  Up(currR++);
        while(currR>R+1) Up(--currR);
        ans[OnlyQry[i].IDx] = currAns;
    }
    for(ll i = 0; i < qu; i++) printf("%lld\n", ans[i]);
}
