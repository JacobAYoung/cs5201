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
class ThomasAlgorithm
{
public:
  MyVector<T> ThomasAlg(const TMatrix<T> &source, const MyVector<T> b) const;
};

#include "ThomasAlgorithm.hpp"