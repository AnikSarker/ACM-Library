/**
 * To count the number of spanning trees in an undirected graph G
   create an N*N matrix mat, and for each edge (a,b) in G, do
     mat[a][a]++, mat[b][b]++, mat[a][b]--, mat[b][a]--.
   Remove the last row and column, and take the determinant.
 */
