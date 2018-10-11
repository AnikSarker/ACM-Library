///Hashing
/// Hashvalue(l...r) = hsh[l] - hsh[r + 1] * base ^ (r - l + 1);
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mods[2] = {1000000007, 1000000009};
ll bases[2] = {137, 281};
ll pwbase[3][200000];
ll hsh[3][200000];
string str;

pair < ll , ll > getHash(ll i, ll j)
{
    ll tmp1 = (hsh[0][i] - (hsh[0][j + 1] * pwbase[0][j - i + 1]) % mods[0]) % mods[0];
    ll tmp2 = (hsh[1][i] - (hsh[1][j + 1] * pwbase[1][j - i + 1]) % mods[1]) % mods[1];
    if(tmp1 < 0) tmp1 += mods[0];
    if(tmp2 < 0) tmp2 += mods[1];
    return make_pair(tmp1, tmp2);
}

int main()
{
    pwbase[0][0] = pwbase[1][0] = 1;
    for(ll i = 0; i < 2; i++){
        for(ll j = 1; j <= 100000; j++) pwbase[i][j] = (pwbase[i][j - 1] * bases[i]) % mods[i];
    }

    str = "abcdabc";
    ll len = str.size();

    for(ll i = len - 1; i >= 0; i--){
        for(ll j = 0; j < 2; j++){
            hsh[j][i] = (hsh[j][i + 1] * bases[j] + str[i]) % mods[j];
            hsh[j][i] = (hsh[j][i] + mods[j]) % mods[j];
        }
    }

    ll tmp1 = (hsh[0][0] - (hsh[0][0] * pwbase[0][3]) % mods[0]) % mods[0];
    ll tmp2 = (hsh[1][0] - (hsh[1][3] * pwbase[1][3]) % mods[1]) % mods[1];
    if(tmp1 < 0) tmp1 += mods[0];
    if(tmp2 < 0) tmp2 += mods[1];

    ll tmp3 = (hsh[0][4] - (hsh[0][7] * pwbase[0][3]) % mods[0]) % mods[0];
    ll tmp4 = (hsh[1][4] - (hsh[1][7] * pwbase[1][3]) % mods[1]) % mods[1];
    if(tmp3 < 0) tmp3 += mods[0];
    if(tmp4 < 0) tmp4 += mods[1];

    cout << tmp1 << ' ' << tmp2 << endl;
    cout << tmp3 << ' ' << tmp4 << endl;
    return 0;
}
