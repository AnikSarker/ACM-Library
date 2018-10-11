#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {int operator() (string x) {return hash<int>{}(x[0] ^ RANDOM);}};
gp_hash_table<string, int, chash> table;
