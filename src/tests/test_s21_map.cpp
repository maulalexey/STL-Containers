#include <gtest/gtest.h>

#include <string>

#include "../containers/s21_map.h"

using namespace s21;

TEST(S21MapTest, INSERT_1) {
  map<int, std::string> nums;
  nums.insert(std::make_pair(1, "One"));

  std::map<int, std::string> expected;
  expected[1] = "One";

  ASSERT_EQ(nums.size(), expected.size());

  auto it1 = nums.begin();
  auto it2 = expected.begin();
  while (it1 != nums.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MapTest, INSERT_2) {
  map<int, std::string> nums{std::pair<int, std::string>{1, "One"},
                             std::pair{2, "Two"}, std::pair{3, "Three"}};

  std::map<int, std::string> expected;
  expected[1] = "One";
  expected[2] = "Two";
  expected[3] = "Three";

  ASSERT_EQ(nums.size(), expected.size());

  auto it1 = nums.begin();
  auto it2 = expected.begin();
  while (it1 != nums.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MapTest, INSERT_3) {
  map<int, std::string> nums;
  nums.insert({1, "One"});
  nums.insert({2, "Two"});
  nums.insert({3, "Three"});

  std::map<int, std::string> expected;
  expected[1] = "One";
  expected[2] = "Two";
  expected[3] = "Three";

  ASSERT_EQ(nums.size(), expected.size());

  auto it1 = nums.begin();
  auto it2 = expected.begin();
  while (it1 != nums.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MapTest, INSERT_4) {
  map<int, std::string> nums = {{1, "One"}, {2, "Two"}, {3, "Three"}};

  std::map<int, std::string> expected;
  expected[1] = "One";
  expected[2] = "Two";
  expected[3] = "Three";

  ASSERT_EQ(nums.size(), expected.size());

  auto it1 = nums.begin();
  auto it2 = expected.begin();
  while (it1 != nums.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MapTest, INSERT_7) {
  std::map<int, std::string> nums = {
      {1, "One"},
      {2, "Two"},
      {3, "Three"},
      {1, "One"},
  };

  std::map<int, std::string> expected;
  expected[1] = "One";
  expected[2] = "Two";
  expected[3] = "Three";

  ASSERT_EQ(nums.size(), expected.size());

  auto it1 = nums.begin();
  auto it2 = expected.begin();
  while (it1 != nums.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MapTest, AT_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});

  std::map<int, std::string> expected;
  expected[1] = "One";

  ASSERT_EQ(nums.at(1), expected.at(1));
}

TEST(S21MapTest, AT_2) {
  map<int, std::string> nums;
  nums.insert({1, "One"});

  ASSERT_THROW(nums.at(3), std::out_of_range);
}

TEST(S21MapTest, SQUARE_BRACKETS_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});
  nums[2] = "Two";

  ASSERT_EQ(nums[1], "One");
  ASSERT_EQ(nums[2], "Two");
  ASSERT_EQ(nums[3], "");
}

TEST(S21MapTest, BEGIN_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});
  nums.insert({2, "Two"});
  auto it = nums.begin();

  ASSERT_EQ((*it).first, 1);
  ASSERT_EQ((*it).second, "One");
}

TEST(S21MapTest, END_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});
  nums.insert({2, "Two"});
  auto it = nums.end();

  ASSERT_EQ(it, nullptr);
}

TEST(S21MapTest, EMPTY_1) {
  map<int, std::string> nums;

  ASSERT_EQ(nums.empty(), true);
}

TEST(S21MapTest, EMPTY_2) {
  map<int, std::string> nums;
  std::map<int, std::string> expected;

  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MapTest, EMPTY_3) {
  map<int, std::string> nums;
  nums.insert({1, "One"});

  ASSERT_EQ(nums.empty(), false);
}

TEST(S21MapTest, SYZE_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});
  nums.insert({2, "Two"});
  nums.insert({3, "Three"});

  std::map<int, std::string> expected;
  expected.insert({1, "One"});
  expected.insert({2, "Two"});
  expected.insert({3, "Three"});

  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MapTest, SYZE_2) {
  map<int, std::string> nums;
  std::map<int, std::string> expected;

  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MapTest, CLEAR_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});
  nums.insert({2, "Two"});
  nums.clear();

  std::map<int, std::string> expected;

  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MapTest, ERASE_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});
  nums.insert({2, "Two"});
  auto it = nums.begin();
  nums.erase(it);

  std::map<int, std::string> expected;
  expected[2] = "Two";

  ASSERT_EQ(nums.size(), expected.size());
}

TEST(S21MapTest, SWAP_1) {
  map<int, std::string> map1, map2;
  map1.insert({1, "One"});
  map2.insert({2, "Two"});
  map1.swap(map2);

  ASSERT_EQ(map1[2], "Two");
  ASSERT_EQ(map2[1], "One");
}

TEST(S21MapTest, MERGE_1) {
  map<int, std::string> map1;
  map1.insert({1, "One"});
  map1.insert({2, "Two"});

  map<int, std::string> map2;
  map2.insert({2, "Two"});
  map2.insert({3, "Three"});

  map1.merge(map2);

  std::map<int, std::string> expected;
  expected[1] = "One";
  expected[2] = "Two";
  expected[3] = "Three";

  ASSERT_EQ(map1.size(), expected.size());

  auto it1 = map1.begin();
  auto it2 = expected.begin();
  while (it1 != map1.end() && it2 != expected.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(S21MapTest, CONTAINS_1) {
  map<int, std::string> nums;
  nums.insert({1, "One"});

  ASSERT_EQ(nums.contains(1), true);
}

TEST(S21MapTest, CONTAINS_2) {
  map<int, std::string> nums;
  nums.insert({1, "One"});

  ASSERT_EQ(nums.contains(2), false);
}

TEST(S21MapTest, CONTAINS_3) {
  map<int, std::string> nums;

  ASSERT_EQ(nums.contains(2), false);
}
