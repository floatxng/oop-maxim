#pragma once

#include "Figure.h"
#include <iostream>

class FiguresManager {
private:
    Figure** figures;
    int size;
    int capacity;

    void resize();

public:
    FiguresManager();
    ~FiguresManager();

    void addFigure(Figure* figure);
    void printAll(std::ostream& stream) const;
    double totalArea() const;
    void deleteFigure(int index);
};
