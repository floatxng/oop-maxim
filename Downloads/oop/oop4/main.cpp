#include "FiguresManager.h"
#include "Polygons.h"
#include <iostream>

int main() {
    FiguresManager<double> manager;
    int choice;

    while (true) {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить трапецию" << std::endl;
        std::cout << "2. Добавить ромб" << std::endl;
        std::cout << "3. Добавить правильный пятиугольник" << std::endl;
        std::cout << "4. Показать все фигуры" << std::endl;
        std::cout << "5. Показать общую площадь" << std::endl;
        std::cout << "6. Удалить фигуру по индексу" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                auto trapezoid = std::make_shared<Trapezoid<double>>();
                std::cin >> *trapezoid;
                manager.addFigure(trapezoid);
                break;
            }
            case 2: {
                auto rhomb = std::make_shared<Rhomb<double>>();
                std::cin >> *rhomb;
                manager.addFigure(rhomb);
                break;
            }
            case 3: {
                auto pentagon = std::make_shared<Pentagon<double>>();
                std::cin >> *pentagon;
                manager.addFigure(pentagon);
                break;
            }
            case 4: {
                manager.printAll(std::cout);
                break;
            }
            case 5: {
                std::cout << "Общая площадь фигур: " << manager.totalArea() << std::endl;
                break;
            }
            case 6: {
                int index;
                std::cout << "Введите индекс фигуры для удаления: ";
                std::cin >> index;
                try {
                    manager.deleteFigure(index);
                    std::cout << "Фигура удалена." << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }

    }

    return 0;
}
