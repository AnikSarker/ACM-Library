//Complexity : O(n*m / 64)

#define MAX 100010
#define ull unsigned long long

bool flag[MAX];
char A[MAX], B[MAX], S[2][MAX];

int lcs(char* A, char* B){
    int n, m, res = 0;
    ull mask[128] = {0};

    memset(flag, 0, sizeof(flag));
    for(n = 0; A[n]; n++) S[0][n] = A[n];
    for(m = 0; B[m]; m++) S[1][m] = B[m];

    for(int i = 0; (i * 64) < m; i++){
        memset(mask, 0, sizeof(mask));
        for(int k = 0; k < 64 && (i * 64 + k) < m; k++){
            mask[S[1][i * 64 + k]] |= (1ULL << k);
        }
        ull x = 0;
        for(int j = 0; j < n; j++){
            ull t = mask[S[0][j]] & ~x;
            x |= t;
            ull v = flag[j];
            ull q = x - (t << 1) - v;
            ull y = (q & ~x) | t;
            flag[j] = y >> 63;
            x &= ~(y << 1);
            if(v) x &= ~1ULL;
        }
        res += __builtin_popcountll(x);
    }
    return res;
}
