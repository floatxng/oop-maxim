#include "Polygons.h"

Polygon::Polygon(Vector2* edges, int edgesCount) : edgesCount(edgesCount) {
    this->edges = new Vector2[edgesCount];
    std::memcpy(this->edges, edges, edgesCount * sizeof(Vector2));
}

Polygon::~Polygon() {
    delete[] edges;
}

Polygon::Polygon(const Polygon& other) : edgesCount(other.edgesCount) {
    edges = new Vector2[edgesCount];
    std::memcpy(edges, other.edges, edgesCount * sizeof(Vector2));
}

Polygon::Polygon(Polygon&& other) noexcept : edges(other.edges), edgesCount(other.edgesCount) {
    other.edges = nullptr;
    other.edgesCount = 0;
}

Polygon& Polygon::operator=(const Polygon& other) {
    if (this == &other)
        return *this;
    delete[] edges;
    edgesCount = other.edgesCount;
    edges = new Vector2[edgesCount];
    std::memcpy(edges, other.edges, edgesCount * sizeof(Vector2));
    return *this;
}

Polygon& Polygon::operator=(Polygon&& other) noexcept {
    if (this == &other)
        return *this;
    delete[] edges;
    edges = other.edges;
    edgesCount = other.edgesCount;
    other.edges = nullptr;
    other.edgesCount = 0;
    return *this;
}

void Polygon::print(std::ostream& stream) const {
    stream << "Polygon with " << edgesCount << " edges:" << std::endl;
    for (int i = 0; i < edgesCount; i++) {
        stream << "Edge #" << i + 1 << ": (" << edges[i].x << ", " << edges[i].y << ")" << std::endl;
    }
}

double Polygon::getArea() const {
    double area = 0.;
    for (int i = 0; i < edgesCount; ++i) {
        int next = (i + 1) % edgesCount;
        area += edges[i].x * edges[next].y;
        area -= edges[next].x * edges[i].y;
    }
    return std::abs(area) / 2.;
}

Vector2 Polygon::getCenter() {
    double eXSum = 0, eYSum = 0;
    for (int i = 0; i < edgesCount; i++) {
        eXSum += edges[i].x;
        eYSum += edges[i].y;
    }
    return Vector2{eXSum / edgesCount, eYSum / edgesCount};
}

void Polygon::input(std::istream& stream) {
    std::cout << "Enter " << edgesCount << " vertices (x y):\n";
    for (int i = 0; i < edgesCount; i++) {
        stream >> edges[i].x >> edges[i].y;
    }
}


Trapezoid::Trapezoid() : Polygon(new Vector2[4]{ {0, 0}, {0, 0}, {0, 0}, {0, 0} }, 4) {}

Trapezoid::Trapezoid(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4) 
    : Polygon(new Vector2[4]{ v1, v2, v3, v4 }, 4) {}

void Trapezoid::input(std::istream& stream) {
    std::cout << "Enter 4 vertices for trapezoid (x y):\n";
    for (int i = 0; i < edgesCount; ++i) {
        stream >> edges[i].x >> edges[i].y;
    }
}

bool Trapezoid::isValid() const {
    auto slope = [&](int i) -> double {
        int next = (i + 1) % edgesCount;
        if (std::abs(edges[next].x - edges[i].x) < 1e-9) return INFINITY;
        return (edges[next].y - edges[i].y) / (edges[next].x - edges[i].x);
    };
    double slope1 = slope(0);
    double slope2 = slope(1);
    double slope3 = slope(2);
    double slope4 = slope(3);
    return (std::abs(slope1 - slope3) < 1e-6) || (std::abs(slope2 - slope4) < 1e-6);
}


Rhomb::Rhomb() : Polygon(new Vector2[4]{ {0, 0}, {0, 0}, {0, 0}, {0, 0} }, 4) {}

Rhomb::Rhomb(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4) 
    : Polygon(new Vector2[4]{ v1, v2, v3, v4 }, 4) {}

void Rhomb::input(std::istream& stream) {
    std::cout << "Enter 4 vertices for rhomb (x y):\n";
    for (int i = 0; i < edgesCount; ++i) {
        stream >> edges[i].x >> edges[i].y;
    }
}

bool Rhomb::isValid() const {
    auto distance = [&](int i) -> double {
        int next = (i + 1) % edgesCount;
        return std::sqrt(std::pow(edges[next].x - edges[i].x, 2) + std::pow(edges[next].y - edges[i].y, 2));
    };
    double d0 = distance(0);
    for (int i = 1; i < edgesCount; ++i) {
        if (std::abs(distance(i) - d0) > 1e-6)
            return false;
    }
    return true;
}


Pentagon::Pentagon() : Polygon(new Vector2[5]{ {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} }, 5) {}

Pentagon::Pentagon(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, Vector2 v5) 
    : Polygon(new Vector2[5]{ v1, v2, v3, v4, v5 }, 5) {}

void Pentagon::input(std::istream& stream) {
    std::cout << "Enter 5 vertices for pentagon (x y):\n";
    for (int i = 0; i < edgesCount; ++i) {
        stream >> edges[i].x >> edges[i].y;
    }
}

bool Pentagon::isValid() const {
    if (edgesCount != 5) return false;
    auto distance = [&](int i) -> double {
        int next = (i + 1) % edgesCount;
        return std::sqrt(std::pow(edges[next].x - edges[i].x, 2) + std::pow(edges[next].y - edges[i].y, 2));
    };
    double d0 = distance(0);
    for (int i = 1; i < edgesCount; ++i) {
        if (std::abs(distance(i) - d0) > 1e-6)
            return false;
    }
    return true;
}
