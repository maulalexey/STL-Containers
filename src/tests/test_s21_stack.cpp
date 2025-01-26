#include <gtest/gtest.h>

#include <vector>

#include "../containers/s21_stack.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s{10, 20, 30};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s.top(), 30);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> s1{1, 2, 3};
  s21::stack<int> s2(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
  s2.pop();
  EXPECT_EQ(s2.top(), 2);
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> s1{1, 2, 3};
  s21::stack<int> s2(std::move(s1));
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, CopyAssignmentOperator) {
  s21::stack<int> s1{1, 2, 3};
  s21::stack<int> s2;
  s2 = s1;
  EXPECT_EQ(s1.size(), s2.size());
  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    s1.pop();
    s2.pop();
  }
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> s1{1, 2, 3};
  s21::stack<int> s2;
  s2 = std::move(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, Empty) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());
  s.push(10);
  EXPECT_FALSE(s.empty());
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, Size) {
  s21::stack<int> s;
  EXPECT_EQ(s.size(), 0);
  s.push(10);
  s.push(20);
  EXPECT_EQ(s.size(), 2);
  s.pop();
  EXPECT_EQ(s.size(), 1);
}

TEST(StackTest, PushAndPop) {
  s21::stack<int> s;
  s.push(10);
  EXPECT_EQ(s.top(), 10);
  s.push(20);
  EXPECT_EQ(s.top(), 20);
  s.pop();
  EXPECT_EQ(s.top(), 10);
}

TEST(StackTest, Swap) {
  s21::stack<int> s1{1, 2, 3};
  s21::stack<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.top(), 6);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, InsertManyFront) {
  s21::stack<int> s;
  s.insert_many_front(1, 2, 3, 4, 5);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.top(), 5);
}

TEST(StackTest, ConstTop) {
  const s21::stack<int> s{1, 2, 3};
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, ConstEmpty) {
  const s21::stack<int> s;
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, ConstSize) {
  const s21::stack<int> s{1, 2, 3};
  EXPECT_EQ(s.size(), 3);
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }