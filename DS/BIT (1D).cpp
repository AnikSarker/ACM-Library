//Tested : LightOJ 1164 - Horrible Queries

#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int MAXN = 1000005;

ll BIT[2][MAXN];
void update(int cs, int indx, ll val){
    while(indx < MAXN){
        BIT[cs][indx] += val;
        indx += (indx & -indx);
    }
}

ll sum(int cs, int indx){
    ll ans = 0;
    while(indx != 0) {
        ans += BIT[cs][indx];
        indx -= (indx & -indx);
    }
    return ans;
}

void updateRange(int l, int r, ll val){
    update(0,l,val);       update(0,r+1,-val);
    update(1,l,val*(l-1)); update(1,r+1,-val*r);
}

ll sumRange(int indx) {return sum(0,indx)*indx - sum(1,indx);}
ll QueryRange(int l, int r) {return sumRange(r)-sumRange(l-1);}

const int LOGN = 20;
int LowerBound(int cs, ll v){
    ll sum = 0;
    int indx = 0;
    for(int i = LOGN; i >= 0; i--){
        int nPos = indx + (1<<i);
        if(nPos < MAXN && sum + BIT[cs][nPos] < v){
            sum += BIT[cs][nPos];
            indx = nPos;
        }
    }
    //pos = maximal x such that Sum(x) < v
    return indx + 1; //+1 for LowerBound
}
