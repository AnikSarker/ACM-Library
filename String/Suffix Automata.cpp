// Tested : HDU 4270 - Dynamic Lover
// Tested : SPOJ SUBLEX, SPOJ LCS, CF 128B

#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int ALPHA = 28;
const int MAXLEN = 300005;
const int LOG = 20;
int TotalLen, Size;
int Root, Last;

// Dstnct_substr can be calculated online as St[pos].Dstnct_substr = St[pos].Len - St[St[pos].link].Len
// Occurrence can be calculated online,
// First, Every node pos except a clone node, St[pos].Occurrence = 1
// then, St[pos].Occurence = sum of St[i].Occurrence where St[i].Link = pos|
// Must make isvlid array 0 for more than one test case

struct Node{
    int Link, Len;
    ll Occurrence;    // How many times each state (endpos) occurs
    ll Word;          // How many substrings can be reached from this node
    ll Dstnct_substr; // How many distinct substrings can be reached from this node
    int FirstPos, version, baseID;
    int Next[ALPHA];
    void Clear(){
        Len = Occurrence = Word = Dstnct_substr = 0;
        Link = baseID = FirstPos = version = -1;
        memset(Next, 0, sizeof(Next));
    }
};

Node St[MAXLEN*2];
bool isValid[MAXLEN*2];
vector<int>CurrList;
vector<int>LastList;
vector < int > linkTree[2 * MAXLEN];
int Par[2 * MAXLEN], P[2 * MAXLEN][LOG];
int perPrefNode[MAXLEN]; ///[i] = node created after inserting ith position in SAM

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
    for(int i = 0; i < 2 * MAXLEN; i++) linkTree[i].clear();
}

inline bool has(int u, int ch){
    int x = St[u].Next[ch];
    return isValid[St[x].baseID];
}

inline void SAM(int pos, int ch){
    TotalLen++;
    int Curr = ++Size;
    CreateNode(St[Last].Len + 1);

    int p = Last;
    while(p !=-1 && !has(p,ch)){
        St[p].Next[ch] = Curr;
        p = St[p].Link;
    }

    if(p == -1) {
        St[Curr].Link = Root;
    }
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
            linkTree[St[Clone].Link].push_back(Clone);
            Par[Clone] = St[Clone].Link;
        }
    }
    perPrefNode[pos] = Curr; //pass pos as parameter
    linkTree[St[Curr].Link].push_back(Curr);
    Par[Curr] = St[Curr].Link;
    CurrList.push_back(Curr);
    LastList.push_back(Last);
    Last = Curr;
}

inline void Del(int len){
    if(!len) return;

    for(int i = 0; i < len; i++){
        isValid[St[CurrList.back()].baseID] = false;
        CurrList.pop_back();
        Last = LastList.back();
        LastList.pop_back();
        TotalLen--;
    }
}

inline void MarkTerminal(int u, int v = 1){
    while(u != -1) St[u].version = v,  u = St[u].Link, St[u].Occurrence = 1;
}

// Returns Smallest Substring with length len
// If i + len > s.size(), consider substring(i, s.size())
int LexSmallestSubStr(int len, int idx){
    MarkTerminal(Last,idx);

    int cur = Root;
    for(int i= 0; i< len; i++){
        if(cur > Root && St[cur].version == idx) return TotalLen - i + 1;
        for(int ch = 0; ch < ALPHA; ch++){
            if(!has(cur, ch )) continue;
            cur = St[cur].Next[ch];
            break;
        }
    }
    return St[cur].FirstPos - len + 1;
}

// Returns longest common substring of 2 strings
int LCS(char * s1, char * s2){
    int len1 = strlen(s1), len2 = strlen(s2);
    init();
    for(int i = 0; i < len1; i++) SAM(i, s1[i] - 'a');

    int curNode = 0, curLen = 0, ans = 0;
    for(int i = 0; i < len2; i++){
        int ch = s2[i] - 'a';
        while(curNode > -1 && St[curNode].Next[ch] == 0)
            curNode = St[curNode].Link, curLen = St[curNode].Len;

        if(curNode == -1) curNode = 0;
        if(St[curNode].Next[ch]) curNode = St[curNode].Next[ch], curLen++;
        ans = max(ans, curLen);
    }
    return ans;
}

// Must call MarkTerminal Before
void dfs_sam(int pos){
    if(St[pos].Dstnct_substr) return;
    int resDstnct = 1;
    for(int i = 0; i < ALPHA; i++) if(St[pos].Next[i]){
        int to = St[pos].Next[i];
        dfs_sam(to);
        resDstnct += St[to].Dstnct_substr;
        St[pos].Occurrence += St[to].Occurrence;
        St[pos].Word += St[to].Word;
    }
    St[pos].Dstnct_substr = resDstnct;
    St[pos].Word += St[pos].Occurrence;
}

void PrintKthLexSubstr(int k){
    // Must call dfs_sam before
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

void PrintKthLexDstSubstr(int k){
    // Must call dfs_sam before
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

void BuildSparse(int n){
    // Using 0 for uninitialized parent (Remember and use carefully)
    for(int i=1; i<=n; i++) for(int j=0; j<LOG; j++) P[i][j] = 0;

    for(int i=1; i<=n; i++) P[i][0] = Par[i];
    for(int j=1; j<LOG; j++){
        for(int i=1; i<=n; i++){
             if(P[i][j-1] != 0){
                 int x = P[i][j-1];
                 P[i][j] = P[x][j-1];
             }
        }
    }
}

int getNodeSubstring(int l, int r){
    int cur = perPrefNode[r], curLen = r - l + 1;
    if(St[St[cur].Link].Len + 1 <= curLen) return cur;

    for(int i = LOG - 1; i >= 0; i--){
        if(P[cur][i] == 0) continue;
        int ncur = P[cur][i];
        if(St[ncur].Len >= curLen) cur = ncur;
    }
}
// must call init() at the start
