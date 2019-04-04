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
class LMatrix;

/**
 * @file UMatrix.h
 * @class UMatrix
 * @author Jake Young
 * @pre UMatrix object is created
 * @post UMatrix can do calculations and can be used as a regular UMatrix
 * @brief Creates a UMatrix that has multiple methods of doing calculations for
 * that UMatrix
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class UMatrix
{
private:
  MatrixController<UMatrix<T>, T> my_controller;
  /**
     * @brief Number of rows
     * 
     */
  int numRows;
  /**
     * @brief Number of columns
     * 
     */
  int numColumns;
  /**
     * @brief vector of a vector where the data will be stored
     * 
     */
  MyVector<MyVector<T>> myVect;

public:
  UMatrix();
  /**
   * 
   * @pre Construct a new UMatrix object
   * @post A new UMatrix object is created
   * @brief Construct a new UMatrix object
   * 
   */
  UMatrix(int rows, int columns);
  /**
     * 
     * @pre Construct a new UMatrix object with set sizes
     * @post A new UMatrix object is created
     * @brief Construct a new UMatrix object
     * 
     * @param rows Number of rows
     * @param columns Number of columns
     */
  UMatrix(const Matrix<T> &source);
  /**
     * @brief Copy constructor
     * @pre A c.o. UMatrix is created and a source UMatrix object is created to be
     * copied from
     * @post Copies the source UMatrix object to the c.o.
     * @param source UMatrix object
     */
  UMatrix(const UMatrix<T> &source);
  /**
     * @brief Destroy the UMatrix object
     * @pre UMatrix object is created
     * @post c.o. UMatrix will be destroyed and deleted from memory.
     */
  ~UMatrix();
  /**
     * @brief Add a vector onto the UMatrix
     * @pre A UMatrix object is created
     * @post The vector has been added to the c.o. UMatrix
     * 
     * @param source The vector that wants to be added to the c.o. UMatrix
     */
  void PushBack(const MyVector<T> &source);
  /**
     * @brief Get the Rows object
     * @pre UMatrix object is created
     * @post Gets the number of rows from the UMatrix object
     * @return int Number of rows within the UMatrix
     */
  int GetRows() const;
  /**
     * @brief Get the Columns object
     * @pre UMatrix object is created
     * @post Gets the number of columns from the UMatrix object
     * @return int Number of columns within the UMatrix
     */
  int GetColumns() const;
  /**
     * @brief Calculate and returns the transpose of the UMatrix object
     * @pre A UMatrix object is created
     * @post Creates a temporary UMatrix object and returns the transpose of the
     * c.o. UMatrix
     * @return UMatrix<T> A copy of the UMatrix c.o. transpose
     */
  UMatrix<T> Transpose();
  /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and UMatrix object is created
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the UMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
  MyVector<T> &operator[](const int &i);
  /**
     * @brief [] operator that returns the data of the pointer at the specified
     * position but its returned as a constant value
     * @pre: The position of the data is known and UMatrix object is created
     * @post: Returns the data from the pointer of the specified position as a
     * constant value. Throws an error if the position is out of the UMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific
     * position as a constant value
     */
  MyVector<T> &operator[](const int &i) const;
  /**
     * @brief Performs the Gauss elimination process on the c.o. UMatrix and a B
     * vector to find the x vector of values
     * @pre A UMatrix object and MyVector object is created
     * @post Creates a MyVector object filled with the x values created from the
     * gauss elimination of the UMatrix and b vector. Throws an error if the size
     * of the UMatrix and B vector don't work together.
     * @param B The B vector
     * @return MyVector<T> A MyVector object filled with x values calculated
     * from the c.o. object and B vector
     */
  //MyVector<T> Eliminate(const MyVector<T> &B);
  /**
     * @brief Scalar multiplcation of a UMatrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre UMatrix object is created
     * @post UMatrix c.o. is multiplied by the value
     * @param val Value to be multiplied against UMatrix
     * @return UMatrix<T> A UMatrix that has been multiplied by the value
     */
  UMatrix<T> operator*(const T &val);
  /**
     * @brief Assignment operator that sets the rhs UMatrix object to the c.o.
     * @pre A UMatrix object is created and another to be copied from
     * @post Copies the rhs UMatrix object to the UMatrix c.o.
     * @param source UMatrix object
     * @return UMatrix<T> The c.o. is now equal to the rhs UMatrix object
     */
  UMatrix<T> &operator=(const UMatrix<T> &source);

  void CalculateUpper(const Matrix<T> &source);
  T &operator()(const int &i, const int &j);
  T &operator()(const int &i, const int &j) const;
};
/**
 * @brief Equals operator. Checks to see if the two UMatrix objects are the same
 * @pre Two UMatrix objects are created
 * @post Returns true or false depending on if the UMatrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs UMatrix object
 * @param rhs UMatrix object
 * @return true If the two UMatrix objects are the same
 * @return false If the two UMatrix objects aren't the same
 */
// template <typename T>
// bool operator==(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the two UMatrix objects are not the same
 * @pre Two UMatrix objects are created
 * @post Returns true or false depending on if the UMatrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs UMatrix object
 * @param rhs UMatrix object
 * @return true If the two UMatrix objects aren't the same
 * @return false If the two UMatrix objects are the same
 */
// template <typename T>
// bool operator!=(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Negates every value within the UMatrix
 * @pre A UMatrix object is created
 * @post Negates every value within the UMatrix
 * 
 * @tparam T template T
 * @param source UMatrix object
 * @return UMatrix<T> A UMatrix that has every value negated
 */
// template <typename T>
// UMatrix<T> operator-(const UMatrix<T> &source);
/**
 * @brief Calculate UMatrix multiplication of two matricies
 * @pre Two UMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs UMatrix and rhs UMatrix to return the multiplication
 * UMatrix of the 2 matricies and returns it as a UMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return UMatrix<T> A UMatrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
UMatrix<T> operator*(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate UMatrix addition of two matricies
 * @pre Two UMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs UMatrix and rhs UMatrix to return the addition
 * UMatrix of the 2 matricies and returns it as a UMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return UMatrix<T> A UMatrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
// template <typename T>
// UMatrix<T> operator+(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate UMatrix subtraction of two matricies
 * @pre Two UMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs UMatrix and rhs UMatrix to return the subtraction
 * UMatrix of the 2 matricies and returns it as a UMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return UMatrix<T> A UMatrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
// template <typename T>
// UMatrix<T> operator-(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Outputs every value within the columns and rows of the UMatrix object
 * @pre A UMatrix object is created
 * @post Outputs every value that is within the UMatrix object
 * @tparam T template T
 * @param out std::ostream object
 * @param source The UMatrix object
 * @return std::ostream& The contents within the UMatrix object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const UMatrix<T> &source);
/**
 * @brief Able to input values into the UMatrix
 * @pre A UMatrix object is created
 * @post Inputs values into the UMatrix object
 * @tparam T template T
 * @param in std::istream object
 * @param source The UMatrix object
 * @return std::istream& Sets the values of the UMatrix object
 */
template <typename T>
std::istream &operator>>(std::istream &in, UMatrix<T> &source);

#include "UMatrix.hpp"
