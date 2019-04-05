#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "GaussElimination.h"
#include "IMatrix.h"
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * @file Matrix.h
 * @class Matrix
 * @author Jake Young
 * @pre Matrix object is created
 * @post Matrix can do calculations and can be used as a regular Matrix
 * @brief Creates a Matrix that has multiple methods of doing calculations for
 * that Matrix. We assume that template T must be some kind of type like int,
 * double, float, etc...
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class Matrix : public IMatrix<Matrix<T>, T>
{
private:
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

  //MatrixController<Matrix<T>, T> my_controller;
  /**
    * @brief Copy function that copies all the data from the source to the c.o.
    * Matrix
    * @pre Matrix object is created and another Matrix object is created to be
    * copied from
    * @post Copies all the data from the source Matrix object and replaces the
    * c.o. data values
    * @param source Matrix object
  */
  void copy(const Matrix<T> &source);

public:
  /**
   * 
   * @pre Construct a new Matrix object
   * @post A new Matrix object is created
   * @brief Construct a new Matrix object
   * 
   */
  Matrix();
  /**
     * 
     * @pre Construct a new Matrix object with set sizes
     * @post A new Matrix object is created
     * @brief Construct a new Matrix object
     * 
     * @param rows Number of rows
     * @param columns Number of columns
     */
  Matrix(int rows, int columns);
  /**
     * @brief Copy constructor
     * @pre A c.o. Matrix is created and a source Matrix object is created to be
     * copied from
     * @post Copies the source Matrix object to the c.o.
     * @param source Matrix object
     */
  Matrix(const Matrix<T> &source);
  /**
     * @brief Destroy the Matrix object
     * @pre Matrix object is created
     * @post c.o. Matrix will be destroyed and deleted from memory.
     */
  ~Matrix();

  Matrix(Matrix<T> &&source);
  /**
     * @brief Add a vector onto the Matrix
     * @pre A Matrix object is created
     * @post The vector has been added to the c.o. Matrix
     * 
     * @param source The vector that wants to be added to the c.o. Matrix
     */
  void PushBack(const MyVector<T> &source);
  /**
     * @brief Get the Rows object
     * @pre Matrix object is created
     * @post Gets the number of rows from the Matrix object
     * @return int Number of rows within the Matrix
     */
  int GetRows() const;
  /**
     * @brief Get the Columns object
     * @pre Matrix object is created
     * @post Gets the number of columns from the Matrix object
     * @return int Number of columns within the Matrix
     */
  int GetColumns() const;
  /**
     * @brief Calculate and returns the transpose of the Matrix object
     * @pre A Matrix object is created
     * @post Creates a temporary Matrix object and returns the transpose of the
     * c.o. Matrix
     * @return Matrix<T> A copy of the Matrix c.o. transpose
     */
  Matrix<T> Transpose();
  /**
     * @brief Performs the Gauss elimination process on the c.o. Matrix and a B
     * vector to find the x vector of values
     * @pre A Matrix object and MyVector object is created
     * @post Creates a MyVector object filled with the x values created from the
     * gauss elimination of the Matrix and b vector. Throws an error if the size
     * of the Matrix and B vector don't work together.
     * @param B The B vector
     * @return MyVector<T> A MyVector object filled with x values calculated
     * from the c.o. object and B vector
     */
  MyVector<T> Eliminate(const MyVector<T> &B);
  /**
   * @brief Determines if the dense matrix is a lower Triangular Matrix
   * @pre A Matrix object is created and has data stored within it
   * @Post Determines if the data stored in the dense Matrix is a lower
   * triangular matrix
   * 
   * @return true if the matrix is a lower triangular matrix
   * @return false if the matrix is a upper triangular matrix
   */
  bool isLowerTriangularMatrix() const;
  /**
   * @brief Determines if the dense matrix is a upper Triangular Matrix
   * @pre A Matrix object is created and has data stored within it
   * @Post Determines if the data stored in the dense Matrix is a upper
   * triangular matrix
   * 
   * @return true if the matrix is a upper triangular matrix
   * @return false if the matrix is a lower triangular matrix
   */
  bool isUpperTriangularMatrix() const;
  /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and Matrix object is created
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the Matrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
  MyVector<T> &operator[](const int &i);
  /**
     * @brief [] operator that returns the data of the pointer at the specified
     * position but its returned as a constant value
     * @pre: The position of the data is known and Matrix object is created
     * @post: Returns the data from the pointer of the specified position as a
     * constant value. Throws an error if the position is out of the Matrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific
     * position as a constant value
     */
  MyVector<T> &operator[](const int &i) const;
  /**
     * @brief Scalar multiplcation of a Matrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre Matrix object is created
     * @post Matrix c.o. is multiplied by the value
     * @param val Value to be multiplied against Matrix
     * @return Matrix<T> A Matrix that has been multiplied by the value
     */
  Matrix<T> operator*(const T &val) const;
  /**
     * @brief Assignment operator that sets the rhs Matrix object to the c.o.
     * @pre A Matrix object is created and another to be copied from
     * @post Copies the rhs Matrix object to the Matrix c.o.
     * @param source Matrix object
     * @return Matrix<T> The c.o. is now equal to the rhs Matrix object
     */
  Matrix<T> &operator=(const Matrix<T> &source);
};
/**
 * @brief Equals operator. Checks to see if the two Matrix objects are the same
 * @pre Two Matrix objects are created
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs Matrix object
 * @return true If the two Matrix objects are the same
 * @return false If the two Matrix objects aren't the same
 */
template <typename T>
bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the two Matrix objects are not the same
 * @pre Two Matrix objects are created
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs Matrix object
 * @return true If the two Matrix objects aren't the same
 * @return false If the two Matrix objects are the same
 */
template <typename T>
bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Negates every value within the Matrix
 * @pre A Matrix object is created
 * @post Negates every value within the Matrix
 * 
 * @tparam T template T
 * @param source Matrix object
 * @return Matrix<T> A Matrix that has every value negated
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &source);
/**
 * @brief Calculate Matrix multiplication of two matricies
 * @pre Two Matrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs Matrix and rhs Matrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate Matrix addition of two matricies
 * @pre Two Matrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs Matrix and rhs Matrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate Matrix subtraction of two matricies
 * @pre Two Matrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs Matrix and rhs Matrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Outputs every value within the columns and rows of the Matrix object
 * @pre A Matrix object is created
 * @post Outputs every value that is within the Matrix object
 * @tparam T template T
 * @param out std::ostream object
 * @param source The Matrix object
 * @return std::ostream& The contents within the Matrix object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &source);
/**
 * @brief Able to input values into the Matrix
 * @pre A Matrix object is created
 * @post Inputs values into the Matrix object
 * @tparam T template T
 * @param in std::istream object
 * @param source The Matrix object
 * @return std::istream& Sets the values of the Matrix object
 */
template <typename T>
std::istream &operator>>(std::istream &in, Matrix<T> &source);

#include "Matrix.hpp"
