#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"

using namespace std;

template <class T>
class Matrix
{
  private:
    int numRows;
    int numColumns;
    MyVector<MyVector<T>> myVect;

  public:
    Matrix();
    Matrix(int rows, int columns);
    void PushBack(const MyVector<T> &source);
    int GetRows() const;
    int GetColumns() const;
    MyVector<T> &operator[](const int &i);
    MyVector<T> &operator[](const int &i) const;
};

template <class T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &source);

#include "Matrix.hpp"
