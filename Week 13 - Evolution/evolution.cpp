#include <iostream>
#include <unordered_map>
#include <string>
#include <array>
#include <algorithm>
#include <vector>

template <typename T>
T load(){
  T val;
  std::cin >> val;
  return val;
}

std::array<std::string, 50'000> names;
std::array<int, 50'000> ages;
std::unordered_map<std::string, int> spiecies_map;
std::vector<std::vector<int>> children;

std::vector<std::vector<std::pair<int,int>>> queries; //age, query idx

std::array<int, 50'000> results;

std::vector<std::pair<int,int>> age_stack; //age, id

void dfs(const int idx) {
  age_stack.emplace_back(ages[idx], idx);
  for(const auto &query : queries[idx]) {
    results[query.second] = (*std::lower_bound(std::begin(age_stack), std::end(age_stack), query.first, [](const auto &elem, const int value){
      return elem.first > value;
    })).second;
  }
  for(const int child : children[idx]) {
    dfs(child);
  }
  age_stack.pop_back();
}

void solve() {
  const int nr_species = load<int>();
  const int nr_queries = load<int>();

  spiecies_map.clear();
  queries = std::vector<std::vector<std::pair<int,int>>>(nr_species);
  children = std::vector<std::vector<int>>(nr_species);

  int max_age = std::numeric_limits<int>::min();
  int max_age_idx = 0;

  // Load species and translate string name to number ID
  {std::string name;
  for(int i = 0; i < nr_species; i++) {
    std::cin >> name;
    std::cin >> ages[i];
    spiecies_map.emplace(name, i);
    names[i] = name;

    if (ages[i] > max_age) {
      max_age = ages[i];
      max_age_idx = i;
    }
  }}

  // Load edges
  {std::string name;
  for(int i = 0; i < nr_species-1; i++) {
    std::cin >> name;
    const int child = spiecies_map[name];
    std::cin >> name;
    const int parent = spiecies_map[name];
    children[parent].push_back(child);
  }}

  // Load queries
  {std::string name;
    for(int i = 0; i < nr_queries; i++) {
      std::cin >> name;
      const int max_age = load<int>();
      queries[spiecies_map[name]].emplace_back(max_age, i);
    }
  }

  // Compute results
  dfs(max_age_idx);

  // Print results
  for(int i = 0; i < nr_queries; i++) {
    std::cout << names[results[i]] << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin >> T;
  while(T--) {
    solve();  
  }
  return 0;
}
