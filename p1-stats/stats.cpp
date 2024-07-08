// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include <cassert>
#include <vector>
#include <cmath>
#include <iostream>
#include "p1_library.h"
using namespace std;
vector<vector<double> > summarize(vector<double> v) {
  // summary of the dataset as (value, frequency) pairs
  assert(!v.empty());

  vector<vector<double> > summary;
  sort(v);
  double frequency = 1;
  
  for (size_t i=0; i<v.size()-1;i++){
    if (v[i] == v[i+1]){
      frequency++;
    }
    else{
      vector<double> pair;
      pair.push_back(v[i]);
      pair.push_back(frequency);
      frequency = 1;
      summary.push_back(pair);
    }
    if (i == v.size()-2){
      vector<double> pair;
      pair.push_back(v[i+1]);
      pair.push_back(frequency);
      summary.push_back(pair);
    }
  }
  return summary;
}
int count(vector<double> v) { //returns the count of the numbers in v
  int c = static_cast<int>(v.size());
  return c; 
}
double sum(vector<double> v) { //returns the sum of the numbers in v
  assert(!v.empty());
  double sumOfNum = 0;
  for(size_t i=0; i<v.size(); i++){
    sumOfNum = sumOfNum + v[i];
  }
  return sumOfNum;
}
double mean(vector<double> v) { //returns the arithmetic mean of the numbers in v
  assert(!v.empty());
  double meanOfNum = 0;
  double sumOfNum = sum(v);
  int countOfNum = count(v);
  meanOfNum = sumOfNum / countOfNum;
  return meanOfNum;
}
double median(vector<double> v) { //returns the sample median of the numbers in v
  assert(!v.empty());
  sort(v);

  int s = static_cast<int>(v.size());
  if(s % 2 != 0){
    return v[s/2];
  }
  else{
    return (v[(s-1)/2]+v[s/2])/2.0;
  }
}
double mode(vector<double> v) { //returns the mode of the numbers in v
  assert(!v.empty());
  sort(v);
  
  double number = v[0];
  double mode = number;
  int count = 1;
  int modeCount = 1;

  for (size_t i=1; i<v.size(); i++){
    if(v[i] == number){
      count++;
    }
    else{
      if(count > modeCount){
        modeCount = count;
        mode = number;
      }
      count = 1;
      number = v[i];
    }
  }

  return mode;
}
double min(vector<double> v) { //returns the min number in v
  assert(!v.empty());
  sort(v);

  return v[0];
}
double max(vector<double> v) { //returns the max number in v
  assert(!v.empty());
  sort(v);
  int size = static_cast<int>(v.size());

  return v[size-1];
}
double stdev(vector<double> v) { //returns the corrected sample standard deviation of the numbers in v
  assert(v.size()>1);
  double meanOfNum = mean(v);
  int count = static_cast<int>(v.size());
  double sum = 0.0;
  double stdev;

  for(size_t i=0; i<v.size(); i++){
    sum = sum + (v[i]-meanOfNum)*(v[i]-meanOfNum);
  }
  stdev = sqrt(sum/(count-1));
  return stdev;
}
double percentile(vector<double> v, double p) { //returns the percentile p of the numbers in v like Microsoft Excel.
  assert(!v.empty());
  sort(v);
  int size = static_cast<int>(v.size());
  double percent;

  if (p != 1){
  double n = p*(size-1)+1;
  double fractpart = 0;
  double intpart = 0;
  fractpart = modf(n, &intpart);

  percent = v[intpart-1] + fractpart * (v[intpart]-v[intpart-1]);
  }
  else{
    percent = v[size-1];
  }

  return percent;
}