#include "mst.hpp"

using std::endl;

void MST::add_edge(Edge e){
    MST::push_back(e);
    wt += e.weight();
}




ostream &operator<<(ostream &os, const MST &M)
{
  os << "MST: " << M.name << " {\n";
  os << " total weight: " << M.wt << endl;
  os << " edges = {\n";
  for (auto e : M) {
    os << "  " << e << '\n';
  }
  os << " }" << endl;
  os << "}" << endl;

  return os;
}

