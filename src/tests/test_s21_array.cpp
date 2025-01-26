#include <gtest/gtest.h>

#include "../containersplus/s21_array.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(5, arr.size());
  for (auto i = arr.begin(); i != arr.end(); ++i) {
    EXPECT_EQ(0, *i);
  }
}

TEST(ArrayTest, ParameterizedConstructor) {
  std::initializer_list<int> items = {15, 25, 35, 45, 55};
  s21::array<int, 10> arr(items);
  EXPECT_EQ(10, arr.max_size());
  EXPECT_EQ(15, arr[0]);
  EXPECT_EQ(25, arr[1]);
  EXPECT_EQ(35, arr[2]);
  EXPECT_EQ(45, arr[3]);
  EXPECT_EQ(55, arr[4]);
  for (int i = 5; i < (int)arr.size(); i++) {
    EXPECT_EQ(0, arr[i]);
  }
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<std::string, 3> original = {"Hello", "C++", "World"};
  s21::array<std::string, 3> arr(original);
  EXPECT_EQ(3, arr.size());
  EXPECT_EQ("Hello", arr[0]);
  EXPECT_EQ("C++", arr[1]);
  EXPECT_EQ("World", arr[2]);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<double, 5> original = {1.23, 4.56, 7.89, 0.12, 3.45};
  s21::array<double, 5> arr(std::move(original));
  EXPECT_EQ(5, arr.size());
  EXPECT_EQ(1.23, arr[0]);
  EXPECT_EQ(4.56, arr[1]);
  EXPECT_EQ(7.89, arr[2]);
  EXPECT_EQ(0.12, arr[3]);
  EXPECT_EQ(3.45, arr[4]);
}

TEST(ArrayTest, CopyAssignmentOperator) {
  s21::array<int, 5> arr1 = {105, 205, 305, 405, 505};
  s21::array<int, 5> arr2 = {605, 705, 805, 905, 1005};
  arr2 = arr1;
  EXPECT_EQ(arr1.size(), arr2.size());
  for (std::size_t i = 0; i < arr1.size(); ++i) EXPECT_EQ(arr1[i], arr2[i]);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {105, 205, 305, 405, 505};
  s21::array<int, 5> arr2 = {605, 705, 805, 905, 1005};
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 5);
  for (std::size_t i = 0; i < arr2.size(); ++i)
    EXPECT_EQ(arr2[i], (i + 1) * 100 + 5);
}

TEST(ArrayTest, At) {
  s21::array<char, 3> arr1 = {'x', 'y', 'z'};
  std::array<char, 3> arr2 = {'x', 'y', 'z'};
  EXPECT_EQ(arr1.at(0), arr2.at(0));
  EXPECT_EQ(arr1.at(1), arr2.at(1));
  EXPECT_EQ(arr1.at(2), arr2.at(2));
  EXPECT_THROW(arr1.at(5), std::out_of_range);
}

TEST(ArrayTest, OperatorSubscript) {
  s21::array<long double, 5> arr = {1.234, 2.345, 3.456, 4.567, 5.678};
  EXPECT_EQ(2.345, arr[1]);
  EXPECT_EQ(3.456, arr[2]);
  EXPECT_EQ(5.678, arr[4]);
}

TEST(ArrayTest, Front_Back) {
  s21::array<int, 5> arr = {15, 25, 35, 45, 55};
  EXPECT_EQ(15, arr.front());
  EXPECT_EQ(55, arr.back());
}

TEST(ArrayTest, Data) {
  s21::array<char, 2> arr = {'a', 'b'};
  EXPECT_EQ(&arr[0], arr.data());
}

TEST(ArrayTest, BeginEndTest) {
  s21::array<int, 5> arr{5, 10, 15, 20, 25};
  EXPECT_EQ(arr.begin(), &arr[0]);
  EXPECT_EQ(arr.end(), &arr[5]);
}

TEST(ArrayTest, EmptyTest) {
  s21::array<int, 0> arr1;
  EXPECT_TRUE(arr1.empty());
  s21::array<int, 5> arr2;
  EXPECT_FALSE(arr2.empty());
}

TEST(ArrayTest, SizeTest) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, SwapTest) {
  s21::array<int, 5> arr1{105, 205, 305, 405, 505};
  s21::array<int, 5> arr2{605, 705, 805, 905, 1005};
  arr1.swap(arr2);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], (i + 6) * 100 + 5);
    EXPECT_EQ(arr2[i], (i + 1) * 100 + 5);
  }
}

TEST(ArrayTest, FloatType) {
  s21::array<float, 3> arr = {1.1f, 2.2f, 3.3f};
  EXPECT_FLOAT_EQ(1.1f, arr[0]);
  EXPECT_FLOAT_EQ(2.2f, arr[1]);
  EXPECT_FLOAT_EQ(3.3f, arr[2]);
}

TEST(ArrayTest, StringType) {
  s21::array<std::string, 2> arr = {"Hello", "World"};
  EXPECT_EQ("Hello", arr[0]);
  EXPECT_EQ("World", arr[1]);
}

struct CustomType {
  int a;
  double b;
  bool operator==(const CustomType& other) const {
    return a == other.a && b == other.b;
  }
};

TEST(ArrayTest, CustomType) {
  s21::array<CustomType, 2> arr = {{1, 2.2}, {3, 4.4}};
  EXPECT_EQ(1, arr[0].a);
  EXPECT_DOUBLE_EQ(2.2, arr[0].b);
  EXPECT_EQ(3, arr[1].a);
  EXPECT_DOUBLE_EQ(4.4, arr[1].b);
}

TEST(ArrayTest, EmptyTestZeroSize) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, OperatorSubscriptCustomType) {
  s21::array<CustomType, 2> arr = {{1, 2.2}, {3, 4.4}};
  EXPECT_EQ(1, arr[0].a);
  EXPECT_DOUBLE_EQ(2.2, arr[0].b);
  EXPECT_EQ(3, arr[1].a);
  EXPECT_DOUBLE_EQ(4.4, arr[1].b);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}