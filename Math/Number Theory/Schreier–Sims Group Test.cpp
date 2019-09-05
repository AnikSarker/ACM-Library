// time complexity : O(n^2 log^3 |G| + t n log |G|)
// working space : O(n^2 log |G| + tn)
// t : number of generator
#include <bits/stdc++.h>
using namespace std;
#define ll long long int

namespace SchreierSimsAlgorithm{
    typedef vector<int> Permu;
    Permu inv(const Permu& p){
        Permu ret(p.size());
        for(int i = 0; i < p.size(); i++) ret[p[i]] = i;
        return ret;
    }

    Permu operator*( const Permu& a, const Permu& b ){
        Permu ret(a.size());
        for(int i = 0 ; i < a.size(); i++) ret[i] = b[a[i]];
        return ret;
    }

    int n, m;
    typedef vector<int> Table;
    typedef pair<int,int> pii;
    typedef vector<Permu> Bucket;
    vector<Table> lookup;
    vector<Bucket> bkts, bktsInv;

    int fastFilter(const Permu &g, bool addToG = 1){
        Permu p;
        n = bkts.size();
        for(int i = 0; i < n ; i++){
            int res = lookup[i][p[i]];
            if(res == -1 ){
                if(addToG){
                    bkts[i].push_back(p);
                    bktsInv[i].push_back(inv(p));
                    lookup[i][p[i]] = bkts[i].size()-1;
                }
                return i;
            }
            p = p * bktsInv[i][res];
        }
        return -1;
    }

    ll calcTotalSize(){
        ll ret = 1;
        for(int i = 0; i < n; i++) ret *= bkts[i].size();
        return ret;
    }

    bool inGroup(Permu &g) {return fastFilter(g, false) == -1;}

    void solve(Bucket &gen, int _n){
        n = _n, m = gen.size(); // m perm[0..n-1]s
        {//clear all
            bkts.clear();
            bktsInv.clear();
            lookup.clear();
        }
		for(int i = 0; i < n ; i++){
            lookup[i].resize(n);
            fill(lookup[i].begin(), lookup[i].end(), -1);
        }
        Permu id( n );
        for(int i = 0; i < n ; i++) id[i] = i;
        for(int i = 0; i < n ; i++){
            bkts[i].push_back(id);
            bktsInv[i].push_back(id);
            lookup[i][i] = 0;
        }
        for(int i = 0; i < m ; i++) fastFilter(gen[i]);

        queue< pair<pii,pii> > toUpd;
        for(int i = 0; i < n ; i++)
            for(int j = i; j < n ; j++)
                for(int k = 0; k < bkts[i].size(); k++)
                    for(int l = 0; l < bkts[j].size(); l++)
                        toUpd.push({pii(i,k), pii(j,l)});

        while(!toUpd.empty()){
            pii a = toUpd.front().first;
            pii b = toUpd.front().second;
            toUpd.pop();
            int res = fastFilter(bkts[a.first][a.second] * bkts[b.first][b.second]);
            if(res == -1) continue;
            pii newPair(res, (int)bkts[res].size() - 1);
            for(int i = 0; i < n; i ++)
                for(int j = 0; j < (int)bkts[i].size(); ++j){
                    if(i <= res)
                        toUpd.push(make_pair(pii(i , j), newPair));
                    if(res <= i)
                        toUpd.push(make_pair(newPair, pii(i, j)));
                }
        }
    }
}
