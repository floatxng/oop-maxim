#include "gtest/gtest.h"
#include "Polygons.h"
#include "FiguresManager.h"
#include <cmath>

TEST(TrapezoidTest, AreaCalculation) {
    Vector2 v1 = {0, 0};
    Vector2 v2 = {4, 0};
    Vector2 v3 = {3, 3};
    Vector2 v4 = {1, 3};
    Trapezoid trapezoid(v1, v2, v3, v4);
    EXPECT_NEAR((double)trapezoid, 9.0, 1e-6);
}

TEST(TrapezoidTest, Validity) {
    Vector2 v1 = {0, 0};
    Vector2 v2 = {4, 0};
    Vector2 v3 = {3, 3};
    Vector2 v4 = {1, 3};
    Trapezoid trapezoid(v1, v2, v3, v4);
    EXPECT_TRUE(trapezoid.isValid());

    Vector2 u1 = {0, 0};
    Vector2 u2 = {4, 1};
    Vector2 u3 = {3, 3};
    Vector2 u4 = {1, 4};
    Trapezoid invalidTrapezoid(u1, u2, u3, u4);
    EXPECT_FALSE(invalidTrapezoid.isValid());
}

TEST(RhombTest, AreaCalculation) {
    Vector2 v1 = {0, 0};
    Vector2 v2 = {1, 1};
    Vector2 v3 = {2, 0};
    Vector2 v4 = {1, -1};
    Rhomb rhomb(v1, v2, v3, v4);
    EXPECT_NEAR((double)rhomb, 2.0, 1e-6);
}

TEST(RhombTest, Validity) {
    Vector2 v1 = {0, 0};
    Vector2 v2 = {1, 1};
    Vector2 v3 = {2, 0};
    Vector2 v4 = {1, -1};
    Rhomb rhomb(v1, v2, v3, v4);
    EXPECT_TRUE(rhomb.isValid());

    Vector2 u1 = {0, 0};
    Vector2 u2 = {2, 1};
    Vector2 u3 = {3, 0};
    Vector2 u4 = {1, -1};
    Rhomb invalidRhomb(u1, u2, u3, u4);
    EXPECT_FALSE(invalidRhomb.isValid());
}

TEST(PentagonTest, AreaCalculation) {
    Vector2 v1 = {0, 1};
    Vector2 v2 = {std::sin(72 * M_PI / 180), std::cos(72 * M_PI / 180)};
    Vector2 v3 = {std::sin(144 * M_PI / 180), -std::cos(36 * M_PI / 180)};
    Vector2 v4 = {-std::sin(144 * M_PI / 180), -std::cos(36 * M_PI / 180)};
    Vector2 v5 = {-std::sin(72 * M_PI / 180), std::cos(72 * M_PI / 180)};
    Pentagon pentagon(v1, v2, v3, v4, v5);
    double expectedArea = 2.377;
    EXPECT_NEAR((double)pentagon, expectedArea, 1e-3);
}

TEST(PentagonTest, Validity) {
    Vector2 v1 = {0, 1};
    Vector2 v2 = {std::sin(72 * M_PI / 180), std::cos(72 * M_PI / 180)};
    Vector2 v3 = {std::sin(144 * M_PI / 180), -std::cos(36 * M_PI / 180)};
    Vector2 v4 = {-std::sin(144 * M_PI / 180), -std::cos(36 * M_PI / 180)};
    Vector2 v5 = {-std::sin(72 * M_PI / 180), std::cos(72 * M_PI / 180)};
    Pentagon pentagon(v1, v2, v3, v4, v5);
    EXPECT_TRUE(pentagon.isValid());

    Vector2 u1 = {0, 0};
    Vector2 u2 = {1, 2};
    Vector2 u3 = {2, 0};
    Vector2 u4 = {1, -1};
    Vector2 u5 = {0, -2};
    Pentagon invalidPentagon(u1, u2, u3, u4, u5);
    EXPECT_FALSE(invalidPentagon.isValid());
}

TEST(FiguresManagerTest, AddAndTotalArea) {
    FiguresManager manager;

    auto* trapezoid = new Trapezoid(Vector2{0, 0}, Vector2{4, 0}, Vector2{3, 3}, Vector2{1, 3});
    manager.addFigure(trapezoid);

    auto* rhomb = new Rhomb(Vector2{0, 0}, Vector2{1, 1}, Vector2{2, 0}, Vector2{1, -1});
    manager.addFigure(rhomb);

    auto* pentagon = new Pentagon(Vector2{0, 1},
                                  Vector2{std::sin(72 * M_PI / 180), std::cos(72 * M_PI / 180)},
                                  Vector2{std::sin(144 * M_PI / 180), -std::cos(36 * M_PI / 180)},
                                  Vector2{-std::sin(144 * M_PI / 180), -std::cos(36 * M_PI / 180)},
                                  Vector2{-std::sin(72 * M_PI / 180), std::cos(72 * M_PI / 180)});
    manager.addFigure(pentagon);

    double expectedTotalArea = 13.3776;
    EXPECT_NEAR(manager.totalArea(), expectedTotalArea, 1e-3);
}

TEST(FiguresManagerTest, DeleteFigure) {
    FiguresManager manager;

    auto* trapezoid = new Trapezoid(Vector2{0, 0}, Vector2{4, 0}, Vector2{3, 3}, Vector2{1, 3});
    manager.addFigure(trapezoid);

    auto* rhomb = new Rhomb(Vector2{0, 0}, Vector2{1, 1}, Vector2{2, 0}, Vector2{1, -1});
    manager.addFigure(rhomb);

    EXPECT_NEAR(manager.totalArea(), 11.0, 1e-6);

    manager.deleteFigure(0);

    EXPECT_NEAR(manager.totalArea(), 2.0, 1e-6);
}

TEST(FiguresManagerTest, DeleteInvalidFigure) {
    FiguresManager manager;

    auto* rhomb = new Rhomb(Vector2{0, 0}, Vector2{1, 1}, Vector2{2, 0}, Vector2{1, -1});
    manager.addFigure(rhomb);

    EXPECT_THROW(manager.deleteFigure(1), std::out_of_range);
}
