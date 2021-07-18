#include <iostream>
#include <vector>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS
>;

using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

void solve(){
  int student_count, skill_count, proposed_util; std::cin >> student_count >> skill_count >> proposed_util;

  std::unordered_map<std::string, std::vector<int>> skill_to_students;
  {
    std::string skill;
    for(int i = 0; i < student_count; i++) {
      for(int j = 0; j < skill_count; j++) {
        std::cin >> skill;
        skill_to_students[skill].push_back(i);
      }
    }
  }

  std::array<std::array<int, 400>, 400> common_skills = {};
  for(const auto &[skill_name, students_with_skill] : skill_to_students) {
    for(int i = 0; i < (int)students_with_skill.size(); i++) {
      for(int j = i+1; j < (int)students_with_skill.size(); j++) {
        const int s1 = students_with_skill[i];
        const int s2 = students_with_skill[j];
        common_skills[s1][s2]++;
        common_skills[s2][s1]++;
      }
    }
  }

  graph g(student_count);
  for(int i = 0; i < student_count; i++) {
    for(int j = i+1; j < student_count; j++) {
      if (common_skills[i][j] > proposed_util) {
        boost::add_edge(i, j, g);
      }
    }
  }

  std::vector<vertex_desc> mate(student_count);
  boost::edmonds_maximum_cardinality_matching(g, &mate[0]);
  const bool possible = static_cast<int>(boost::matching_size(g, &mate[0])) == student_count/2;

  std::cout << (possible ? "not optimal" : "optimal") << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T; std::cin >> T;
  while(T--) {
    solve();
  }
}
