//Solution to codeforces.com/gym/101561 - problem C
//Given a set of input points, find the nearest point (manhattan distance) for each query point
#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX
#define ll long long int
#define ld long double
#define pii pair<int,int>

const int NLOG=18, N=100000;
pair<int,int> pts[N];
int sorty[NLOG][N];
int aux1[NLOG][N], aux2[NLOG][N];
int root1[N],root2[N],root3[N],root4[N];
int n,q;

struct compy{
    bool operator()(const int &a1, const int &a2) const{
        pii p1 = pts[a1],p2=pts[a2];
        if (p1.second < p2.second) return true;
        if (p1.second > p2.second) return false;
        return (p1.first < p2.first);
    }
};

void Build(int dpt,int lft,int rgt,bool leftBranch=false){
    assert(dpt<NLOG);

    if(rgt==lft) sorty[dpt][lft]=lft;
    else{
        int mid=(lft+rgt)/2;
        Build(dpt+1,lft,mid,true);
        Build(dpt+1,mid+1,rgt,false);
        for(int j=lft; j<=rgt; j++) sorty[dpt][j]=sorty[dpt+1][j];
        sort(&sorty[dpt][lft],&sorty[dpt][rgt+1],compy());
    }


    if(dpt>0){
        int val1,val2;
        if(!leftBranch){
            val1=pts[sorty[dpt][lft]].first-pts[sorty[dpt][lft]].second;
            aux1[dpt][lft]=sorty[dpt][lft];
            for(int i=lft+1; i<=rgt; i++){
                int idx=sorty[dpt][i];
                if(pts[idx].first-pts[idx].second < val1) aux1[dpt][i]=idx;
                else aux1[dpt][i]=aux1[dpt][i-1];
                val1=min(val1,pts[idx].first-pts[idx].second);
            }
            val2=pts[sorty[dpt][rgt]].first+pts[sorty[dpt][rgt]].second;
            aux2[dpt][rgt]=sorty[dpt][rgt];
            for(int i=rgt-1; i>=lft; i--){
                int idx=sorty[dpt][i];
                if(pts[idx].first + pts[idx].second < val2) aux2[dpt][i]=idx;
                else aux2[dpt][i]=aux2[dpt][i+1];
                val2=min(val2,pts[idx].first + pts[idx].second);
            }
        }
        else{
            val1=-pts[sorty[dpt][lft]].first-pts[sorty[dpt][lft]].second;
            aux1[dpt][lft]=sorty[dpt][lft];
            for(int i=lft+1; i<=rgt; i++){
                int idx = sorty[dpt][i];
                if(-pts[idx].first-pts[idx].second < val1) aux1[dpt][i]=idx;
                else aux1[dpt][i]=aux1[dpt][i-1];
                val1=min(val1,-pts[idx].first-pts[idx].second);
            }
            aux2[dpt][rgt]=sorty[dpt][rgt];
            val2=-pts[sorty[dpt][rgt]].first+pts[sorty[dpt][rgt]].second;
            for(int i=rgt-1; i>=lft; i--){
                int idx = sorty[dpt][i];
                if(-pts[idx].first + pts[idx].second < val2) aux2[dpt][i]=idx;
                else aux2[dpt][i]=aux2[dpt][i+1];
                val2 = min(val2,-pts[idx].first + pts[idx].second);
            }
        }
    }
    else{
        int val1,val2,val3,val4;
        // val 1 and val2 are for the case when input is at the left of everything
        val1=pts[sorty[0][lft]].first-pts[sorty[0][lft]].second;
        root1[lft]=sorty[0][lft];
        for(int i=lft+1; i<=rgt; i++){
            int idx = sorty[dpt][i];
            if(pts[idx].first-pts[idx].second < val1) root1[i]=idx;
            else root1[i]=root1[i-1];
            val1=min(val1,pts[idx].first-pts[idx].second);
        }
        root2[rgt]=sorty[0][rgt];
        val2=pts[sorty[0][rgt]].first+pts[sorty[0][rgt]].second;
        for(int i=rgt-1; i>=lft; i--){
            int idx = sorty[dpt][i];
            if(pts[idx].first + pts[idx].second < val2) root2[i]=idx;
            else root2[i]=root2[i+1];
            val2=min(val2,pts[idx].first + pts[idx].second);

        }

        // val 3 and val4 are for the case when input is at the right of everything
        val3=-pts[sorty[0][lft]].first-pts[sorty[0][lft]].second;
        root3[lft]=sorty[0][lft];
        for(int i=lft+1; i<=rgt; i++){
            int idx = sorty[dpt][i];
            if(-pts[idx].first-pts[idx].second < val3) root3[i]=idx;
            else root3[i]=root3[i-1];
            val3=min(val3,-pts[idx].first-pts[idx].second);
        }
        val4=-pts[sorty[0][rgt]].first+pts[sorty[0][rgt]].second;
        root4[rgt]=sorty[0][rgt];
        for(int i=rgt-1; i>=lft; i--){
            int idx = sorty[dpt][i];
            if(-pts[idx].first + pts[idx].second < val4) root4[i]=idx;
            else root4[i]=root4[i+1];
            val4 = min(val4,-pts[idx].first + pts[idx].second);
        }

    }

}


