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

std::array<int, 4> cluster_sizes; //1, 2, 3, 4+

int get_family_count_fit(const int tents_needed) {
  const auto &counts = cluster_sizes;
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

void solve() {
  const auto nr_tents = load<int>();
  const auto tents_needed = load<int>();
  const auto query_families = load<int>();
  const auto query_distance = load<double>();
  
  const auto tents = loadv2dp(nr_tents);
  
  cluster_sizes = {nr_tents, 0, 0, 0};
  std::vector<int> cluster_sizes(nr_tents, 1);
  Triangulation t(std::begin(tents), std::end(tents));
  boost::disjoint_sets_with_storage<> uf(nr_tents);
  
  for(auto edge = t.finite_edges_begin(); edge != t.finite_edges_end(); ++edge) {
    Index i1 = edge->first->vertex((edge->second+1)%3)->info();
    Index i2 = edge->first->vertex((edge->second+2)%3)->info();
    Index c1 = uf.find_set(i1);
    Index c2 = uf.find_set(i2);
    if (c1 != c2 && t.segment(edge).squared_length() < query_distance) {
      uf.link(c1, c2);
      const int size1 = cluster_sizes[c1];
      const int size2 = cluster_sizes[c2];
      const int new_size = std::min(size1+size2, 4);
      cluster_sizes[c1] = cluster_sizes[c2] = new_size;
      cluster_sizes[size1-1]--;
      cluster_sizes[size2-1]--;
      cluster_sizes[new_size-1]++;
    }
  }
  
  const int query_distance_result = get_family_count_fit(tents_needed);
  
  cluster_sizes = {nr_tents, 0, 0, 0};
  cluster_sizes = std::vector<int>(nr_tents, 1);
  uf = boost::disjoint_sets_with_storage<>(nr_tents);
  std::vector<std::tuple<Index,Index,K::FT>> edges;
  edges.reserve(3*nr_tents);
  for(auto edge = t.finite_edges_begin(); edge != t.finite_edges_end(); ++edge) {
    Index i1 = edge->first->vertex((edge->second+1)%3)->info();
    Index i2 = edge->first->vertex((edge->second+2)%3)->info();
    edges.emplace_back(i1, i2, t.segment(edge).squared_length());
  }
  
  std::sort(std::begin(edges), std::end(edges), [](const auto &e1, const auto &e2){
    return std::get<2>(e1) < std::get<2>(e2);
  });
  
  int64_t query_families_result = -1;
  for(const auto [i1, i2, squared_distance] : edges) {
    Index c1 = uf.find_set(i1);
    Index c2 = uf.find_set(i2);
    if (c1 != c2) {
      uf.link(c1, c2);
      const int size1 = cluster_sizes[c1];
      const int size2 = cluster_sizes[c2];
      const int new_size = std::min(size1+size2, 4);
      cluster_sizes[c1] = cluster_sizes[c2] = new_size;
      cluster_sizes[size1-1]--;
      cluster_sizes[size2-1]--;
      cluster_sizes[new_size-1]++;
      
      if (get_family_count_fit(tents_needed) < query_families) {
        query_families_result = squared_distance;
        break;
      }
    }
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
