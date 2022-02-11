// Copyright (C) 2017-2019 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include "test_parser.hpp"

using namespace cppast;

TEST_CASE("cpp_class_template_constraint")
{
    auto code = R"(
#include <concepts>

class Base {};

template <typename T>
concept BaseType = std::derived_from<T, Base>;

template <typename T> requires BaseType<T>
class A {};
)";

    cpp_entity_index idx;
    parse(idx, "cpp_class_template_constraint.cpp", code, false, cpp_standard::cpp_20);
}

TEST_CASE("cpp_class_template_templated_constraint")
{
    auto code = R"(
#include <concepts>

template <typename T>
class Base {};

template <typename T, typename U>
concept BaseType = std::derived_from<T, Base<U>>;

template <typename T> requires BaseType<T, int>
class A {};
)";

    cpp_entity_index idx;
    parse(idx, "cpp_class_template_templated_constraint.cpp", code, false, cpp_standard::cpp_20);
}

TEST_CASE("cpp_function_template_constraint")
{
    auto code = R"(
#include <concepts>

class Base {};

template <typename T>
concept BaseType = std::derived_from<T, Base>;

template <typename T> requires BaseType<T>
void a(T t);
)";

    cpp_entity_index idx;
    parse(idx, "cpp_function_template_constraint.cpp", code, false, cpp_standard::cpp_20);
}

TEST_CASE("cpp_function_template_constraint_trailing")
{
    auto code = R"(
#include <concepts>

class Base {};

template <typename T>
concept BaseType = std::derived_from<T, Base>;

template <typename T>
void a(T t) requires BaseType<T>;

template <typename T>
void b(T t) requires BaseType<T> {}
)";

    cpp_entity_index idx;
    parse(idx, "cpp_function_template_constraint_trailing.cpp", code, false, cpp_standard::cpp_20);
}
