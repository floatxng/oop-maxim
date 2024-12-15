#include "gtest/gtest.h"
#include "Polygons.h"
#include "FiguresManager.h"
#include <memory>
#include <cmath>

TEST(TrapezoidTest, AreaCalculation) {
    auto v1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto v2 = std::make_unique<Point<double>>(4.0, 0.0);
    auto v3 = std::make_unique<Point<double>>(3.0, 3.0);
    auto v4 = std::make_unique<Point<double>>(1.0, 3.0);
    Trapezoid<double> trapezoid(std::move(v1), std::move(v2), std::move(v3), std::move(v4));
    EXPECT_NEAR((double)trapezoid, 9.0, 1e-6);
}

TEST(TrapezoidTest, Validity) {
    auto v1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto v2 = std::make_unique<Point<double>>(4.0, 0.0);
    auto v3 = std::make_unique<Point<double>>(3.0, 3.0);
    auto v4 = std::make_unique<Point<double>>(1.0, 3.0);
    Trapezoid<double> trapezoid(std::move(v1), std::move(v2), std::move(v3), std::move(v4));
    EXPECT_TRUE(trapezoid.isValid());

    auto u1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto u2 = std::make_unique<Point<double>>(4.0, 1.0);
    auto u3 = std::make_unique<Point<double>>(3.0, 3.0);
    auto u4 = std::make_unique<Point<double>>(1.0, 4.0);
    Trapezoid<double> invalidTrapezoid(std::move(u1), std::move(u2), std::move(u3), std::move(u4));
    EXPECT_FALSE(invalidTrapezoid.isValid());
}

TEST(RhombTest, AreaCalculation) {
    auto v1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto v2 = std::make_unique<Point<double>>(1.0, 1.0);
    auto v3 = std::make_unique<Point<double>>(2.0, 0.0);
    auto v4 = std::make_unique<Point<double>>(1.0, -1.0);
    Rhomb<double> rhomb(std::move(v1), std::move(v2), std::move(v3), std::move(v4));
    EXPECT_NEAR((double)rhomb, 2.0, 1e-6);
}

TEST(RhombTest, Validity) {
    auto v1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto v2 = std::make_unique<Point<double>>(1.0, 1.0);
    auto v3 = std::make_unique<Point<double>>(2.0, 0.0);
    auto v4 = std::make_unique<Point<double>>(1.0, -1.0);
    Rhomb<double> rhomb(std::move(v1), std::move(v2), std::move(v3), std::move(v4));
    EXPECT_TRUE(rhomb.isValid());

    auto u1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto u2 = std::make_unique<Point<double>>(2.0, 1.0);
    auto u3 = std::make_unique<Point<double>>(3.0, 0.0);
    auto u4 = std::make_unique<Point<double>>(1.0, -1.0);
    Rhomb<double> invalidRhomb(std::move(u1), std::move(u2), std::move(u3), std::move(u4));
    EXPECT_FALSE(invalidRhomb.isValid());
}

TEST(PentagonTest, AreaCalculation) {
    double angle = 72.0 * M_PI / 180.0;
    auto v1 = std::make_unique<Point<double>>(0.0, 1.0);
    auto v2 = std::make_unique<Point<double>>(std::sin(angle), std::cos(angle));
    auto v3 = std::make_unique<Point<double>>(std::sin(2 * angle), -std::cos(M_PI / 5.0));
    auto v4 = std::make_unique<Point<double>>(-std::sin(2 * angle), -std::cos(M_PI / 5.0));
    auto v5 = std::make_unique<Point<double>>(-std::sin(angle), std::cos(angle));
    Pentagon<double> pentagon(std::move(v1), std::move(v2), std::move(v3), std::move(v4), std::move(v5));

    double expectedArea = 2.377;
    EXPECT_NEAR((double)pentagon, expectedArea, 1e-3);
}

