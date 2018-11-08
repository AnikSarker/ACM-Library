#define MAX 1005
#define ll long long int

struct BIT2D{
    ll tree[4][MAX][MAX];
    BIT2D() {memset(tree,0,sizeof(tree));}

    // Add v to submatrix from upper-left [p,q] to lower-right [n,n]
    void update(int p, int q, ll v){
        if((p <= 0) || (q <= 0) || (p >= MAX) || (q >= MAX)) return;

        int i = p, c = p - 1, d = q - 1;
        while(i < MAX){
            int j = q;
            while(j < MAX){
                tree[0][i][j] += v;        tree[1][i][j] += (v * d);
                tree[2][i][j] += (v * c);  tree[3][i][j] += (v * c * d);
                j += (j & (-j));
            }
            i += (i & (-i));
        }
    }

    // Query sum of submatrix from upper-left [p,q] to lower-right [n,n]
    ll query(int p, int q){
        int i, j;
        ll x, y, z, c, d, res;

        i = p, x = y = z = 0;
        while(i != 0){
            j = q, c = d = 0;
            while(j != 0){
                c += tree[0][i][j];        d += tree[1][i][j];
                y += tree[2][i][j];        z += tree[3][i][j];
                j ^= (j & (-j));
            }
            i ^= (i & (-i));
            x += ((c * q) - d);
        }
        res = (x * p) - (y * q) + z;
        return res;
    }

    // Add v to submatrix from upper-left [i,j] to lower-right [k,l]
    void update(int i, int j, int k, int l, ll v){
        update(i, j, v);                   update(k + 1, j, -v);
        update(k + 1, l + 1, v);           update(i, l + 1, -v);
    }

    // Query for sum of submatrix from upper-left [i,j] to lower-right [k,l]
    ll query(int i, int j, int k, int l){
        if (i > k || j > l) return 0;
        ll res = query(k, l)-query(i - 1, l) + query(i - 1, j - 1)-query(k, j - 1);
        return res;
    }
};
