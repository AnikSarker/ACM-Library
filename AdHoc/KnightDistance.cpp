//O(1)
//Taken from Rezwan Arefin
struct point {
	ll x, y;
	bool operator < (const point &p) const {
		return x == p.x ? y < p.y : x < p.x;
	}
};
ll kdist(point p, point q) {
	ll dx = abs(p.x - q.x);
	ll dy = abs(p.y - q.y);
	ll cnt = max({(dx+1)/2, (dy+1)/2, (dx+dy+2)/3});
	while((cnt%2) != (dx+dy)%2) cnt++;
	if(dx == 1 && !dy) return 3; 
	if(dy == 1 && !dx) return 3;
	if(dx == dy && dx == 2) return 4;
	return cnt;
}

// O(log Max)

const int KN = 101;
i64 dk[KN][KN];
int dx[] = {-1, -1, 1, 1, -2, -2, 2, 2};
int dy[] = {-2, 2, -2, 2, -1, 1, -1, 1};
 
void precalc() {
    int x, y, x1, y1, i;
    queue< int > Q;
    memset(dk, 0x3f, sizeof dk);
    x = y = (KN >> 1);
    dk[x][y] = 0;
    Q.push(x); Q.push(y);
    while(!Q.empty()) {
        x = Q.front(); Q.pop();
        y = Q.front(); Q.pop();
        for(i = 0; i < 8; i++) {
            x1 = x + dx[i], y1 = y + dy[i];
            if(0 <= x1 && x1 < KN && 0 <= y1 && y1 < KN) {
                if(dk[x1][y1] > dk[x][y] + 1) {
                    dk[x1][y1] = dk[x][y] + 1;
                    Q.push(x1); Q.push(y1);
                }
            }
        }
    }
}

// Returns knight distance between (0,0) -> (x,y) 
i64 knight(i64 x, i64 y) {
    i64 step, res = 0;
    if(x < y) swap(x, y);
    while((x<<1) > KN) {
        step = x / 2 / 2; res += step;
        x -= step * 2; y -= step;
        if(y < 0) y = ((y % 2) + 2) % 2;
        if(x < y) swap(x, y);
    }
    res += dk[x+(KN>>1)][y+(KN>>1)];
    return res;
}
