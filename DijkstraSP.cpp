/*
https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm

Here's my short implementation of the efficient 𝑂(𝑚log𝑛)
O(mlogn) version. It's written in C++11, using a set to store the "priority queue" of active vertices. It's pretty fast: it passed on SPOJ.com - Problem SHPATH wihout any optimizations.

The function expects that:
1) the vertices are labeled 0 through n-1
2) graph[x] is the list of directed edges from vertex x
3) the edge lengths are zero or positive, and small enough so that no temporary distance will overflow an int.
*/

struct edge { int to, length; };
    
int dijkstra(const vector< vector<edge> > &graph, int source, int target) {
    vector<int> min_distance( graph.size(), INT_MAX );
    min_distance[ source ] = 0;
    set< pair<int,int> > active_vertices;
    active_vertices.insert( {0,source} );
        
    while (!active_vertices.empty()) {
        int where = active_vertices.begin()->second;
        if (where == target) return min_distance[where];
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : graph[where]) 
            if (min_distance[ed.to] > min_distance[where] + ed.length) {
                active_vertices.erase( { min_distance[ed.to], ed.to } );
                min_distance[ed.to] = min_distance[where] + ed.length;
                active_vertices.insert( { min_distance[ed.to], ed.to } );
            }
    }
    return INT_MAX;
}

