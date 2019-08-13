//Persistent Segment Tree
struct node{
    node *left,*right; int val;
    node(){val=0;left=NULL;right=NULL;}
    node(int a,node *b,node *c){val=a,left=b,right=c;}

    node *update(int lo,int hi,int i,int v){
        node* ret = new node(val,left,right);

        if(lo==hi) {ret->val += v; return ret;}
        int mid=(lo+hi)/2;

        if(i<=mid){
            if(!left) left = new node();
            ret->left = left->update(lo,mid,i,v);
        }
        else{
            if(!right) right = new node();
            ret->right = right->update(mid+1,hi,i,v);
        }

        ret->val=0;
        if(ret->left)  ret->val += ret->left->val;
        if(ret->right) ret->val += ret->right-> val;

        return ret;
    }

    int query(int lo,int hi,int i,int j) {
        if(hi<i || lo>j) return 0;
        if(i<=lo && hi<=j) return val;
        int mid=(lo+hi)/2;

        int ret = 0;
        if(left) ret += left->query(lo,mid,i,j);
        if(right) ret += right->query(mid+1,hi,i,j);
        return ret;
    }
};

inline int Val(node* x)    {return x ? x->val : 0;}
inline node* Left(node* x)   {return x ? x->left : NULL;}
inline node* Right(node* x)  {return x ? x->right : NULL;}

//Searching kth minimum element in sorted order
int Search(node *a,node *b,node* c,node* d,int l,int r,int k) {
  if(l==r) return l;
  int Count=Val(Left(a))+Val(Left(b))-Val(Left(c))-Val(Left(d));

  int mid=(l+r)/2;
  if(Count>=k) return Search(Left(a),Left(b),Left(c),Left(d),l,mid,k);
  else return Search(Right(a),Right(b),Right(c),Right(d),mid+1,r,k-Count);
}

void dfs(int u,int p,int d){
    ......
    root[u]=root[p]->update(1,Size,w[u],1);
    ......
}

int main(){
    ......
    dfs(1,0,0);
    Size=Map.size();  //number of distinct elements after co-ordinate compression
    root[0]=new node();
    ......
}
