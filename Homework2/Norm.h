#pragma once

#include <vector>
#include <math.h>

using namespace std;

template <class T, class U>
class Norm
{
public:
  T operator()(const vector<U> &vect) const;
};

#include "Norm.hpp"