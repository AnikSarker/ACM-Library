/* 
* Number of permutations of n elements with k disjoint cycles
= Str1(n,k) = (n-1) * Str1(n-1,k) + Str1(n-1,k-1)

* n! = Sum(Str1(n,k)) (for all 0 <= k <= n).

* Ways to partition n labelled objects into k unlabelled
subsets = Str2(n,k) = k * Str2(n-1,k) + Str2(n-1,k-1)

* Parity of Str2(n,k) : ( (n-k) & Floor((k-1)/2) ) == 0)

* Ways to partition n labelled objects into k unlabelled 
subsets, with each subset containing at least r elements : 
SR(n,k) = k * SR(n-1,k) + C(n-1,r-1) * SR(n-r,k-1)

* Number of ways to partition n labelled objects 1,2,3, ... n
into k non-empty subsets so that for any integers i and j in a
given subset |i-j| >= d : Str2(n-d+1, k-d+1), n >= k >= d
*/
