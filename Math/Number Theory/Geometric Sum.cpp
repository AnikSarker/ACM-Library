//Computes the sum of a^1 + a^2 .... + a^n

ll GeoSum(ll a,int n){
    ll sz = 0;
    ll ret = 0;
    ll mul = 1;
    int MSB = 31 - __builtin_clz(n);
 
    while(MSB >= 0){
        ret = ret * (1 + mul); sz <<= 1; mul = (mul * mul) % MOD;
        if((n>>MSB)&1) mul = (mul * a) % MOD, ret += mul;
        ret %= MOD; MSB--;
    }
    return ret;
}
