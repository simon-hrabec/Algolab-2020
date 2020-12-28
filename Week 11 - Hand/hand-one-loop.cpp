#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
#include <array>

#include <boost/pending/disjoint_sets.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;

using Index = std::size_t;
using Vb = CGAL::Triangulation_vertex_base_with_info_2<Index,K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb,Fb>;
using Triangulation = CGAL::Delaunay_triangulation_2<K,Tds>;

using Edge = std::tuple<Index,Index,K::FT>;
using Point = K::Point_2;
using IPoint = std::pair<K::Point_2,Index>;
using v2dp = std::vector<IPoint>;

Point loadpoint(){
  int a, b;
  std::cin >> a >> b;
  return Point{a, b};
}

v2dp loadv2dp(const int count) {
  v2dp v;
  v.reserve(count);
  for(int i = 0; i < count; i++) {
    v.emplace_back(loadpoint(), i);
  }
  return v;
}

template <typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

std::array<int, 4> cluster_counts_by_size; //1, 2, 3, 4+
std::array<int, 90000> cluster_sizes;
boost::disjoint_sets_with_storage<> uf;
int tents_needed;

int family_fit_count() {
  const auto &counts = cluster_counts_by_size;
  switch(tents_needed) {
    case 4: {
      const int matched3with1 = std::min(counts[2], counts[0]);
      const int remaining3 = counts[2] - matched3with1;
      const int remaining1 = counts[0] - matched3with1;
      const int tents_of_2 = (counts[1] + remaining3);
      return counts[3] + matched3with1 + tents_of_2/2 + (((tents_of_2 & 1) * 2) + remaining1)/4;
    }
    case 3: {
      const int matched2with1 = std::min(counts[1], counts[0]);
      const int tents_using2 = (counts[1]-matched2with1)/2;
      const int tents_using1 = (counts[0]-matched2with1)/3;
      return counts[3] + counts[2] + matched2with1 + tents_using2 + tents_using1;
    }
    case 2: {
      return counts[3] + counts[2] + counts[1] + counts[0]/2;
    }
    default: {
      return counts[3] + counts[2] + counts[1] + counts[0];
    }
  }
}

void merge_clusters_by_edge(Edge edge) {
    const Index c1 = uf.find_set(std::get<0>(edge));
    const Index c2 = uf.find_set(std::get<1>(edge));
    if (c1 != c2) {
      uf.link(c1, c2);
      const int size1 = cluster_sizes[c1];
      const int size2 = cluster_sizes[c2];
      const int new_size = std::min(size1+size2, 4);
      cluster_sizes[c1] = cluster_sizes[c2] = new_size;
      cluster_counts_by_size[size1-1]--;
      cluster_counts_by_size[size2-1]--;
      cluster_counts_by_size[new_size-1]++;
    }
}

void solve() {
  // Load data, initialize variables
  const auto nr_tents = load<int>();
  tents_needed = load<int>();
  const auto query_families = load<int>();
  const auto query_distance = load<double>();
  
  cluster_counts_by_size = {nr_tents, 0, 0, 0};
  for(int i = 0; i < nr_tents; i++) {
    cluster_sizes[i] = 1;
  }
  uf = boost::disjoint_sets_with_storage<>(nr_tents);
  
  const auto tents = loadv2dp(nr_tents);
  Triangulation t(std::begin(tents), std::end(tents));
  
  // Extract and sort edges
  std::vector<Edge> edges;
  edges.reserve(3*nr_tents);
  for(auto edge = t.finite_edges_begin(); edge != t.finite_edges_end(); ++edge) {
    Index i1 = edge->first->vertex((edge->second+1)%3)->info();
    Index i2 = edge->first->vertex((edge->second+2)%3)->info();
    edges.emplace_back(i1, i2, t.segment(edge).squared_length());
  }
  
  std::sort(std::begin(edges), std::end(edges), [](const auto &e1, const auto &e2){
    return std::get<2>(e1) < std::get<2>(e2);
  });

  // Iterate over edges to solve both queries
  int idx = 0;
  while(family_fit_count() >= query_families && std::get<2>(edges[idx]) < query_distance) {
    merge_clusters_by_edge(edges[idx]);
    idx++;
  }
  
  int64_t query_families_result;
  int query_distance_result;
  if (family_fit_count() < query_families) {
    query_families_result = std::get<2>(edges[idx-1]);
    while(idx < (int)edges.size() && std::get<2>(edges[idx]) < query_distance) {
      merge_clusters_by_edge(edges[idx]);
      idx++;
    }
    query_distance_result = family_fit_count();
  } else {
    query_distance_result = family_fit_count();
    while(family_fit_count() >= query_families) {
      merge_clusters_by_edge(edges[idx]);
      idx++;
    }
    query_families_result = std::get<2>(edges[idx-1]);
  }
  
  std::cout << query_families_result << " " << query_distance_result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--){
    solve();
  }
  return 0;
}
