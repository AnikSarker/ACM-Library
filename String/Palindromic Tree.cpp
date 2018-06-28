//Palindromic Tree
//Complexity : O(n) memory and O(n) time

#include<bits/stdc++.h>
using namespace std;
#define MAX 1000005

struct node{
    int Next[26];
    int Len;        //Length of the palindrome represented by current node
    int Count;      //Number of palindromic suffixes of the palindrome represented by current node 
    int SuffLink;   //Links such node w such that the palindrome represented by node w is the largest
                    //palindrome which is a proper suffix of the palindrome represented by current node
};

string s;
node Tree[MAX];
int Suff;           // Points to Current (initially previous) node in palindromic tree
int num;            // num = Total number of node in palindromic tree
                    // num = 1 denotes node 1 (root with Len -1)
                    // num = 2 denotes node 2 (root with Len  0)
bool addLetter(int pos){
    int Cur=Suff;
    int CurLen=0;
    int Let=s[pos]-'a';

    while(true){
        CurLen=Tree[Cur].Len;
        if(pos-1 >= CurLen && s[pos-1-CurLen]==s[pos]) break;
        Cur=Tree[Cur].SuffLink;
    }

    if(Tree[Cur].Next[Let]) {Suff=Tree[Cur].Next[Let]; return false;}
    num++;
    Suff=num;
    Tree[num].Len = Tree[Cur].Len + 2;
    Tree[Cur].Next[Let] = num;

    if(Tree[num].Len==1) {Tree[num].SuffLink=2; Tree[num].Count=1; return true;}

    while(true){
        Cur=Tree[Cur].SuffLink;
        CurLen=Tree[Cur].Len;
        if(pos-1 >= CurLen && s[pos-1-CurLen]==s[pos]){
            Tree[num].SuffLink=Tree[Cur].Next[Let];
            break;
        }
    }

    Tree[num].Count=1+Tree[Tree[num].SuffLink].Count;
    return true;
}

void initTree(){
    num = 2; Suff = 2;
    Tree[1].Len = -1; Tree[1].SuffLink = 1;
    Tree[2].Len = 0;  Tree[2].SuffLink = 1;
}

int main(){
    //memset(Tree,0,sizeof(Tree));
    //initTree();
    //for(int i=0;i<n;i++) addLetter(i);
    //distinct palindrome count = num - 2
}
