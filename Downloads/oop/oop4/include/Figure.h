#pragma once

#include <iostream>
#include <memory>
#include <cmath>
#include "Point.h"

template <Scalar T>
class Figure {

protected:
    virtual double getArea() const = 0;
    virtual void print(std::ostream& stream) const = 0;
    virtual void input(std::istream& stream) = 0;

public:
    virtual std::unique_ptr<Point<T>> getCenter() const = 0;
    virtual bool isValid() const = 0;

    virtual ~Figure() = default;

    explicit operator double() const {
        return getArea();
    }

    friend std::ostream& operator<<(std::ostream& stream, const Figure<T>& figure) {
        figure.print(stream);
        return stream;
    }

    friend std::istream& operator>>(std::istream& stream, Figure<T>& figure) {
        figure.input(stream);
        return stream;
    }
};
