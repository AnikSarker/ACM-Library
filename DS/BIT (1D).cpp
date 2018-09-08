//1D BIT
int BIT[MAX];
void update(int indx,int val){
    while(indx<MAX) {BIT[indx]+=val; indx+=(indx&-indx);}
}

int sum(int indx){
    int ans=0;
    while(indx!=0) {ans+=BIT[indx];indx-=(indx&-indx);}
    return ans;
}

int LowerBound(int v){
    int sum=0,indx=0;
    for(int i=LOGN;i>=0;i--){
        int nPos=indx+(1<<i);
        if(nPos<MAX && sum+BIT[nPos]<v) {sum+=BIT[nPos]; indx=nPos;}
    }
    //pos = maximal x such that Sum(x) < v
    return indx+1; //+1 for LowerBound
}
