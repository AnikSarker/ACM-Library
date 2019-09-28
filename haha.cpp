#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
const int maxn = 105;
typedef long long ll;
#define ACCEPTED 0
#define REJECTED 1
#define PENDING 2

struct data{
    int state;
    int time;
    int run;
    data(int s, int t, int r) {state = s, time = t, run = r;}

    void Print(){
        cout<<state<<" "<<time<<" "<<run<<endl;
    }
};

data parse(string info){
    data ret(0,0,0);
    if(info[0] == '0') {ret.state = REJECTED; return ret;}

    int idx = 0;
    if(info[idx] == '?') ret.state = PENDING, idx++;
    else if(info[idx] == '-') ret.state = REJECTED, idx++;
    else ret.state = ACCEPTED;

    int val = 0;
    while(info[idx] != '/') {val = val * 10 + info[idx] - '0'; idx++;}
    ret.run = val;

    idx++;

    val = 0;
    while(idx < info.size() && info[idx] != ' ') {val = val * 10 + info[idx] - '0'; idx++;}
    ret.time = val;
    return ret;
}

string Names[maxn];
vector<data> vec[maxn];
vector<string> RankList;

map < string , int > id;

ll dp1[105][22][9000];
ll dp2[105][22][9000];
ll csum[105][22][9000];

int main(){
    int t;
    scanf("%d",&t);

    for(int cs=1; cs<=t; cs++){
        int n, m;
        scanf("%d %d",&n, &m);

        memset(dp1, 0, sizeof(dp1));
        memset(dp2, 0, sizeof(dp2));
        memset(csum, 0, sizeof(csum));

        cin.ignore();
        string str;
        getline(cin, str);
        getline(cin, str);
        getline(cin, str);

        int Count = 0;
        for(char ch : str) if(ch == '|') Count++;
        Count = Count - 3;

        for(int i=1; i<=n; i++){
            getline(cin, str);

            string name = "";
            for(int j=1;j<21;j++) name += str[j];
            Names[i] = name;
            id[name] = i;

            int beg = 22;
            for(int j=0; j<=m; j++){
                string ToParse = "";
                for(int k=0; k<7;k++) ToParse += str[beg+k];
                data gelum = parse(ToParse);

                beg += 8;
                if(j > 0) vec[i].push_back(gelum);
            }
            getline(cin, str);
        }

        getline(cin, str);
        getline(cin, str);
        RankList.resize(n);

        for(int i=1; i<=n; i++){
            getline(cin, str);
            string name = "";
            for(int j=1;j<21;j++) name += str[j];
            RankList.push_back(name);
//            cout<<name<< ' ' << id[name] << endl;
        }
        getline(cin, str);

        for(int i = 1; i <= n; i++){

            for(int j = 0; j < (1 << m); j++){

                bool flg = true;
                int pen = 0;
                for(int k = 0; k < m; k++){

                    if(vec[i][k].state == ACCEPTED && ((1 << k) & j) == 0) {
                        flg = false;
                        break;
                    }

                    if(vec[i][k].state == REJECTED && ((1 << k) & j) == 1) {
                        flg = false;
                        break;
                    }
                    if((1 << k) & j) pen += vec[i][k].time + (vec[i][k].run - 1) * 20, cout << k << ' ';
                }
                if(!flg) continue;
                int slvcnt = __builtin_popcount(j);

                dp1[i][slvcnt][pen]++;
                cout << endl << i << ' ' << j << ' ' << slvcnt << ' ' << pen << endl;

            }

        }

        int idd = id[RankList[0]];

        for(int j = 1; j <= m; j++) {
            for(int k = 8600; k >= 1; k--){
                dp2[1][j][k] = dp1[idd][j][k];
                csum[1][j][k] = csum[1][j][k + 1] + dp2[1][j][k];
                if(csum[1][j][k] >= mod) csum[1][j][k] -= mod;
            }
        }

        for(int i = 2; i <= n; i++){

            int curid = id[RankList[i - 1]];

            for(int myslv = 1; myslv <= m; myslv++){

                for(int mypen = 1; mypen <= 8600; mypen++){

                    int curanss = csum[i - 1][myslv][mypen];

                    for(int j = myslv + 1; j <= m; j++){
                        curanss = (curanss + csum[i - 1][j][1]);
                        if(curanss >= mod) curanss -= mod;
                    }

                    curanss = (curanss * 1LL * dp1[curid][myslv][mypen]) % mod;

                    dp2[i][myslv][mypen] = curanss;

                }

                for(int j = 8600; j >= 1; j--) {
                    csum[i][myslv][j] = csum[i][myslv][j + 1] + dp2[i][myslv][j];
                    if(csum[i][myslv][j] >= mod) csum[i][myslv][j] -= mod;
                }
            }

        }

        int anss = 0;
        for(int i = 1; i <= m; i++) {
            anss = anss + csum[n][i][1];
        }

        anss = anss % mod;

        printf("Case %d: %d", cs++, anss);

    }

}

/*
1
3 4
|--------------------|-------|-------|-------|-------|-------|
|Team Name           |Total  |A      |B      |C      |D      |
|--------------------|-------|-------|-------|-------|-------|
|Team X              |2/330  |?10/255|0/--   |1/10   |5/240  |
|--------------------|-------|-------|-------|-------|-------|
|Team Y              |2/330  |5/230  |0/--   |1/20   |?5/270 |
|--------------------|-------|-------|-------|-------|-------|
|Team Z              |1/30   |-4/--  |1/30   |?1/241 |?1/245 |
|--------------------|-------|-------|-------|-------|-------|

|--------------------|
|Team Z              |
|Team X              |
|Team Y              |
|--------------------|
*/
