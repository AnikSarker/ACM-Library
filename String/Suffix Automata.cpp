#include <bits/stdc++.h>
using namespace std;
#define ll long long int

namespace SAM{
    struct Node{
        int Len, Link;
        int FrPos; ll pathCount;
        map<char,int>Next;
        void Clear() {Len = pathCount = 0; Link = FrPos = -1; Next.clear();}
    };

    const int MAXLEN = 100000;
    Node St[MAXLEN*2];
    int Size, Last;

    // root is St[0]
    void Init() {Size = Last = 0; St[0].Clear();}

    void Extend(char c){
        int Curr = ++Size;
        St[Curr].Clear();
        St[Curr].Len = St[Curr].FrPos = St[Last].Len + 1;

        int p = Last;
        while(p!=-1 && !St[p].Next.count(c)) St[p].Next[c] = Curr, p = St[p].Link;

        if(p == -1) St[Curr].Link = 0;
        else{
            int q = St[p].Next[c];
            if(St[p].Len + 1 == St[q].Len) St[Curr].Link = q;
            else{
                int Clone = ++Size;
                St[Clone].Len = St[p].Len + 1;
                St[Clone].Next = St[q].Next;
                St[Clone].Link = St[q].Link;
                St[Clone].FrPos = St[q].FrPos;

                while(p!=-1 && St[p].Next[c]==q) St[p].Next[c] = Clone, p=St[p].Link;
                St[q].Link = St[Curr].Link = Clone;
            }
        }
        Last = Curr;
    }

    ll pathCalc(int pos){
        if(St[pos].pathCount != 0) return St[pos].pathCount;
        ll re = 1;
        for(auto to : St[pos].Next) re += pathCalc(to.second);
        return St[pos].pathCount = re;
    }
}
