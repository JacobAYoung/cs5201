#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "GaussElimination.h"

using namespace std;

/**
 * @file Matrix.h
 * @author Jake Young
 * @pre Matrix object is created
 * @post Matrix can do calculations and can be used as a regular matrix
 * @brief Creates a matrix that has multiple methods of doing calculations for
 * that matrix
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class Matrix
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
    /**
     * @brief Copy function that copies all the data from the source to the c.o.
     * matrix
     * @pre Matrix object is created and another matrix object is created to be
     * copied from
     * @post Copies all the data from the source matrix object and replaces the
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
     * @pre A c.o. matrix is created and a source matrix object is created to be
     * copied from
     * @post Copies the source matrix object to the c.o.
     * @param source Matrix object
     */
    Matrix(const Matrix<T> &source);
    /**
     * @brief Destroy the Matrix object
     * @pre Matrix object is created
     * @post c.o. matrix will be destroyed and deleted from memory.
     */
    ~Matrix();
    /**
     * @brief Add a vector onto the matrix
     * @pre A matrix object is created
     * @post The vector has been added to the c.o. matrix
     * 
     * @param source The vector that wants to be added to the c.o. matrix
     */
    void PushBack(const MyVector<T> &source);
    /**
     * @brief Get the Rows object
     * @pre Matrix object is created
     * @post Gets the number of rows from the matrix object
     * @return int Number of rows within the matrix
     */
    int GetRows() const;
    /**
     * @brief Get the Columns object
     * @pre Matrix object is created
     * @post Gets the number of columns from the matrix object
     * @return int Number of columns within the matrix
     */
    int GetColumns() const;
    /**
     * @brief Calculate and returns the transpose of the matrix object
     * @pre A matrix object is created
     * @post Creates a temporary Matrix object and returns the transpose of the
     * c.o. matrix
     * @return Matrix<T> A copy of the Matrix c.o. transpose
     */
    Matrix<T> Transpose();
    /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and matrix object is created
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the matrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
    MyVector<T> &operator[](const int &i);
    /**
     * @brief [] operator that returns the data of the pointer at the specified
     * position but its returned as a constant value
     * @pre: The position of the data is known and matrix object is created
     * @post: Returns the data from the pointer of the specified position as a
     * constant value. Throws an error if the position is out of the matrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific
     * position as a constant value
     */
    MyVector<T> &operator[](const int &i) const;
    /**
     * @brief Performs the Gauss elimination process on the c.o. matrix and a B
     * vector to find the x vector of values
     * @pre A matrix object and MyVector object is created
     * @post Creates a MyVector object filled with the x values created from the
     * gauss elimination of the matrix and b vector. Throws an error if the size
     * of the matrix and B vector don't work together.
     * @param B The B vector
     * @return MyVector<T> A MyVector object filled with x values calculated
     * from the c.o. object and B vector
     */
    MyVector<T> Eliminate(const MyVector<T> &B);
    /**
     * @brief Scalar multiplcation of a matrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre Matrix object is created
     * @post Matrix c.o. is multiplied by the value
     * @param val Value to be multiplied against matrix
     * @return Matrix<T> A matrix that has been multiplied by the value
     */
    Matrix<T> operator*(const T &val);
    /**
     * @brief Assignment operator that sets the rhs Matrix object to the c.o.
     * @pre A matrix object is created and another to be copied from
     * @post Copies the rhs matrix object to the matrix c.o.
     * @param source Matrix object
     * @return Matrix<T> The c.o. is now equal to the rhs matrix object
     */
    Matrix<T> &operator=(const Matrix<T> &source);
};
/**
 * @brief Equals operator. Checks to see if the two matrix objects are the same
 * @pre Two matrix objects are created
 * @post Returns true or false depending on if the matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs Matrix object
 * @return true If the two matrix objects are the same
 * @return false If the two matrix objects aren't the same
 */
template <typename T>
bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the two matrix objects are not the same
 * @pre Two matrix objects are created
 * @post Returns true or false depending on if the matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs Matrix object
 * @return true If the two matrix objects aren't the same
 * @return false If the two matrix objects are the same
 */
template <typename T>
bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Negates every value within the matrix
 * @pre A matrix object is created
 * @post Negates every value within the matrix
 * 
 * @tparam T template T
 * @param source Matrix object
 * @return Matrix<T> A matrix that has every value negated
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &source);
/**
 * @brief Calculate matrix multiplication of two matricies
 * @pre Two matrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs matrix and rhs matrix to return the multiplication
 * matrix of the 2 matricies and returns it as a matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate matrix addition of two matricies
 * @pre Two matrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs matrix and rhs matrix to return the addition
 * matrix of the 2 matricies and returns it as a matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate matrix subtraction of two matricies
 * @pre Two matrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs matrix and rhs matrix to return the subtraction
 * matrix of the 2 matricies and returns it as a matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Outputs every value within the columns and rows of the matrix object
 * @pre A matrix object is created
 * @post Outputs every value that is within the matrix object
 * @tparam T template T
 * @param out std::ostream object
 * @param source The matrix object
 * @return std::ostream& The contents within the matrix object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &source);
/**
 * @brief Able to input values into the matrix
 * @pre A Matrix object is created
 * @post Inputs values into the matrix object
 * @tparam T template T
 * @param in std::istream object
 * @param source The matrix object
 * @return std::istream& Sets the values of the matrix object
 */
template <typename T>
std::istream &operator>>(std::istream &in, Matrix<T> &source);

#include "Matrix.hpp"
