//Aho-Corasick
//Complexity : |Text| + Sum of all |Pattern| + O(number of Occurrences)
//if occurrence positions needed, Worst Case Complexity : (SumLen) Root (SumLen)
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define MAX 1000005

int n;
map<char,int>node[MAX];
int Root;                //AC automaton Root
int Nnode;               //Total node count
int Link[MAX];           //failure links
pii Level[MAX];          //Level[i] = Depth of node i
int Len[MAX];            //Len[i] = length of i-th query string
vector<int>End[MAX];     //End[i] = indices of strings those end in node i
//vector<int>Occ[MAX];     //Occ[i] = occurrences of i-th query string
vector < int > edgeslink[MAX];
vector < int > perNodeText[MAX];

int in[MAX], out[MAX];
int euler[MAX];
int momentCur;

void init(){
    Root=0;
    Nnode=0;
    momentCur = 0;

    edgeslink[Root].clear();
    node[Root].clear();
    perNodeText[Root].clear();
}

void insertword(string p,int ind){
    int len=p.size();
    int now=Root;
    for(int i=0;i<len;i++){
        if(!node[now][p[i]]){
            node[now][p[i]]=++Nnode;
            Level[Nnode]=make_pair(Level[now].first+1,Nnode);
            node[Nnode].clear();
            End[Nnode].clear();
            edgeslink[Nnode].clear();
            perNodeText[Nnode].clear();
        }
        now=node[now][p[i]];
    }
    End[now].push_back(ind);
}

void push_links(){
    queue<int>q;
    Link[0]=-1;
    q.push(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto edge : node[u]){
            char ch=edge.first;
            int v=edge.second;
            int j=Link[u];

            while(j!=-1 && !node[j][ch]) j=Link[j];
            if(j!=-1) Link[v]=node[j][ch];
            else Link[v]=0;

            q.push(v);
            edgeslink[Link[v]].push_back(v);
//            for(int x : End[Link[v]]) End[v].push_back(x);
        }
    }
}

void traverse(string s){
    int len=s.size();
    int now=Root;
    for(int i=0;i<len;i++)    {
        while(now!=-1 && !node[now][s[i]]) now=Link[now];
        if(now!=-1) now=node[now][s[i]];
        else now=0;
        perNodeText[now].push_back(i + 1); /// using 1 based indexing for text
//        for(int x=0;x<End[now].size();x++) Occ[End[now][x]].push_back(i);
    }
}
///After dfs, the occurence of ith query string will be the sum of all the occurrence of the subtree under the endNode of ith string
void dfs(int pos)
{
    in[pos] = momentCur + 1;
    for(int val : perNodeText[pos]) euler[++momentCur] = val;
    for(int to : edgeslink[pos]) dfs(to);
    out[pos] = momentCur;
}

int main(){
    ///init();
    ///push_links();
    ///traverse(s);
    ///dfs(Root);

}
