// 1. Checks the relation between a/b and c/d, a, c >= 0, b, d > 0
bool comp (ll a, ll b, ll c, ll d){
  if(a / b != c / d) return a / b < c / d;
  a %= b, c %= d;
  if(c == 0) return 0;
  if(a == 0) return 1;
  return comp(d, c, b, a);
}

// 2. Sorting points based on polar angle
bool sgn (Point p) {return p.y < 0 || (p.y == 0 && p.x < 0);}

bool operator < (Point p, Point q) const{
  if(sgn(p) != sgn(q)) return sgn(p) < sgn(q);
  return getCross(p, q) > 0;
}

// 3. Check whether Angle(a1, b1) < Angle(a2, b2)
bool angleLess (Vector a1, Vector b1, Vector a2, Vector b2) {
    pt p1 ( getDot(a1, b1), abs(getCross(a1, b1)) );
    pt p2 ( getDot(a2, b2), abs(getCross(a2, b2)) );
    return getCross(p1, p2) > 0;
}
