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

void Solve(int m, int q){
    for(int i=1;i<=q;i++) lo[i] = 1, hi[i] = m;

    bool Changed = true;
    while(Changed){
        Changed = false;
        Clear and Re-initialize ds
        for(int i=1;i<=m;i++) Check[i].clear();

        for(int i=1;i<=q;i++){
            if(lo[i] == hi[i]) continue;
            Changed = true;
            int mid = (lo[i] + hi[i]) / 2;
            Check[mid].push_back(i);
        }

        for(int upd = 1; upd <= m; upd++){
            //Apply Update[upd]

            for(int qry : Check[i]){
                bool Ok = [conditions for Query[qry] is satisfied]
                if(ok) hi[qry] = i;
                else lo[qry] = i + 1;
            }
        }
    }
}
