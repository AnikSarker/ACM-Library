//1. Checks the relation between a/b and c/d 
bool comp(ll a, ll b, ll c, ll d){
  if(a / b != c / d) return a / b < c / d;
  a %= b, c %= d;
  if(c == 0) return 0;
  if(a == 0) return 1;
  return comp(d, c, b, a);
}

//2. Sorting points based on angle
bool sgn(Point p){
  if(p.y != 0) return p.y < 0;
  return p.x < 0;
}
 
bool operator < (Point p, Point q) const{
  if(sgn(p) != sgn(q)) return sgn(p) < sgn(q);
  return getCross(p, q) > 0;
}

