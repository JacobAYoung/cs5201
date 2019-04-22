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

template <class T>
class SMatrix;

template <class T>
class UMatrix;

template <class T>
class DMatrix;

/**
 * @file TMatrix.h
 * @class TMatrix
 * @author Jake Young
 * @pre TMatrix object is created
 * @post TMatrix can do calculations and can be used as a regular TMatrix
 * @brief Creates a TMatrix that has multiple methods of doing calculations for
 * that TMatrix
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class TMatrix : public IMatrix<TMatrix<T>, T>
{
private:
  /**
   * @brief A matrixcontroller base class to be used for common functionallity
   * over multiple kinds of matricies.
   * 
   */
  MatrixController<TMatrix<T>, T> my_controller;

public:
  /**
 * @brief Construct a new TMatrix object
 * 
 */
  TMatrix();
  /**
   * @brief Construct a new TMatrix object
   * @pre A TMatrix object is being created with specified sizes
   * @post a TMatrix object is created with specified sizes.
   * 
   * @param rows number of rows
   * @param columns number of columns
   */
  TMatrix(int rows, int columns);
  /**
     * @brief Copy constructor
     * @pre A c.o. TMatrix is created and a source TMatrix object is created to be
     * copied from
     * @post Copies the source TMatrix object to the c.o.
     * @param source TMatrix object
     */
  TMatrix(const TMatrix<T> &source);
  /**
     * @brief Destroy the TMatrix object
     * @pre TMatrix object is created
     * @post c.o. TMatrix will be destroyed and deleted from memory.
     */
  ~TMatrix();
  /**
 * @brief Construct a new TMatrix object
 * @pre Moves the TMatrix object from the source
 * @post moved the TMatrix source object to the c.o.
 * 
 * @param source TMatrix source object
 */
  TMatrix(TMatrix<T> &&source);
  /**
     * @brief Add a vector onto the TMatrix
     * @pre A TMatrix object is created
     * @post The vector has been added to the c.o. TMatrix
     * 
     * @param source The vector that wants to be added to the c.o. TMatrix
     */
  void PushBack(const MyVector<T> &source);
  /**
     * @brief Get the Rows object
     * @pre TMatrix object is created
     * @post Gets the number of rows from the TMatrix object
     * @return int Number of rows within the TMatrix
     */
  int GetRows() const;
  /**
     * @brief Get the Columns object
     * @pre TMatrix object is created
     * @post Gets the number of columns from the TMatrix object
     * @return int Number of columns within the TMatrix
     */
  int GetColumns() const;
  /**
   * @brief Creates a LMatrix from the transpose of the umatrix
   * @pre A Umatrix object is created and filled with data
   * @post A Lmatrix is returned from the umatrix being transposed.
   * 
   * @return LMatrix<T> A Lmatrix object
   */
  TMatrix<T> Transpose();
  /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and TMatrix object is created
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the TMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
  MyVector<T> &operator[](const int &i);
  /**
     * @brief [] operator that returns the data of the pointer at the specified
     * position but its returned as a constant value
     * @pre: The position of the data is known and TMatrix object is created
     * @post: Returns the data from the pointer of the specified position as a
     * constant value. Throws an error if the position is out of the TMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific
     * position as a constant value
     */
  MyVector<T> &operator[](const int &i) const;
  /**
     * @brief Scalar multiplcation of a TMatrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre TMatrix object is created
     * @post TMatrix c.o. is multiplied by the value
     * @param val Value to be multiplied against TMatrix
     * @return TMatrix<T> A TMatrix that has been multiplied by the value
     */
  TMatrix<T> operator*(const T &val) const;
  /**
     * @brief Assignment operator that sets the rhs TMatrix object to the c.o.
     * @pre A TMatrix object is created and another to be copied from
     * @post Copies the rhs TMatrix object to the TMatrix c.o.
     * @param source TMatrix object
     * @return TMatrix<T> The c.o. is now equal to the rhs TMatrix object
     */
  TMatrix<T> &operator=(const TMatrix<T> &source);
  /**
     * @brief Assignment operator that sets the rhs Matrix object to the c.o.
     * @pre A TMatrix object is created and a Matrix object to be copied from
     * @post Copies the rhs Matrix object to the TMatrix c.o.
     * @param source Matrix object
     * @return TMatrix<T> The c.o. is now equal to the rhs Matrix object
     */
  TMatrix<T> &operator=(const Matrix<T> &source);
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
 * @brief Equals operator. Checks to see if the two TMatrix objects are the same
 * @pre Two TMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs TMatrix object
 * @param rhs TMatrix object
 * @return true If the two TMatrix objects are the same
 * @return false If the two TMatrix objects aren't the same
 */
