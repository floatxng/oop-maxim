#pragma once

#include "Figure.h"
#include <memory>
#include <iostream>
#include <stdexcept>

template <Scalar T>
class FiguresManager {
private:
    std::shared_ptr<std::shared_ptr<Figure<T>>[]> figures;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity) {
        std::shared_ptr<std::shared_ptr<Figure<T>>[]> new_figures =
            std::make_shared<std::shared_ptr<Figure<T>>[]>(new_capacity);
        for (size_t i = 0; i < size; ++i) {
            new_figures[i] = figures[i];
        }
        figures = new_figures;
        capacity = new_capacity;
    }

public:
    FiguresManager();
    FiguresManager(const FiguresManager& other) = delete;
    FiguresManager& operator=(const FiguresManager& other) = delete;

    FiguresManager(FiguresManager&& other) noexcept;
    FiguresManager& operator=(FiguresManager&& other) noexcept;

    void addFigure(std::shared_ptr<Figure<T>> figure);
    void printAll(std::ostream& stream) const;
    double totalArea() const;
    void deleteFigure(int index);
    size_t getSize() const { return size; }
};

template <Scalar T>
FiguresManager<T>::FiguresManager()
    : figures(std::make_shared<std::shared_ptr<Figure<T>>[]>(10)), capacity(10), size(0) {}

template <Scalar T>
FiguresManager<T>::FiguresManager(FiguresManager<T>&& other) noexcept
    : figures(std::move(other.figures)), capacity(other.capacity), size(other.size) {
    other.capacity = 0;
    other.size = 0;
}

template <Scalar T>
FiguresManager<T>& FiguresManager<T>::operator=(FiguresManager<T>&& other) noexcept {
    if (this != &other) {
        figures = std::move(other.figures);
        capacity = other.capacity;
        size = other.size;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

template <Scalar T>
void FiguresManager<T>::addFigure(std::shared_ptr<Figure<T>> figure) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    figures[size++] = figure;
}

template <Scalar T>
void FiguresManager<T>::printAll(std::ostream& stream) const {
    for (size_t i = 0; i < size; ++i) {
        stream << "Figure #" << i + 1 << ":\n";
        stream << *figures[i] << "\n";
        std::unique_ptr<Point<T>> center = figures[i]->getCenter();
        stream << "Center: (" << center->x << ", " << center->y << ")\n";
        stream << "Area: " << static_cast<double>(*figures[i]) << "\n";
        stream << "Is Valid: " << (figures[i]->isValid() ? "Yes" : "No") << "\n";
        stream << "-------------------------\n";
    }
}

template <Scalar T>
double FiguresManager<T>::totalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < size; ++i) {
        total += static_cast<double>(*figures[i]);
    }
    return total;
}

template <Scalar T>
void FiguresManager<T>::deleteFigure(int index) {
    if (index < 0 || static_cast<size_t>(index) >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1];
    }
    figures[size - 1].reset();
    --size;
}
