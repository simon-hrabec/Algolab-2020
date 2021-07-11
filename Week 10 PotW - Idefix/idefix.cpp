#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/pending/disjoint_sets.hpp>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Index = std::size_t;
using Vb = CGAL::Triangulation_vertex_base_with_info_2<Index,K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb,Fb>;
using Triangulation = CGAL::Delaunay_triangulation_2<K,Tds>;
using Point = K::Point_2;
using IPoint = std::pair<K::Point_2, Index>;

// if bool = false - idx1, idx1, distance
// if bool = true - tree_idx, tree_idx, distance
using universal_edge = std::tuple<Index, Index, K::FT, bool>;

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

Point loadp() {
  int x, y;
  std::cin >> x >> y;
  return Point{x, y};
}

void solve() {
  // Load data, process trees/bones, define used data structures
  const std::size_t tree_count = load<int>();
  const std::size_t bone_count = load<int>();
  const double sradius = load<double>();
  const int more_bones_count = load<int>();

  std::vector<IPoint> trees;
  std::vector<int> tree_has_bones(tree_count);
  std::vector<universal_edge> edges;
  boost::disjoint_sets_with_storage<> uf(tree_count);

  trees.reserve(tree_count);
  for(Index i = 0; i < tree_count; i++) {
    const Point tree = loadp();
    trees.emplace_back(tree, i);
  }

  Triangulation t(std::begin(trees), std::end(trees));

  // Create bone edges and calculate bone count for trees
  for(Index i = 0; i < bone_count; i++) {
    const Point bone = loadp();

    Index idx = t.nearest_vertex(bone)->info();
    const double dis = 4*CGAL::squared_distance(bone, trees[idx].first);
    edges.emplace_back(idx, idx, dis, true);
    if (dis <= sradius) {
      tree_has_bones[idx]++;
    }
  }

  // Iterate over all triangulation edges, connect components
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();

    if (i1 > i2) {
      std::swap(i1, i2);
    }

    const auto &p1 = trees[i1].first;
    const auto &p2 = trees[i2].first;

    const double dis = CGAL::squared_distance(p1, p2);

    edges.emplace_back(i1, i2, dis, false);

    if (dis <= sradius) {
      Index c1 = uf.find_set(i1);
      Index c2 = uf.find_set(i2);

      if (c1 != c2) {
        uf.link(c1, c2);
        tree_has_bones[uf.find_set(i1)] = tree_has_bones[c1] + tree_has_bones[c2];
      }
    }
  }

  const int max_reachable_bones = *max_element(std::begin(tree_has_bones), std::end(tree_has_bones));
  uint64_t min_required_radius = 0;

  std::sort(std::begin(edges), std::end(edges), [](const universal_edge& e1, const universal_edge& e2) {
    return std::get<2>(e1) < std::get<2>(e2);
  });

  uf = boost::disjoint_sets_with_storage<>(tree_count);
  std::fill(std::begin(tree_has_bones), std::end(tree_has_bones), 0);

  // Iterate from shortest edges to find minimal required radius
  for(const universal_edge &e : edges) {
    const Index i1 = std::get<0>(e);
    const Index i2 = std::get<1>(e);
    const double dis = std::get<2>(e);
    const bool is_bone = std::get<3>(e);

    if (is_bone) {
      Index c1 = uf.find_set(i1);
      tree_has_bones[c1]++;
      if (tree_has_bones[c1] >= more_bones_count) {
        min_required_radius = dis;
        break;
      }
    } else {
      Index c1 = uf.find_set(i1);
      Index c2 = uf.find_set(i2);

      if (c1 != c2) {
        uf.link(c1, c2);
        Index cnew = uf.find_set(i1);
        tree_has_bones[cnew] = tree_has_bones[c1] + tree_has_bones[c2];

        if (tree_has_bones[cnew] >= more_bones_count) {
          min_required_radius = dis;
          break;
        }
      }
    }
  }

  std::cout << max_reachable_bones << " " << min_required_radius << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