int BinSearch(int *arr, int lft, int rgt, int val){
    if(pts[arr[lft]].second >= val) return -1;
    if(pts[arr[rgt]].second < val) return rgt;
    while(rgt-lft>1){
        int mid=(rgt+lft)/2;
        if(pts[arr[mid]].second < val) lft = mid;
        else rgt = mid;
    }
    return lft;
}

//first is the distance, second is the point
pii MinDist(int dpt,int lft,int rgt,int xq,int yq,bool leftBranch=false){
    assert(dpt < NLOG);

    if(rgt-lft<=3){
        int dist=INF,idx;
        for(int i=lft; i<=rgt; i++){
            int Now=abs(xq-pts[i].first)+abs(yq-pts[i].second);
            if(Now<dist) {dist=Now;idx=i;}
        }
        return make_pair(dist,idx);
    }

    if(xq>=pts[rgt].first || xq<=pts[lft].first){
        pii res; int *ax1,*ax2;
        if(dpt==0){
            if(xq >= pts[rgt].first) {ax1=root3;ax2=root4;}
            else {ax1=root1;ax2=root2;}
        }
        else {ax1=aux1[dpt];ax2=aux2[dpt];}

        //ID is the last one
        int ID=BinSearch(sorty[dpt],lft,rgt,yq);
        if(ID==-1){
            res.second=ax2[lft];
            res.first=abs(pts[res.second].first-xq)+abs(pts[res.second].second-yq);
        }
        else if(ID==rgt){
            res.second=ax1[rgt];
            res.first=abs(pts[res.second].first-xq)+abs(pts[res.second].second-yq);
        }
        else{
            int d1=abs(pts[ax1[ID]].first-xq)+ abs(pts[ax1[ID]].second-yq);
            int d2=abs(pts[ax2[ID+1]].first-xq)+ abs(pts[ax2[ID+1]].second-yq);
            if(d1<d2) res=make_pair(d1,ax1[ID]);
            else res=make_pair(d2,ax2[ID+1]);
        }
        return res;
    }
    else{
        int mid=(lft+rgt)/2;
        pii resl=MinDist(dpt+1,lft,mid,xq,yq,true);
        pii resr=MinDist(dpt+1,mid+1,rgt,xq,yq,false);
        if(resl.first<resr.first) return resl;
        else return resr;
    }
}


int main(){
    int a,b;
    for(int i=1; i<=n; i++){
        scanf("%d %d",&a,&b);
        pts[i]=make_pair(a,b);
    }
    sort(&pts[1],&pts[n+1]);

    Build(0,1,n);
    scanf("%d",&q);
    while(q--){
        scanf("%d %d",&a,&b);
        pii res=MinDist(0,1,n,a,b);
        printf("%d\n",res.first);
    }
}

