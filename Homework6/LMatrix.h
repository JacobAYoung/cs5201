#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "MatrixController.h"
#include "Matrix.h"
#include "IMatrix.h"

using namespace std;

template <class T>
class UMatrix;

template <class T>
class SMatrix;

template <class T>
class DMatrix;

template <class T>
class TMatrix;

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
class LMatrix : public IMatrix<LMatrix<T>, T>
{
private:
  /**
   * @brief A matrixcontroller base class to be used for common functionallity
   * over multiple kinds of matricies.
   * 
   */
  MatrixController<LMatrix<T>, T> my_controller;

public:
  /**
 * @brief Construct a new LMatrix object
 * 
 */
  LMatrix();
  /**
   * @brief Construct a new LMatrix object
   * 
   * @param rows number of rows 
   * @param columns number of columns
   */
  LMatrix(int rows, int columns);
  /**
   * @brief Copy constructor
   * @pre A c.o. LMatrix is created and a source Matrix object is created to be
   * copied from
   * @post Copies the source Matrix object to the c.o. and then sets the values
   * as a lower matrix
    * @param source Matrix object
    */
  LMatrix(const Matrix<T> &source);
  /**
 * @brief Construct a new LMatrix object
 * @pre A lmatrix object is created to be copied from
 * @post The lmatrix is copied from
 * 
 * @param source lmatrix object to be copied from
 */
  LMatrix(const LMatrix<T> &source);
  /**
     * @brief Destroy the LMatrix object
     * @pre LMatrix object is created
     * @post c.o. LMatrix will be destroyed and deleted from memory.
     */
  ~LMatrix();
  /**
 * @brief Construct a new LMatrix object
 * @pre Moves the lmatrix object from the source
 * @post moved the lmatrix source object to the c.o.
 * 
 * @param source LMatrix source object
 */
  LMatrix(LMatrix<T> &&source);
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
   * @brief Calculates the lower triangular matrix from a dense matrix.
   * @pre The dense matrix must have values to make it a dense matrix to solve
   * for the lower triangular matrix.
   * @post Computes and saves the data for a lower triangular matrix
   * 
   * @param source A dense matrix
   */
  void CalculateLower(const Matrix<T> &source);
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
     * @brief Scalar multiplcation of a LMatrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre LMatrix object is created
     * @post LMatrix c.o. is multiplied by the value
     * @param val Value to be multiplied against LMatrix
     * @return LMatrix<T> A LMatrix that has been multiplied by the value
     */
  LMatrix<T> operator*(const T &val) const;
  /**
     * @brief Assignment operator that sets the rhs LMatrix object to the c.o.
     * @pre A LMatrix object is created and another to be copied from
     * @post Copies the rhs LMatrix object to the LMatrix c.o.
     * @param source LMatrix object
     * @return LMatrix<T> The c.o. is now equal to the rhs LMatrix object
     */
  LMatrix<T> &operator=(const LMatrix<T> &source);
  /**
     * @brief Assignment operator that sets the rhs Matrix object to the c.o.
     * @pre A LMatrix object is created and a Matrix object to be copied from
     * @post Copies the rhs Matrix object to the LMatrix c.o.
     * @param source Matrix object
     * @return LMatrix<T> The c.o. is now equal to the rhs Matrix object
     */
  LMatrix<T> &operator=(const Matrix<T> &source);
  /**
   * @brief Works as the [] operator. To get data from the matrix.
   * @pre A lmatrix must be created and have data stored within it. i and j must
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
   * @pre A lmatrix must be created and have data stored within it. i and j must
   * be positive and within the bounds of the matrix otherwise it will throw an error.
   * @post Data at position i and j will be returned as a constant value. 
   * 
   * @param i int value at position i
   * @param j int value at position j
   * @return T& A element at the data position as a constant value
   */
  T &operator()(const int &i, const int &j) const;

  Matrix<T> add(const IMatrix<Matrix<T>, T> &source) const;
  Matrix<T> subtract(const IMatrix<Matrix<T>, T> &source) const;
  Matrix<T> multiply(const IMatrix<Matrix<T>, T> &source) const;
  bool equals(const IMatrix<Matrix<T>, T> &source) const;

  Matrix<T> add(const IMatrix<TMatrix<T>, T> &source) const;
  Matrix<T> subtract(const IMatrix<TMatrix<T>, T> &source) const;
  Matrix<T> multiply(const IMatrix<TMatrix<T>, T> &source) const;
  bool equals(const IMatrix<TMatrix<T>, T> &source) const;

  Matrix<T> add(const IMatrix<LMatrix<T>, T> &source) const;
  Matrix<T> subtract(const IMatrix<LMatrix<T>, T> &source) const;
  Matrix<T> multiply(const IMatrix<LMatrix<T>, T> &source) const;
  bool equals(const IMatrix<LMatrix<T>, T> &source) const;

