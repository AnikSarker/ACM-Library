//Computes the sum of a^1 + a^2 .... + a^n

ll GeoSum(ll a, ll n){
    ll sz = 0;
    ll ret = 0;
    ll mul = 1;
    int MSB = 63 - __builtin_clzll(n);
 
    while(MSB >= 0){
        ret = ret * (1 + mul); mul = (mul * mul) % MOD; sz <<= 1; 
        if( (n >> MSB) & 1) {mul = (mul * a) % MOD; ret += mul; sz++;}
        ret %= MOD; MSB--;
    }
    return ret;
}
