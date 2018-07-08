// Solution to 'Cybercrime Donut Investigation'.
// Abel Molina Prieto
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <complex>
#include <stack>
#include <cctype>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>

#define PB push_back
#define MP make_pair
#define FR(i,n) for( long long i = 0; i < n; i ++ )
#define FOR(i,a,n) for(long long i = a; i < n; i ++)
#define FREACH(it,v) for( typeof(v.end()) it = v.begin(); it != v.end(); it ++ )
#define EPS 1e-9


using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int NLOG=18,N=100000;
pair<int,int> pts[N];
int sorty[NLOG][N];
int aux1[NLOG][N], aux2[NLOG][N];
int root1[N],root2[N],root3[N],root4[N];


int n,q;

struct compy {
	bool operator() ( const int &a1, const int &a2) const {
		pair<int,int> p1 = pts[a1],p2=pts[a2];
		if (p1.second < p2.second) return true;
		if (p1.second > p2.second) return false;
		return (p1.first < p2.first);
	}
};

void build_tree(int dpt, int lft, int rgt, bool leftBranch=false) {
	
	assert(dpt < NLOG);
	
	if(rgt==lft) {
		sorty[dpt][lft]=lft;
	} else {
		build_tree(dpt+1,lft,(lft+rgt)/2,true);
		build_tree(dpt+1,(lft+rgt)/2 + 1,rgt,false);			
		FOR(j,lft,rgt+1) {
			sorty[dpt][j]=sorty[dpt+1][j];
		} 
		sort(&sorty[dpt][lft],&sorty[dpt][rgt+1],compy());
	}	
	
	
	if(dpt>0) {
		int val1,val2;
		if(!leftBranch) {
			val1=pts[sorty[dpt][lft]].first-pts[sorty[dpt][lft]].second;
			aux1[dpt][lft]=sorty[dpt][lft];
			FOR(i,lft+1,rgt+1) {
				int idx = sorty[dpt][i];
				if(pts[idx].first-pts[idx].second < val1) aux1[dpt][i]=idx;
				else aux1[dpt][i]=aux1[dpt][i-1];
				val1=min(val1,pts[idx].first-pts[idx].second);
			}
			val2=pts[sorty[dpt][rgt]].first+pts[sorty[dpt][rgt]].second;
			aux2[dpt][rgt]=sorty[dpt][rgt];
			for(int i=rgt-1;i>=lft;i--) {
				int idx = sorty[dpt][i];
				if(pts[idx].first + pts[idx].second < val2) aux2[dpt][i]=idx;
				else aux2[dpt][i]=aux2[dpt][i+1];
				val2=min(val2,pts[idx].first + pts[idx].second);
			}

		} else {
			val1=-pts[sorty[dpt][lft]].first-pts[sorty[dpt][lft]].second;
			aux1[dpt][lft]=sorty[dpt][lft];
			FOR(i,lft+1,rgt+1) {
				int idx = sorty[dpt][i];
				if(-pts[idx].first-pts[idx].second < val1) aux1[dpt][i]=idx;
				else aux1[dpt][i]=aux1[dpt][i-1];
				val1=min(val1,-pts[idx].first-pts[idx].second);
			}
			aux2[dpt][rgt]=sorty[dpt][rgt];
			val2=-pts[sorty[dpt][rgt]].first+pts[sorty[dpt][rgt]].second;
			for(int i=rgt-1;i>=lft;i--) {
				int idx = sorty[dpt][i];
				if(-pts[idx].first + pts[idx].second < val2) aux2[dpt][i]=idx;
				else aux2[dpt][i]=aux2[dpt][i+1];
				val2 = min(val2,-pts[idx].first + pts[idx].second);
			}
		}
	} else {
		
		
		int val1,val2,val3,val4;		
		// val 1 and val2 are for the case when input is at the left of everything
		val1=pts[sorty[0][lft]].first-pts[sorty[0][lft]].second;
		root1[lft]=sorty[0][lft];
		FOR(i,lft+1,rgt+1) {
			int idx = sorty[dpt][i];
			if(pts[idx].first-pts[idx].second < val1) root1[i]=idx;
			else root1[i]=root1[i-1];
			val1=min(val1,pts[idx].first-pts[idx].second);
		}
		root2[rgt]=sorty[0][rgt];
		val2=pts[sorty[0][rgt]].first+pts[sorty[0][rgt]].second;
		for(int i=rgt-1;i>=lft;i--) {
			int idx = sorty[dpt][i];
			if(pts[idx].first + pts[idx].second < val2) root2[i]=idx;
			else root2[i]=root2[i+1];
			val2=min(val2,pts[idx].first + pts[idx].second);
			
		}
		
		// val 3 and val4 are for the case when input is at the right of everything
		val3=-pts[sorty[0][lft]].first-pts[sorty[0][lft]].second;
		root3[lft]=sorty[0][lft];
		FOR(i,lft+1,rgt+1) {
			int idx = sorty[dpt][i];
			if(-pts[idx].first-pts[idx].second < val3) root3[i]=idx;
			else root3[i]=root3[i-1];
			val3=min(val3,-pts[idx].first-pts[idx].second);
		}
		val4=-pts[sorty[0][rgt]].first+pts[sorty[0][rgt]].second;
		root4[rgt]=sorty[0][rgt];
		for(int i=rgt-1;i>=lft;i--) {
			int idx = sorty[dpt][i];
			if(-pts[idx].first + pts[idx].second < val4) root4[i]=idx;
			else root4[i]=root4[i+1];
			val4 = min(val4,-pts[idx].first + pts[idx].second);
		}
		
	}
	
}


