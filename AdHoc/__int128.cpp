#include <bits/stdc++.h>
using namespace std;

int main(){
    int n = 100;
    __int128 Ans = n;

    vector<char> vec;
    vec.clear();
    while(Ans) vec.push_back((int) Ans % 10), Ans /= 10;
    reverse(vec.begin(),vec.end());
    for(int x : vec) printf("%d",x);
    printf("\n");
}
