#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"
#include "Matrix.h"
#include "IMatrix.h"
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * @file SMatrix.h
 * @class SMatrix
 * @author Jake Young
 * @pre SMatrix object is created
 * @post SMatrix can do calculations and can be used as a regular SMatrix
 * @brief Creates a SMatrix that has multiple methods of doing calculations for
 * that SMatrix. 
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class SMatrix : public IMatrix<SMatrix<T>, T>
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

  //MatrixController<SMatrix<T>, T> my_controller;
  /**
    * @brief Copy function that copies all the data from the source to the c.o.
    * SMatrix
    * @pre SMatrix object is created and another SMatrix object is created to be
    * copied from
    * @post Copies all the data from the source SMatrix object and replaces the
    * c.o. data values
    * @param source SMatrix object
  */
  void copy(const SMatrix<T> &source);

public:
  /**
   * 
   * @pre Construct a new SMatrix object
   * @post A new SMatrix object is created
   * @brief Construct a new SMatrix object
   * 
   */
  SMatrix();
  /**
     * 
     * @pre Construct a new SMatrix object with set sizes
     * @post A new SMatrix object is created
     * @brief Construct a new SMatrix object
     * 
     * @param rows Number of rows
     * @param columns Number of columns
     */
  SMatrix(int rows, int columns);
  /**
     * @brief Copy constructor
     * @pre A c.o. SMatrix is created and a source SMatrix object is created to be
     * copied from
     * @post Copies the source SMatrix object to the c.o.
     * @param source SMatrix object
     */
  SMatrix(const SMatrix<T> &source);
  /**
     * @brief Destroy the SMatrix object
     * @pre SMatrix object is created
     * @post c.o. SMatrix will be destroyed and deleted from memory.
     */
  ~SMatrix();
  /**
 * @brief Construct a new SMatrix object for move semantics
 * @pre Performs move semantics over the new matrix object
 * @post correctly swaps all the values to the current matrix
 * @param source matrix object
 */
  SMatrix(SMatrix<T> &&source);
  /**
     * @brief Add a vector onto the SMatrix
     * @pre A SMatrix object is created
     * @post The vector has been added to the c.o. SMatrix
     * 
     * @param source The vector that wants to be added to the c.o. SMatrix
     */
  void PushBack(const MyVector<T> &source);
  /**
     * @brief Get the Rows object
     * @pre SMatrix object is created
     * @post Gets the number of rows from the SMatrix object
     * @return int Number of rows within the SMatrix
     */
  int GetRows() const;
  /**
     * @brief Get the Columns object
     * @pre SMatrix object is created
     * @post Gets the number of columns from the SMatrix object
     * @return int Number of columns within the SMatrix
     */
  int GetColumns() const;
  /**
     * @brief Calculate and returns the transpose of the SMatrix object
     * @pre A SMatrix object is created
     * @post Creates a temporary SMatrix object and returns the transpose of the
     * c.o. SMatrix
     * @return SMatrix<T> A copy of the SMatrix c.o. transpose
     */
  SMatrix<T> Transpose();
  /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and SMatrix object is created.
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the SMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
  MyVector<T> &operator[](const int &i);
  /**
     * @brief [] operator that returns the data of the pointer at the specified
     * position but its returned as a constant value
     * @pre: The position of the data is known and SMatrix object is created
     * @post: Returns the data from the pointer of the specified position as a
     * constant value. Throws an error if the position is out of the SMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific
     * position as a constant value
     */
  MyVector<T> &operator[](const int &i) const;
  /**
   * @brief Works as the [] operator. To get data from the matrix.
   * @pre A DMatrix must be created and have data stored within it. i and j must
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
   * @pre A DMatrix must be created and have data stored within it. i and j must
   * be positive and within the bounds of the matrix otherwise it will throw an error.
   * @post Data at position i and j will be returned as a constant value. 
   * 
   * @param i int value at position i
   * @param j int value at position j
   * @return T& A element at the data position as a constant value
   */
  T &operator()(const int &i, const int &j) const;
  /**
     * @brief Scalar multiplcation of a SMatrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre SMatrix object is created
     * @post SMatrix c.o. is multiplied by the value
     * @param val Value to be multiplied against SMatrix
     * @return SMatrix<T> A SMatrix that has been multiplied by the value
     */
  SMatrix<T> operator*(const T &val) const;
  /**
     * @brief Assignment operator that sets the rhs SMatrix object to the c.o.
     * @pre A SMatrix object is created and another to be copied from
     * @post Copies the rhs SMatrix object to the SMatrix c.o.
     * @param source SMatrix object
     * @return SMatrix<T> The c.o. is now equal to the rhs SMatrix object
     */
  SMatrix<T> &operator=(const SMatrix<T> &source);
  /**
 * @brief Sets the SMatrix object to the values of the dense matrix object
 * @pre a dense matrix object is created to be copied from
 * @post the dense matrix object's elements are copied to the SMatrix
 * 
 * @param source A dense Matrix
 * @return SMatrix<T>& A symmetric matrix
 */
  SMatrix<T> &operator=(const Matrix<T> &source);

  /**
 * @brief Works as a addition between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be added.
 * @post Returns the addition of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> add(const IMatrix<Matrix<T>, T> &source) const;
  /**
 * @brief Works as a subtraction between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be subtracted.
 * @post Returns the subtraction of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> subtract(const IMatrix<Matrix<T>, T> &source) const;
  /**
 * @brief Works as a multiplcation between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be multipled.
 * @post Returns the multiplcation of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> multiply(const IMatrix<Matrix<T>, T> &source) const;
  /**
   * @brief Checks to see if two IMatrix objects are the same size, and every
   * value withem are the same.
   * @pre Two IMatrix objects are created and needs to be checked if they are equal
   * @post returns true or false depending on if the IMatrix objects are the same.
   * 
   * @param source A IMatrix object
   * @return true If they are equal
   * @return false If they are not equal
   */
  bool equals(const IMatrix<Matrix<T>, T> &source) const;

  /**
 * @brief Works as a addition between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be added.
 * @post Returns the addition of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> add(const IMatrix<TMatrix<T>, T> &source) const;
  /**
 * @brief Works as a subtraction between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be subtracted.
 * @post Returns the subtraction of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> subtract(const IMatrix<TMatrix<T>, T> &source) const;
  /**
 * @brief Works as a multiplcation between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be multipled.
 * @post Returns the multiplcation of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> multiply(const IMatrix<TMatrix<T>, T> &source) const;
  /**
   * @brief Checks to see if two IMatrix objects are the same size, and every
   * value withem are the same.
   * @pre Two IMatrix objects are created and needs to be checked if they are equal
   * @post returns true or false depending on if the IMatrix objects are the same.
   * 
   * @param source A IMatrix object
   * @return true If they are equal
   * @return false If they are not equal
   */
  bool equals(const IMatrix<TMatrix<T>, T> &source) const;

  /**
 * @brief Works as a addition between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be added.
 * @post Returns the addition of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> add(const IMatrix<LMatrix<T>, T> &source) const;
  /**
 * @brief Works as a subtraction between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be subtracted.
 * @post Returns the subtraction of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> subtract(const IMatrix<LMatrix<T>, T> &source) const;
  /**
 * @brief Works as a multiplcation between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be multipled.
 * @post Returns the multiplcation of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> multiply(const IMatrix<LMatrix<T>, T> &source) const;
  /**
   * @brief Checks to see if two IMatrix objects are the same size, and every
   * value withem are the same.
   * @pre Two IMatrix objects are created and needs to be checked if they are equal
   * @post returns true or false depending on if the IMatrix objects are the same.
   * 
   * @param source A IMatrix object
   * @return true If they are equal
   * @return false If they are not equal
   */
  bool equals(const IMatrix<LMatrix<T>, T> &source) const;

  /**
 * @brief Works as a addition between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be added.
 * @post Returns the addition of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> add(const IMatrix<UMatrix<T>, T> &source) const;
  /**
 * @brief Works as a subtraction between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be subtracted.
 * @post Returns the subtraction of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> subtract(const IMatrix<UMatrix<T>, T> &source) const;
  /**
 * @brief Works as a multiplcation between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be multipled.
 * @post Returns the multiplcation of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> multiply(const IMatrix<UMatrix<T>, T> &source) const;
  /**
   * @brief Checks to see if two IMatrix objects are the same size, and every
   * value withem are the same.
   * @pre Two IMatrix objects are created and needs to be checked if they are equal
   * @post returns true or false depending on if the IMatrix objects are the same.
   * 
   * @param source A IMatrix object
   * @return true If they are equal
   * @return false If they are not equal
   */
  bool equals(const IMatrix<UMatrix<T>, T> &source) const;

  /**
 * @brief Works as a addition between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be added.
 * @post Returns the addition of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> add(const IMatrix<SMatrix<T>, T> &source) const;
  /**
 * @brief Works as a subtraction between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be subtracted.
 * @post Returns the subtraction of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> subtract(const IMatrix<SMatrix<T>, T> &source) const;
  /**
 * @brief Works as a multiplcation between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be multipled.
 * @post Returns the multiplcation of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> multiply(const IMatrix<SMatrix<T>, T> &source) const;
  /**
   * @brief Checks to see if two IMatrix objects are the same size, and every
   * value withem are the same.
   * @pre Two IMatrix objects are created and needs to be checked if they are equal
   * @post returns true or false depending on if the IMatrix objects are the same.
   * 
   * @param source A IMatrix object
   * @return true If they are equal
   * @return false If they are not equal
   */
  bool equals(const IMatrix<SMatrix<T>, T> &source) const;

  /**
 * @brief Works as a addition between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be added.
 * @post Returns the addition of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> add(const IMatrix<DMatrix<T>, T> &source) const;
  /**
 * @brief Works as a subtraction between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be subtracted.
 * @post Returns the subtraction of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> subtract(const IMatrix<DMatrix<T>, T> &source) const;
  /**
 * @brief Works as a multiplcation between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be multipled.
 * @post Returns the multiplcation of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  Matrix<T> multiply(const IMatrix<DMatrix<T>, T> &source) const;
  /**
   * @brief Checks to see if two IMatrix objects are the same size, and every
   * value withem are the same.
   * @pre Two IMatrix objects are created and needs to be checked if they are equal
   * @post returns true or false depending on if the IMatrix objects are the same.
   * 
   * @param source A IMatrix object
   * @return true If they are equal
   * @return false If they are not equal
   */
  bool equals(const IMatrix<DMatrix<T>, T> &source) const;
};
/**
 * @brief Equals operator. Checks to see if the two SMatrix objects are the same
 * @pre Two SMatrix objects are created. The value T must be the same.
 * @post Returns true or false depending on if the SMatrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs SMatrix object
 * @param rhs SMatrix object
 * @return true If the two SMatrix objects are the same
 * @return false If the two SMatrix objects aren't the same
 */
