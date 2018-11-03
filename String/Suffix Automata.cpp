struct State{
    int Len, Link;
    map<char,int>Next;
    ll pathCount;
    void Clear() {Len = pathCount = 0; Link= -1; Next.clear();}
};

const int MAXLEN = 100000;
State St[MAXLEN*2];
int Size, Last;

// root is St[0]
void SA_Init() {Size = Last = 0; St[0].Clear();}

void SA_Extend(char c){
    int cur = ++Size;
    St[cur].Clear();

    St[cur].Len = St[Last].Len + 1;
    int p;
    for(p=Last; p!=-1 && !St[p].Next.count(c); p=St[p].Link)
        St[p].Next[c] = cur;

    if(p == -1) St[cur].Link = 0;
    else{
        int q = St[p].Next[c];
        if(St[p].Len + 1 == St[q].Len) St[cur].Link = q;
        else{
            int clone = ++Size;
            St[clone].Len = St[p].Len + 1;
            St[clone].Next = St[q].Next;
            St[clone].Link = St[q].Link;
            for(; p!=-1 && St[p].Next[c]==q; p=St[p].Link)
                St[p].Next[c] = clone;
            St[q].Link = St[cur].Link = clone;
        }
    }
    Last = cur;
}

ll pathCalc(int pos){
    if(St[pos].pathCount != 0) return St[pos].pathCount;
    ll re = 1;
    for(auto to : St[pos].Next) re += pathCalc(to.second);
    return St[pos].pathCount = re;
}
