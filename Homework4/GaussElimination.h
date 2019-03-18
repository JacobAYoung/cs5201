#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"

using namespace std;

/**
 * @file GaussElimination.h
 * @author Jake Young
 * @pre GaussElimination object is created and matrix object is created along
 * with a b vector
 * @post Can calcuate the forward elimination of a matrix and b vector
 * @brief File for calculating forward elimination of a matrix and b vector
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
   * @pre: A matrix and B vector are created to calculate the forward elimination
   * @post: Returns a matrix that has been calculated with forward elimination
   * @param source The matrix
   * @param B The b vector
     * @return MyVector<MyVector<T>> A matrix that has been calculated with
     * forward elimination
   */
  MyVector<MyVector<T>> ForwardElimination(const MyVector<MyVector<T>> &source, const MyVector<T> &B);

public:
  /**
    * @brief Calculates the Gauss Elimination of a matrix and a B vector and
    * returns a x vector for the calculated values
     * @pre: A matrix and B vector are created to calculate the forward
     * elimination and GaussElimination object is created.
     * @post: Returns a x vector for the calculated values within the matrix and
     * B vector
    * @param source The matrix
    * @param B The b vector
     * @return MyVector<T> A x vector for the calculated values of the matrix
     * and B vector using Guass elimination (forward elimination)
    */
  MyVector<T> GaussEliminate(const MyVector<MyVector<T>> &source, const MyVector<T> &B);
};

#include "GaussElimination.hpp"