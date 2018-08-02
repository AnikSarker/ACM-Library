// Taken From Rezwan Arefin
// Gaussian Elimination Online 
struct maxxor {
	int best[32], msb;
	maxxor() { memset(best, -1, sizeof best); }
	void add(int x) { 
		while(x > 0) {
			msb = 31 - __builtin_clz(x); // clzll for ll
			if(best[msb] == -1) {
				best[msb] = x; break;
			} else x = x ^ best[msb]; 
		}
	}
	int get(int ret = 0) {
		for(int i = 31; i >= 0; i--) {
			if(best[i] != -1) 
				ret = max(ret, ret ^ best[i]);
		} return ret;
	}
} ds;

// Gaussian Elimination Offline 

int a[maxn], n;
int maxxor() {
	int r = 0, ret = 0;
	for(int c = 31; c >= 0; c--) {
		int idx = -1;
		for(int i = r; i < n && idx < 0; i++) 
			if(a[i] >> c & 1) idx = i;
		if(idx == -1) continue; 
		swap(a[r], a[idx]); 
		for(int i = 0; i < n; i++) if(i != r) 
			if(a[i] >> c & 1) a[i] ^= a[r];
		r++;
	}
	for(int i = 0; i < n; i++) ret = max(ret, ret ^ a[i]);
}
