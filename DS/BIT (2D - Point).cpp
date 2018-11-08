//2D BIT
int BIT[MAX][MAX];
void update(int x,int y,int val){  //A[x][y]+=val
    int xx=x;
    while(xx<MAX){
        int yy=y;
        while(yy<MAX) {BIT[xx][yy]+=val;yy+=(yy&-yy);}
        xx+=(xx&-xx);
    }
}

int sum(int x,int y){  //sum=SUM of all A[i][j], where 1<=i<=x and 1<=j<=y
    int ans=0;
    int xx=x;
    while(xx!=0){
        int yy=y;
        while(yy!=0) {ans+=BIT[xx][yy];yy-=(yy&-yy);}
        xx-=(xx&-xx);
    }
    return ans;
}
