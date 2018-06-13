//MO
//Given an array of N integers indexed from 1 to N, and q queries, each in the form i j,
//Find the number of distinct integers from index i to j (inclusive).

int S;
int A[MAX];
int Ans[MAX];
bool vis[MAX];
int Count[MAX];

struct Q{
    int L,R,id;
    Q (){}
    Q(int x,int y,int i){L=x;R=y;id=i;}
    bool operator<(const Q other)const {
      if (L/S!=other.L/S) return L/S<other.L/S;
      return R>other.R;
    }
}my[MAX];

int Unique;
bool Check(int x){
    if(!vis[x]) {vis[x]=1;  if(Count[A[x]]==0) Unique++; Count[A[x]]++;}
    else        {vis[x]=0;  Count[A[x]]--; if(Count[A[x]]==0) Unique--;}
}

int main(){
    int n,q,a,b;
    int t;
    scanf("%d",&t);

    for(int cs=1;cs<=t;cs++){
        scanf("%d %d",&n,&q);
        Unique=0;
        S=sqrt(n);
        memset(vis,0,sizeof(vis));
        memset(Count,0,sizeof(Count));
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        for(int i=1;i<=q;i++) {scanf("%d %d",&a,&b); my[i]=Q(a,b,i);}
        sort(my+1,my+q+1);

        int left=my[1].L;
        int right=my[1].L-1;
        for(int i=1;i<=q;i++){
            Q now=my[i];
            while(left<now.L)  Check(left++);
            while(left>now.L)  Check(--left);
            while(right<now.R) Check(++right);
            while(right>now.R) Check(right--);
            Ans[my[i].id]=Unique;
        }
    }
}

//MO on Tree Path
BuildSparse(){...}
LCA(){...}
int main(){
	......
	for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        if(D[u]>D[v]) swap(u,v);
        int lca=LCA(u,v);
        if(lca==u) my[i]=Q(st[u],st[v],i);    //Case 1 : range(st[u],st[v])
        else my[i]=Q(en[u],st[v],i);          //Case 2 : range(en[u],st[v]) and LCA(u,v)
    }
    ......
    for(int i=1;i<=m;i++){
        Q now=my[i];
	......
        int lca=LCA(A[left],A[right]);
        if(A[left]!=lca && A[right]!=lca) Check(lca); //Adding LCA(u,v) for Case 2
        Ans[my[i].id]=Unique;
        if(A[left]!=lca && A[right]!=lca) Check(lca); //Discarding the Addition
    }
}
