#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;
const int MAXQ = 100005;

TYPE ds; //Size MAXN
TYPE Update[MAXM];
TYPE Query[MAXQ];
vector<int> Check[MAXM];
int lo[MAXQ], hi[MAXQ];

void Solve(int n, int m, int q){
    for(int qry=1; qry<=q; qry++) lo[qry] = 1, hi[qry] = m;

    bool Changed = true;
    while(Changed){
        Changed = false;
        // Clear and Re-initialize ds upto size n
        for(int upd=1; upd<=m; upd++) Check[upd].clear();

        for(int qry=1; qry<=q; qry++){
            if(lo[qry] == hi[qry]) continue;
            Changed = true;
            int mid = (lo[qry] + hi[qry]) / 2;
            Check[mid].push_back(qry);
        }

        for(int upd=1; upd<=m; upd++){
            //Apply Update[upd]

            for(int qry : Check[upd]){
                bool Ok = [conditions for Query[qry] is satisfied]
                if(ok) hi[qry] = i;
                else lo[qry] = i + 1;
            }
        }
    }
}
