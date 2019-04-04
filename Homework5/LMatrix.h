#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "GaussElimination.h"
#include "MatrixController.h"
#include "Matrix.h"

using namespace std;

template <class T>
class UMatrix;

/**
 * @file LMatrix.h
 * @class LMatrix
 * @author Jake Young
 * @pre LMatrix object is created
 * @post LMatrix can do calculations and can be used as a regular LMatrix
 * @brief Creates a LMatrix that has multiple methods of doing calculations for
 * that LMatrix
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class LMatrix
{
private:
  MatrixController<LMatrix<T>, T> my_controller;

public:
  LMatrix();
  /**
   * 
   * @pre Construct a new LMatrix object
   * @post A new LMatrix object is created
   * @brief Construct a new LMatrix object
   * 
   */
  LMatrix(int rows, int columns);
  /**
     * 
     * @pre Construct a new LMatrix object with set sizes
     * @post A new LMatrix object is created
     * @brief Construct a new LMatrix object
     * 
     * @param rows Number of rows
     * @param columns Number of columns
     */
  LMatrix(const Matrix<T> &source);
  /**
     * @brief Copy constructor
     * @pre A c.o. LMatrix is created and a source LMatrix object is created to be
     * copied from
     * @post Copies the source LMatrix object to the c.o.
     * @param source LMatrix object
     */
  LMatrix(const LMatrix<T> &source);
  /**
     * @brief Destroy the LMatrix object
     * @pre LMatrix object is created
     * @post c.o. LMatrix will be destroyed and deleted from memory.
     */
  ~LMatrix();
  /**
     * @brief Add a vector onto the LMatrix
     * @pre A LMatrix object is created
     * @post The vector has been added to the c.o. LMatrix
     * 
     * @param source The vector that wants to be added to the c.o. LMatrix
     */
  void PushBack(const MyVector<T> &source);
  /**
     * @brief Get the Rows object
     * @pre LMatrix object is created
     * @post Gets the number of rows from the LMatrix object
     * @return int Number of rows within the LMatrix
     */
  int GetRows() const;
  /**
     * @brief Get the Columns object
     * @pre LMatrix object is created
     * @post Gets the number of columns from the LMatrix object
     * @return int Number of columns within the LMatrix
     */
  int GetColumns() const;
  /**
     * @brief Calculate and returns the transpose of the LMatrix object
     * @pre A LMatrix object is created
     * @post Creates a temporary LMatrix object and returns the transpose of the
     * c.o. LMatrix
     * @return LMatrix<T> A copy of the LMatrix c.o. transpose
     */
  UMatrix<T> Transpose();
  /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and LMatrix object is created
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the LMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
  MyVector<T> &operator[](const int &i);
  /**
     * @brief [] operator that returns the data of the pointer at the specified
     * position but its returned as a constant value
     * @pre: The position of the data is known and LMatrix object is created
     * @post: Returns the data from the pointer of the specified position as a
     * constant value. Throws an error if the position is out of the LMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific
     * position as a constant value
     */
  MyVector<T> &operator[](const int &i) const;
  /**
     * @brief Performs the Gauss elimination process on the c.o. LMatrix and a B
     * vector to find the x vector of values
     * @pre A LMatrix object and MyVector object is created
     * @post Creates a MyVector object filled with the x values created from the
     * gauss elimination of the LMatrix and b vector. Throws an error if the size
     * of the LMatrix and B vector don't work together.
     * @param B The B vector
     * @return MyVector<T> A MyVector object filled with x values calculated
     * from the c.o. object and B vector
     */
  //MyVector<T> Eliminate(const MyVector<T> &B);
  /**
     * @brief Scalar multiplcation of a LMatrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre LMatrix object is created
     * @post LMatrix c.o. is multiplied by the value
     * @param val Value to be multiplied against LMatrix
     * @return LMatrix<T> A LMatrix that has been multiplied by the value
     */
  LMatrix<T> operator*(const T &val);
  /**
     * @brief Assignment operator that sets the rhs LMatrix object to the c.o.
     * @pre A LMatrix object is created and another to be copied from
     * @post Copies the rhs LMatrix object to the LMatrix c.o.
     * @param source LMatrix object
     * @return LMatrix<T> The c.o. is now equal to the rhs LMatrix object
     */
  LMatrix<T> &operator=(const LMatrix<T> &source);

  void CalculateLower(const Matrix<T> &source);
  T &operator()(const int &i, const int &j);
  T &operator()(const int &i, const int &j) const;
};
/**
 * @brief Equals operator. Checks to see if the two LMatrix objects are the same
 * @pre Two LMatrix objects are created
 * @post Returns true or false depending on if the LMatrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs LMatrix object
 * @param rhs LMatrix object
 * @return true If the two LMatrix objects are the same
 * @return false If the two LMatrix objects aren't the same
 */
template <typename T>
bool operator==(const LMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the two LMatrix objects are not the same
 * @pre Two LMatrix objects are created
 * @post Returns true or false depending on if the LMatrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs LMatrix object
 * @param rhs LMatrix object
 * @return true If the two LMatrix objects aren't the same
 * @return false If the two LMatrix objects are the same
 */
template <typename T>
bool operator!=(const LMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Negates every value within the LMatrix
 * @pre A LMatrix object is created
 * @post Negates every value within the LMatrix
 * 
 * @tparam T template T
 * @param source LMatrix object
 * @return LMatrix<T> A LMatrix that has every value negated
 */
template <typename T>
LMatrix<T> operator-(const LMatrix<T> &source);
/**
 * @brief Calculate LMatrix multiplication of two matricies
 * @pre Two LMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs LMatrix and rhs LMatrix to return the multiplication
 * LMatrix of the 2 matricies and returns it as a LMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return LMatrix<T> A LMatrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
LMatrix<T> operator*(const LMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const LMatrix<T> &lhs, const UMatrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const UMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const LMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate LMatrix addition of two matricies
 * @pre Two LMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs LMatrix and rhs LMatrix to return the addition
 * LMatrix of the 2 matricies and returns it as a LMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return LMatrix<T> A LMatrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
LMatrix<T> operator+(const LMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const LMatrix<T> &lhs, const UMatrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const UMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const LMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate LMatrix subtraction of two matricies
 * @pre Two LMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs LMatrix and rhs LMatrix to return the subtraction
 * LMatrix of the 2 matricies and returns it as a LMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return LMatrix<T> A LMatrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
LMatrix<T> operator-(const LMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const LMatrix<T> &lhs, const UMatrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const UMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const LMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Outputs every value within the columns and rows of the LMatrix object
 * @pre A LMatrix object is created
 * @post Outputs every value that is within the LMatrix object
 * @tparam T template T
 * @param out std::ostream object
 * @param source The LMatrix object
 * @return std::ostream& The contents within the LMatrix object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const LMatrix<T> &source);
/**
 * @brief Able to input values into the LMatrix
 * @pre A LMatrix object is created
 * @post Inputs values into the LMatrix object
 * @tparam T template T
 * @param in std::istream object
 * @param source The LMatrix object
 * @return std::istream& Sets the values of the LMatrix object
 */
template <typename T>
std::istream &operator>>(std::istream &in, LMatrix<T> &source);

#include "LMatrix.hpp"
