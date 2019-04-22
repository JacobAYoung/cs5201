#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "SMatrix.h"
#include "LMatrix.h"

using namespace std;

/**
 * @file CholeskyDecomposition.h
 * @class CholeskyDecomposition
 * @author Jake Young
 * @pre CholeskyDecomposition object is created and smatrix object is created
 * for cholesky to work properly.
 * @post Calculates the lower triangular matrix for a symmetric matrix. 
 * @brief File for calculating lower triangular matrix for a symmetric matrix.
 * Template type t is assumed any value type such as int, double, etc..
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class CholeskyDecomposition
{
public:
  /**
   * @brief Cholesky Decomposition function that calculates the lower triangular
   * matrix for a symmetric matrix
   * @pre A smatrix object is created and has data to be used for the calculation.
   * @post A LMatrix object is returned from the calculations of the SMatrix.
   * The function will throw an error if there is division by zero.
   * 
   * @param source A symmetric matrix
   * @return LMatrix<T> A lower bound matrix
   */
  LMatrix<T> CholeskyDecomp(const SMatrix<T> &source) const;
};

#include "CholeskyDecomposition.hpp"