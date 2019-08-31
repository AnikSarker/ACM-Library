int bigMod(int n, int k, int mod){
    if(k == 0) return 1;
    long long re = bigMod(n, (k / 2), mod);
    re = (re * re) % mod;
    if(k % 2) re = (re * n) % mod;
    return re;
}

int phi(int n){
    //Find phi(n) in feasible way
    //return n-1 if n prime
}

int primitive_root(int p){
    vector<int> factor;
    int php = phi(p);

    int tmp = php;
    for(int i = 2; i * i <= tmp; i++){
        if(tmp % i == 0){
            factor.push_back(i);
            while (tmp % i == 0) tmp /= i;
        }
    }
    if(tmp != 1) factor.push_back(tmp);

    for(int root=1; ; root++){
        bool flag = true;
        for(int i = 0; i < factor.size(); ++i){
            if(bigMod(root, php / factor[i], p) == 1){
                flag = false;
                break;
            }
        }
        if (flag) return root;
    }
}
