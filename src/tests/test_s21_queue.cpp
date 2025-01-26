#include <gtest/gtest.h>

#include <queue>
#include <string>

#include "../containers/s21_queue.h"

template <typename value_type>
bool compare_queues(s21::queue<value_type> my_queue,
                    std::queue<value_type> std_queue) {
  bool result = true;
  if (my_queue.size() == std_queue.size()) {
    while (!my_queue.empty() && !std_queue.empty()) {
      if (my_queue.front() != std_queue.front()) {
        result = false;
        break;
      }
      my_queue.pop();
      std_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(QueueConstructor, CompareQueues1) {
  s21::queue<int> my_queue{-100, 0, 100, 9999, -9999};
  std::queue<int> std_queue;
  std_queue.push(-100);
  std_queue.push(0);
  std_queue.push(100);
  std_queue.push(9999);
  std_queue.push(-9999);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(compare_queues(my_queue, std_queue));
}

TEST(QueueConstructor, CompareQueues2) {
  s21::queue<std::string> my_queue{"hello", "world", "test", "queue", "s21"};
  std::queue<std::string> std_queue;
  std_queue.push("hello");
  std_queue.push("world");
  std_queue.push("test");
  std_queue.push("queue");
  std_queue.push("s21");
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueConstructor, DefaultConstructor) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.size(), 0);
  EXPECT_TRUE(my_queue.empty());
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueConstructor, InitializerQueueConstructor) {
  s21::queue<int> my_queue{-5, 0, 42, 100, -1000};
  std::initializer_list<int> il = {-5, 0, 42, 100, -1000};
  std::queue<int> std_queue{il};
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueConstructor, CopyConstructor) {
  s21::queue<int> my_queue{10, -10, 20, -20, 30};
  s21::queue<int> my_queue_copy(my_queue);
  std::initializer_list<int> il = {10, -10, 20, -20, 30};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueConstructor, CopyConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueConstructor, MoveConstructor) {
  s21::queue<int> my_queue{-1, -2, -3, -4, -5};
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move(std::move(my_queue));
  std::initializer_list<int> il = {-1, -2, -3, -4, -5};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueConstructor, MoveConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move(std::move(my_queue));
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueConstructor, MoveAssignmentOperator) {
  s21::queue<int> my_queue{1, 2, 3, 7, 20};
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move = std::move(my_queue);
  std::initializer_list<int> il = {1, 2, 3, 7, 20};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
}

TEST(QueueConstructor, MoveAssignmentOperatorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move = std::move(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
}

TEST(QueueAccess, Front) {
  s21::queue<int> my_queue{1000, -500, 300, 200, -100};
  std::initializer_list<int> il = {1000, -500, 300, 200, -100};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.front(), std_queue.front());
}

TEST(QueueAccess, Back) {
  s21::queue<int> my_queue{10, 20, 30, 40, 50, 1000};
  std::initializer_list<int> il = {10, 20, 30, 40, 50, 1000};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.back(), std_queue.back());
}

TEST(QueueCapacity, Empty) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  my_queue.push(1000);
  std_queue.push(1000);
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(QueueCapacity, Size) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueModifiers, Push) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  my_queue.push(-999);
  std_queue.push(-999);
  my_queue.push(0);
  std_queue.push(0);
  my_queue.push(999);
  std_queue.push(999);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueModifiers, Pop) {
  s21::queue<int> my_queue{100, 200, 300, 400, 500};
  std::initializer_list<int> il = {100, 200, 300, 400, 500};
  std::queue<int> std_queue{il};
  my_queue.pop();
  my_queue.pop();
  std_queue.pop();
  std_queue.pop();
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
  EXPECT_EQ(my_queue.front(), 300);
}

TEST(QueueModifiers, Swap) {
  s21::queue<int> my_queue1{-1, -2, -3};
  s21::queue<int> my_queue2{10, 20, 30, 40};
  my_queue1.swap(my_queue2);

  std::initializer_list<int> il1 = {-1, -2, -3};
  std::initializer_list<int> il2 = {10, 20, 30, 40};
  std::queue<int> std_queue1{il1};
  std::queue<int> std_queue2{il2};
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(QueueModifiers, Swap2) {
  s21::queue<int> my_queue1{-100, 0, 100};
  s21::queue<int> my_queue2;
  my_queue1.swap(my_queue2);

  std::initializer_list<int> il = {-100, 0, 100};
  std::queue<int> std_queue1{il};
  std::queue<int> std_queue2;
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}