  Matrix<T> add(const IMatrix<UMatrix<T>, T> &source) const;
  Matrix<T> subtract(const IMatrix<UMatrix<T>, T> &source) const;
  Matrix<T> multiply(const IMatrix<UMatrix<T>, T> &source) const;
  bool equals(const IMatrix<UMatrix<T>, T> &source) const;

  Matrix<T> add(const IMatrix<SMatrix<T>, T> &source) const;
  Matrix<T> subtract(const IMatrix<SMatrix<T>, T> &source) const;
  Matrix<T> multiply(const IMatrix<SMatrix<T>, T> &source) const;
  bool equals(const IMatrix<SMatrix<T>, T> &source) const;

  Matrix<T> add(const IMatrix<DMatrix<T>, T> &source) const;
  Matrix<T> subtract(const IMatrix<DMatrix<T>, T> &source) const;
  Matrix<T> multiply(const IMatrix<DMatrix<T>, T> &source) const;
  bool equals(const IMatrix<DMatrix<T>, T> &source) const;
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
 * @brief Equals operator. Checks to see if the LMatrix and UMatrix objects are the same
 * @pre LMatrix and UMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs LMatrix object
 * @param rhs UMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const LMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the LMatrix and Matrix objects are the same
 * @pre LMatrix and Matrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs LMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const LMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the Matrix and LMatrix objects are the same
 * @pre Matrix and LMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const Matrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
bool operator==(const LMatrix<T> &lhs, const SMatrix<T> &rhs);

template <typename T>
bool operator==(const SMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
bool operator==(const LMatrix<T> &lhs, const DMatrix<T> &rhs);

template <typename T>
bool operator==(const LMatrix<T> &lhs, const TMatrix<T> &rhs);
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
 * @brief Not Equals operator. Checks to see if the LMatrix and UMatrix objects
 * are not the same
 * @pre LMatrix and UMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs LMatrix object
 * @param rhs UMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const LMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the LMatrix and Matrix objects
 * are not the same
 * @pre LMatrix and Matrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs LMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const LMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the Matrix and LMatrix objects
 * are not the same
 * @pre Matrix and LMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const Matrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const SMatrix<T> &rhs);

template <typename T>
bool operator!=(const SMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const DMatrix<T> &rhs);

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const TMatrix<T> &rhs);
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
/**
 * @brief Calculate Matrix multiplication of two matricies (lmatrix and umatrix)
 * @pre LMatrix object and UMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs LMatrix and rhs UMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const LMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (matrix and LMatrix)
 * @pre Matrix object and LMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs Matrix and rhs LMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (lmatrix and matrix)
 * @pre LMatrix object and Matrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs LMatrix and rhs Matrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const LMatrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const SMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const LMatrix<T> &lhs, const SMatrix<T> &rhs);

template <typename T>
LMatrix<T> operator*(const LMatrix<T> &lhs, const DMatrix<T> &rhs);

template <typename T>
Matrix<T> operator*(const LMatrix<T> &lhs, const TMatrix<T> &rhs);
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
/**
 * @brief Calculate LMatrix addition of two matricies (lmatrix and Umatrix)
 * @pre LMatrix and UMatrix objects are created and the lhs column size is the same as
 * the rhs row size. T types must be the same
 * @post Calculates the lhs LMatrix and rhs UMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const LMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (matrix and lmatrix)
 * @pre Matrix and LMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs Matrix and rhs LMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (lmatrix and matrix)
 * @pre lMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs lMatrix and rhs Matrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const LMatrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const SMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const LMatrix<T> &lhs, const SMatrix<T> &rhs);

template <typename T>
LMatrix<T> operator+(const LMatrix<T> &lhs, const DMatrix<T> &rhs);

template <typename T>
Matrix<T> operator+(const LMatrix<T> &lhs, const TMatrix<T> &rhs);
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
/**
 * @brief Calculate subtraction of two matricies (lmatrix and Umatrix)
 * @pre LMatrix and UMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs LMatrix and rhs UMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs LMatrix object of the left hand side
 * @param rhs UMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const LMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (matrix and Lmatrix)
 * @pre Matrix and lMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs Matrix and rhs LMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (lmatrix and matrix)
 * @pre LMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs lMatrix and rhs Matrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs lMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const LMatrix<T> &lhs, const Matrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const SMatrix<T> &lhs, const LMatrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const LMatrix<T> &lhs, const SMatrix<T> &rhs);

template <typename T>
LMatrix<T> operator-(const LMatrix<T> &lhs, const DMatrix<T> &rhs);

template <typename T>
Matrix<T> operator-(const LMatrix<T> &lhs, const TMatrix<T> &rhs);
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
