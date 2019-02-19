#pragma once

#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

class MyVector
{
  private:
    int numElements;
    float *ptr_to_data;
    void copy(const MyVector &source);

  public:
    MyVector();
    MyVector(int n);
    MyVector(const MyVector &source);
    ~MyVector();
    float &operator[](int i);
    int GetNumElements();
    MyVector &operator=(const MyVector &source);
    MyVector &operator=(const float val);
    void SetSize(const int n);
};

#include "MyVector.hpp"