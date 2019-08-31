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

Minimum Vertex Cover in bipartite graph
Let's say the maximum matching is M.

And orientation of edges will be :
Those edges that belong to M will go from right to left, 
all other edges will go from left to right.
Now run DFS starting at all left vertices that are not incident to edges in M. 
Some vertices of the graph will become visited during this DFS and some not-visited.
To get minimum vertex cover you take all visited right vertices of M, and all not-visited left vertices of M.

***************************************************************************************
***************************************************************************************

Minimum Path cover in a Directed Acyclic Graph :

find the minimum number of vertex-disjoint paths to cover each vertex in V.
make a bipartite graph G' = {Vout X Vin , E }
Vout = nodes having positive out-degree
Vin = nodes have positive in-degree
G' has a matching of size m iff there exists n-m vertex-disjoint paths that cover each vertex in G.

***************************************************************************************
***************************************************************************************

In a DAG delete some edges so that each node’s indegree=outdegree=k and maximise the sum of the deleted edge’s cost :

From source to each node i (1<=i<=n), add edge of capacity k, cost 0
From each node j (n<j<=n+n) to Sink, add edge of capacity k, cost 0
For all i,j (1<=i,j<=n) If in the main graph from i to j , there is an edge , then add from each node i to n+j of capacity 1
and cost = original edge’s cost. Then run the min cost max flow algorithm.
if max flow = n*k , then minimum cost will be the answer.
Otherwise it will not be possible.


***************************************************************************************
***************************************************************************************

Given a graph where each node has value and each edge’s cost = value[y] xor value[x].
Initially some node’s values are given and we have to find other node’s value such that sum of all edge is minimum.

We make LOG(MAX_VAL) graphs for each bit.
For ith bit,for each known node u, 
  add edge with capacity INF from source to u whose i bit is set.
  otherwise add edge with capacity INF from node to sink.
add the regular edge with capacity 1 .
Then after finding the MinCut , let U are those node which are in source's component.
Then their bit will be set. 

***************************************************************************************
***************************************************************************************

find a subgraph such that cost(edge)-cost(node) is maximum
Consider each EDGE & NODE as node.
Add edge from Source to each EDGE of capacity w & from each EDGE to both nodes of capacity INF & from each node to sink of capacity p.
Ans = sum of w - maxflow 


***************************************************************************************
***************************************************************************************
Finding an euler circuit in a graph G with both directed and undirected edges where undirected edges can be used once.

Euler circuit exists iff every vettex's indegree = outdegree

make a bipartite graph.One partition contains all edges and other contains all nodes. 
For each directed edge , connect this edge to its head endpoint . 
For each undirected edge , connect this edge to its both endpoints .
Now from Source node , add edges to each G's edge.
all of these edges' capacity will be 1.
Now from each G's node , add edges to sink.
Edge i's capacity will be total degree/2 of node i.

Then check the flow and so on. 


***************************************************************************************
***************************************************************************************

Find a subgraph where |edge|/|node] is maximum.

make a bipartite graph.One partition contains all edges and other contains all nodes. 
For each G's edge , connect this edge to its both endpoints .
Now from Source node , add edges to each G's edge.
all of these edges' capacity will be 1.
Now from each G's node , add edges to sink.
Edge i's capacity will be X.

we do binary search on X's value.
if( Flow < Number of Edges )  left = mid
otherwise right = mid. 


**********************************************************************************************************************
**********************************************************************************************************************/
