Lets say we need to divide n elements into k groups and
minimize the sum of a specific function for each group.
Normally this kind of problem can be solved by CHT or D&C.
Alien trick comes into use when N, K <= 10^5.

We can use alien trick if the following conditions holds:
Here, Fn(K) = The value of dividing N elements into K groups
1. Fn(K) >= Fn(K + 1) (FOR MINIMIZE , For maximum it's reverse)
It means its always optimal to use (K+1) groups than K groups
2. Fn(K - 1) - Fn(K) >= Fn(K) - Fn(K + 1) (FOR Minimize)

It means with the increase of K, ans becomes more optimal,
but the rate of becoming optimal slows down.

If a function satisfies the above 2 conditions : then 
we define G(n) = Fn(k) + kC
That means we need to add an extra C for each group we use. 
Now this G(n) function will follow a convex property.

So now we can do binary search on C. Inside the binary search.
For each mid, we find the optmial value of G(n) and the 
corresponding k for that value. This k decreases when C increases.

We find the lowest C for which corresponding k is <= given K.
This trick may apply for problems other than DP as well.
