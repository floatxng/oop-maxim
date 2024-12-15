#pragma once

#include "Figure.h"
#include <cstring>

class Polygon : public Figure {
protected:
    Vector2* edges;
    int edgesCount;

    void print(std::ostream& stream) const override;
    double getArea() const override;
    virtual void input(std::istream& stream) override;

public:
    Polygon(Vector2* edges, int edgesCount);
    Polygon(const Polygon& other); // Конструктор копирования
    Polygon(Polygon&& other) noexcept; // Конструктор перемещения
    Polygon& operator=(const Polygon& other); // Оператор копирующего присваивания
    Polygon& operator=(Polygon&& other) noexcept; // Оператор перемещающего присваивания
    virtual ~Polygon(); // Деструктор

    Vector2 getCenter() override;
    bool isValid() const override = 0; // Сделать Polygon абстрактным
};

class Trapezoid : public Polygon {
public:
    Trapezoid();
    Trapezoid(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);
    void input(std::istream& stream) override;
    bool isValid() const override;
};

class Rhomb : public Polygon {
public:
    Rhomb();
    Rhomb(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);
    void input(std::istream& stream) override;
    bool isValid() const override;
};

class Pentagon : public Polygon {
public:
    Pentagon();
    Pentagon(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, Vector2 v5);
    void input(std::istream& stream) override;
    bool isValid() const override;
};
