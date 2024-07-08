// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_copy_ctor){
    List<int> intList;
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);
    intList.push_back(4);
    List<int> intList2(intList);
    ASSERT_EQUAL(4, intList2.size());
}

TEST(test_push){
    List<int> intList;
    intList.push_front(12);
    intList.push_back(12);
    ASSERT_FALSE(intList.empty());
    ASSERT_EQUAL(2, intList.size());
    intList.push_back(23);
    ASSERT_EQUAL(23, intList.back());
    ASSERT_EQUAL(12, intList.front());
}

TEST(test_pop){
    List<int> intList;
    intList.push_front(12);
    intList.push_back(22);
    intList.pop_front();
    ASSERT_EQUAL(1, intList.size());
    ASSERT_EQUAL(22, intList.front());
    ASSERT_EQUAL(22, intList.back());
    intList.pop_back();
    ASSERT_EQUAL(0, intList.size());
}

TEST(test_clear){
    List<int> intList;
    intList.push_front(12);
    intList.push_back(22);
    intList.push_back(32);
    intList.push_back(42);
    intList.clear();
    ASSERT_EQUAL(0, intList.size());
}

TEST(test_begin_end){
    List<int> intList;
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);
    List<int>::Iterator i = intList.begin();
    intList.erase(i);
    ASSERT_EQUAL(2, intList.front());
}

TEST(test_insert){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 123);
    i = intList.begin();
    intList.erase(i);
    ASSERT_TRUE(intList.empty());
}

TEST(test_insert2){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 123);
    i = intList.begin();
    intList.insert(i, 1234);
    i = intList.end();
    intList.insert(i, 12345);
    ASSERT_EQUAL(12345, intList.back());
    intList.pop_back();
    ASSERT_EQUAL(123, intList.back());
    ASSERT_EQUAL(2, intList.size());
}

TEST(test_erase){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 123);
    i = intList.begin();
    intList.insert(i, 12);
    i = intList.begin();
    intList.erase(i);
    ASSERT_EQUAL(123, intList.front());
}

TEST(test_insert3){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 1);
    intList.insert(i, 2);
    intList.insert(i, 3);
    intList.insert(i, 4);
    intList.insert(i, 5);
    ASSERT_EQUAL(5, intList.back());
}

TEST(test_it_equal){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 1);
    intList.insert(i, 2);
    intList.insert(i, 3);
    intList.insert(i, 4);
    intList.insert(i, 5);
    List<int>::Iterator i2 = intList.begin();
    ++i2;
    --i2;
    i = intList.begin();
    ASSERT_EQUAL(i, i2);
}

TEST(test_it_assignment){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 1);
    intList.insert(i, 2);
    intList.insert(i, 3);
    intList.insert(i, 4);
    intList.insert(i, 5);
    i = intList.begin();
    ASSERT_EQUAL(*i, 1);
    ++i;
    ASSERT_EQUAL(*i, 2);
    ++i;
    ASSERT_EQUAL(*i, 3);
    ++i;
    ASSERT_EQUAL(*i, 4);
    ++i;
    ASSERT_EQUAL(*i, 5);
}

TEST(test_it_assignment2){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 1);
    intList.insert(i, 2);
    intList.insert(i, 3);
    intList.insert(i, 4);
    intList.insert(i, 5);
    i = intList.begin();
    List<int>::Iterator i2 = intList.begin();
    ASSERT_TRUE(i == i2);
    ++i2;
    ASSERT_TRUE(i != i2);
}

TEST(test_it_bigthree){
    List<int> intList;
    List<int>::Iterator i = intList.begin();
    intList.insert(i, 1);
    intList.insert(i, 2);
    intList.insert(i, 3);
    intList.insert(i, 4);
    intList.insert(i, 5);
    i = intList.begin();
    List<int>::Iterator i2(i);
    ASSERT_EQUAL(i, i2);
}

TEST(test_my_test){
    List<int> my_list;
    my_list.push_front(1); 
    my_list.push_front(7); 
    my_list.push_front(5);
    my_list.push_front(10); 
    my_list.push_back(8);
    List<int>::Iterator iter = my_list.begin();
    my_list.insert(iter, 2);
    ASSERT_EQUAL(my_list.front(), 2);
    ASSERT_EQUAL(my_list.size(), 6);
    iter = my_list.end();
    my_list.insert(iter, 7);
    // List<int>::Iterator iter2 = my_list.end();
    // --iter2;
    // ASSERT_EQUAL(*iter2, 7);
}

TEST(test_anything){
    List<int> intList;
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);
    ASSERT_EQUAL(intList.back(), 3);
    ASSERT_EQUAL(intList.front(), 1);
    intList.pop_front();
    intList.pop_back();
    ASSERT_EQUAL(intList.back(), 2);
    ASSERT_EQUAL(intList.front(), 2);
    List<int>::Iterator i = intList.begin();
    ASSERT_EQUAL(*i, 2);
}

TEST_MAIN()
