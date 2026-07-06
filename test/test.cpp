#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "export_data.h"
#include "point.h"
#include "rectangle.h"
#include "vec1D.h"

TEST(PointTest, CalculatesLengthAndSupportsArithmetic) {
    const Point point{3.0f, 4.0f};

    EXPECT_FLOAT_EQ(static_cast<float>(point.length()), 5.0f);
    EXPECT_FLOAT_EQ(point.lengthSlow(), 5.0f);

    const Point sum = point + Point{1.0f, -2.0f};
    EXPECT_FLOAT_EQ(sum._x, 4.0f);
    EXPECT_FLOAT_EQ(sum._y, 2.0f);

    const Point difference = point - Point{1.0f, -2.0f};
    EXPECT_FLOAT_EQ(difference._x, 2.0f);
    EXPECT_FLOAT_EQ(difference._y, 6.0f);
}

TEST(PointTest, FindsMinimumLength) {
    const std::vector<Point> points{
        Point{8.0f, 15.0f},
        Point{3.0f, 4.0f},
        Point{5.0f, 12.0f},
    };

    EXPECT_FLOAT_EQ(min_length(points), 5.0f);
    EXPECT_FLOAT_EQ(min_length_slow(points), 5.0f);
}

TEST(RectangleTest, ChecksStrictInteriorBounds) {
    Rectangle rectangle{0.0f, 0.0f, 10.0f, 10.0f};

    EXPECT_TRUE(rectangle.withinRectangle(Point{5.0f, 5.0f}));
    EXPECT_FALSE(rectangle.withinRectangle(Point{0.0f, 5.0f}));
    EXPECT_FALSE(rectangle.withinRectangle(Point{10.0f, 5.0f}));
    EXPECT_FALSE(rectangle.withinRectangle(Point{5.0f, 10.0f}));
    EXPECT_FALSE(rectangle.withinRectangle(Point{-1.0f, 5.0f}));
}

TEST(RectangleTest, CountsPointsInRectangle) {
    Vec1D points{5};
    auto& data = points.getData();
    data[0] = Point{1.0f, 1.0f};
    data[1] = Point{5.0f, 5.0f};
    data[2] = Point{9.0f, 9.0f};
    data[3] = Point{10.0f, 10.0f};
    data[4] = Point{-1.0f, 5.0f};

    Rectangle rectangle{0.0f, 0.0f, 10.0f, 10.0f};

    EXPECT_EQ(rectangle.countPointsInRectangle(points), 3);
}

TEST(Vec1DTest, AddsVectorsOfEqualSize) {
    Vec1D left{2};
    left.getData()[0] = Point{1.0f, 2.0f};
    left.getData()[1] = Point{3.0f, 4.0f};

    Vec1D right{2};
    right.getData()[0] = Point{10.0f, 20.0f};
    right.getData()[1] = Point{30.0f, 40.0f};

    const auto result = left + right;

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->getSize(), 2);
    EXPECT_FLOAT_EQ(result->getData()[0]._x, 11.0f);
    EXPECT_FLOAT_EQ(result->getData()[0]._y, 22.0f);
    EXPECT_FLOAT_EQ(result->getData()[1]._x, 33.0f);
    EXPECT_FLOAT_EQ(result->getData()[1]._y, 44.0f);
}

TEST(Vec1DTest, RejectsAdditionWhenSizesDiffer) {
    const Vec1D left{2};
    const Vec1D right{3};

    EXPECT_FALSE((left + right).has_value());
}

TEST(ExportDataTest, WritesVectorsToCsv) {
    Vec1D vectors{2};
    vectors.getData()[0] = Point{1.5f, 2.5f};
    vectors.getData()[1] = Point{-3.0f, 4.0f};

    const std::string filename = "test_vectors.csv";
    exportVectorsToCSV(vectors, filename, "unit");

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    ASSERT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[0], "x,y,type");
    EXPECT_EQ(lines[1], "1.5,2.5,unit");
    EXPECT_EQ(lines[2], "-3,4,unit");

    file.close();
    EXPECT_EQ(std::remove(filename.c_str()), 0);
}
