#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../containers/s21_list.h"

template <typename value_type>
bool compare_lists(s21::list<value_type> my_list,
                   std::list<value_type> std_list) {
  bool result = my_list.size() == std_list.size();
  if (result) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.size() && result; ++i) {
      result = *my_it == *std_it;
      ++my_it;
      ++std_it;
    }
  }
  return result;
}

TEST(ListConstructor, DefaultConstructor) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_TRUE(my_list.empty());
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, SizeConstructor) {
  s21::list<int> my_list(5);
  std::list<int> std_list(5);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, InitializerListConstructor) {
  s21::list<int> my_list{10, 20, 30, 40, 50};
  std::list<int> std_list{10, 20, 30, 40, 50};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, InitializerListConstructor2) {
  s21::list<char> my_list{'q', 'w', 'e', 'r'};
  std::list<char> std_list{'q', 'w', 'e', 'r'};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, CopyConstructor) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListConstructor, CopyConstructor2) {
  s21::list<char> my_list{'q', 'w', 'e', 'r'};
  s21::list<char> my_list_copy1(my_list);
  std::list<char> std_list{'q', 'w', 'e', 'r'};
  std::list<char> std_list_copy1(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy1, std_list_copy1));
}

TEST(ListConstructor, MoveConstructor) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list{1, 2, 3, 4, 5};
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListConstructor, MoveConstructor2) {
  s21::list<char> my_list{'q', 'w', 'e', 'r'};
  s21::list<char> my_list_move1(std::move(my_list));
  std::list<char> std_list{'q', 'w', 'e', 'r'};
  std::list<char> std_list_move1(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_move1, std_list_move1));
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListAccess, Front) {
  s21::list<int> my_list{100, 200, 300, 400, 500};
  std::list<int> std_list{100, 200, 300, 400, 500};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListAccess, Back) {
  s21::list<int> my_list{100, 200, 300, 400, 500};
  std::list<int> std_list{100, 200, 300, 400, 500};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListModifiers, PushBack) {
  s21::list<int> my_list{1, 2, 3};
  my_list.push_back(4);
  std::list<int> std_list{1, 2, 3};
  std_list.push_back(4);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopBack) {
  s21::list<int> my_list{1, 2, 3, 4};
  my_list.pop_back();
  std::list<int> std_list{1, 2, 3, 4};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushFront) {
  s21::list<int> my_list{2, 3, 4};
  my_list.push_front(1);
  std::list<int> std_list{2, 3, 4};
  std_list.push_front(1);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopFront) {
  s21::list<int> my_list{1, 2, 3, 4};
  my_list.pop_front();
  std::list<int> std_list{1, 2, 3, 4};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Insert) {
  s21::list<int> my_list{1, 2, 4, 5};
  auto it = my_list.begin();
  ++it;
  ++it;
  my_list.insert(it, 3);
  std::list<int> std_list{1, 2, 4, 5};
  auto std_it = std_list.begin();
  ++std_it;
  ++std_it;
  std_list.insert(std_it, 3);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Erase) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  auto it = my_list.begin();
  ++it;
  my_list.erase(it);
  std::list<int> std_list{1, 2, 3, 4, 5};
  auto std_it = std_list.begin();
  ++std_it;
  std_list.erase(std_it);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Swap) {
  s21::list<int> my_list1{1, 2, 3};
  s21::list<int> my_list2{4, 5, 6};
  my_list1.swap(my_list2);
  std::list<int> std_list1{1, 2, 3};
  std::list<int> std_list2{4, 5, 6};
  std_list1.swap(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListModifiers, Merge) {
  s21::list<int> my_list1{1, 3, 5};
  s21::list<int> my_list2{2, 4, 6};
  my_list1.merge(my_list2);
  std::list<int> std_list1{1, 3, 5};
  std::list<int> std_list2{2, 4, 6};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Reverse) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.reverse();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Unique) {
  s21::list<int> my_list{1, 1, 2, 3, 3, 3, 4, 5, 5};
  my_list.unique();
  std::list<int> std_list{1, 1, 2, 3, 3, 3, 4, 5, 5};
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Sort) {
  s21::list<int> my_list{5, 3, 1, 4, 2};
  my_list.sort();
  std::list<int> std_list{5, 3, 1, 4, 2};
  std_list.sort();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, InsertLargeList) {
  s21::list<int> my_list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it = my_list.begin();
  ++it;
  ++it;
  my_list.insert(it, 100);
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto std_it = std_list.begin();
  ++std_it;
  ++std_it;
  std_list.insert(std_it, 100);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, MergeLargeList) {
  s21::list<int> my_list1{1, 3, 5, 7, 9};
  s21::list<int> my_list2{2, 4, 6, 8, 10};
  my_list1.merge(my_list2);
  std::list<int> std_list1{1, 3, 5, 7, 9};
  std::list<int> std_list2{2, 4, 6, 8, 10};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(my_list2.empty());
}

TEST(ListModifiers, SortRandomOrder) {
  s21::list<int> my_list{5, 3, 1, 4, 2};
  my_list.sort();
  std::list<int> std_list{5, 3, 1, 4, 2};
  std_list.sort();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, SortAlreadySorted) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.sort();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.sort();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, InsertMany) {
  s21::list<int> l = {1, 2, 3};

  auto it = l.insert_many(l.begin(), 4, 5, 6);
  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(l.front(), 4);
  EXPECT_EQ(l.back(), 3);

  auto expected = {4, 5, 6, 1, 2, 3};
  auto it_list = l.begin();
  for (auto it_expected = expected.begin(); it_expected != expected.end();
       ++it_expected, ++it_list) {
    EXPECT_EQ(*it_list, *it_expected);
  }
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> l = {1, 2, 3};

  l.insert_many_back(4, 5, 6);
  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 6);

  auto expected = {1, 2, 3, 4, 5, 6};
  auto it_list = l.begin();
  for (auto it_expected = expected.begin(); it_expected != expected.end();
       ++it_expected, ++it_list) {
    EXPECT_EQ(*it_list, *it_expected);
  }
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> l = {1, 2, 3};

  l.insert_many_front(4, 5, 6);
  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(l.front(), 6);
  EXPECT_EQ(l.back(), 3);

  auto expected = {6, 5, 4, 1, 2, 3};
  auto it_list = l.begin();
  for (auto it_expected = expected.begin(); it_expected != expected.end();
       ++it_expected, ++it_list) {
    EXPECT_EQ(*it_list, *it_expected);
  }
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }