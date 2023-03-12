#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <queue.h>
#include <stdlib.h>
#include <error_handler.h>


class QueueTest : public ::testing::Test {
 protected:

  virtual void SetUp() {
    // Set up any resources for the test
  }

  virtual void TearDown() {
    // Clean up any resources created during the test
  }
};

TEST_F(QueueTest, EnqueueAndDequeue) {
  queue_t* queue = queue_init();

  int value1 = 10;
  int value2 = 20;
  int value3 = 30;

  queue_enqueue(queue, &value1);
  queue_enqueue(queue, &value2);
  queue_enqueue(queue, &value3);

  EXPECT_EQ(&value1, queue_dequeue(queue));
  EXPECT_EQ(&value2, queue_dequeue(queue));
  EXPECT_EQ(&value3, queue_dequeue(queue));
  EXPECT_EQ(NULL, queue_dequeue(queue));

  queue_destroy(&queue);
}

TEST_F(QueueTest, DestroyQueue) {
  queue_t *queue = queue_init();
  int *data1 = (int*)calloc(1, sizeof(int));;
  int *data2 = (int*)calloc(1, sizeof(int));;
  *data1 = 1;
  *data2 = 2;
  queue_enqueue(queue, data1);
  queue_enqueue(queue, data2);

  queue_destroy(&queue);

  // Test that the queue is destroyed
  EXPECT_EQ(NULL, queue);
}

TEST_F(QueueTest, CountItems) {
  queue_t *queue = queue_init();
  int value1 = 10;
  int value2 = 20;
  int value3 = 30;

  // Test that the queue count starts at 0
  EXPECT_EQ(0, queue_count(queue));

  queue_enqueue(queue, &value1);
  queue_enqueue(queue, &value2);

  // Test that the queue count increases after enqueuing items
  EXPECT_EQ(2, queue_count(queue));

  queue_enqueue(queue, &value3);

  // Test that the queue count updates after enqueuing another item
  EXPECT_EQ(3, queue_count(queue));

  queue_dequeue(queue);

  // Test that the queue count updates after dequeuing an item
  EXPECT_EQ(2, queue_count(queue));

  queue_dequeue(queue);
  queue_dequeue(queue);

  // Test that the queue count decreases after dequeuing all items
  EXPECT_EQ(0, queue_count(queue));

  queue_destroy(&queue);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
