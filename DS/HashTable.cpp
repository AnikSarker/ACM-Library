#include <bits/stdc++.h.>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
struct chash {int operator()(int x) const { return hash_f(x); }};
typedef gp_hash_table<int, int, chash>gp;
gp table;
