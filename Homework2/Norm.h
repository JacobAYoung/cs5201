///Author: Jake Young
///Date: 2-15-2019
///PRE: Norm object is created
///POST: This class SO FAR is used to calcuate the norm of a vector of objects magnitude.

#pragma once

#include <vector>
#include <math.h>

using namespace std;

template <class T, class U>
class Norm
{
public:
  //operator(): () operator That calculates the norm of the vector of objects
  //pre: The vector is filled with some kind of data or object
  //post: The sum of the magnitudes are calculated and returned
  T operator()(const vector<U> &vect) const;
};

#include "Norm.hpp"