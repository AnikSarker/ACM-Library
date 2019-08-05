//Resources : http://www.geometer.org/mathcircles/hackenbush.pdf

Lets say you are given a rooted tree and edges are coloured red and blue.
Red player will cut red edges and blue player will cut blue edges.
When a edge is cut, then the subtree under it is cut. Who will win?

It can be solved by red-blue hacken bush.

If the tree is a chain, then it's simple. 
Let cur = 1, and from root there are consecutive x blue/red edges.
Then we add cur x times to our grundy val if the first edges are blue,
otherwise minus cur x times if the first edges are red. And for every next edges
we make cur = cur / 2 and add it to our grundy value depending on the edge colour.

For a tree follow this pseudo-code:

dfs(u):
    if(u == LEAF_NODE) return 0
    else:
        double grundy = 0
        
        for(all child v of u)
            double x = dfs(v)
            if(edge(u,v) is blue):
                y = smallest integer > 0 so that (x + y) > 1
                x = x + y
                y = 2 ^ (y - 1)
                grundy = grundy + (x / y) //Double Divison
            else:
                y = smallest integer > 0 so that (x - y) < -1
                x = x - y
                y = 2 ^ (y - 1)
                grundy = grundy + (x / y) //Double Divison
    return grundy

If the grundy is positive, then blue wins
if it's negetive red wins
If it's 0, then the player who first moves lose.
