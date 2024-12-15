#pragma once
#include "Figure.h"
#include "Point.h"
#include <memory>
#include <cmath>
#include <iostream>

template <Scalar T>
class Polygon : public Figure<T> {
protected:
    std::unique_ptr<std::unique_ptr<Point<T>>[]> edges;
    int edgesCount;


    void print(std::ostream& stream) const override;
    double getArea() const override;
    void input(std::istream& stream) override;

public:
    Polygon(std::unique_ptr<std::unique_ptr<Point<T>>[]> edges_ptr, int count);
    Polygon(const Polygon& other);
    Polygon(Polygon&& other) noexcept;

    Polygon& operator=(const Polygon& other);
    Polygon& operator=(Polygon&& other) noexcept;

    virtual ~Polygon() = default;

    std::unique_ptr<Point<T>> getCenter() const override;

    bool isValid() const override = 0;
};


template <Scalar T>
Polygon<T>::Polygon(std::unique_ptr<std::unique_ptr<Point<T>>[]> edges_ptr, int count)
    : edgesCount(count), edges(std::move(edges_ptr)) {}

template <Scalar T>
Polygon<T>::Polygon(const Polygon<T>& other) : edgesCount(other.edgesCount) {
    edges = std::make_unique<std::unique_ptr<Point<T>>[]>(edgesCount);
    for (int i = 0; i < edgesCount; ++i) {
        edges[i] = std::make_unique<Point<T>>(*other.edges[i]);
    }
}

template <Scalar T>
Polygon<T>::Polygon(Polygon<T>&& other) noexcept
    : edges(std::move(other.edges)), edgesCount(other.edgesCount) {
    other.edgesCount = 0;
}

template <Scalar T>
Polygon<T>& Polygon<T>::operator=(const Polygon<T>& other) {
    if (this == &other)
        return *this;

    edgesCount = other.edgesCount;
    edges = std::make_unique<std::unique_ptr<Point<T>>[]>(edgesCount);
    for (int i = 0; i < edgesCount; ++i) {
        edges[i] = std::make_unique<Point<T>>(*other.edges[i]);
    }
    return *this;
}

template <Scalar T>
Polygon<T>& Polygon<T>::operator=(Polygon<T>&& other) noexcept {
    if (this == &other)
        return *this;

    edges = std::move(other.edges);
    edgesCount = other.edgesCount;
    other.edgesCount = 0;
    return *this;
}

template <Scalar T>
void Polygon<T>::print(std::ostream& stream) const {
    stream << "Polygon with " << edgesCount << " edges:" << std::endl;
    for (int i = 0; i < edgesCount; i++) {
        stream << "Edge #" << i + 1 << ": (" << edges[i]->x << ", " << edges[i]->y << ")" << std::endl;
    }
}

template <Scalar T>
double Polygon<T>::getArea() const {
    double area = 0.;
    for (int i = 0; i < edgesCount; ++i) {
        int next = (i + 1) % edgesCount;
        area += static_cast<double>(edges[i]->x) * static_cast<double>(edges[next]->y);
        area -= static_cast<double>(edges[next]->x) * static_cast<double>(edges[i]->y);
    }
    return std::abs(area) / 2.;
}

template <Scalar T>
std::unique_ptr<Point<T>> Polygon<T>::getCenter() const {
    double eXSum = 0, eYSum = 0;
    for (int i = 0; i < edgesCount; i++) {
        eXSum += static_cast<double>(edges[i]->x);
        eYSum += static_cast<double>(edges[i]->y);
    }
    return std::make_unique<Point<T>>(static_cast<T>(eXSum / edgesCount),
                                      static_cast<T>(eYSum / edgesCount));
}

template <Scalar T>
void Polygon<T>::input(std::istream& stream) {
    std::cout << "Enter " << edgesCount << " vertices (x y):\n";
    for (int i = 0; i < edgesCount; ++i) {
        T x, y;
        stream >> x >> y;
        this->edges[i] = std::make_unique<Point<T>>(x, y);
    }
}

template <Scalar T>
class Trapezoid : public Polygon<T> {
public:
    Trapezoid();
    Trapezoid(std::unique_ptr<Point<T>> v1, std::unique_ptr<Point<T>> v2,
             std::unique_ptr<Point<T>> v3, std::unique_ptr<Point<T>> v4);

    void input(std::istream& stream) override;
    bool isValid() const override;
};

