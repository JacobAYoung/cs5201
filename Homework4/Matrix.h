#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "GaussElimination.h"

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
    Matrix<T> Transpose();
    MyVector<T> &operator[](const int &i);
    MyVector<T> &operator[](const int &i) const;
    MyVector<T> Eliminate(const MyVector<T> &B);
};

template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs);

template <class T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &source);

#include "Matrix.hpp"
