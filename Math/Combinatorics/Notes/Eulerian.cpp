* Eulerian number of the first kind :

* A1(n,k) is the number of permutations of 1 to n in which 
exactly k elements are greater than their previous element.
Then : A1(n,k) = (n-k) * A1(n-1,k-1) + (k+1) * A1(n-1,k).

* Eulerian number of the second kind :

* Number of permutations of the multiset {1,1,2,2,..,n,n}
such that for each k, all the numbers appearing between the
two occurrences of k are greater than k = (2n - 1) !

* A2(n,k) is the number of such permutations with k ascents.
Then : A2(n,k) = (2n-k-1) * A2(n-1, k-1) + (k+1) * A2(n-1,k)
