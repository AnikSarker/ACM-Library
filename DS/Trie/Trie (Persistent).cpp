// Tested : Codechef GPD - Gotham PD

const int LOG = 31;
struct PersistentTrie{
    struct Node{
        Node* Child[2];
        Node() {Child[0]=Child[1]=NULL;}
    };
    Node* root;

    void Init() {root = new Node();}
    bool Check(int x,int b) {return (x>>b)&1;}

    Node* Insert(int n){
        Node *Old = root;
        Node *Cur = new Node();
        Node* newRoot = Cur;

        for(int i = LOG-1; i>=0; i--){
            bool ID = Check(n,i);
            if(Old && Old->Child[!ID]) Cur->Child[!ID] = Old->Child[!ID];
            Cur->Child[ID] = new Node();

            Cur = Cur->Child[ID];
            if(Old) Old = Old->Child[ID];
        }
        return newRoot;
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
