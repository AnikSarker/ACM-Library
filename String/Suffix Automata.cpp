//Tested : HDU 4270 - Dynamic Lover

#include<bits/stdc++.h>
using namespace std;
const int alphabetSize = 28;
const int MAXLEN = 300005;

int TotalLen,Size;
int Root,Last;

struct Node{
    int Link,Len;
    long long Occurrence; ///How many times each state(endpos) occurs
    long long Word;     ///How many substrings can be reached from this node
    long long Dstnct_substr; ///How many distinct substrings can be reached from this node
    int FirstPos,version,baseID;
    int Next[alphabetSize];
    void Clear(){
        Len = Occurrence = Word = Dstnct_substr = 0; Link = baseID = FirstPos = version = -1;
        memset(Next,0,sizeof(Next));
    }
};

Node St[MAXLEN*2];
bool isValid[MAXLEN*2];
vector<int>CurrList;
vector<int>LastList;


inline void CreateNode(int dep){
    St[Size].Clear();
    St[Size].Len = dep;
    St[Size].FirstPos = dep;
    St[Size].baseID = Size;
    isValid[Size] = true;
}

inline void init(){
    Size = 0;
    Root = Last = TotalLen = 0;
    St[Root].Clear();
    CurrList.clear();
    LastList.clear();
}

inline bool has(int u, int ch){
    int x = St[u].Next[ch];
    return isValid[St[x].baseID];
}

inline void SAM(int ch){
    TotalLen++;
    int Curr = ++Size;
    CreateNode(St[Last].Len + 1);

    int p = Last;
    while(p !=-1 && !has(p,ch)){
        St[p].Next[ch] = Curr;
        p = St[p].Link;
    }

    if(p == -1) St[Curr].Link = Root;
    else{
        int q = St[p].Next[ch];
        if(St[q].Len == St[p].Len + 1) St[Curr].Link = q;
        else{
            int Clone = ++Size;
            CreateNode(St[p].Len + 1);

            St[Clone].FirstPos = St[q].FirstPos;
            memcpy(St[Clone].Next,St[q].Next,sizeof(St[q].Next));
            St[Clone].Link = St[q].Link;
            St[Clone].baseID = St[q].baseID;
            St[q].Link = St[Curr].Link = Clone;

            while(p != -1 && St[p].Next[ch] == q) St[p].Next[ch] = Clone, p = St[p].Link;
        }
    }
    CurrList.push_back(Curr);
    LastList.push_back(Last);
    Last = Curr;
}

inline void del(int len){
    if(!len) return;

    for(int i = 0; i < len; i++){
        isValid[St[CurrList.back()].baseID] = false;
        CurrList.pop_back();
        Last = LastList.back();
        LastList.pop_back();
        TotalLen--;
    }
}

inline void MarkTerminal(int u,int v){
    while(u != -1) St[u].version = v,  u = St[u].Link;
}

int FindSmallest(int len,int idx){
    MarkTerminal(Last,idx);

    int cur = Root;
    for(int i= 0; i< len; i++){
        if(cur > Root && St[cur].version == idx) return TotalLen - i + 1;
        for(int ch = 0; ch < alphabetSize; ch++){
            if(!has(cur, ch )) continue;
            cur = St[cur].Next[ch];
            break;
        }
    }
    return St[cur].FirstPos - len + 1;
}
///Returns longest common substring of 2 strings
int LCS(char * s1, char * s2)
{
    int len1 = strlen(s1), len2 = strlen(s2);
    init();
    for(int i = 0; i < len1; i++) SAM(s1[i] - 'a');
    int curNode = 0, curLen = 0, ans = 0;
    for(int i = 0; i < len2; i++){
        while(curNode > -1 && St[curNode].Next[s2[i] - 'a'] == 0) curNode = St[curNode].Link, curLen = St[curNode].Len;
        if(curNode == -1) curNode = 0;
        if(St[curNode].Next[s2[i] - 'a']) curNode = St[curNode].Next[s2[i] - 'a'], curLen++;
        ans = max(ans, curLen);
    }
    return ans;
}

///finds number of distinct substring
///finds number of occurrence of every state(endpos class)
///finds number of substring which can be reached from this node
///must call findAllTerminal Before
void dfs_sam(int pos)
{
    if(St[pos].Dstnct_substr) return;
    int resDstnct = 1;
    for(int i = 0; i < alphabetSize; i++) if(St[pos].Next[i]) {
        int to = St[pos].Next[i];
        dfs_sam(to);
        resDstnct += St[to].Dstnct_substr;
        St[pos].Occurrence += St[to].Occurrence;
        St[pos].Word += St[to].Word;
    }
    St[pos].Dstnct_substr = resDstnct;
    St[pos].Word += St[pos].Occurrence;
}

void findAllTerminal()
{
    int cur = Last;
    while(cur > Root) St[cur].Occurrence++, cur = St[cur].Link;
}

void PrintKthLexSubstr(int k)
{
    ///must call dfs_sam before
    int cur = Root;
    while(k > 0){
        int tmp = 0;
        for(int i = 0; i < 26; i++){
            if(St[cur].Next[i] == 0) continue;
            int to = St[cur].Next[i];
            if(tmp + St[to].Word >= k){
                k -= (tmp + St[to].Occurrence), cur = to;
                printf("%c", 'a' + i);
                break;
            }
            tmp += St[to].Word;
        }
    }
}

void PrintKthLexDstSubstr(int k)
{
    ///must call dfs_sam before
    int cur = Root;
    while(k > 0){
        int tmp = 0;
        for(int i = 0; i < 26; i++){
            if(St[cur].Next[i] == 0) continue;
            int to = St[cur].Next[i];
            if(tmp + St[to].Dstnct_substr >= k){
                k -= (tmp + 1), cur = to;
                printf("%c", 'a' + i);
                break;
            }
            tmp += St[to].Dstnct_substr;
        }
    }
}
