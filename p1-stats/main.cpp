// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <string>
#include <vector> 
#include <cassert>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;
int main() {

  string filename;
  string column_name;

  cout << "enter a filename" << endl;
  cin >> filename;
  cout << "enter a column name" << endl;
  cin >> column_name;
  cout << "reading column " << column_name << " from " << filename << endl;

  vector<double> numbers = extract_column(filename, column_name);

  //summarize
  vector<vector<double> > summary = summarize(numbers);
  cout << "Summary (value: frequency)" << endl;
  for (size_t i = 0; i < summary.size(); i++)
  {
    for (size_t j = 0; j < 1; j++)
    {
        cout << summary[i][0] << ": " << summary[i][1] << endl;
    }
  }
  cout << ""<< endl;
  //count
  cout << "count = " << count(numbers) << endl;
  //sum
  cout << "sum = " << sum(numbers) << endl;
  //mean
  cout << "mean = " << mean(numbers) << endl;
  //stdev
  cout << "stdev = " << stdev(numbers) << endl;
  //median
  cout << "median = " << median(numbers) << endl;
  //mode
  cout << "mode = " << mode(numbers) << endl;
  //min
  cout << "min = " << min(numbers) << endl;
  //max
  cout << "max = " << max(numbers) << endl;
  //percentile
  cout << "  0th percentile = " << percentile(numbers, 0) << endl;
  cout << " 25th percentile = " << percentile(numbers, 0.25) << endl;
  cout << " 50th percentile = " << percentile(numbers, 0.5) << endl;
  cout << " 75th percentile = " << percentile(numbers, 0.75) << endl;
  cout << "100th percentile = " << percentile(numbers, 1) << endl;

}