template <Scalar T>
Trapezoid<T>::Trapezoid()
    : Polygon<T>(std::make_unique<std::unique_ptr<Point<T>>[]>(4), 4) {
    for (int i = 0; i < 4; ++i) {
        this->edges[i] = std::make_unique<Point<T>>(0, 0);
    }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(std::unique_ptr<Point<T>> v1,
                        std::unique_ptr<Point<T>> v2,
                        std::unique_ptr<Point<T>> v3,
                        std::unique_ptr<Point<T>> v4)
    : Polygon<T>(std::make_unique<std::unique_ptr<Point<T>>[]>(4), 4) {
    this->edges[0] = std::move(v1);
    this->edges[1] = std::move(v2);
    this->edges[2] = std::move(v3);
    this->edges[3] = std::move(v4);
}

template <Scalar T>
void Trapezoid<T>::input(std::istream& stream) {
    std::cout << "Enter 4 vertices for trapezoid (x y):\n";
    for (int i = 0; i < 4; ++i) {
        T x, y;
        stream >> x >> y;
        this->edges[i] = std::make_unique<Point<T>>(x, y);
    }
}

template <Scalar T>
bool Trapezoid<T>::isValid() const {
    auto slope = [&](int i) -> double {
        int next = (i + 1) % 4;
        double dx = static_cast<double>(this->edges[next]->x) - static_cast<double>(this->edges[i]->x);
        double dy = static_cast<double>(this->edges[next]->y) - static_cast<double>(this->edges[i]->y);
        if (std::abs(dx) < 1e-9) return INFINITY;
        return dy / dx;
    };

    double slope1 = slope(0);
    double slope2 = slope(1);
    double slope3 = slope(2);
    double slope4 = slope(3);

    return (std::abs(slope1 - slope3) < 1e-6) || (std::abs(slope2 - slope4) < 1e-6);
}


template <Scalar T>
class Rhomb : public Polygon<T> {
public:
    Rhomb();
    Rhomb(std::unique_ptr<Point<T>> v1, std::unique_ptr<Point<T>> v2,
          std::unique_ptr<Point<T>> v3, std::unique_ptr<Point<T>> v4);

    void input(std::istream& stream) override;
    bool isValid() const override;
};

template <Scalar T>
Rhomb<T>::Rhomb()
    : Polygon<T>(std::make_unique<std::unique_ptr<Point<T>>[]>(4), 4) {
    for (int i = 0; i < 4; ++i) {
        this->edges[i] = std::make_unique<Point<T>>(0, 0);
    }
}

template <Scalar T>
Rhomb<T>::Rhomb(std::unique_ptr<Point<T>> v1,
               std::unique_ptr<Point<T>> v2,
               std::unique_ptr<Point<T>> v3,
               std::unique_ptr<Point<T>> v4)
    : Polygon<T>(std::make_unique<std::unique_ptr<Point<T>>[]>(4), 4) {
    this->edges[0] = std::move(v1);
    this->edges[1] = std::move(v2);
    this->edges[2] = std::move(v3);
    this->edges[3] = std::move(v4);
}

template <Scalar T>
void Rhomb<T>::input(std::istream& stream) {
    std::cout << "Enter 4 vertices for rhomb (x y):\n";
    for (int i = 0; i < 4; ++i) {
        T x, y;
        stream >> x >> y;
        this->edges[i] = std::make_unique<Point<T>>(x, y);
    }
}

template <Scalar T>
bool Rhomb<T>::isValid() const {
    auto distance = [&](int i) -> double {
        int next = (i + 1) % 4;
        double dx = static_cast<double>(this->edges[next]->x) - static_cast<double>(this->edges[i]->x);
        double dy = static_cast<double>(this->edges[next]->y) - static_cast<double>(this->edges[i]->y);
        return std::sqrt(dx * dx + dy * dy);
    };

    double d0 = distance(0);
    for (int i = 1; i < 4; ++i) {
        if (std::abs(distance(i) - d0) > 1e-6)
            return false;
    }

    return true;
}


template <Scalar T>
class Pentagon : public Polygon<T> {
public:
    Pentagon();
    Pentagon(std::unique_ptr<Point<T>> v1, std::unique_ptr<Point<T>> v2,
             std::unique_ptr<Point<T>> v3, std::unique_ptr<Point<T>> v4,
             std::unique_ptr<Point<T>> v5);

    void input(std::istream& stream) override;
    bool isValid() const override;
};

template <Scalar T>
Pentagon<T>::Pentagon()
    : Polygon<T>(std::make_unique<std::unique_ptr<Point<T>>[]>(5), 5) {
    for (int i = 0; i < 5; ++i) {
        this->edges[i] = std::make_unique<Point<T>>(0, 0);
    }
}

template <Scalar T>
Pentagon<T>::Pentagon(std::unique_ptr<Point<T>> v1,
                      std::unique_ptr<Point<T>> v2,
                      std::unique_ptr<Point<T>> v3,
                      std::unique_ptr<Point<T>> v4,
                      std::unique_ptr<Point<T>> v5)
    : Polygon<T>(std::make_unique<std::unique_ptr<Point<T>>[]>(5), 5) {
    this->edges[0] = std::move(v1);
    this->edges[1] = std::move(v2);
    this->edges[2] = std::move(v3);
    this->edges[3] = std::move(v4);
    this->edges[4] = std::move(v5);
}

template <Scalar T>
void Pentagon<T>::input(std::istream& stream) {
    std::cout << "Enter 5 vertices for pentagon (x y):\n";
    for (int i = 0; i < 5; ++i) {
        T x, y;
        stream >> x >> y;
        this->edges[i] = std::make_unique<Point<T>>(x, y);
    }
}

template <Scalar T>
bool Pentagon<T>::isValid() const {
    auto distance = [&](int i) -> double {
        int next = (i + 1) % 5;
        double dx = static_cast<double>(this->edges[next]->x) - static_cast<double>(this->edges[i]->x);
        double dy = static_cast<double>(this->edges[next]->y) - static_cast<double>(this->edges[i]->y);
        return std::sqrt(dx * dx + dy * dy);
    };

    double d0 = distance(0);
    for (int i = 1; i < 5; ++i) {
        if (std::abs(distance(i) - d0) > 1e-6)
            return false;
    }

    return true;
}
