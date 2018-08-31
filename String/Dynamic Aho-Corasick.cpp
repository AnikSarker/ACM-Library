#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define MAX 300009
const int LOG = 19;
typedef long long ll;

struct Aho{
//Aho-Corasick
//Complexity : |Text| + Sum of all |Pattern| + O(number of Occurrences)
//if occurrence positions needed, Worst Case Complexity : (SumLen) Root (SumLen)
    int Size;
    map<char,int>node[MAX];
    int Root;                //AC automaton Root
    int Nnode;               //Total node count
    int Link[MAX];           //failure links
    pii Level[MAX];          //Level[i] = Depth of node i
    int Len[MAX];            //Len[i] = length of i-th query string
    //vector<int>End[MAX];     //End[i] = indices of strings those end in node i
    //vector<int>Occ[MAX];     //Occ[i] = occurrences of i-th query string
    vector < string > vec;
    int EndCounter[MAX];

    Aho(){init();}

    void init(){
        Root=0;
        Nnode=0;
        node[Root].clear();
        vec.clear();
        Size = 0;
        EndCounter[Root] = 0;
    }

    void insertword(string p,int ind){
        vec.push_back(p);
        Size++;
        int len=p.size();
        int now=Root;
        for(int i=0;i<len;i++){
            if(!node[now][p[i]]){
                node[now][p[i]]=++Nnode;
                Level[Nnode]=make_pair(Level[now].first+1,Nnode);
                node[Nnode].clear();
                //End[Nnode].clear();
                EndCounter[Nnode] = 0;
            }
            now=node[now][p[i]];
        }
        //End[now].push_back(ind);
        EndCounter[now]++;
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
                //for(int x : End[Link[v]]) End[v].push_back(x);
                EndCounter[v] += EndCounter[Link[v]];
            }
        }
    }

    ll traverse(string s){
        if(Size == 0) return 0;
        int len=s.size();
        int now=Root;
        ll ans = 0;
        for(int i=0;i<len;i++)    {
            while(now!=-1 && !node[now][s[i]]) now=Link[now];
            if(now!=-1) now=node[now][s[i]];
            else now=0;
            //for(int x=0;x<End[now].size();x++) Occ[End[now][x]].push_back(i);
            ans += EndCounter[now];

        }
        return ans;
    }

};

//Complexity : (Complexity of Aho-Corasick) * LOG
struct DynamicAho{
    Aho aho[LOG];
    DynamicAho() {init();}
    void init() {for(ll i = 0; i < LOG; i++) aho[i].init();}

    void Insert(string str){
        int k = 0;
        for(k = 0; k < LOG && aho[k].Size > 0; k++);
        aho[k].insertword(str, 0);

        for(int i = 0; i < k; i++){
            vector < string > vec = aho[i].vec;
            aho[i].init();
            for(auto s : vec) aho[k].insertword(s, 0);
        }
        aho[k].push_links();
    }

    ll getCount(string s){
        ll ans = 0;
        for(ll i = 0; i < LOG; i++) ans += aho[i].traverse(s);
        return ans;
    }
};

DynamicAho dn_aho[2];

int main(){
    //init();
    //Must clear Occ vector before starting every test case
    //insert identical query strings only once and handle others keeping map
    //push_links();
    //traverse(s);
    //Find the occurrences from Occ array and use them.
    ios::sync_with_stdio(false);
    ll n, tp;
    string str;

    cin >> n;
    for(ll i = 1; i <= n; i++){
        cin >> tp >> str;
        if(tp == 3){
            ll ans1 = dn_aho[0].getCount(str) ;
            ll ans2 = dn_aho[1].getCount(str);
            cout << ans1 - ans2 << '\n';
            fflush(stdout);
        }
        else dn_aho[tp - 1].Insert(str);
    }
}