TEST(PentagonTest, Validity) {
    double angle = 72.0 * M_PI / 180.0;
    auto v1 = std::make_unique<Point<double>>(0.0, 1.0);
    auto v2 = std::make_unique<Point<double>>(std::sin(angle), std::cos(angle));
    auto v3 = std::make_unique<Point<double>>(std::sin(2 * angle), -std::cos(M_PI / 5.0));
    auto v4 = std::make_unique<Point<double>>(-std::sin(2 * angle), -std::cos(M_PI / 5.0));
    auto v5 = std::make_unique<Point<double>>(-std::sin(angle), std::cos(angle));
    Pentagon<double> pentagon(std::move(v1), std::move(v2), std::move(v3), std::move(v4), std::move(v5));
    EXPECT_TRUE(pentagon.isValid());

    auto u1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto u2 = std::make_unique<Point<double>>(1.0, 2.0);
    auto u3 = std::make_unique<Point<double>>(2.0, 0.0);
    auto u4 = std::make_unique<Point<double>>(1.0, -1.0);
    auto u5 = std::make_unique<Point<double>>(0.0, -2.0);
    Pentagon<double> invalidPentagon(std::move(u1), std::move(u2), std::move(u3), std::move(u4), std::move(u5));
    EXPECT_FALSE(invalidPentagon.isValid());
}

TEST(FiguresManagerTest, AddAndTotalArea) {
    FiguresManager<double> manager;

    auto t1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto t2 = std::make_unique<Point<double>>(4.0, 0.0);
    auto t3 = std::make_unique<Point<double>>(3.0, 3.0);
    auto t4 = std::make_unique<Point<double>>(1.0, 3.0);
    auto trapezoid = std::make_shared<Trapezoid<double>>(std::move(t1), std::move(t2), std::move(t3), std::move(t4));
    manager.addFigure(trapezoid);

    auto r1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto r2 = std::make_unique<Point<double>>(1.0, 1.0);
    auto r3 = std::make_unique<Point<double>>(2.0, 0.0);
    auto r4 = std::make_unique<Point<double>>(1.0, -1.0);
    auto rhomb = std::make_shared<Rhomb<double>>(std::move(r1), std::move(r2), std::move(r3), std::move(r4));
    manager.addFigure(rhomb);

    double angle = 72.0 * M_PI / 180.0;
    auto p1 = std::make_unique<Point<double>>(0.0, 1.0);
    auto p2 = std::make_unique<Point<double>>(std::sin(angle), std::cos(angle));
    auto p3 = std::make_unique<Point<double>>(std::sin(2 * angle), -std::cos(M_PI / 5.0));
    auto p4 = std::make_unique<Point<double>>(-std::sin(2 * angle), -std::cos(M_PI / 5.0));
    auto p5 = std::make_unique<Point<double>>(-std::sin(angle), std::cos(angle));
    auto pentagon = std::make_shared<Pentagon<double>>(std::move(p1), std::move(p2), std::move(p3), std::move(p4), std::move(p5));
    manager.addFigure(pentagon);

    double expectedTotalArea = 13.377;
    EXPECT_NEAR(manager.totalArea(), expectedTotalArea, 1e-3);
}

TEST(FiguresManagerTest, DeleteFigure) {
    FiguresManager<double> manager;

    auto t1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto t2 = std::make_unique<Point<double>>(4.0, 0.0);
    auto t3 = std::make_unique<Point<double>>(3.0, 3.0);
    auto t4 = std::make_unique<Point<double>>(1.0, 3.0);
    auto trapezoid = std::make_shared<Trapezoid<double>>(std::move(t1), std::move(t2), std::move(t3), std::move(t4));
    manager.addFigure(trapezoid);

    auto r1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto r2 = std::make_unique<Point<double>>(1.0, 1.0);
    auto r3 = std::make_unique<Point<double>>(2.0, 0.0);
    auto r4 = std::make_unique<Point<double>>(1.0, -1.0);
    auto rhomb = std::make_shared<Rhomb<double>>(std::move(r1), std::move(r2), std::move(r3), std::move(r4));
    manager.addFigure(rhomb);

    EXPECT_NEAR(manager.totalArea(), 11.0, 1e-6);

    manager.deleteFigure(0);

    EXPECT_NEAR(manager.totalArea(), 2.0, 1e-6);
}

TEST(FiguresManagerTest, DeleteInvalidFigure) {
    FiguresManager<double> manager;

    auto r1 = std::make_unique<Point<double>>(0.0, 0.0);
    auto r2 = std::make_unique<Point<double>>(1.0, 1.0);
    auto r3 = std::make_unique<Point<double>>(2.0, 0.0);
    auto r4 = std::make_unique<Point<double>>(1.0, -1.0);
    auto rhomb = std::make_shared<Rhomb<double>>(std::move(r1), std::move(r2), std::move(r3), std::move(r4));
    manager.addFigure(rhomb);

    EXPECT_THROW(manager.deleteFigure(1), std::out_of_range);
}
