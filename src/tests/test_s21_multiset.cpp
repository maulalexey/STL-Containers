#include <gtest/gtest.h>

#include <string>

#include "../containersplus/s21_multiset.h"

using namespace s21;

TEST(S21MultisetTest, INIT_LIST_CONSTRUCTOR_1) {
  multiset<int> nums{5, 3, 2, 7, 6, 8, 8};
  std::multiset<int> expected{5, 3, 2, 7, 6, 8, 8};

  ASSERT_EQ(nums.size(), expected.size());

  auto it1 = nums.begin();
  auto it2 = expected.begin();
  while (it1 != nums.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MultisetTest, INSERT_1) {
  multiset<int> nums;
  nums.insert(5);
  nums.insert(3);
  nums.insert(2);
  nums.insert(7);
  nums.insert(6);
  nums.insert(8);
  nums.insert(8);

  std::multiset<int> expected{5, 3, 2, 7, 6, 8, 8};

  ASSERT_EQ(nums.size(), expected.size());

  auto it1 = nums.begin();
  auto it2 = expected.begin();
  while (it1 != nums.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MultisetTest, BEGIN_1) {
  multiset<int> nums{5, 3, 2, 7, 6, 8, 5, 3, 2, 7, 6, 8};
  auto it = nums.begin();

  ASSERT_EQ((*it), 2);
}

TEST(S21MultisetTest, END_1) {
  multiset<int> nums{5, 3, 2, 7, 6, 8, 5, 3, 2, 7, 6, 8};
  auto it = nums.end();

  ASSERT_EQ(it, nullptr);
}

TEST(S21MultisetTest, EMPTY_1) {
  multiset<int> empty{};
  ASSERT_EQ(empty.empty(), true);
}

TEST(S21MultisetTest, EMPTY_2) {
  multiset<int> empty{};
  std::multiset<int> expected{};
  ASSERT_EQ(empty.size(), expected.size());
}

TEST(S21MultisetTest, EMPTY_3) {
  multiset<int> empty{1, 2, 6, 4, 9};
  ASSERT_EQ(empty.empty(), false);
}

TEST(S21MultisetTest, SYZE_1) {
  multiset<int> nums{2, 2, 6, 6, 3, 3, 8, 8};
  std::multiset<int> expected{2, 2, 6, 6, 3, 3, 8, 8};
  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MultisetTest, SYZE_2) {
  multiset<std::string> letters{"a", "b", "c", "e", "f", "g",
                                "a", "b", "c", "e", "f", "g"};
  std::multiset<std::string> expected{"a", "b", "c", "e", "f", "g",
                                      "a", "b", "c", "e", "f", "g"};
  ASSERT_EQ(letters.size(), expected.size());
}

TEST(S21MultisetTest, SYZE_3) {
  multiset<int> empty{};
  std::multiset<int> expected{};
  ASSERT_EQ(empty.size(), expected.size());
}

TEST(S21MultisetTest, CLEAR_1) {
  multiset<int> nums{5, 3, 2, 7, 6, 8, 5, 3, 2};
  std::multiset<int> expected{};
  nums.clear();
  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MultisetTest, CLEAR_2) {
  multiset<int> nums{2, 2, 6, 6, 3, 3, 8, 8};
  std::multiset<int> expected{};
  nums.clear();
  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MultisetTest, CLEAR_3) {
  multiset<int> nums{};
  std::multiset<int> expected{};
  nums.clear();
  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MultisetTest, SWAP_1) {
  multiset<int> nums_1{2, 4, 6, 8, 10, 10};
  multiset<int> nums_2{1, 3, 5, 7, 9, 9};
  nums_1.swap(nums_2);

  std::multiset<int> expected{1, 3, 5, 7, 9, 9};

  auto it1 = nums_1.begin();
  auto it2 = expected.begin();
  while (it1 != nums_1.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MultisetTest, SWAP_2) {
  multiset<char> letters_1{'a', 'b', 'b', 'd'};
  multiset<char> letters_2;
  letters_1.swap(letters_2);

  std::multiset<char> expected{'a', 'b', 'b', 'd'};

  auto it1 = letters_2.begin();
  auto it2 = expected.begin();
  while (it1 != letters_2.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MultisetTest, MERGE_1) {
  multiset<int> numbers_1{2, 12, 6, 4, 10};
  multiset<int> numbers_2{1, 1, 9, 7, 15};
  numbers_1.merge(numbers_2);

  std::multiset<int> expected{1, 2, 4, 6, 7, 9, 10, 12, 15};

  auto it1 = numbers_1.begin();
  auto it2 = expected.begin();
  while (it1 != numbers_1.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MultisetTest, MERGE_2) {
  multiset<int> numbers_1;
  multiset<int> numbers_2;
  numbers_1.merge(numbers_2);

  std::multiset<int> expected;
  ASSERT_EQ(numbers_1.size(), expected.size());
}

TEST(S21MultisetTest, MERGE_3) {
  multiset<char> letters_1{'a', 'i', 'e', 'q'};
  multiset<char> letters_2{'g', 'd', 'o'};
  letters_1.merge(letters_2);

  std::multiset<char> expected{'a', 'i', 'e', 'q', 'g', 'd', 'o'};

  auto it1 = letters_1.begin();
  auto it2 = expected.begin();
  while (it1 != letters_1.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MultisetTest, FIND_1) {
  multiset<int> nums{2, 4, 6, 8, 10, 4};
  auto it = nums.find(4);
  ASSERT_EQ(*it, 4);
}

TEST(S21MultisetTest, FIND_2) {
  multiset<int> nums{2, 4, 6, 8, 10, 8};
  auto it = nums.find(4);
  ASSERT_NE(it, nums.end());
}

TEST(S21MultisetTest, FIND_3) {
  multiset<int> nums{2, 4, 6, 8, 10, 4};
  auto it = nums.find(5);
  ASSERT_EQ(it, nums.end());
}

TEST(S21MultisetTest, FIND_4) {
  multiset<char> letters{'a', 'b', 'c', 'd', 'f', 'b', 'd', 'a'};
  auto it = letters.find('e');
  ASSERT_EQ(it, letters.end());
}

TEST(S21MultisetTest, FIND_5) {
  multiset<char> letters;
  auto it = letters.find('e');
  ASSERT_EQ(it, letters.end());
}

TEST(S21MultisetTest, CONTAINS_1) {
  multiset<int> nums{2, 4, 6, 8, 10, 4};

  ASSERT_EQ(nums.contains(6), true);
}

TEST(S21MultisetTest, CONTAINS_2) {
  multiset<int> nums{2, 4, 6, 8, 10, 4};

  ASSERT_EQ(nums.contains(4), true);
}

TEST(S21MultisetTest, CONTAINS_3) {
  multiset<int> nums{2, 4, 6, 8, 10, 4};

  ASSERT_EQ(nums.contains(9), false);
}

TEST(S21MultisetTest, CONTAINS_4) {
  multiset<int> nums;

  ASSERT_EQ(nums.contains(1), false);
}

TEST(S21MultisetTest, LOWER_BOUND_1) {
  multiset<int> s{1, 2, 2, 1, 4};

  auto it = s.lower_bound(2);
  ASSERT_EQ(*it, 2);

  it = s.lower_bound(3);
  ASSERT_EQ(*it, 4);
}

TEST(S21MultisetTest, LOWER_BOUND_2) {
  multiset<int> s{1, 2, 2, 1, 4};

  auto it = s.lower_bound(7);
  ASSERT_EQ(it, s.end());
}

TEST(S21MultisetTest, UPPER_BOUND_1) {
  multiset<int> s;
  s.insert(10);
  s.insert(13);
  s.insert(13);
  s.insert(25);
  s.insert(24);

  auto it = s.upper_bound(10);
  ASSERT_EQ(*it, 13);

  it = s.upper_bound(2);
  ASSERT_EQ(*it, 10);

  it = s.upper_bound(24);
  ASSERT_EQ(*it, 25);
}

TEST(S21MultisetTest, UPPER_BOUND_2) {
  multiset<int> s;
  s.insert(10);
  s.insert(13);
  s.insert(13);
  s.insert(25);
  s.insert(24);

  auto it = s.upper_bound(30);
  ASSERT_EQ(it, s.end());
}

TEST(S21MultisetTest, COUNT_1) {
  multiset<int> nums;
  nums.insert(1);
  nums.insert(5);
  nums.insert(12);
  nums.insert(15);
  nums.insert(5);
  nums.insert(7);
  nums.insert(4);

  ASSERT_EQ(nums.count(5), 2);
}

TEST(S21MultisetTest, COUNT_2) {
  multiset<int> nums;
  nums.insert(1);
  nums.insert(5);
  nums.insert(12);
  nums.insert(15);
  nums.insert(5);
  nums.insert(7);
  nums.insert(4);

  ASSERT_EQ(nums.count(7), 1);
}

TEST(S21MultisetTest, COUNT_3) {
  multiset<int> nums;

  ASSERT_EQ(nums.count(7), 0);
}

TEST(S21MultisetTest, EQUAL_RANGE_1) {
  multiset<int> nums;
  nums.insert(1);
  nums.insert(5);
  nums.insert(12);
  nums.insert(15);
  nums.insert(5);
  nums.insert(7);
  nums.insert(4);

  std::multiset<int> expected;
  expected.insert(1);
  expected.insert(5);
  expected.insert(12);
  expected.insert(15);
  expected.insert(5);
  expected.insert(7);
  expected.insert(4);

  auto range_nums = nums.equal_range(5);
  auto range_expected = expected.equal_range(5);

  ASSERT_EQ(*range_nums.first, 5);
  ASSERT_EQ(*range_nums.second, 7);

  ASSERT_EQ(*range_expected.first, 5);
  ASSERT_EQ(*range_expected.second, 7);
}

// TEST(S21MultisetTest, INSERT_MANY_1) {
//   multiset<int> nums;
//   nums.insert(1, 2, 3);
//   nums.print();
// }
