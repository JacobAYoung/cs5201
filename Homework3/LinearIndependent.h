#pragma once

#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

template <class T>
class LinearIndependent
{
private:
  vector<T> data;
  const double EPSILON = 0.0001;

public:
  LinearIndependent();
  LinearIndependent(int size);
  bool CheckLinearIndependent(vector<vector<T>> &matrix, const int &size);
  vector<T> GetData() const;
  double GetEpsilon() const;
};

#include "LinearIndependent.hpp"