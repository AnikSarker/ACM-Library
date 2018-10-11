#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 100005

string str;
ll mods[2] = {1000000007, 1000000009};
ll bases[2] = {137, 281};
ll Pow[2][MAX];
ll Hash[2][MAX];

// HashValue(l...r) = Hash[l] - Hash[r + 1] * base ^ (r - l + 1);
pair < ll , ll > getHash(ll i, ll j){
    ll tmp1 = (Hash[0][i] - (Hash[0][j + 1] * Pow[0][j - i + 1]) % mods[0]) % mods[0];
    ll tmp2 = (Hash[1][i] - (Hash[1][j + 1] * Pow[1][j - i + 1]) % mods[1]) % mods[1];
    if(tmp1 < 0) tmp1 += mods[0];
    if(tmp2 < 0) tmp2 += mods[1];
    return make_pair(tmp1, tmp2);
}

int main(){
    Pow[0][0] = Pow[1][0] = 1;
    for(int i=0;i<2;i++) for(int j=1; j < MAX; j++) Pow[i][j]= (Pow[i][j-1]*bases[i]) % mods[i];

    str = "abcdabc";
    int len = str.size();
    for(int i = len - 1; i >= 0; i--){
        for(int j = 0; j < 2; j++){
            Hash[j][i] = (Hash[j][i + 1] * bases[j] + str[i]) % mods[j];
            Hash[j][i] = (Hash[j][i] + mods[j]) % mods[j];
        }
    }
}
