#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <d_list.h>
#include <error_handler.h>


class LinkedListTest : public ::testing::Test {
 protected:

  virtual void SetUp() {
    // Set up any resources for the test
  }

  virtual void TearDown() {
    // Clean up any resources created during the test
  }
};

TEST_F(LinkedListTest, PrintAll) {
    /*
    variable
    variable
    EXPECT_EQ(, error);
    */
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
