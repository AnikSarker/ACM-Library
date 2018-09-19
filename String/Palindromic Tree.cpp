//Palindromic Tree
//Complexity : O(n) memory and O(n) time

#include<bits/stdc++.h>
using namespace std;
#define MAX 300005
#define INF 1e9
#define pii pair<int,int>

struct node{
    int Next[26];
    int MinPos;     //Position in string where this node first occurs
    int Occurrence; //Total number of occurrence of this node
    int Len;        //Length of the palindrome represented by current node
    int Count;      //Number of palindromic suffixes of the palindrome represented by current node
    int SuffLink;   //Links such node w such that the palindrome represented by node w is the largest
                    //palindrome which is a proper suffix of the palindrome represented by current node

    //Used for palindrome factorization
    int Diff;
    pii SeriesAns;
    int SerialLink;

    void nodeClear(){
        Len = Count = MinPos = Occurrence = SuffLink = 0;
        Diff = SerialLink = 0; SeriesAns = {INT_MAX,INT_MAX};
        memset(Next, 0, sizeof(Next));
    }
};

string s;
pii DP[MAX];
node Tree[MAX];
int Suff;           // Points to Current (initially previous) node in palindromic tree
int Size;           // Size = Total number of node in palindromic tree
                    // Size = 1 denotes node 1 (root with Len -1)
                    // Size = 2 denotes node 2 (root with Len  0)


bool AddLetter(int pos){
    int Cur=Suff;
    int CurLen=0;
    int Let=s[pos]-'a';

    while(true){
        CurLen=Tree[Cur].Len;
        if(pos-1>=CurLen && s[pos-1-CurLen]==s[pos]) break;
        Cur=Tree[Cur].SuffLink;
    }
    Tree[Cur].Occurrence++;

    if(Tree[Cur].Next[Let]) {Suff=Tree[Cur].Next[Let]; return false;}

    Size++;
    Tree[Size].nodeClear();

    Suff=Size;
    Tree[Suff].MinPos=pos;
    Tree[Suff].Len=Tree[Cur].Len+2;
    Tree[Cur].Next[Let]=Suff;

    if(Tree[Size].Len==1) Tree[Size].SuffLink=2;
    else{
        while(true){
            Cur=Tree[Cur].SuffLink;
            CurLen=Tree[Cur].Len;
            if(pos-1>=CurLen && s[pos-1-CurLen]==s[pos]){
                Tree[Size].SuffLink=Tree[Cur].Next[Let];
                break;
            }
        }
    }
    Tree[Size].Count=1+Tree[Tree[Size].SuffLink].Count;

    //Update for palindromic factorization Begin
    Tree[Suff].Diff = Tree[Suff].Len - Tree[Tree[Suff].SuffLink].Len;
    if(Tree[Suff].Diff == Tree[Tree[Suff].SuffLink].Diff){
        Tree[Suff].SerialLink = Tree[Tree[Suff].SuffLink].SerialLink;
    }
    else Tree[Suff].SerialLink = Suff;
    //Update for palindromic factorization Ended

    return true;
}

void Update(int pos){
    DP[pos]={INF,INF};
    for(int j=Suff; Tree[j].Len > 0;){
        int slv = Tree[Tree[j].SerialLink].SuffLink;
        Tree[j].SeriesAns = DP[pos - (Tree[slv].Len + Tree[j].Diff)];

        if(Tree[j].Diff == Tree[Tree[j].SuffLink].Diff){
            Tree[j].SeriesAns.first = min(Tree[j].SeriesAns.first, Tree[Tree[j].SuffLink].SeriesAns.first);
            Tree[j].SeriesAns.second = min(Tree[j].SeriesAns.second, Tree[Tree[j].SuffLink].SeriesAns.second);
        }

        auto val = Tree[j].SeriesAns;
        DP[pos].first = min(DP[pos].first, val.second + 1);
        DP[pos].second = min(DP[pos].second, val.first + 1);
        j = slv;
    }
}

void InitTree(){
    Size=2; Suff=2;
    Tree[1].nodeClear(); Tree[2].nodeClear();
    Tree[1].Len=-1; Tree[1].SuffLink=1;
    Tree[2].Len=0;  Tree[2].SuffLink=1;
    DP[0] = {INF,0};
}

int main(){
    //InitTree();
    //cin>>s; int n=s.size(); s="$"+s;
    //for(int i=1;i<=n;i++) AddLetter(i), Update(i);
    //distinct palindrome count = Size - 2
    //For(i=Size;i>=1;i--) Tree[Tree[i].SuffLink].Occurrence+=Tree[i].Occurrence;
}
