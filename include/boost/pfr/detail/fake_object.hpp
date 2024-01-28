// Copyright (c) 2023 Bela Schaum, X-Ryl669, Denis Mikhailov.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// Initial implementation by Bela Schaum, https://github.com/schaumb
// The way to make it union and UB free by X-Ryl669, https://github.com/X-Ryl669
//

#ifndef BOOST_PFR_DETAIL_FAKE_OBJECT_HPP
#define BOOST_PFR_DETAIL_FAKE_OBJECT_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

namespace boost { namespace pfr { namespace detail {

// This class has external linkage while T has not sure.
template <class T>
struct wrapper {
    const T value;
};

// This variable servers as a link-time assert.
// If linker requires it, then `fake_object()` is used at runtime.
template <class T>
extern const wrapper<T> report_if_you_see_link_error_with_this_object;

// For returning non default constructible types, it's exclusively used in member name retrieval.
//
// Neither std::declval nor boost::pfr::detail::unsafe_declval are usable there.
// This takes advantage of C++20 features, while boost::pfr::detail::unsafe_declval works
// with the former standards.
template <class T>
constexpr const T& fake_object() noexcept {
    return report_if_you_see_link_error_with_this_object<T>.value;
}

}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_FAKE_OBJECT_HPP

