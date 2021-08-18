#include <iostream>
#include <vector>
#include <queue>
#include <string>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;

struct Vertex_info {
  int color;
  int component;
};
using Vb = CGAL::Triangulation_vertex_base_with_info_2<Vertex_info, K>;
using Fb = CGAL::Triangulation_face_base_2<K>;
using Tds = CGAL::Triangulation_data_structure_2<Vb, Fb>;
using Triangulation_augmented = CGAL::Delaunay_triangulation_2<K, Tds>;

using Point = K::Point_2;
using v2dp = std::vector<Point>;

Point loadpoint(){
  int a, b;
  std::cin >> a >> b;
  return Point{a, b};
}

v2dp loadv2dp(const int count) {
  v2dp v;
  v.reserve(count);
  for(int i = 0; i < count; i++) {
    v.push_back(loadpoint());
  }
  return v;
}

template<typename T>
T load() {
  T val;
  std::cin >> val;
  return val;
}

void skip_input(const int count) {
  int num;
  for(int i = 0; i < count; i++) {
    std::cin >> num;
  }
}

bool is_bipartite(Triangulation_augmented &t, const double squared_radius) {
  int component_id = 0;

  for(auto f = t.finite_vertices_begin(); f != t.finite_vertices_end(); ++f) {
    f->info() = {0, 0};
  }

  // Run BFS on all components and color all nodes
  std::queue<Triangulation_augmented::Vertex_handle> q;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    if (v->info().component) {
      continue;
    }

    component_id++;
    q.push(v);
    int current_color = 1;
    while(!q.empty()) {
      const int current_size = q.size();
      for(int i = 0; i < current_size; i++) {
        const auto v_handle = q.front(); q.pop();

        if ((v_handle->info().color | current_color) == 3) {
          return false;
        }

        if (v_handle->info().component) {
          continue;
        }

        v_handle->info() = {current_color, component_id};
        Triangulation_augmented::Vertex_circulator c = t.incident_vertices(v_handle);
        do {
          if (!t.is_infinite(c) && CGAL::squared_distance(v_handle->point(), c->point()) <= squared_radius){
            q.push(c);
          }
        } while (++c != t.incident_vertices(v_handle));
      }

      // After one level swap color
      current_color = (~current_color) & 3;
    }
  }

  std::vector<Triangulation_augmented::Vertex_handle> neighbor_set;
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v) {
    neighbor_set.clear();

    Triangulation_augmented::Vertex_circulator c = t.incident_vertices(v);
    do {
      if (!t.is_infinite(c)){
        neighbor_set.push_back(c);
      }
    } while (++c != t.incident_vertices(v));

    for(int i = 0; i < (int)neighbor_set.size(); i++) {
      for(int j = i+1; j < (int)neighbor_set.size(); j++) {
        const auto v1 = neighbor_set[i];
        const auto v2 = neighbor_set[j];
        if (CGAL::squared_distance(v1->point(), v2->point()) <= squared_radius && v1->info().color == v2->info().color) {
          return false;
        }
      }
    }
  }

  return true;
}

void solve() {
  const int station_count = load<int>();
  const int clue_count = load<int>();
  const double radius = load<int>();
  const double squared_radius = radius*radius;
  const auto stations = loadv2dp(station_count);

  Triangulation_augmented t(std::begin(stations), std::end(stations));

  // Check for network with interferences
  if(!is_bipartite(t, squared_radius)) {
    skip_input(4*clue_count);
    std::cout << std::string(clue_count, 'n') << std::endl;
    return;
  }

  // Check if Holmes and Watson can connect to same network or communicate directly
  for(int i = 0; i < clue_count; i++) {
    const Point from = loadpoint();
    const Point to = loadpoint();

    if (CGAL::squared_distance(from, to) <= squared_radius) {
      std::cout << 'y';
      continue;
    }

    const auto v1 = t.nearest_vertex(from);
    const auto v2 = t.nearest_vertex(to);
    const bool reachable = CGAL::squared_distance(from, v1->point()) <= squared_radius && CGAL::squared_distance(to, v2->point()) <= squared_radius;
    const bool same_component = v1->info().component == v2->info().component;
    std::cout << "ny"[reachable && same_component];
  }

  std::cout << std::endl;
}

int main() {
std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}

