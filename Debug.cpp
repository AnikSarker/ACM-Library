void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
#define debug(...) cerr << "Line : " << __LINE__ <<" [" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
