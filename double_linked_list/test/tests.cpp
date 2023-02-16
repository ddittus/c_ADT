#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <d_list.h>

extern Node *head;

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

void print_int(void *data) {
    int value = *(int *)data;
    printf("%d ", value);
}

int compare_int(void *node_data, void *search_data) {
    int node_value = *(int *)node_data;
    int search_value = *(int *)search_data;
    return node_value - search_value;
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
    //print_all(print_int);
    Node *current = head;
    int expected[] = {3, 2, 1};
    int i = 0;
    while (current != NULL) {
        EXPECT_EQ(expected[i++], *(int *)current->data);
        current = current->next;
    }
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