template <typename T>
bool operator==(const TMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the TMatrix and LMatrix objects are the same
 * @pre TMatrix and LMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs TMatrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const TMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the TMatrix and Matrix objects are the same
 * @pre TMatrix and Matrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs TMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const TMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the TMatrix and LMatrix objects are the same
 * @pre Matrix and TMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs TMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const Matrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs TMatrix object
 * @param rhs SMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const TMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs SMatrix object
 * @param rhs TMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const SMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs TMatrix object
 * @param rhs DMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const TMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs TMatrix object
 * @param rhs UMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const TMatrix<T> &lhs, const UMatrix<T> &rhs);
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
bool operator!=(const TMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the TMatrix and LMatrix objects
 * are not the same
 * @pre TMatrix and LMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs TMatrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const TMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the TMatrix and Matrix objects
 * are not the same
 * @pre TMatrix and Matrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs TMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const TMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the Matrix and TMatrix objects
 * are not the same
 * @pre Matrix and TMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs TMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const Matrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs TMatrix object
 * @param rhs SMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const TMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs SMatrix object
 * @param rhs TMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const SMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs TMatrix object
 * @param rhs DMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const TMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs TMatrix object
 * @param rhs UMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const TMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Negates every value within the TMatrix
 * @pre A TMatrix object is created
 * @post Negates every value within the TMatrix
 * 
 * @tparam T template T
 * @param source TMatrix object
 * @return TMatrix<T> A TMatrix that has every value negated
 */
template <typename T>
TMatrix<T> operator-(const TMatrix<T> &source);
/**
 * @brief Calculate TMatrix multiplication of two matricies
 * @pre Two TMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs TMatrix and rhs TMatrix to return the multiplication
 * TMatrix of the 2 matricies and returns it as a TMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs TMatrix object of the right hand side
 * @return TMatrix<T> A TMatrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (umatrix and lmatrix)
 * @pre LMatrix object and TMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs TMatrix and rhs LMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (matrix and TMatrix)
 * @pre Matrix object and TMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs Matrix and rhs TMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs TMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (TMatrix and matrix)
 * @pre TMatrix object and Matrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs TMatrix and rhs Matrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs TMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator*(const SMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs SMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs DMatrix
 * @return TMatrix<T> A TMatrix object 
 */
template <typename T>
TMatrix<T> operator*(const TMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs UMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate TMatrix addition of two matricies
 * @pre Two TMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs TMatrix and rhs TMatrix to return the addition
 * TMatrix of the 2 matricies and returns it as a TMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs TMatrix object of the right hand side
 * @return TMatrix<T> A TMatrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
TMatrix<T> operator+(const TMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (umatrix and lmatrix)
 * @pre TMatrix and LMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs TMatrix and rhs LMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (matrix and TMatrix)
 * @pre Matrix and TMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs Matrix and rhs TMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (TMatrix and matrix)
 * @pre TMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs TMatrix and rhs Matrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs TMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator+(const SMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs SMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs DMatrix
 * @return TMatrix<T> A TMatrix object 
 */
template <typename T>
TMatrix<T> operator+(const TMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs UMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate TMatrix subtraction of two matricies
 * @pre Two TMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs TMatrix and rhs TMatrix to return the subtraction
 * TMatrix of the 2 matricies and returns it as a TMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs TMatrix object of the right hand side
 * @return TMatrix<T> A TMatrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
TMatrix<T> operator-(const TMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (umatrix and Lmatrix)
 * @pre LMatrix and TMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs TMatrix and rhs LMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (matrix and TMatrix)
 * @pre Matrix and TMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs Matrix and rhs TMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs TMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (TMatrix and matrix)
 * @pre TMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs TMatrix and rhs Matrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs TMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs TMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator-(const SMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs SMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs DMatrix
 * @return TMatrix<T> A TMatrix object 
 */
template <typename T>
TMatrix<T> operator-(const TMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs TMatrix
 * @param rhs UMatrix
 * @return Matrix<T> A Matrix object 
 */
template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Outputs every value within the columns and rows of the TMatrix object
 * @pre A TMatrix object is created
 * @post Outputs every value that is within the TMatrix object
 * @tparam T template T
 * @param out std::ostream object
 * @param source The TMatrix object
 * @return std::ostream& The contents within the TMatrix object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const TMatrix<T> &source);
/**
 * @brief Able to input values into the TMatrix
 * @pre A TMatrix object is created
 * @post Inputs values into the TMatrix object
 * @tparam T template T
 * @param in std::istream object
 * @param source The TMatrix object
 * @return std::istream& Sets the values of the TMatrix object
 */
template <typename T>
std::istream &operator>>(std::istream &in, TMatrix<T> &source);

#include "TMatrix.hpp"
