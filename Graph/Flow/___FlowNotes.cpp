/*************************************************************************************
**************************************************************************************
Partial Ordered Set 

Let S be a set of elements and  ≤  be a partial ordering on the set. That is, 
for some elements x and y in S we may have x ≤ y. The only properties that  ≤  
must satisfy are reflexivity (x ≤ x), antisymmetry (if x ≤ y and y ≤ x, then x = y), 
and transitivity (if x ≤ y and y ≤ z, then x ≤ z). Note that because it is a partial ordering,
not all x and y are comparable.
An example of a partially ordered set (poset) is the set of points (x, y) in the Cartesian plane with the 
operator (x1, y1) ≤ (x2, y2) iff x1 ≤ x2 and y1 ≤ y2 (e.g. NCPC 2007 problem).

We define a chain C to be a subset of S such that the elements of C can be labelled x1, x2, ..., xn 
such that x1 ≤ x2 ≤ ... ≤ xn. A partition P is a set of chains where each element  occurs in exactly one chain.

We define an antichain A to be a subset of S such that for any x and y in A we have neither x ≤ y nor y ≤ x. 
That is, no two elements of an antichain are comparable.

Dilworth's Theorem
We can define the width of a poset in two ways, which is the result of Dilworth's Theorem. 
One definition is the size of the maximum antichain; the other is the size of the minimum partition. 
It is easy to see that any partition must have at least as many chains as the size of the maximum 
antichain because every element of the antichain must be in a different chain. Dilworth's Theorem 
tells us that there exists a partition of exactly that size and can be proved inductively.

Calculating the Width
So how does one calculate the width of a poset? To solve this problem in general, we can use maximum matching
on a bipartite graph. Duplicate each element x in S as ux and vx and if x ≤ y (for x ≠ y) then add the edge .
If you compute the maximum matching on this graph, this is equivalent to partitioning the elements into chains,
where if the edge  is chosen then x and y are in the same chain. In particular, if the size of the matching is m
and |S| = n, then the number of partitions is n - m. Notice that this gives a bijection between partitions and 
matchings, so the maximum matching gives the minimum partition, which we know is equal to the width as given
by Dilworth's Theorem.

***************************************************************************************
***************************************************************************************

MAX/MIN Closure :  

Closure is a directed subgraph with no outgoing edges. 
MAX/Min Closure means a closure with max/min sum of weighted nodes outside the graph.
For MAX, join source with positive nodes,sink with negative nodes and capacities are
absolute value,infinite capacity between existing edges. 
For min,source & sink is reversed.
Ans = sum of positive nodes - min cut (For max)
Ans = sum of negative nodes + min cut (For min)

***************************************************************************************
***************************************************************************************
Demand Capacity : 

We add a new source s′ and a new sink t′, a new edge from the source s′ to every other vertex, 
a new edge for every vertex to the sink t′, and one edge from t to s. Additionally we define 
the new capacity function c′ as:

c′((s′,v))=∑u∈Vd((u,v)) for each edge (s′,v).
c′((v,t′))=∑w∈Vd((v,w)) for each edge (v,t′).
c′((u,v))=c((u,v))−d((u,v)) for each edge (u,v) in the old network.
c′((t,s))=∞

If the new network has a saturating flow (a flow where each edge outgoing from s′ is
completely filled, which is equivalent to every edge incoming to t′ is completely filled),then
the network with demands has a valid flow, and the actual flow can be easily reconstructed from
the new network. Otherwise there doesn't exist a flow that satisfies all conditions. 

***************************************************************************************
***************************************************************************************

König-Egeváry Theorem
The König-Egeváry theorem (König's theorem) , asserts that 
the maximum matching is equal to the vertex cover number for a bipartite graph.

***************************************************************************************
***************************************************************************************

Minimum Path cover in a Directed Acyclic Graph :

find the minimum number of vertex-disjoint paths to cover each vertex in V.
make a bipartite graph G' = {Vout X Vin , E }
Vout = nodes having positive out-degree
Vin = nodes have positive in-degree
G' has a matching of size m iff there exists n-m vertex-disjoint paths that cover each vertex in G.


**********************************************************************************************************************
**********************************************************************************************************************/
