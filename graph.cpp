#include <queue>
#include "graph.hpp"
#include "mst.hpp"
#include "union_find.hpp"

using std::cerr;
using std::endl;
using std::cout;

Weighted_Graph::Weighted_Graph(string name) : name(name), E(0), V(0), adj(1) {}


MST Weighted_Graph::kruskal() const
{
  MST mst;

  // The priority pq stores the edges with the minimum element determined by the edge weights.
  // I'm spotting you the declaration of the priority queue since the syntax is particularly forbidding. 
  // I couldn't resist passing a lambda expression (new in C++11) to serve as the comparator in the
  // priority queue.
  auto compare = [](Edge e, Edge f) {return (e.weight() > f.weight());};
  std::priority_queue<Edge, std::vector<Edge>, decltype(compare)> pq(compare);

    
    //Choose edge from non-decreasing list
    //Check if edge is in a cycle
    //If not in a cycl e, add to MST
    //Repeat until all the vertices are covered.
    for (Edge e: edges){
        pq.push(e);
    }
    
    int g = pq.size() + 1;
    
    Union_Find uf = Union_Find(g);
    
    
    
    while(!(pq.size() <= 0) && mst.size() <= (g)){
        Edge e = pq.top();
        pq.pop();
        int v = e.either(), w = e.other(v);
        if (uf.connected(v,w)) continue;
        uf.onion(v,w);
        mst.add_edge(e);
    }
    
  return mst;
}

void Weighted_Graph::add_edge(Edge e)
{
    E += 1;
    edges.push_back(e);
    int v = e.either();
    int w = e.other(v);
    if (V == 0){
        V = 1;
    }

    while (adj.size() <= v | adj.size() <= w){
    adj.resize(adj.size()+1);
        V += 1;
    }
    
    
    adj[v].push_back(w);
    adj[w].push_back(v);
    
}



ostream &operator<<(ostream &os, const Weighted_Graph &G) 
{
  os << "graph: " << G.name << " {\n";
  os << " V: " << G.V << "\n";
  os << " E: " << G.E << "\n";
  os << " adjacency list = {" << "\n";
  for (auto v = 0; v < G.V; v++) {
    os << "  " << v << ": ";
    if (!G.adj[v].empty()) {
      for (auto &w : G.adj[v]) {
	os << w << " ";
      }
    }
    os << endl;
  }
  os << " }" << endl;
  os << "}" << endl;

  return os;
}
