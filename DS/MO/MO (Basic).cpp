namespace MO{
    const int MAXN = 100005;
    const int MAXQ = 100005;

    int Sz;
    int A[MAXN];
    int blkId[MAXN];
    bool vis[MAXN];

    struct Query{
        int L,R,id;
        Query(){}
        Query(int x,int y,int i){L=x;R=y;id=i;}
        bool operator<(const Query other) const{
            int a = blkId[L]; int b = blkId[other.L];
            return a == b ? (a & 1 ? (R > other.R) : (R < other.R)) : a < b;
        }
    }qry[MAXQ];
    int perQ[MAXQ];

    int MaxFreq = 0;
    int CoC[MAXN];
    int Count[MAXN];
    void Check(int x){
        if(!vis[x]){
            vis[x]=1;
            if(Count[A[x]]) CoC[Count[A[x]]]--;
            Count[A[x]]++; CoC[Count[A[x]]]++;
            if(CoC[MaxFreq + 1]) MaxFreq++;
        }
        else{
            vis[x]=0;
            CoC[Count[A[x]]]--; Count[A[x]]--;
            if(Count[A[x]]) CoC[Count[A[x]]]++;
            if(CoC[MaxFreq] == 0) MaxFreq--;
        }
    }
}
using namespace MO;

int main(){
    int N,Q;
    scanf("%d %d",&N,&Q);

    //Initiate Global
    Sz=sqrt(N);
    memset(vis,0,sizeof(vis));
    memset(Count,0,sizeof(Count));
    for(int i=0;i<=N;i++) blkId[i] = i/Sz;

    for(int i=1;i<=N;i++) scanf("%d",&A[i]);
    for(int i=1;i<=Q;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        qry[i] = Query(l,r,i);
    }
    sort(qry+1,qry+Q+1);

    int left = qry[1].L;
    int right = left-1;

    for(int i=1;i<=Q;i++){
        Query now = qry[i];
        while(left<now.L)  Check(left++);
        while(left>now.L)  Check(--left);
        while(right<now.R) Check(++right);
        while(right>now.R) Check(right--);
        perQ[now.id] = MaxFreq;
    }
}
