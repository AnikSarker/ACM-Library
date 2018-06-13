//1D SparseTable
int n;
int A[MAX];
int M[MAX][MAXlogN];

void buildSparse(){
    for(int i=1;i<=n;i++) M[i][0]=A[i];
    for(int j=1; (1<<j)<=n ;j++){
        for(int i=1; (i+ (1<<j)-1) <=n; i++)
            M[i][j]=max(M[i][j-1],M[i + (1<<(j-1))][j - 1]);
    }
}

int Query(int i,int j){
    int k=log2(j-i+1);
    return max(M[i][k],M[j-(1<<k)+1][k]);
}

//2D SparseTable
int N;
int A[MAX][MAX];
int M[MAX][MAX][MAXlogN];

//O(n^2 logn)
//Supports Square Query
void Build2DSparse(){
    for(int k=0; (1<<k)<=N; k++){
        for(int i=1; i+(1<<k)-1 <= N; i++){
            for(int j=1; j+(1<<k)-1<= N; j++){
                if(k==0) M[i][j][k] = A[i][j];
                else{
                    int add = 1<<(k-1);
                    M[i][j][k]=max( max(M[i][j][k-1],M[i+add][j][k-1]), max(M[i][j+add][k-1],M[i+add][j+add][k-1]) );
                }
            }
        }
    }
}

//returns max of all A[i][j], where p<=i<=p+s-1 and q<=j<=q+s-1
int Query(int p,int q,int s){
    int k=log2(s);
    int add=1<<k;
    int ret1=max(M[p][q][k], M[p+s-add][q][k]);
    int ret2=max(M[p][q+s-add][k], M[p+s-add][q+s-add][k]);
    return max(ret1,ret2);
}

//O(n^2 (logn)^2
//Supports Rectangular Query
int A[MAX][MAX];
int M[MAX][MAX][MAXlogN][MAXlogN];

void Build2DSparse(int N){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            M[i][j][0][0] = A[i][j];
        }
        for(int q=1; (1<<q)<=N; q++){
            int add = 1<<(q-1);
            for(int j=1; j+add<=N; j++){
                M[i][j][0][q]=max(M[i][j][0][q-1],M[i][j+add][0][q-1]);
            }
        }
    }

    for(int p=1; (1<<p)<=N; p++){
        int add = 1<<(p-1);
        for(int i=1; i+add<=N; i++){
            for(int q=0; (1<<q)<=N; q++){
                for(int j=1; j<= N; j++){
                    M[i][j][p][q]=max(M[i][j][p-1][q],M[i+add][j][p-1][q]);
                }
            }
        }
    }
}

//returns max of all A[i][j], where x1<=i<=x2 and y1<=j<=y2
int Query(int x1,int y1,int x2,int y2){
    int kX=log2(x2-x1+1); int kY=log2(y2-y1+1);
    int addX=1<<kX;       int addY=1<<kY;

    int ret1=max(M[x1][y1][kX][kY], M[x1][y2-addY+1][kX][kY]);
    int ret2=max(M[x2-addX+1][y1][kX][kY], M[x2-addX+1][y2-addY+1][kX][kY]);
    return max(ret1,ret2);
}
