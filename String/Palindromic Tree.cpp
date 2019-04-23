//Palindromic Tree
//Complexity : O(n) memory and O(n) time

#include<bits/stdc++.h>
using namespace std;
#define INF 1e9
#define MAX 300005
#define ff first
#define ss second
#define pii pair<int,int>

struct node{
    int next[26];
    int minPos;       //Position in string where this node ff occurs
    int occurrence;   //Total number of occurrence of this node
    int len;          //Length of the palindrome represented by current node
    int power;        //Number of palindromic suffixes of the palindrome represented by current node
    int suffLink;     //Links such node w such that the palindrome represented by node w is the largest
                      //palindrome which is a proper suffix of the palindrome represented by current node

    //Used for palindrome factorization
    int diff;
    pii seriesAns;
    int serialLink;

    void Init(){
        memset(next, 0, sizeof(next));
        len = power = minPos = occurrence = suffLink = 0;
        diff = serialLink = 0; seriesAns = {INT_MAX,INT_MAX};
    }
};

struct eerTree{
    string s;
    pii DP[MAX];
    node Tree[MAX];
    int suff;           // Points to current (initially previous) node in palindromic tree
    int num;           // num = Total number of node in palindromic tree
                        // num = 1 --> root 1 (len -1),  num = 2 ---> root 2 (len  0)

    void initTree(){
        num=2; suff=2;
        Tree[1].Init(); Tree[2].Init();
        Tree[1].len=-1; Tree[1].suffLink=1;
        Tree[2].len=0;  Tree[2].suffLink=1;
        DP[0] = {INF,0};
    }

    bool addLetter(int pos){
        int curr = suff, curLen = 0;
        int let=s[pos]-'a';

        while(true){
            curLen=Tree[curr].len;
            if(pos-1>=curLen && s[pos-1-curLen]==s[pos]) break;
            curr=Tree[curr].suffLink;
        }

        if(Tree[curr].next[let]) {
            suff=Tree[curr].next[let];
            Tree[suff].occurrence++;
            return false;
        }

        suff = ++num;
        Tree[suff].Init();
        Tree[suff].minPos = pos;
        Tree[suff].len = Tree[curr].len+2;
        Tree[curr].next[let] = suff;

        if(Tree[num].len == 1) Tree[num].suffLink=2;
        else{
            while(true){
                curr = Tree[curr].suffLink;
                curLen = Tree[curr].len;
                if(pos-1 >= curLen && s[pos-1-curLen] == s[pos]){
                    Tree[num].suffLink=Tree[curr].next[let];
                    break;
                }
            }
        }
        Tree[num].power = 1+Tree[Tree[num].suffLink].power;
        Tree[num].occurrence++;

        //update for palindromic factorization Begin
        int xx = Tree[suff].suffLink;
        Tree[suff].diff = Tree[suff].len - Tree[xx].len;
        if(Tree[suff].diff == Tree[xx].diff){
            Tree[suff].serialLink = Tree[xx].serialLink;
        }
        else Tree[suff].serialLink = suff;
        //update for palindromic factorization Ended

        return true;
    }

    void update(int pos){
        DP[pos]={INF,INF};
        for(int j=suff; Tree[j].len > 0;){
            int sfl = Tree[j].suffLink;
            int srl = Tree[j].serialLink;
            int slv = Tree[srl].suffLink;
            Tree[j].seriesAns = DP[pos - (Tree[slv].len + Tree[j].diff)];

            if(Tree[j].diff == Tree[sfl].diff){
                Tree[j].seriesAns.ff = min(Tree[j].seriesAns.ff, Tree[sfl].seriesAns.ff);
                Tree[j].seriesAns.ss = min(Tree[j].seriesAns.ss, Tree[sfl].seriesAns.ss);
            }

            auto val = Tree[j].seriesAns;
            DP[pos].ff = min(DP[pos].ff, val.ss + 1);
            DP[pos].ss = min(DP[pos].ss, val.ff + 1);
            j = slv;
        }
    }
};

int main(){
    // eerTree T; T.initTree();
    // cin>>s; int n=s.num(); s="$"+s;
    // for(int i=1;i<=n;i++) addLetter(i, s[i-1]), update(i);
    // distinct palindrome Count = num - 2
}
