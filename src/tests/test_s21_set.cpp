#include <gtest/gtest.h>

#include <string>

#include "../Tree/tree.h"
#include "../containers/s21_set.h"

using namespace s21;

TEST(S21SetTest, INSERT_1) {
  set<int> numbers;
  numbers.insert(5);
  numbers.insert(3);
  numbers.insert(2);
  numbers.insert(7);
  numbers.insert(6);
  numbers.insert(8);
  numbers.insert(8);

  std::set<int> expected{5, 3, 2, 7, 6, 8, 8};

  ASSERT_EQ(numbers.size(), expected.size());

  auto it1 = numbers.begin();
  auto it2 = expected.begin();
  while (it1 != numbers.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, INSERT_2) {
  set<std::string> str;
  str.insert("hello");
  str.insert("world");

  set<std::string> expected{"hello", "world"};

  ASSERT_EQ(str.size(), expected.size());

  auto it1 = str.begin();
  auto it2 = expected.begin();
  while (it1 != str.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, INSERT_3) {
  set<double> numbers;
  numbers.insert(4.5);
  numbers.insert(1.000);
  numbers.insert(2);
  numbers.insert(0.0001);
  numbers.insert(14.3);
  numbers.insert(25.2);
  numbers.insert(100);

  set<double> expected{4.5, 1.000, 2, 0.0001, 14.3, 25.2, 100};

  ASSERT_EQ(numbers.size(), expected.size());

  auto it1 = numbers.begin();
  auto it2 = expected.begin();
  while (it1 != numbers.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, INIT_LIST_CONSTRUCTOR_1) {
  set<int> numbers{5, 3, 2, 7, 6, 8};
  std::set<int> expected{2, 3, 5, 6, 7, 8};

  ASSERT_EQ(numbers.size(), expected.size());

  auto it1 = numbers.begin();
  auto it2 = expected.begin();
  while (it1 != numbers.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, INIT_LIST_CONSTRUCTOR_2) {
  set<int> numbers{5, 3, 3, 2, 7, 6, 8, 8};
  std::set<int> expected{2, 3, 5, 6, 7, 8};

  ASSERT_EQ(numbers.size(), expected.size());

  auto it1 = numbers.begin();
  auto it2 = expected.begin();
  while (it1 != numbers.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, INIT_LIST_CONSTRUCTOR_3) {
  set<std::string> letters{"a", "b", "c", "d", "d", "e"};
  std::set<std::string> expected{"a", "b", "c", "d", "e"};

  ASSERT_EQ(letters.size(), expected.size());

  auto it1 = letters.begin();
  auto it2 = expected.begin();
  while (it1 != letters.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, INIT_LIST_CONSTRUCTOR_4) {
  set<std::string> s{};
  std::set<std::string> expected{};

  ASSERT_EQ(s.size(), expected.size());
}

TEST(S21SetTest, INIT_LIST_CONSTRUCTOR_5) {
  set<std::string> letters{"a", "b", "c", "d", "d", "e"};
  std::set<std::string> expected{"a", "b", "c", "d", "e"};

  ASSERT_EQ(letters.size(), expected.size());

  auto it1 = letters.begin();
  auto it2 = expected.begin();

  while (it1 != letters.end() && it2 != expected.end()) {
    ASSERT_EQ(*(it1++), *(it2++));
  }
}

TEST(S21SetTest, BEGIN_1) {
  set<int> nums{5, 3, 2, 7, 6, 8};
  auto it = nums.begin();

  ASSERT_EQ((*it), 2);
}

TEST(S21SetTest, BEGIN_2) {
  set<int> nums;
  auto it = nums.begin();

  ASSERT_EQ(it, nullptr);
}

TEST(S21SetTest, END_1) {
  set<int> nums{5, 3, 2, 7, 6, 8};
  auto it = nums.end();

  ASSERT_EQ(it, nullptr);
}

TEST(S21SetTest, EMPTY_1) {
  set<int> empty{};
  ASSERT_EQ(empty.empty(), true);
}

TEST(S21SetTest, EMPTY_2) {
  set<int> empty{};
  std::set<int> expected{};
  ASSERT_EQ(empty.size(), expected.size());
}

TEST(S21SetTest, EMPTY_3) {
  set<int> empty{4, 10, 2, 7};
  ASSERT_EQ(empty.empty(), false);
}

TEST(S21SetTest, SYZE_1) {
  set<int> numbers{5, 3, 2, 7, 6, 8};
  std::set<int> expected{5, 3, 2, 7, 6, 8};
  ASSERT_EQ(numbers.size(), expected.size());
}

TEST(S21SetTest, SYZE_2) {
  set<std::string> letters{"a", "g", "h", "r", "f", "c", "n"};
  std::set<std::string> expected{"a", "g", "h", "r", "f", "c", "n"};
  ASSERT_EQ(letters.size(), expected.size());
}

TEST(S21SetTest, SYZE_3) {
  set<int> empty{};
  std::set<int> expected{};
  ASSERT_EQ(empty.size(), expected.size());
}

TEST(S21SetTest, CLEAR_1) {
  set<int> numbers{5, 3, 2, 7, 6, 8};
  std::set<int> expected{};
  numbers.clear();
  ASSERT_EQ(numbers.size(), expected.size());
}

TEST(S21SetTest, CLEAR_2) {
  set<int> numbers{};
  std::set<int> expected{};
  numbers.clear();
  ASSERT_EQ(numbers.size(), expected.size());
}

TEST(S21SetTest, ERASE_1) {
  set<int> numbers = {5, 3, 2, 7, 6, 8};
  numbers.erase(numbers.find(8));

  std::set<int> expected{5, 3, 2, 7, 6, 8};
  expected.erase(8);

  ASSERT_EQ(numbers.size(), expected.size());

  auto it1 = numbers.begin();
  auto it2 = expected.begin();
  while (it1 != numbers.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, ERASE_2) {
  set<int> numbers;
  numbers.erase(numbers.find(8));

  std::set<int> expected;
  expected.erase(8);

  ASSERT_EQ(numbers.size(), expected.size());
}

TEST(S21SetTest, SWAP_1) {
  set<int> numbers_1{2, 4, 6, 8, 10};
  set<int> numbers_2{1, 3, 5, 7, 9};
  numbers_1.swap(numbers_2);

  std::set<int> expected{1, 3, 5, 7, 9};

  auto it1 = numbers_1.begin();
  auto it2 = expected.begin();
  while (it1 != numbers_1.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, SWAP_2) {
  set<int> numbers_1{2, 4, 6, 8, 10};
  set<int> numbers_2;
  numbers_1.swap(numbers_2);

  std::set<int> expected{2, 4, 6, 8, 10};

  auto it1 = numbers_2.begin();
  auto it2 = expected.begin();
  while (it1 != numbers_2.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, SWAP_3) {
  set<int> numbers_1;
  set<int> numbers_2;
  numbers_1.swap(numbers_2);

  std::set<int> expected;

  ASSERT_EQ(numbers_1.size(), expected.size());
}

TEST(S21SetTest, MERGE_1) {
  set<std::string> numbers_1;
  numbers_1.insert("hello");
  set<std::string> numbers_2;
  numbers_2.insert("world");
  numbers_1.merge(numbers_2);

  std::set<std::string> expected;
  expected.insert("hello");
  expected.insert("world");

  auto it1 = numbers_1.begin();
  auto it2 = expected.begin();
  while (it1 != numbers_1.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21SetTest, MERGE_2) {
  set<std::string> numbers_1;
  set<std::string> numbers_2;
  numbers_1.merge(numbers_2);

  std::set<std::string> expected;
  ASSERT_EQ(numbers_1.size(), expected.size());
}

TEST(S21SetTest, FIND_1) {
  set<int> numbers{2, 4, 6, 8, 10};
  auto it = numbers.find(4);
  ASSERT_EQ(*it, 4);
}

TEST(S21SetTest, FIND_2) {
  set<int> numbers{2, 4, 6, 8, 10};
  auto it = numbers.find(4);
  ASSERT_NE(it, numbers.end());
}

TEST(S21SetTest, FIND_3) {
  set<int> numbers{2, 4, 6, 8, 10};
  auto it = numbers.find(5);
  ASSERT_EQ(it, numbers.end());
}

TEST(S21SetTest, FIND_4) {
  set<int> numbers;
  auto it = numbers.find(5);
  ASSERT_EQ(it, numbers.end());
}

TEST(S21SetTest, CONTAINS_1) {
  set<int> numbers{2, 9, 6, 15, 10};
  ASSERT_EQ(numbers.contains(15), true);
}

TEST(S21SetTest, CONTAINS_2) {
  set<int> numbers{2, 9, 6, 15, 10};
  ASSERT_EQ(numbers.contains(1), false);
}

TEST(S21SetTest, CONTAINS_3) {
  set<int> numbers;
  ASSERT_EQ(numbers.contains(2), false);
}
