#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <d_list.h>
#include <error_handler.h>

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
    ErrorCode error = insert_at_head(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_head(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_head(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    testing::internal::CaptureStdout();
    print_all(print_int);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected_output = "3 2 1 \n";
    EXPECT_EQ(output, expected_output);
}

TEST_F(LinkedListTest, CreateNode) {
    int data = 69;
    Node *node = create_node(&data);
    EXPECT_EQ(69, *(int *)node->data);
    EXPECT_EQ(NULL, node->prev);
    EXPECT_EQ(NULL, node->next);
    free(node);
}

TEST_F(LinkedListTest, InsertAtHead) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    ErrorCode error = insert_at_head(&data1);
    CHECK_ERROR(error);
    error = insert_at_head(&data2);
    CHECK_ERROR(error);
    error = insert_at_head(&data3);
    CHECK_ERROR(error);
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
    ErrorCode error = insert_at_tail(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    Node *current = head;
    int expected[] = {1, 2, 3};
    int i = 0;
    while (current != NULL) {
        EXPECT_EQ(expected[i++], *(int *)current->data);
        current = current->next;
    }
}

TEST_F(LinkedListTest, InsertAtPosition) {
    int data1 = 5;
    int data2 = 10;
    int data3 = 15;
    int data4 = 20;
    ErrorCode error = insert_at_head(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_head(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_head(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_position(&data4, 2);
    EXPECT_EQ(ERROR_SUCCESS, error);

    int expected[] = {data3, data4, data2, data1};
    int i = 0;

    Node *current = head;
    while (current != NULL) {
        EXPECT_EQ(expected[i++], *(int *)current->data);
        current = current->next;
    }
}

TEST_F(LinkedListTest, PopTail) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    insert_at_tail(&data1);
    insert_at_tail(&data2);
    insert_at_tail(&data3);
    Node *tail;
    ErrorCode error = pop_tail(&tail);
    EXPECT_EQ(ERROR_SUCCESS, error);
    EXPECT_EQ(data3, *(int *)tail->data);
    free(tail);
    error = pop_tail(&tail);
    EXPECT_EQ(ERROR_SUCCESS, error);
    EXPECT_EQ(data2, *(int *)tail->data);
    free(tail);
    error = pop_tail(&tail);
    EXPECT_EQ(ERROR_SUCCESS, error);
    EXPECT_EQ(data1, *(int *)tail->data);
    free(tail);
    error = pop_tail(&tail);
    EXPECT_EQ(ERROR_INVALID_INPUT, error);
    tail = NULL;
}

TEST_F(LinkedListTest, DeleteNode) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    ErrorCode error = insert_at_head(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_head(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_head(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = delete_node(&data2, compare_int);
    EXPECT_EQ(ERROR_SUCCESS, error);
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
    ErrorCode error = insert_at_tail(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    Node *popped_node;
    error = pop_head(&popped_node);
    EXPECT_EQ(ERROR_SUCCESS, error);
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
    ErrorCode error = insert_at_tail(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    void *head_data;
    error = peek_head(&head_data);
    EXPECT_EQ(ERROR_SUCCESS, error);
    EXPECT_EQ(data1, *(int *)head_data);
}

TEST_F(LinkedListTest, PeekTail) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    ErrorCode error = insert_at_tail(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    void *tail_data;
    error = peek_tail(&tail_data);
    EXPECT_EQ(ERROR_SUCCESS, error);
    EXPECT_EQ(data3, *(int *)tail_data);
}

TEST_F(LinkedListTest, PeekAt) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    ErrorCode error = insert_at_tail(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    void *index_data = NULL;
    error = peek_at(1, &index_data);
    EXPECT_EQ(ERROR_SUCCESS, error);
    EXPECT_EQ(data2, *(int *)index_data);
}

TEST_F(LinkedListTest, ListLength) {
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    ErrorCode error = insert_at_tail(&data1);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data2);
    EXPECT_EQ(ERROR_SUCCESS, error);
    error = insert_at_tail(&data3);
    EXPECT_EQ(ERROR_SUCCESS, error);
    int length = 0;
    error = list_length(&length);
    EXPECT_EQ(ERROR_SUCCESS, error);
    EXPECT_EQ(3, length);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
