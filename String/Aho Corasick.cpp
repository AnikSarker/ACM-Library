// Aho-Corasick
// Complexity : |Text| + Sum of all |Pattern| + O(number of Occurrences)
// if occurrence positions needed, Worst Case Complexity : (SumLen) Root (SumLen)
#include <bits/stdc++.h>
using namespace std;
const int MAXT = 1000005;  // Length of Text
const int MAXP = 1000005;  // Sun of all |Pattern|
const int MAXQ = 1000005;  // Number of Patterns

int n;
map<char,int> Next[MAXP];
int Root;                 // AC automaton Root
int Nnode;                // Total node count
int Link[MAXP];           // failure links
int Len[MAXP];            // Len[i] = length of i-th pattern
vector<int> End[MAXP];    // End[i] = indices of patterns those end in node i
// vector<int> Occ[MAX];  // Occ[i] = occurrences of i-th pattern
vector<int> edgeLink[MAXP];
vector<int> perNodeText[MAXP];

int in[MAXQ], out[MAXQ];
int euler[MAXT];
int Time;

void Clear(int node){
    Next[node].clear();
    End[node].clear();
    edgeLink[node].clear();
    perNodeText[node].clear();
}

void init(){
    Time = 0;
    Root = Nnode = 0;
    Clear(Root);
}

void insertword(string p,int ind){
    int len = p.size();
    int now = Root;
    for(int i=0; i<len; i++){
        if(!Next[now][p[i]]){
            Next[now][p[i]] = ++Nnode;
            Clear(Nnode);
        }
        now = Next[now][p[i]];
    }
    End[now].push_back(ind);
}

void push_links(){
    queue<int> q;
    Link[0] = -1;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto edge : Next[u]){
            char ch = edge.first;
            int v = edge.second;
            int j = Link[u];

            while(j != -1 && !Next[j][ch]) j = Link[j];
            if(j != -1) Link[v] = Next[j][ch];
            else Link[v] = 0;

            q.push(v);
            edgeLink[Link[v]].push_back(v);
            // for(int x : End[Link[v]]) End[v].push_back(x);
        }
    }
}

void traverse(string s){
    int len = s.size();
    int now = Root;
    for(int i = 0; i < len; i++)    {
        while(now != -1 && !Next[now][s[i]]) now = Link[now];
        if(now!=-1) now = Next[now][s[i]];
        else now = 0;
        perNodeText[now].push_back(i+1);  // using 1 based indexing for text indices
        // for(int x=0;x<End[now].size();x++) Occ[End[now][x]].push_back(i);
    }
}

// After dfs, the occurence of ith query string will be the count of
// all the occurrence of the subtree under the endNode of ith string
void dfs(int pos){
    for(int q : End[pos]) in[q] = Time + 1;
    for(int val : perNodeText[pos]) euler[++Time] = val;
    for(int to : edgeLink[pos]) dfs(to);
    for(int q : End[pos]) out[q] = Time;
}

int main(){
    // init();
    // push_links();
    // traverse(s);
    // dfs(Root);
}
