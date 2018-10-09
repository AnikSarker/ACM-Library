//Online FFT Calculation
//a[i] = Sum of a[j]*b[i-j-1] for j in range [0,i-1]
//Problem Link : https://www.codechef.com/problems/MANCBST

const ll MAX = 1e5 + 9;
ll a[2*MAX+10], b[2*MAX+10];
vector<ll> vec1,vec2,res;

int main(){
    b[0]=b[1]=1;
    for(int i=2;i< MAX;i++) b[i]=bigMod(i,i-1);

    a[0]=1;
    for(int i = 0; i < MAX; i++){
        //+1 because of the format of the recurrence
        a[i + 0 + 1] += (a[i] * b[0]) % mod;
        a[i + 1 + 1] += (a[i] * b[1]) % mod;
        if(a[i + 0 + 1] >= mod) a[i + 0 +1]-=mod;
        if(a[i + 1 + 1] >= mod) a[i + 1 +1]-=mod;

        ll cc = 1;
        ll tmp = i;
        while(tmp && (tmp & 1) == 0){
            tmp = tmp / 2; cc = cc * 2;
            vec1.clear(); vec2.clear();

            for(int j=i-cc;j<i;j++) vec1.push_back(a[j]);
            for(int j=cc;j<cc+cc;j++) vec2.push_back(b[j]);
            ntt.multiply(vec1, vec2, res);

            ll Beg = i+1; //+1 because of the format of the recurrence
            for(ll j = 0; j < res.size(); j++){
                a[Beg+j] += res[j];
                if(a[Beg+j]>=mod) a[Beg+j]-=mod;
            }
        }
    }
}
