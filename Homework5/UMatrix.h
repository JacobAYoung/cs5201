#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "GaussElimination.h"
#include "MatrixController.h"
#include "Matrix.h"
#include "IMatrix.h"

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
class UMatrix : public IMatrix<UMatrix<T>, T>
{
private:
  /**
   * @brief A matrixcontroller base class to be used for common functionallity
   * over multiple kinds of matricies.
   * 
   */
  MatrixController<UMatrix<T>, T> my_controller;

public:
  /**
 * @brief Construct a new UMatrix object
 * 
 */
  UMatrix();
  /**
   * @brief Construct a new UMatrix object
   * @pre A UMatrix object is being created with specified sizes
   * @post a UMatrix object is created with specified sizes.
   * 
   * @param rows number of rows
   * @param columns number of columns
   */
  UMatrix(int rows, int columns);
  /**
     * 
     * @pre Construct a new UMatrix object with set sizes
     * @post A new UMatrix object is created
     * @brief Construct a new UMatrix object from a dense matrix
     * 
     * @param source A dense matrix object
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
 * @brief Construct a new UMatrix object
 * @pre Moves the UMatrix object from the source
 * @post moved the UMatrix source object to the c.o.
 * 
 * @param source UMatrix source object
 */
  UMatrix(UMatrix<T> &&source);
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
   * @brief Creates a LMatrix from the transpose of the umatrix
   * @pre A Umatrix object is created and filled with data
   * @post A Lmatrix is returned from the umatrix being transposed.
   * 
   * @return LMatrix<T> A Lmatrix object
   */
  LMatrix<T> Transpose();
  /**
   * @brief Calculates the upper triangular matrix from a dense matrix.
   * @pre The dense matrix must have values to make it a dense matrix to solve
   * for the upper triangular matrix.
   * @post Computes and saves the data for a upper triangular matrix
   * 
   * @param source A dense matrix
   */
  void CalculateUpper(const Matrix<T> &source);
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
     * @brief Scalar multiplcation of a UMatrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre UMatrix object is created
     * @post UMatrix c.o. is multiplied by the value
     * @param val Value to be multiplied against UMatrix
     * @return UMatrix<T> A UMatrix that has been multiplied by the value
     */
  UMatrix<T> operator*(const T &val) const;
  /**
     * @brief Assignment operator that sets the rhs UMatrix object to the c.o.
     * @pre A UMatrix object is created and another to be copied from
     * @post Copies the rhs UMatrix object to the UMatrix c.o.
     * @param source UMatrix object
     * @return UMatrix<T> The c.o. is now equal to the rhs UMatrix object
     */
  UMatrix<T> &operator=(const UMatrix<T> &source);
  /**
     * @brief Assignment operator that sets the rhs Matrix object to the c.o.
     * @pre A UMatrix object is created and a Matrix object to be copied from
     * @post Copies the rhs Matrix object to the UMatrix c.o.
     * @param source Matrix object
     * @return UMatrix<T> The c.o. is now equal to the rhs Matrix object
     */
  UMatrix<T> &operator=(const Matrix<T> &source);
  /**
   * @brief Works as the [] operator. To get data from the matrix.
   * @pre A umatrix must be created and have data stored within it. i and j must
   * be positive and within the bounds of the matrix otherwise it will throw an error.
   * @post Data at position i and j will be returned. 
   * 
   * @param i int value at position i
   * @param j int value at position j
   * @return T& A element at the data position
   */
  T &operator()(const int &i, const int &j);
  /**
   * @brief Works as the [] operator. To get data from the matrix as a constant value.
   * @pre A umatrix must be created and have data stored within it. i and j must
   * be positive and within the bounds of the matrix otherwise it will throw an error.
   * @post Data at position i and j will be returned as a constant value. 
   * 
   * @param i int value at position i
   * @param j int value at position j
   * @return T& A element at the data position as a constant value
   */
  T &operator()(const int &i, const int &j) const;
};
/**
 * @brief Equals operator. Checks to see if the two UMatrix objects are the same
 * @pre Two UMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs UMatrix object
 * @param rhs UMatrix object
 * @return true If the two UMatrix objects are the same
 * @return false If the two UMatrix objects aren't the same
 */
template <typename T>
bool operator==(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the UMatrix and LMatrix objects are the same
 * @pre UMatrix and LMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs UMatrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const UMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the UMatrix and Matrix objects are the same
 * @pre UMatrix and Matrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs UMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const UMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the UMatrix and LMatrix objects are the same
 * @pre Matrix and UMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs UMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const Matrix<T> &lhs, const UMatrix<T> &rhs);
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
bool operator!=(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the UMatrix and LMatrix objects
 * are not the same
 * @pre UMatrix and LMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs UMatrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const UMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the UMatrix and Matrix objects
 * are not the same
 * @pre UMatrix and Matrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs UMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const UMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the Matrix and UMatrix objects
 * are not the same
 * @pre Matrix and UMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs UMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const Matrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Negates every value within the UMatrix
 * @pre A UMatrix object is created
 * @post Negates every value within the UMatrix
 * 
 * @tparam T template T
 * @param source UMatrix object
 * @return UMatrix<T> A UMatrix that has every value negated
 */
template <typename T>
UMatrix<T> operator-(const UMatrix<T> &source);
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
 * @brief Calculate Matrix multiplication of two matricies (umatrix and lmatrix)
 * @pre LMatrix object and UMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs UMatrix and rhs LMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const UMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (matrix and UMatrix)
 * @pre Matrix object and UMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs Matrix and rhs UMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (UMatrix and matrix)
 * @pre UMatrix object and Matrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs UMatrix and rhs Matrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const UMatrix<T> &lhs, const Matrix<T> &rhs);
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
template <typename T>
UMatrix<T> operator+(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (umatrix and lmatrix)
 * @pre UMatrix and LMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs UMatrix and rhs LMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const UMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (matrix and UMatrix)
 * @pre Matrix and UMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs Matrix and rhs UMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (UMatrix and matrix)
 * @pre UMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs UMatrix and rhs Matrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const UMatrix<T> &lhs, const Matrix<T> &rhs);
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
template <typename T>
UMatrix<T> operator-(const UMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (umatrix and Lmatrix)
 * @pre LMatrix and UMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs UMatrix and rhs LMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const UMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (matrix and UMatrix)
 * @pre Matrix and UMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs Matrix and rhs UMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (UMatrix and matrix)
 * @pre UMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs UMatrix and rhs Matrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs UMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const UMatrix<T> &lhs, const Matrix<T> &rhs);
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
