#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <d_list.h>

extern Node *head;

void print_int(void *data) {
    int value = *(int *)data;
    printf("%d ", value);
}

int compare_int(void *node_data, void *search_data) {
    int node_value = *(int *)node_data;
    int search_value = *(int *)search_data;
    return node_value - search_value;
}

class LinkedListTest : public ::testing::Test {
 protected:

  virtual void SetUp() {
    head = NULL;
  }

  virtual void TearDown() {
    // Clean up any resources created during the test
    while (head != NULL) {
      Node *temp = head;
      head = head->next;
      free(temp);
      temp = NULL;
    }
  }
};

TEST_F(LinkedListTest, PrintAll) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_head(&data1);
    insert_at_head(&data2);
    insert_at_head(&data3);
    testing::internal::CaptureStdout();
    print_all(print_int);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected_output = "3 2 1 \n";
    EXPECT_EQ(output, expected_output);
}

TEST_F(LinkedListTest, CreateNode) {
    int data = 42;
    Node *node = create_node(&data);
    EXPECT_EQ(42, *(int *)node->data);
    EXPECT_EQ(NULL, node->prev);
    EXPECT_EQ(NULL, node->next);
    free(node);
}

TEST_F(LinkedListTest, InsertAtHead) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_head(&data1);
    insert_at_head(&data2);
    insert_at_head(&data3);
    Node *current = head;
    int expected[] = {3, 2, 1};
    int i = 0;
    while (current != NULL) {
        EXPECT_EQ(expected[i++], *(int *)current->data);
        current = current->next;
    }
}

TEST_F(LinkedListTest, InsertAtTail) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_tail(&data1);
    insert_at_tail(&data2);
    insert_at_tail(&data3);
    Node *current = head;
    int expected[] = {1, 2, 3};
    int i = 0;
    while (current != NULL) {
        EXPECT_EQ(expected[i++], *(int *)current->data);
        current = current->next;
    }
}

TEST_F(LinkedListTest, PopTail) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_head(&data1);
    insert_at_head(&data2);
    insert_at_head(&data3);
    Node *tail = pop_tail();
    EXPECT_EQ(1, *(int *)tail->data);
    free(tail);
}

TEST_F(LinkedListTest, DeleteNode) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_head(&data1);
    insert_at_head(&data2);
    insert_at_head(&data3);
    delete_node(&data2, compare_int);
    Node *current = head;
    int expected[] = {3, 1};
    int i = 0;
    while (current != NULL) {
        EXPECT_EQ(expected[i++], *(int *)current->data);
        current = current->next;
    }
}

TEST_F(LinkedListTest, PopHead) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_tail(&data1);
    insert_at_tail(&data2);
    insert_at_tail(&data3);
    Node *popped_node = pop_head();
    EXPECT_EQ(data1, *(int *)popped_node->data);
    free(popped_node);
    popped_node = NULL;
    int expected[] = {2, 3};
    int i = 0;
    Node *current = head;
    while (current != NULL) {
        EXPECT_EQ(expected[i++], *(int *)current->data);
        current = current->next;
    }
}

TEST_F(LinkedListTest, PeekHead) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_tail(&data1);
    insert_at_tail(&data2);
    insert_at_tail(&data3);
    void *head_data = peek_head();
    EXPECT_EQ(data1, *(int *)head_data);
}

TEST_F(LinkedListTest, PeekTail) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_tail(&data1);
    insert_at_tail(&data2);
    insert_at_tail(&data3);
    void *tail_data = peek_tail();
    EXPECT_EQ(data3, *(int *)tail_data);
}

TEST_F(LinkedListTest, PeekAt) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_tail(&data1);
    insert_at_tail(&data2);
    insert_at_tail(&data3);
    void *index_data = peek_at(1);
    EXPECT_EQ(data2, *(int *)index_data);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
