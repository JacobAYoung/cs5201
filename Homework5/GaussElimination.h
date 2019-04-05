#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "Matrix.h"

using namespace std;

/**
 * @file GaussElimination.h
 * @class GaussElimination
 * @author Jake Young
 * @pre GaussElimination object is created and matrix object is created along
 * with a b vector
 * @post Can calcuate the forward elimination of a matrix and b vector
 * @brief File for calculating forward elimination of a matrix and b vector.
 * double, float, etc...
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class GaussElimination
{
private:
  /**
   * @brief Forward elimination of Gauss Elimination
   * @pre: A matrix and B vector are created to calculate the forward
   * elimination. T values must be the same
   * @post: Returns a matrix that has been calculated with forward elimination
   * @param source The matrix
   * @param B The b vector
     * @return MyVector<MyVector<T>> A matrix that has been calculated with
     * forward elimination
   */
  Matrix<T> ForwardElimination(const Matrix<T> &source, const MyVector<T> &B) const;

public:
  /**
    * @brief Calculates the Gauss Elimination of a matrix and a B vector and
    * returns a x vector for the calculated values
   * @pre: A matrix and B vector are created to calculate the forward. T values
   * must be the same
     * elimination and GaussElimination object is created.
     * @post: Returns a x vector for the calculated values within the matrix and
     * B vector
    * @param source The matrix
    * @param B The b vector
     * @return MyVector<T> A x vector for the calculated values of the matrix
     * and B vector using Guass elimination (forward elimination)
    */
  MyVector<T> GaussEliminate(const Matrix<T> &source, const MyVector<T> &B) const;
  /**
   * @brief A function that completes the backsub for a upper triangular matrix.
   * @pre A vector of vectors is created with data stored and a single vector. T
   * values must be the same
   * stored with values to do the calculations.
   * @post This will return a vector of x values that were calculated from the function.
   * 
   * @param A The matrix, that is a MyVector<MyVector<T>> of data
   * @param B The MyVector<T> object that has the B values stored.
   * @return MyVector<T> 
   */
  MyVector<T> BackSub(const Matrix<T> &A, const MyVector<T> &B) const;
  /**
   * @brief A function that completes the forwardsub for a lower triangular matrix.
   * @pre A vector of vectors is created with data stored and a single vector. T
   * values must be the same
   * stored with values to do the calculations.
   * @post This will return a vector of x values that were calculated from the function.
   * 
   * @param A The matrix, that is a MyVector<MyVector<T>> of data
   * @param B The MyVector<T> object that has the B values stored.
   * @return MyVector<T> 
   */
  MyVector<T> ForwardSub(const Matrix<T> &A, const MyVector<T> &B) const;
};

#include "GaussElimination.hpp"