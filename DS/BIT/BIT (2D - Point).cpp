//Tested : LightOJ 1266 - Points in Rectangle

#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const int MAXN = 1005;
int BIT[MAXN][MAXN];

//A[x][y] += val
void update(int x, int y, int val){
    int xx = x;
    while(xx < MAXN){
        int yy = y;
        while(yy < MAXN){
            BIT[xx][yy] += val;
            yy += (yy & -yy);
        }
        xx += (xx & -xx);
    }
}

//return sum over all A[i][j], where 1 <= i <= x and 1 <= j <= y
int sum(int x, int y){
    int ans = 0;
    int xx = x;
    while(xx != 0){
        int yy = y;
        while(yy != 0){
            ans += BIT[xx][yy];
            yy -= (yy & -yy);
        }
        xx -= (xx & -xx);
    }
    return ans;
}
