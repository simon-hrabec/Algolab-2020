template <typename T>
struct iter_wrapper{
  T iter, iter_end;
  T begin() const {return iter;}
  T end() const {return iter_end;}
};

template <typename T>
iter_wrapper<typename T::first_type> range_loop_wrapper(const T& iter_pair) {
  return iter_wrapper<typename T::first_type>{iter_pair.first, iter_pair.second};
}

for(const auto &edge : range_loop_wrapper(boost::edges(G))) {
	// now you can use a range loop without need to derefence the iterator
}
