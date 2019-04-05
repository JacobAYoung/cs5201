#ifndef IMATRIX_H
#define IMATRIX_H

#include "MyVector.h"

/**
 * @file IMatrix.h
 * @class IMatrix
 * @author Jake Young
 * @pre A class that will inherit from this class is created
 * @post This class contains the definitions of functions to be used within the
 * inherited classes.
 * @brief This abstract class is used to define a matrix
 * that Matrix. 
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class M, class T>
class IMatrix
{
public:
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