#pragma once

#include <iostream>
#include <cmath>

struct Vector2 {
    double x; 
    double y;
};

class Figure {
protected:
    virtual double getArea() const = 0;
    virtual void print(std::ostream& stream) const = 0;
    virtual void input(std::istream& stream) = 0; 

public:
    virtual Vector2 getCenter() = 0;
    virtual bool isValid() const = 0;

    virtual ~Figure() = default; // Виртуальный деструктор

    explicit operator double() const {
        return getArea();
    }

    friend std::ostream& operator<< (std::ostream& stream, const Figure& figure);
    friend std::istream& operator>> (std::istream& stream, Figure& figure);
};
