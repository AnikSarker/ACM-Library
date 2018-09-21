struct state {
    int len, link;
    map<char,int>next;
    ll pathCount;
    void Clear(){len = pathCount = 0; link= -1; next.clear();}
};

const int MAXLEN = 100000;
state st[MAXLEN*2];
int sz, last;

///root is st[0]
void sa_init() {sz = last = 0; st[0].Clear();}

void sa_extend (char c) {
    int cur = ++sz;
    st[cur].Clear();

    st[cur].len = st[last].len + 1;
    int p;
    for(p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
        st[p].next[c] = cur;
    
    if(p == -1) st[cur].link = 0;
    else{
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) st[cur].link = q;
        else{
            int clone = ++sz;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                st[p].next[c] = clone;
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

ll pathCalc(int pos){
    if(st[pos].pathCount != 0) return st[pos].pathCount;
    ll re = 1;
    for(auto to : st[pos].next) re += pathCalc(to.second);
    return st[pos].pathCount = re;
}
