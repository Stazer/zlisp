#pragma once

// template hacks

#include <type_traits>

struct nonesuch {
  ~nonesuch() = delete;
  nonesuch(nonesuch const&) = delete;
  void operator=(nonesuch const&) = delete;
};

namespace detail
{
  template <class Default, class AlwaysVoid, template<class...> class Op, class... Args>
  struct detector
  {
    using value_t = std::false_type;
    using type = Default;
  };

  template <class Default, template<class...> class Op, class... Args>
  struct detector<Default, std::void_t<Op<Args...>>, Op, Args...>
  {
    using value_t = std::true_type;
    using type = Op<Args...>;
  };

}
template <template<class...> class Op, class... Args>
using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

template<typename T>
using has_method_empty_trait = decltype(std::declval<T>().empty());

template<typename T>
constexpr bool has_method_empty()
{ return is_detected<has_method_empty_trait, T>::value; }

