/*
MST : Prim’s Algorithm
initial distance of all nodes are INFINITE except the starting node , which distance is 0.
and all nodes are marked as non-visited.
Now until all nodes are visited, pick the non-visited node u 
which distance is lowest than all other non-visited nodes.
After picking any nodes, update its all adjacent node v’s distance 
	 if dis[u]+edgeCost(u,v)<dis[v] .  

MST : Borukuva’s Algorithm
*all edge cost must be distinct.
initially all nodes are individual components.
While there is more than one components,
  for each components	
    find the smallest edge which connects this component 
		 	to any other component. And then add this edge.
These edges are the edges of minimum spanning tree. */
