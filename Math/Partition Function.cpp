// Calculates Partition Function(x) for all x <= n 
// p(n) = number of distinct ways of representing n
// as sum of natural numbers (with order irrelevant).
// Complexity : O(n sqrt(n))

#define MAX 60005
#define MOD 1000000007
int p[MAX];
inline int Add(int a,int b){return (a+b)%MOD;}

int PartitionFunction(){
    p[0] = 1;
    for(int i = 1; i < MAX; i++){
        int j = 1, r = 1;
        while(i - (3*j*j - j) / 2 >= 0){
            p[i] = Add(p[i], p[i - (3*j*j - j) / 2] * r);

            if(i - (3*j*j + j) / 2 >= 0)
                p[i] = Add(p[i], p[i - (3*j*j + j) / 2] * r);

            j += 1;
            r *= -1;
        }
        if(p[i]<0) p[i]+=MOD;
    }
}
