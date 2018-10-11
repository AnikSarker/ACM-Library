//LCA using SparseTable
struct Info{
    int P;
    ll Dist;
    Info(){}
    Info(int a,ll d){P=a;Dist=d;}
}M[MAX][MaxLog];

Info Merge(Info D,Info U) {Info now; now.P=U.P; now.Dist=D.Dist+U.Dist; return now;}

void BuildSparse(){
    //Using 0 for uninitialized parent (Remember and use carefully)
    for(int i=1;i<=n;i++) for(int j=0;(1<<j)<n;j++) M[i][j]=Info(0,-1);
	
    for(int i=1;i<=n;i++) M[i][0]=Info(Par[i],Cost[i]);
    for(int j=1;(1<<j)<n;j++){
        for(int i=1;i<=n;i++){
             if(M[i][j-1].P!=0){
                int x=M[i][j-1].P;
                M[i][j]=Merge(M[i][j-1],M[x][j-1]);
            }
        }
    }
}

Info LCA(int p,int q){
    if (D[p]<D[q]) swap(p,q);

    Info u=Info(p,0);
    Info v=Info(q,0);

    int Log=log2(D[p])+1;
    for(int i=Log;i>=0;i--) if(D[p]-D[q]>=(1<<i)) {u=Merge(u,M[p][i]); p=M[p][i].P;}
    if(p==q) return u;

    for(int i=Log;i>=0;i--){
        if(M[p][i].P!=0 && M[p][i].P!=M[q][i].P){
            u=Merge(u,M[p][i]); p=M[p][i].P;
            v=Merge(v,M[q][i]); q=M[q][i].P;
        }
    }
    u=Merge(u,M[p][0]);
    v=Merge(v,M[q][0]);
	
    int LCA=Par[p];
    return Info(LCA,u.Dist+v.Dist);
    //Note 1 : Reversing v while merging (u,v) might be necessary in some case.
    //Note 2 : We  assign cost of an edge as the cost of the child node.
    //Note 3 : In case values/costs for each node given (instead of each edge), merge u,M[LCA][0] and v together. 
}

int kth_par(int u,int d){
    int Log=log2(d)+1;
    for(int i=Log;i>=0;i--) if(d>=(1<<i)) {u=M[u][i].P; d-=(1<<i);}
    return u;
}
