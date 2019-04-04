#ifndef IMATRIX_H
#define IMATRIX_H

#include "MyVector.h"

template <class M, class T>
class IMatrix
{
public:
  virtual MyVector<T> Eliminate(const MyVector<T> &B) = 0;
  virtual void PushBack(const MyVector<T> &source) = 0;
  virtual int GetRows() const = 0;
  virtual int GetColumns() const = 0;
  virtual MyVector<T> &operator[](const int &i) = 0;
  virtual MyVector<T> &operator[](const int &i) const = 0;
  virtual M &operator=(const M &source) = 0;
  virtual M operator*(const T &val) const = 0;
  virtual ~IMatrix() {}
};

#endif