/*
* Total number of paths from point P(x1, y1) 
to point Q(x2, y2) where x2 >= x1 and y2 >= y1 :
Let x = x2 - x1 and y = y2 - y1. Then ans = C(x+y, x).

* Total number of paths from point P(x1, y1) to point Q(x2, y2)
where x2 >= x1 and y2 >= y1 without crossing the line X = Y + c :
Let x = x2 - x1 and y = y2 - y1. Then ans = C(x+y, x) - C(x+y, x+c-1).
Special Case : x = n, y = n, c = 0, then ans = C(2n, n) - C(2n, n-1) [Catalan]

* Catalan triangle : Total number of permutation having n X and k Y
so that Count(X)-Count(Y)>=0 in any prefix (Non-negative Partial Sum) :
ans =  C(n+k,k) - C(n+k, k-1)

* Catalan trapezoid : Total number of permutation having n X and k Y 
so that Count(Y) - Count(X) < m in any prefix, then :
when 0 <= k < m, ans = C(n+k,k)
when m <= k <= n+m-1, ans = C(n+k,k) - C(n+k,k-m)
when k > n+m-1, ans = 0
*/
