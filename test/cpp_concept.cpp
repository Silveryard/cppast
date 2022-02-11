// Copyright (C) 2017-2019 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include "test_parser.hpp"

using namespace cppast;

TEST_CASE("cpp_class_template_concept")
{
    auto code = R"(
#include <concepts>

class Base {};

template <typename T>
concept BaseType = std::derived_from<T, Base>;

template <BaseType T>
class A {};
)";

    cpp_entity_index idx;
    parse(idx, "cpp_class_template_concept.cpp", code, false, cpp_standard::cpp_20);
}

TEST_CASE("cpp_class_template_templated_concept")
{
    auto code = R"(
#include <concepts>

template <typename T>
class Base {};

template <typename T, typename U>
concept BaseType = std::derived_from<T, Base<U>>;

template <typename U, BaseType<U> T>
class A {};
)";

    cpp_entity_index idx;
    parse(idx, "cpp_class_template_templated_concept.cpp", code, false, cpp_standard::cpp_20);
}

TEST_CASE("cpp_function_template_concept")
{
    auto code = R"(
#include <concepts>

class Base {};

template <typename T>
concept BaseType = std::derived_from<T, Base>;

template <BaseType T>
void a(T t);
)";

    cpp_entity_index idx;
    parse(idx, "cpp_function_template_concept.cpp", code, false, cpp_standard::cpp_20);
}

TEST_CASE("cpp_function_template_concept_abbreviated")
{
    auto code = R"(
#include <concepts>

class Base {};
class Derived : public Base {};

template <typename T>
concept BaseType = std::derived_from<T, Base>;

void a(auto t);
void b(BaseType auto t);
void c(BaseType auto... t);
void d(const BaseType auto* t);
void e(BaseType auto& t);

template <>
void d<Derived>(const Derived* t);
)";

    cpp_entity_index idx;
    parse(idx, "cpp_function_template_concept_abbreviated.cpp", code, false, cpp_standard::cpp_20);
}
