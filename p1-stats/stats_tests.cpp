/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void test_sum_small_data_set();
void test_count();
void test_summarize();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();

// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  // Call your test functions here
  test_count();
  test_summarize();
  test_mean();
  test_median();
  test_mode();
  test_min();
  test_max();
  test_stdev();
  test_percentile();


  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.

void test_summarize(){
  cout << "test_summarize" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(1);
  data.push_back(2);
  data.push_back(2);
  data.push_back(2);

  vector<vector<double> > summary = summarize(data);
  
  cout << "Summary (value: frequency)" << endl;
  for (size_t i = 0; i < summary.size(); i++)
  {
    for (size_t j = 0; j < 1; j++)
    {
        cout << summary[i][0] << ": " << summary[i][1] << endl;
    }
  }
}

void test_count(){
  cout << "test_count" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);

  assert(count(data) == 4);

  cout << "PASS!" << endl;
}

void test_mean(){
  cout << "test_mean" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);

  assert(mean(data) == 2.4);

  cout << "PASS!" << endl;
}

void test_median(){
  cout << "test_median" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);


  assert(median(data) == 2);

  cout << "PASS!" << endl;
}

void test_mode(){
  cout << "test_mode" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);

  assert(mode(data) == 2);

  cout << "PASS!" << endl;
}

void test_min(){
  cout << "test_min" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);

  assert(min(data) == 1);

  cout << "PASS!" << endl;
}

void test_max(){
  cout << "test_max" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);

  assert(max(data) == 4);

  cout << "PASS!" << endl;
}

void test_stdev(){
  cout << "test_stdev" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);
  double stdeviation = stdev(data);

  cout << "Standard deviation is " << stdeviation << endl;
}

void test_percentile(){
  cout << "test_percentile" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(2);
  data.push_back(5);

  double percent = percentile(data, 0.5);

  cout << "50th percentile is " << percent << endl;
}
