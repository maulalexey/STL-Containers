#include <gtest/gtest.h>

#include "../containers/s21_vector.h"

using namespace s21;

TEST(VectorTest, DefaultConstructor) {
  vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, SizeConstructor) {
  vector<int> v(5);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, InitializerListConstructor) {
  vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], i + 1);
  }
}

TEST(VectorTest, CopyConstructor) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2(v1);
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }
}

TEST(VectorTest, MoveConstructor) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);
  EXPECT_TRUE(v1.empty());
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }
}

TEST(VectorTest, CopyAssignmentOperator) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2;
  v2 = v1;
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }
}

TEST(VectorTest, MoveAssignmentOperator) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);
  EXPECT_TRUE(v1.empty());
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }
}

TEST(VectorTest, ElementAccess) {
  vector<int> v{10, 20, 30, 40, 50};
  EXPECT_EQ(v.at(0), 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v.front(), 10);
  EXPECT_EQ(v.back(), 50);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(VectorTest, PushBack) {
  vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
}

TEST(VectorTest, PopBack) {
  vector<int> v{10, 20, 30};
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 20);
}

TEST(VectorTest, Insert) {
  vector<int> v{10, 20, 30};
  auto it = v.insert(v.begin() + 1, 15);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(*it, 15);
  EXPECT_EQ(v[1], 15);
}

TEST(VectorTest, Erase) {
  vector<int> v{10, 20, 30};
  auto it = v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(*it, 30);
  EXPECT_EQ(v[1], 30);
}

TEST(VectorTest, Swap) {
  vector<int> v1{10, 20, 30};
  vector<int> v2{40, 50};
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v1[0], 40);
  EXPECT_EQ(v2[0], 10);
}

TEST(VectorTest, Clear) {
  vector<int> v{10, 20, 30};
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, Reserve) {
  vector<int> v;
  v.reserve(100);
  EXPECT_EQ(v.capacity(), 100);
  v.push_back(10);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.capacity(), 100);
}

TEST(VectorTest, ShrinkToFit) {
  vector<int> v{10, 20, 30};
  v.reserve(100);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), v.size());
}

TEST(VectorTest, MaxSize) {
  vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

TEST(VectorTest, InsertAtBegin) {
  s21::vector<int> v{2, 3, 4};
  v.insert(v.begin(), 1);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, InsertAtEnd) {
  s21::vector<int> v{1, 2, 3};
  v.insert(v.end(), 4);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, EraseAtBegin) {
  s21::vector<int> v{1, 2, 3, 4};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 2);
  EXPECT_EQ(v[1], 3);
  EXPECT_EQ(v[2], 4);
}

TEST(VectorTest, EraseAtEnd) {
  s21::vector<int> v{1, 2, 3, 4};
  auto it = v.end() - 1;
  v.erase(it);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, SwapDifferentSizes) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2{4, 5};
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v2[0], 1);
}

struct CustomType {
  int a;
  double b;
  bool operator==(const CustomType& other) const {
    return a == other.a && b == other.b;
  }
};

TEST(VectorTest, PushBackCustomType) {
  s21::vector<CustomType> v;
  v.push_back({1, 2.2});
  v.push_back({3, 4.4});
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0].a, 1);
  EXPECT_EQ(v[0].b, 2.2);
  EXPECT_EQ(v[1].a, 3);
  EXPECT_EQ(v[1].b, 4.4);
}

TEST(VectorTest, EraseCustomType) {
  s21::vector<CustomType> v{{1, 2.2}, {2, 3.3}, {3, 4.4}};
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0].a, 1);
  EXPECT_EQ(v[1].a, 3);
}

TEST(VectorTest, SwapCustomType) {
  s21::vector<CustomType> v1{{1, 2.2}, {3, 4.4}};
  s21::vector<CustomType> v2{{5, 6.6}};
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 1);
  EXPECT_EQ(v2.size(), 2);
  EXPECT_EQ(v1[0].a, 5);
  EXPECT_EQ(v2[0].a, 1);
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  auto it = v.insert_many(v.begin(), 4, 5, 6);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(v.front(), 4);
  EXPECT_EQ(v.back(), 3);

  auto expected = {4, 5, 6, 1, 2, 3};
  auto it_vec = v.begin();
  for (auto it_expected = expected.begin(); it_expected != expected.end();
       ++it_expected, ++it_vec) {
    EXPECT_EQ(*it_vec, *it_expected);
  }
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }