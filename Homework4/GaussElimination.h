#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"

using namespace std;

template <class T>
class GaussElimination
{
  public:
    MyVector<T> GaussEliminate(const MyVector<MyVector<T>> &source, const MyVector<T> &B);
};

#include "GaussElimination.hpp"