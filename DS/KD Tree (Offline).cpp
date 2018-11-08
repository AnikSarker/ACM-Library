#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const int MAX = 1<<17;
const ll INF = 2000000000000000007;

struct point{
	int p[2];
	bool operator != (const point &a) const{
		return !(p[0]==a.p[0] && p[1]==a.p[1]);
	}
};

struct kd_node{
	int axis,value;
	point p;
	kd_node *left, *right;
};
typedef kd_node* node_ptr;
node_ptr root;

struct cmp_points{
	int axis;
	cmp_points(){}
	cmp_points(int x): axis(x) {}
	bool operator ()(const point &a, const point &b) const {
		return a.p[axis]<b.p[axis];
	}
};

int n;
point SET1[MAX],SET2[MAX];

ll Dist(point a, point b) {
	ll ret = 0;
	for(int i=0;i<2;i++) ret += (a.p[i]-b.p[i])*1ll*(a.p[i]-b.p[i]);
	return ret;
}

void Build(node_ptr &node, int from, int to, int axis) {
	if(from>to) {node=NULL; return;}

	node=new kd_node();
	if(from==to) {node->p=SET1[from]; node->left=NULL; node->right=NULL; return;}

	int mid=(from+to)/2;
	nth_element(SET1+from, SET1+mid, SET1+to+1, cmp_points(axis));
	node->value = SET1[mid].p[axis];
	node->axis = axis;
	Build(node->left, from, mid, axis^1);
	Build(node->right, mid+1, to, axis^1);
}

ll Ans;
void NearestNeighbour(node_ptr node, point q, ll&Ans) {
	if(node==NULL) return;

	if(node->left==NULL && node->right==NULL) {
		if(q!=node->p) Ans=min(Ans,Dist(node->p,q));
		return;
	}

	if(q.p[node->axis] <= node->value) {
		NearestNeighbour(node->left,q,Ans);
		if(q.p[node->axis]+sqrt(Ans)>=node->value) NearestNeighbour(node->right,q,Ans);
	}

	else{
		NearestNeighbour(node->right,q,Ans);
		if(q.p[node->axis]-sqrt(Ans)<=node->value) NearestNeighbour(node->left,q,Ans);
	}
}

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d %d", &SET1[i].p[0], &SET1[i].p[1]);
    for(int i=1;i<=n;i++) scanf("%d %d", &SET2[i].p[0], &SET2[i].p[1]);

    Build(root,1,n,0);
    for(int i=1;i<=n;i++){
        Ans=INF;
        NearestNeighbour(root,SET2[i],Ans);
        printf("%lld\n", Ans);
	}
}
