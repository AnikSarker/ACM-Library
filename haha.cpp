#include <bits/stdc++.h>
using namespace std ;
typedef long long ll;
#define maxn 100005
ll t, cs = 1, n;
ll h[maxn];

pair < ll , ll > getPos(ll idx, ll ttm)
{
    ll re1 = ttm % (2 * h[idx]);
    if(re1 >= h[idx]) return make_pair(2 * h[idx] - re1, -1);
    else return make_pair(re1, 1);
}

int main(){
    cin >> t;

    while(t--){

        cin >> n;
        for(ll i = 1; i <= n; i++) scanf("%lld", &h[i]);

        ll anss = 0;

        for(ll i = 2; i <= n; i++){


            pair < ll , ll > cur1 = getPos(i - 1, anss);
            pair < ll , ll > cur2 = getPos(i, anss);

            if(cur1.first >= cur2.first){
                anss++;
                continue;
            }

            if(h[i - 1] < h[i]){
                if(cur2.second == 1){
                    anss += h[i] - cur2.first + h[i] - h[i - 1];
                    cur1 = getPos(i - 1, anss);
                    cur2 = getPos(i, anss);
                }
                else if(cur2.second == -1 && cur1.first > h[i - 1]){
                    anss += cur1.first - h[i - 1];
                    cur1 = getPos(i - 1, anss);
                    cur2 = getPos(i, anss);
                }
            }
            if(cur1.first >= cur2.first){
                anss++;
                continue;
            }


            ll x = cur1.first;
            ll y = h[i] - cur2.first;
            ll z = cur2.first - x;
            ll p;


            if(cur1.second == -1 && cur2.second == 1){
                p = abs(x - y) + (z + 1) / 2;
            }
            else if(cur1.second == 1 && cur2.second == 1){
                p = y + (z + 1) / 2;
            }
            else if(cur1.second == 1 && cur2.second == -1){
                p = (z + 1) / 2;
            }
            else if(cur1.second == -1 && cur2.second == -1){
                p = x + (z + 1) / 2;
            }
            else assert(false);

            anss += p + 1;

//            cout << "yo : " << i << ' ' << x << ' ' << y << ' ' << z << ' ' << p << endl;
//            cout << "yo : " << i << ' ' << cur1.first << ' ' << cur1.second << ' ' << cur2.first << ' ' << cur2.second << endl;

//            cout << i << ' ' << anss << endl;

        }

        printf("Case %lld: %lld\n", cs++, anss);

    }


    return 0;
}
