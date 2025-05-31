#pragma once

#include <concepts>
#include <functional>

namespace rb_tree
{

template<typename T>
concept EQable = requires(T a, T b) {
  { a == b } -> std::convertible_to<bool>;
};

template<typename T>
concept LTable = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
};

template <typename T>
concept Treeable = EQable<T> && LTable<T>;

} // namespace rb_tree