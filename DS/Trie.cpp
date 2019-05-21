//Space Complexity : O(Sum of length of all strings)

struct NODE{
    NODE* Child[2];
    int SIZE;
    NODE(){
        Child[0]=Child[1]=NULL;
        SIZE=0;
    }
};

NODE* root;
void INSERT(int n){
    NODE *Cur=root;
    for(int i=MAX-1;i>=0;i--)    {
        int ID=check(n,i);
        if(Cur->Child[ID]==NULL) Cur->Child[ID]=new NODE();
        Cur=Cur->Child[ID];
        Cur->SIZE++;
    }
}

int QUERY(int L){
    NODE *Cur=root;
    int Ans=0;
    for(int i=MAX-1; i>=0; i--){......}
    return Ans;
}
