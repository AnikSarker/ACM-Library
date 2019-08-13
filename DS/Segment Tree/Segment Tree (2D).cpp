// 2D Segment Tree
// Memory Complexity : O(16nm)
// Be careful writing lx, rx, ly, ry

const int MAXN = 1030;
int tree[4*MAXN][4*MAXN];

int n, m;
void updateY(int ndx, int lx, int rx, int ndy, int ly, int ry, int y, int val) {
    if(ly == ry) {
        if(lx == rx) tree[ndx][ndy] = val;
        else tree[ndx][ndy] = tree[ndx*2][ndy] + tree[ndx*2+1][ndy];
        return;
    }
    int mid = (ly + ry) >> 1;
    if(y <= mid) updateY(ndx, lx, rx, ndy*2, ly, mid, y, val);
    else updateY(ndx, lx, rx, ndy*2+1, mid+1, ry, y, val);
    tree[ndx][ndy] = tree[ndx][ndy*2] + tree[ndx][ndy*2+1];
}

void updateX(int ndx, int lx, int rx, int x, int y, int val) {
    if(lx != rx) {
        int mid = (lx + rx) >> 1;
        if(x <= mid) updateX(ndx*2, lx, mid, x, y, val);
        else updateX(ndx*2+1, mid+1, rx, x,y, val);
    }
    updateY(ndx, lx, rx, 1, 1, m, y,val);
}

int queryY(int ndx, int ndy, int ly, int ry, int y1, int y2) {
    if(ry < y1 || ly > y2) return 0;
    if(y1 <= ly && ry <= y2) return tree[ndx][ndy];

    int mid = (ly + ry) >> 1;
    return queryY(ndx, ndy*2, ly, mid, y1, y2) + queryY(ndx, ndy*2+1, mid+1, ry, y1, y2);
}

int queryX(int ndx, int lx, int rx, int x1, int y1, int x2, int y2) {
    if(rx < x1 || lx > x2) return 0;
    if(x1 <= lx && rx <= x2) return queryY(ndx, 1, 1, m, y1, y2);

    int mid = (lx + rx) >> 1;
    return queryX(ndx*2, lx, mid, x1,y1,x2,y2) + queryX(ndx*2+1, mid+1, rx, x1,y1,x2,y2);
}
