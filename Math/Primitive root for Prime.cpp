#include<bits/stdc++.h>
using namespace std;

// primitive root, finding the number with order p-1
//If the number is not prime tmp should be equal to phi(p)
//Taken from Rezwan Arefin
int Pow(int n, int k, int mod){
    if(k == 0) return 1;
    long long re = Pow(n, (k / 2), mod);
    re = (re * re) % mod;
    if(k % 2) re = (re * n) % mod;
    return (int)re;
}

int phi(int p){
    return p - 1;///if prime
}

int primitive_root(int p) {
	vector<int> factor;
	int php = phi(p);

	int tmp = php;
	for(int i = 2; i * i <= tmp; ++i) {
		if (tmp % i == 0) {
			factor.push_back(i);
			while (tmp % i == 0) tmp /= i;
		}
	}
	if(tmp != 1) factor.push_back(tmp);
	for(int root = 1; ; ++root) {
		bool flag = true;
		for(int i = 0; i < factor.size(); ++i) {
			if(Pow(root, php / factor[i], p) == 1) {
				flag = false;
				break;
			}
		}
		if (flag) return root;
	}
}
