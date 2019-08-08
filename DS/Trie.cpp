//Space Complexity : O(Sum of |S_i|)

const int LOG = 20;
struct Trie{
    struct Node{
        Node* Child[2];
        Node() {Child[0]=Child[1]=NULL;}
    };
    Node* root;

    void Init() {root = new Node();}
    bool Check(int x,int b) {return (x>>b)&1;}

    void Insert(int n){
        Node *Cur = root;
        for(int i = LOG-1; i>=0; i--){
            bool ID = Check(n,i);
            if(!Cur->Child[ID]) Cur->Child[ID] = new Node();
            Cur = Cur->Child[ID];
        }
    }

    int MinQuery(int XOR){
        int Ans = 0;
        Node *Cur = root;
        for(int i = LOG-1; i>=0; i--){
            bool ID = Check(XOR,i);
            if(Cur->Child[ID]) Cur = Cur->Child[ID];
            else Cur = Cur->Child[!ID], Ans += (1<<i);
        }
        return Ans;
    }
};
