#include<bits/stdc++.h>
using namespace std;

#define MAX 1000005
typedef long long ll;

struct node{
    int prior, size;
    ll val, sum;
    node *l, *r;
    node(int v = 0) {
        val = sum = v;
        prior = rand();
        size = 1;
        l = r = NULL;
    }
};

node* root[MAX];
typedef node* pnode;

int sz(pnode t) {return t ? t -> size : 0;}
void upd_sz(pnode t) {if(t) t -> size = sz(t -> l) + 1 + sz(t -> r);}

void combine(pnode t) {
    // Note: This function should reset datas of t first (MUST!!)
    // Then update datas from l and r.
    if(!t) return;
    t -> sum = t -> val; // Reset
    if(t -> l) t -> sum += t -> l -> sum;
    if(t -> r) t -> sum += t -> r -> sum;
}

void split(pnode t, pnode &l, pnode &r, int pos, int add = 0) {
    if(!t) return void(l = r = NULL);
    node* cn = new node();
    *cn = *t;

    int curr = sz(cn -> l) + add;
    if(curr <= pos) split(cn -> r, cn -> r, r, pos, curr + 1), l = cn;
    else split(cn -> l, l, cn -> l, pos, add), r = cn;

    upd_sz(cn);
    combine(cn);
}

void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r) {t = l ? l : r; return;}
    node* cn = new node();

    if(l -> prior > r -> prior) {*cn = *l; merge(cn -> r, cn -> r, r);}
    else {*cn = *r; merge(cn -> l, l, cn -> l);}
    t = cn;

    upd_sz(t);
    combine(t);
}

//Use pnode &t for non-persistent operation (will update original t)
//Use pnode t for persistent operation (will not update the original one)
//No need to merge back to retrieve the original node after split in persistent operation

void insert(pnode &t, int pos, int v){
    pnode L, R, tmp, y = new node(v);
    split(t, L, R, pos - 1);
    merge(tmp, L, y);
    merge(t, tmp, R);
}

void Replace(pnode &t,int x, int val){
    pnode L, R, mid;
    split(t,L,mid,x);
    split(L,t,R,x-1);
    R->val = R->sum = val;
    merge(L,t,R);
    merge(t,L,mid);
}

ll Query(pnode t, int pos1, int pos2){
    pnode L, R, mid, tmp;
    split(t, L, R, pos2);
    split(L, mid, tmp, pos1 - 1);
    return tmp->sum;
}

int main(){
    int n;
    scanf("%d",&n);
    root[0]=new node();

    int version=0;
    for(int i=1;i<=n;i++){//set A[version]=A[ID] and insert(pos,v)
        int tp; scanf("%d",&tp);
        if(tp==1){
            int ID,pos,v;
            scanf("%d %d %d",&ID,&pos,&v);
            root[++version]=root[ID];
            insert(root[version],pos,v);
        }
        else if(tp==2){//set A[ID][pos]=v;
            int ID,pos,v;
            scanf("%d %d %d",&ID,&pos,&v);
            Replace(root[ID],pos,v);
        }
        else if(tp==3){//print A[version]
            int ID;
            scanf("%d",&ID);
            for(int i=1;i<root[ID]->size;i++) printf("%d ",Query(root[ID],i,i));
            printf("\n");
        }
    }
}
