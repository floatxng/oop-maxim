#pragma once

#include <type_traits>
#include <memory>
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    T x;
    T y;

    Point() : x(0), y(0) {}
    Point(T x_val, T y_val) : x(x_val), y(y_val) {}

    Point(const Point& other) = default;

    Point(Point&& other) noexcept = default;

    Point& operator=(const Point& other) = default;

    Point& operator=(Point&& other) noexcept = default;

    ~Point() = default;
};
