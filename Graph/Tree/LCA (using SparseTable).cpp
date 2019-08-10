int Par[MAX], D[MAX];
void BuildSparse(int n){
    //Using 0 for uninitialized parent (Remember and use carefully)
    for(int i=1; i<=n; i++) for(int j=0; j<LOG; j++) P[i][j] = 0;

    for(int i=1; i<=n; i++) P[i][0] = Par[i];
    for(int j=1; j<LOG; j++){
        for(int i=1; i<=n; i++){
             if(P[i][j-1] != 0){
                 int x = P[i][j-1]; 
                 P[i][j] = P[x][j-1];
             }
        }
    }
}

int LCA(int p,int q){
    if(D[p]<D[q]) swap(p,q);

    int Log = log2(D[p])+1;
    for(int i=Log;i>=0;i--) if(D[p]-D[q] >= (1<<i)) p = P[p][i];
    if(p==q) return p;

    for(int i=Log;i>=0;i--) if(P[p][i]!=0 && P[p][i] != P[q][i]) {p = P[p][i]; q = P[q][i];}
    int LCA = Par[p];
    return LCA;
}

//Note 1 : Reversing v while merging (u,v) might be necessary in some case.
//Note 2 : We assign cost of an edge as the cost of the child node.
//Note 3 : In case values/costs for each node given (instead of each edge), merge LCA too along with merging u and v.

int kth_par(int u,int d){
    int Log = log2(d)+1;
    for(int i=Log; i>=0; i--) if(d >= (1<<i)) {u = P[u][i]; d -= (1<<i);}
    return u;
}
