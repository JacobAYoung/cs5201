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

  public:
    MyVector();
    MyVector(int n);
    MyVector(const MyVector &source);
    ~MyVector();
    float &operator[](int i);
    int numElements();
    MyVector &operator=(const MyVector &source);
    MyVector &operator=(float numb);
    void setSize(int n);
};

#include "MyVector.hpp"