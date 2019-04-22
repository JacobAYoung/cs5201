#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "TMatrix.h"

using namespace std;

template <class T>
class DMatrix;

/**
 * @file ThomasAlgorithm.h
 * @class ThomasAlgorithm
 * @author Jake Young
 * @pre ThomasAlgorithm object is created and TMatrix object is created along
 * with a b vector
 * @post Calculates the x values for a triangular matrix. T = T types must be
 * the same and will throw an error if there is division by zero.
 * @brief Calculates the x values for a Triangular matrix.
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class ThomasAlgorithm
{
public:
  /**
 * @brief Calculates the triangular matricies x values using the Thomas Algorithm
 * @pre A triangular matrix is created with values within it and a vector of b
 * values are created as well to be used for the calculation.
 * @post T = T types must be the same and any division by zero will error out.
 * Returns a vector of x values from the calculation.
 * 
 * @param source TMatrix object of triangular values
 * @param b MyVector object of B values
 * @return MyVector<T> A MyVector object of x values
 */
  MyVector<T> ThomasAlg(const TMatrix<T> &source, const MyVector<T> b) const;
};

#include "ThomasAlgorithm.hpp"