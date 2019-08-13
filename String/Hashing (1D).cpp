// Hashing
// Hashvalue(l...r) = hsh[l] - hsh[r + 1] * base ^ (r - l + 1);
// Must call preprocess
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 100009;
ll mods[2] = {1000000007, 1000000009};
//Some back-up primes: 1072857881, 1066517951, 1040160883
ll bases[2] = {137, 281};
ll pwbase[3][MAX];

void Preprocess(){
    pwbase[0][0] = pwbase[1][0] = 1;
    for(ll i = 0; i < 2; i++){
        for(ll j = 1; j < MAX; j++){
            pwbase[i][j] = (pwbase[i][j - 1] * bases[i]) % mods[i];
        }
    }
}

struct Hashing{
    ll hsh[2][MAX];
    string str;

    Hashing(){}
    Hashing(string _str) {str = _str; memset(hsh, 0, sizeof(hsh)); build();}

    void Build(){
        for(ll i = str.size() - 1; i >= 0; i--){
            for(int j = 0; j < 2; j++){
                hsh[j][i] = (hsh[j][i + 1] * bases[j] + str[i]) % mods[j];
                hsh[j][i] = (hsh[j][i] + mods[j]) % mods[j];
            }
        }
    }

    pair<ll,ll> GetHash(ll i, ll j){
        assert(i <= j);
        ll tmp1 = (hsh[0][i] - (hsh[0][j + 1] * pwbase[0][j - i + 1]) % mods[0]) % mods[0];
        ll tmp2 = (hsh[1][i] - (hsh[1][j + 1] * pwbase[1][j - i + 1]) % mods[1]) % mods[1];
        if(tmp1 < 0) tmp1 += mods[0];
        if(tmp2 < 0) tmp2 += mods[1];
        return make_pair(tmp1, tmp2);
    }
};
