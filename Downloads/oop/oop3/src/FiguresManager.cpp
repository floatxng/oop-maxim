#include "FiguresManager.h"
#include <stdexcept>
#include <algorithm>

FiguresManager::FiguresManager() : figures(nullptr), size(0), capacity(0) {}

FiguresManager::~FiguresManager() {
    for (int i = 0; i < size; ++i) {
        delete figures[i];
    }
    delete[] figures;
}

void FiguresManager::resize() {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Figure** newFigures = new Figure*[newCapacity];
    if (figures) {
        std::copy(figures, figures + size, newFigures);
        delete[] figures;
    }
    figures = newFigures;
    capacity = newCapacity;
}

void FiguresManager::addFigure(Figure* figure) {
    if (size == capacity) {
        resize();
    }
    figures[size++] = figure;
}

void FiguresManager::printAll(std::ostream& stream) const {
    for (int i = 0; i < size; ++i) {
        stream << "Figure #" << i + 1 << ":" << std::endl;
        stream << *figures[i] << std::endl;
        Vector2 center = figures[i]->getCenter();
        stream << "Center: (" << center.x << ", " << center.y << ")" << std::endl;
        stream << "Area: " << static_cast<double>(*figures[i]) << std::endl;
        stream << "Is Valid: " << (figures[i]->isValid() ? "Yes" : "No") << std::endl;
        stream << "-------------------------" << std::endl;
    }
}

double FiguresManager::totalArea() const {
    double total = 0.0;
    for (int i = 0; i < size; ++i) {
        total += static_cast<double>(*figures[i]);
    }
    return total;
}

void FiguresManager::deleteFigure(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    delete figures[index];
    for (int i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1];
    }
    --size;
}
