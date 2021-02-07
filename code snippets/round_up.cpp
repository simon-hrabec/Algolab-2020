template <typename T>
int64_t round_up(const T &input_val)
{
  double num = std::ceil(CGAL::to_double(input_val));
  while (num < input_val) num += 1;
  while (num-1 >= input_val) num -= 1;
  return static_cast<int64_t>(num);
}
