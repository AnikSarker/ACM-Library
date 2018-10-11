void calc(int l,int r,int L,int R){
    if(l>r)return;
    if(L==R){
        for(int i=l;i<=r;i++)ans[i]=L;
        return;
    }
    int mid=(l+r)/2;
    int ans=F(mid);
    calc(l,mid-1,ans,R);
    calc(mid+1,r,L,ans);
}
//call calc(1,n,0,n);
