## [Main function - N cases](main_n_cases.cpp)
The default main/solve snippet to start coding. Use this one if the problem gives the T (number of cases) at the beginning

## [Main function - 0 terminated](main_unspecified_cases.cpp)
The default main/solve snippet to start coding. Use this one if the problem terminates by 0 for some input parameter.

## [Kernel conversions](kernel_conversions.cpp)
When you have some values in one kernel it can be almost impossible to convert them to another kernel. Even if you know the value has not been calculated but it is the value you inserted. For example the `EPECK::FT` is in fact `CGAL::Lazy_exact_nt<boost::multiprecision::number<boost::multiprecision::backends::gmp_rational>>`. However, using the `CGAL::exact` function it can be converted to `const boost::multiprecision::number<boost::multiprecision::backends::gmp_rational>` which can be converted to e.g. `int64_t`.
This can be used only if you know the value is an integer and fits into 64 bits (e.g. if you created such value from the input data).

## [CGAL round down](round_down.cpp)
The templetized version of the provided round down function for CGAL types (Gmpq etc.).

Attibution: Rewritten code from the lecture

## [CGAL round uo](round_up.cpp)
The same as round down but instead rounding up.

Attibution: Modified code from the lecture

## [CGAL intersections](cgal_intersections.cpp)
When two object intersects the result can be of several types. It requires the usage of `boost::get`. This code can be used for intersections of segment/ray. For different objects it needs to be extended accordingly but the structure can remain the same.

Attibution: Rewritten code from the lecture

## [Min Circle](min_circle.cpp)
CGAL has speciall class to find out the minimum enclosing circle. This code shows how to construct it and few properties it offers (supporting points, resulting circle center/squared radius).

Attibution: Rewritten/augmented code from the lecture

## [Linear programming](linear_programming.cpp)
The linear program interface in CGAL can be a bit confusing. This code snippet contain all the code you gonna need, just delete the unnecessary parts. Since the value setting is also a bit confusing (all the `set_a`, `set_b` and `set_c`) there is quite clear linear program specified that should make clear which parameter is which.

## [Range loop - iterator wrapper](range_loop_iterator_wrapper.cpp)
When working with BGL or CGAL sometimes we are provided with function that return a pair of iterators for things like vertices, edges etc. It requires usage of not so elegant constructs such as structural binding in a for loop init-statement

    for(auto [edge_it, edge_it_end] = boost::edges(G); edge_it != edge_it_end; ++edge_it) {
    ...
    }

or declaring the iterators (which means writing explicitly their type or using some kind of decltype)

    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    ...
    }

or accessing the first/second of the iterator pair.

    for (auto edge_it = boost::edges(G).first; edge_it != boost::edges(G).second; ++edge_it) {
    ...
    }

and there is the subsequent need to dereference the iterator. But with the use of the wrapper it is easy to resort to the standard range for loop:

    for(const auto &edge : range_loop_wrapper(boost::edges(G))) {
    ...
    }