int binSearch(int *arr, int lft, int rgt, int val) {
	if(pts[arr[lft]].second >= val) return -1;
	if(pts[arr[rgt]].second < val) return rgt;
	while(rgt-lft>1) {
		int md=(rgt+lft)/2;
		if(pts[arr[md]].second < val) lft = md;
		else rgt = md;
	}
	return lft;
}

// first is the distance, second is the point
pair<int,int> min_dist(int dpt, int lft, int rgt, int xq, int yq, bool leftBranch=false) {
	
	
	assert(dpt < NLOG);
	
	if(rgt-lft <= 3) {		
		int dist=2000000001,idx;
		FOR(i,lft,rgt+1) {
			if(abs(xq-pts[i].first)+abs(yq-pts[i].second)<dist) {
				dist=abs(xq-pts[i].first)+abs(yq-pts[i].second);
				idx=i;
			}
		}		
		return MP(dist,idx);
	}	
	
	if(xq >= pts[rgt].first || xq <= pts[lft].first ) {
		pair<int,int> res;
		
		int *ax1,*ax2;
		if(dpt==0) {
			if(xq >= pts[rgt].first) {
				ax1=root3;
				ax2=root4;
			} else {
				ax1=root1;
				ax2=root2;
			}
		} else {
			ax1=aux1[dpt];
			ax2=aux2[dpt];
		}
		
		// id is the last one < 
		int id=binSearch(sorty[dpt],lft,rgt,yq);
		if(id==-1) {
			res.second=ax2[lft];
			res.first=abs(pts[res.second].first-xq)+abs(pts[res.second].second-yq);
		} else if(id==rgt) {
			res.second=ax1[rgt];
			res.first=abs(pts[res.second].first-xq)+abs(pts[res.second].second-yq);
		} else {
			int d1=abs(pts[ax1[id]].first-xq)+ abs(pts[ax1[id]].second-yq);
			int d2=abs(pts[ax2[id+1]].first-xq)+ abs(pts[ax2[id+1]].second-yq);		
			if(d1<d2) {
				res=MP(d1,ax1[id]);
			} else {
				res=MP(d2,ax2[id+1]);
			}
		}
		return res;
	} else {
		pii resl=min_dist(dpt+1,lft,(lft+rgt)/2,xq,yq,true);
		pii resr=min_dist(dpt+1,(lft+rgt)/2 + 1,rgt,xq,yq,false);			
		if(resl.first<resr.first) {
			return resl;		
		} else {
			return resr;
		}	
	}
}


int main() {
		
	bool pr=false;
	while(scanf("%d",&n)) {
		if(n==-1) break;
		
		if(pr) printf("\n");
		pr = true;

		int a,b;
		FR(i,n){
			scanf("%d %d",&a,&b);
			pts[i]=MP(a,b);
		}
		sort(&pts[0],&pts[n]);

		
		build_tree(0,0,n-1);
		
		scanf("%d",&q);
		FR(i,q) {
			scanf("%d %d",&a,&b);
			pii res = min_dist(0,0,n-1,a,b);
			printf("%d\n",res.first);
	//		printf("%d %d\n",pts[res.second].first, pts[res.second].second);
		}	
	}
	
}
