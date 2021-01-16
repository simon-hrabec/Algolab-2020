## [Linear programming](linear-programming.cpp)
The linear program interface in CGAL can be a bit confusing. This code snippet contain all the code you gonna need, just delete the unnecessary parts. Since the value setting is also a bit confusing (all the `set_a`, `set_b` and `set_c`) there is quite clear linear program specified that should make clear which parameter is which.

## [Main function - N cases](main-n-cases.cpp)
The default main/solve snippet to start coding. Use this one if the problem gives the T (number of cases) at the beginning

## [Main function - 0 terminated](main-unspecified-cases.cpp)
The default main/solve snippet to start coding. Use this one if the problem terminates by 0 for some input parameter.

## [CGAL round down](round_down.cpp)
The templetized version of the provided round down function for CGAL types (Gmpq etc.).

## [Kernel conversions](kernel_conversions.cpp)
When you have some values in one kernel it can be almost impossible to convert them to another kernel. Even if you know the value has not been calculated but it is the value you inserted. For example the `EPECK::FT` is in fact `CGAL::Lazy_exact_nt<boost::multiprecision::number<boost::multiprecision::backends::gmp_rational>>`. However, using the `CGAL::exact` function it can be converted to `const boost::multiprecision::number<boost::multiprecision::backends::gmp_rational>` which can be converted to e.g. `int64_t`.
This can be used only if you know the value is an integer and fits into 64 bits (e.g. if you created such value from the input data).