#include <iostream>
#include <boost/numeric/conversion/cast.hpp>

template <class SourceT, class TargetT>
struct mythrow_overflow_handler
{
     void operator()(boost::numeric::range_check_result r)
     {
          if (r != boost::numeric::cInRange)
          {
               throw std::logic_error("Not in range!");
          }
     }
};

template <class TargetT, class SourceT>
TargetT my_numeric_cast(const SourceT &in)
{
     typedef boost::numeric::conversion_traits<
         TargetT, SourceT>
         conv_traits;

     typedef boost::numeric::converter<
         TargetT,
         SourceT,
         conv_traits,                               // default conversion traits
         mythrow_overflow_handler<SourceT, TargetT> // !!!
         >
         converter;

     return converter::convert(in);
}

int
main()
try
{
     auto v = my_numeric_cast<u_int16_t>(100000);
     (void) v;
     return 0;
}
catch (const std::logic_error &e)
{
     std::cout << "It works! " << e.what() << std::endl;
     return 1;
}

