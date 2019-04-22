#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "SMatrix.h"
#include "LMatrix.h"

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
class CholeskyDecomposition
{
  public:
    LMatrix<T> CholeskyDecomp(const SMatrix<T> &source) const;
};

#include "CholeskyDecomposition.hpp"