template <typename T>
bool operator==(const SMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the two SMatrix objects are not the same
 * @pre Two SMatrix objects are created. The value T must be the same.
 * @post Returns true or false depending on if the SMatrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs SMatrix object
 * @param rhs SMatrix object
 * @return true If the two SMatrix objects aren't the same
 * @return false If the two SMatrix objects are the same
 */
template <typename T>
bool operator!=(const SMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Negates every value within the SMatrix
 * @pre A SMatrix object is created.
 * @post Negates every value within the SMatrix
 * 
 * @tparam T template T
 * @param source SMatrix object
 * @return SMatrix<T> A SMatrix that has every value negated
 */
template <typename T>
SMatrix<T> operator-(const SMatrix<T> &source);
/**
 * @brief Calculate SMatrix multiplication of two matricies
 * @pre Two SMatrix object's are created and the lhs column size is the same as
 * the rhs row size. The value T must be the same.
 * @post Calculates the lhs SMatrix and rhs SMatrix to return the multiplication
 * SMatrix of the 2 matricies and returns it as a SMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs SMatrix object of the left hand side
 * @param rhs SMatrix object of the right hand side
 * @return SMatrix<T> A SMatrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
SMatrix<T> operator*(const SMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs Matrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator*(const SMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs Matrix
 * @param rhs SMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate SMatrix addition of two matricies
 * @pre Two SMatrix object's are created and the lhs column size is the same as
 * the rhs row size. The value T must be the same.
 * @post Calculates the lhs SMatrix and rhs SMatrix to return the addition
 * SMatrix of the 2 matricies and returns it as a SMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs SMatrix object of the left hand side
 * @param rhs SMatrix object of the right hand side
 * @return SMatrix<T> A SMatrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
SMatrix<T> operator+(const SMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs Matrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator+(const SMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs Matrix
 * @param rhs SMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate SMatrix subtraction of two matricies
 * @pre Two SMatrix object's are created and the lhs column size is the same as
 * the rhs row size. The value T must be the same.
 * @post Calculates the lhs SMatrix and rhs SMatrix to return the subtraction
 * SMatrix of the 2 matricies and returns it as a SMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs SMatrix object of the left hand side
 * @param rhs SMatrix object of the right hand side
 * @return SMatrix<T> A SMatrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
SMatrix<T> operator-(const SMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs MMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator-(const SMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs Matrix
 * @param rhs SMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Outputs every value within the columns and rows of the SMatrix object
 * @pre A SMatrix object is created
 * @post Outputs every value that is within the SMatrix object
 * @tparam T template T
 * @param out std::ostream object
 * @param source The SMatrix object
 * @return std::ostream& The contents within the SMatrix object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const SMatrix<T> &source);
/**
 * @brief Able to input values into the SMatrix
 * @pre A SMatrix object is created
 * @post Inputs values into the SMatrix object
 * @tparam T template T
 * @param in std::istream object
 * @param source The SMatrix object
 * @return std::istream& Sets the values of the SMatrix object
 */
template <typename T>
std::istream &operator>>(std::istream &in, SMatrix<T> &source);

#include "SMatrix.hpp"
