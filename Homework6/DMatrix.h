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
class TMatrix;

/**
 * @file DMatrix.h
 * @class DMatrix
 * @author Jake Young
 * @pre DMatrix object is created
 * @post DMatrix can do calculations and is used as a matrix class with only the
 * diagonals able to be accessed within the matrix
 * @brief Creates a DMatrix that has multiple methods of doing calculations for
 * that DMatrix
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
class DMatrix : public IMatrix<DMatrix<T>, T>
{
private:
  /**
   * @brief A matrixcontroller base class to be used for common functionallity
   * over multiple kinds of matricies.
   * 
   */
  MatrixController<DMatrix<T>, T> my_controller;

public:
  /**
 * @brief Construct a new DMatrix object
 * 
 */
  DMatrix();
  /**
   * @brief Construct a new DMatrix object
   * @pre A DMatrix object is being created with specified sizes
   * @post a DMatrix object is created with specified sizes.
   * 
   * @param rows number of rows
   * @param columns number of columns
   */
  DMatrix(int rows, int columns);
  /**
     * 
     * @pre Construct a new DMatrix object with set sizes
     * @post A new DMatrix object is created
     * @brief Construct a new DMatrix object from a dense matrix
     * 
     * @param source A dense matrix object
     */
  DMatrix(const Matrix<T> &source);
  /**
     * @brief Copy constructor
     * @pre A c.o. DMatrix is created and a source DMatrix object is created to be
     * copied from
     * @post Copies the source DMatrix object to the c.o.
     * @param source DMatrix object
     */
  DMatrix(const DMatrix<T> &source);
  /**
     * @brief Destroy the DMatrix object
     * @pre DMatrix object is created
     * @post c.o. DMatrix will be destroyed and deleted from memory.
     */
  ~DMatrix();
  /**
     * @brief Construct a new DMatrix object
     * @pre Moves the DMatrix object from the source
     * @post moved the DMatrix source object to the c.o.
     * 
     * @param source DMatrix source object
     */
  DMatrix(DMatrix<T> &&source);
  /**
     * @brief Add a vector onto the DMatrix
     * @pre A DMatrix object is created
     * @post The vector has been added to the c.o. DMatrix
     * 
     * @param source The vector that wants to be added to the c.o. DMatrix
     */
  void PushBack(const MyVector<T> &source);
  /**
     * @brief Get the Rows object
     * @pre DMatrix object is created
     * @post Gets the number of rows from the DMatrix object
     * @return int Number of rows within the DMatrix
     */
  int GetRows() const;
  /**
     * @brief Get the Columns object
     * @pre DMatrix object is created
     * @post Gets the number of columns from the DMatrix object
     * @return int Number of columns within the DMatrix
     */
  int GetColumns() const;
  /**
   * @brief Creates a DMatrix from the transpose of the DMatrix
   * @pre A DMatrix object is created and filled with data
   * @post A Dmatrix is returned from the DMatrix being transposed.
   * 
   * @return DMatrix<T> A Dmatrix object
   */
  DMatrix<T> Transpose();
  /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and DMatrix object is created
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the DMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
  MyVector<T> &operator[](const int &i);
  /**
     * @brief [] operator that returns the data of the pointer at the specified
     * position but its returned as a constant value
     * @pre: The position of the data is known and DMatrix object is created
     * @post: Returns the data from the pointer of the specified position as a
     * constant value. Throws an error if the position is out of the DMatrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific
     * position as a constant value
     */
  MyVector<T> &operator[](const int &i) const;
  /**
     * @brief Scalar multiplcation of a DMatrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre DMatrix object is created
     * @post DMatrix c.o. is multiplied by the value
     * @param val Value to be multiplied against DMatrix
     * @return DMatrix<T> A DMatrix that has been multiplied by the value
     */
  DMatrix<T> operator*(const T &val) const;
  /**
     * @brief Assignment operator that sets the rhs DMatrix object to the c.o.
     * @pre A DMatrix object is created and another to be copied from
     * @post Copies the rhs DMatrix object to the DMatrix c.o.
     * @param source DMatrix object
     * @return DMatrix<T> The c.o. is now equal to the rhs DMatrix object
     */
  DMatrix<T> &operator=(const DMatrix<T> &source);
  /**
     * @brief Assignment operator that sets the rhs Matrix object to the c.o.
     * @pre A DMatrix object is created and a Matrix object to be copied from
     * @post Copies the rhs Matrix object to the DMatrix c.o.
     * @param source Matrix object
     * @return DMatrix<T> The c.o. is now equal to the rhs Matrix object
     */
  DMatrix<T> &operator=(const Matrix<T> &source);
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
 * @brief Equals operator. Checks to see if the two DMatrix objects are the same
 * @pre Two DMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs DMatrix object
 * @param rhs DMatrix object
 * @return true If the two DMatrix objects are the same
 * @return false If the two DMatrix objects aren't the same
 */
template <typename T>
bool operator==(const DMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the DMatrix and LMatrix objects are the same
 * @pre DMatrix and LMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs DMatrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const DMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the DMatrix and Matrix objects are the same
 * @pre DMatrix and Matrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs DMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const DMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Equals operator. Checks to see if the DMatrix and LMatrix objects are the same
 * @pre Matrix and DMatrix objects are created to be tested to see if they are the same.
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs DMatrix object
 * @return true If the Matrix objects are the same
 * @return false If the Matrix objects aren't the same
 */
template <typename T>
bool operator==(const Matrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs DMatrix object
 * @param rhs SMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const DMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs SMatrix object
 * @param rhs DMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const SMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs DMatrix object
 * @param rhs UMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const DMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs DMatrix object
 * @param rhs TMatrix object
 * @return true If the matricies are the same
 * @return false If the matricies are not the same
 */
template <typename T>
bool operator==(const DMatrix<T> &lhs, const TMatrix<T> &rhs);
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
bool operator!=(const DMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the DMatrix and LMatrix objects
 * are not the same
 * @pre DMatrix and LMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs DMatrix object
 * @param rhs LMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const DMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the DMatrix and Matrix objects
 * are not the same
 * @pre DMatrix and Matrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs DMatrix object
 * @param rhs Matrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const DMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Not Equals operator. Checks to see if the Matrix and DMatrix objects
 * are not the same
 * @pre Matrix and DMatrix objects are created to be tested to see if they are
 * the same. or different
 * @post Returns true or false depending on if the Matrix objects are the same
 * or not
 * @tparam T template T
 * @param lhs Matrix object
 * @param rhs DMatrix object
 * @return true If the Matrix objects are not the same
 * @return false If the Matrix objects are the same
 */
template <typename T>
bool operator!=(const Matrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs DMatrix object
 * @param rhs SMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const DMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs SMatrix object
 * @param rhs DMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const SMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs DMatrix object
 * @param rhs UMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const DMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Checks to see if the two Matrix objects are not the same
 * @pre The two matrix objects are created and data is filled within them
 * @post T=T types must be the same. Returns true or false if the matrix's are
 * the same or not. Will also throw an error if the sizes do not match.
 * 
 * @tparam T type T
 * @param lhs DMatrix object
 * @param rhs TMatrix object
 * @return true If the matricies are not the same
 * @return false If the matricies are the same
 */
template <typename T>
bool operator!=(const DMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Negates every value within the DMatrix
 * @pre A DMatrix object is created
 * @post Negates every value within the DMatrix
 * 
 * @tparam T template T
 * @param source DMatrix object
 * @return DMatrix<T> A DMatrix that has every value negated
 */
template <typename T>
DMatrix<T> operator-(const DMatrix<T> &source);
/**
 * @brief Calculate DMatrix multiplication of two matricies
 * @pre Two DMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs DMatrix and rhs DMatrix to return the multiplication
 * DMatrix of the 2 matricies and returns it as a DMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs DMatrix object of the right hand side
 * @return DMatrix<T> A DMatrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
DMatrix<T> operator*(const DMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (DMatrix and lmatrix)
 * @pre LMatrix object and DMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs DMatrix and rhs LMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
LMatrix<T> operator*(const DMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (matrix and DMatrix)
 * @pre Matrix object and DMatrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs Matrix and rhs DMatrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs DMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate Matrix multiplication of two matricies (DMatrix and matrix)
 * @pre DMatrix object and Matrix are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs DMatrix and rhs Matrix to return the multiplication
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing multiplication of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator*(const DMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns a SMatrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs SMatrix
 * @return SMatrix<T> A SMatrix object 
 */
template <typename T>
SMatrix<T> operator*(const DMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs DMatrix
 * @return SMatrix<T> A SMatrix object 
 */
template <typename T>
SMatrix<T> operator*(const SMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs UMatrix
 * @return UMatrix<T> A UMatrix object 
 */
template <typename T>
UMatrix<T> operator*(const DMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate the multiplcation of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Multipies
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs TMatrix
 * @return TMatrix<T> A UMatrix object 
 */
template <typename T>
TMatrix<T> operator*(const DMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate DMatrix addition of two matricies
 * @pre Two DMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs DMatrix and rhs DMatrix to return the addition
 * DMatrix of the 2 matricies and returns it as a DMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs DMatrix object of the right hand side
 * @return DMatrix<T> A DMatrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
DMatrix<T> operator+(const DMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (DMatrix and lmatrix)
 * @pre DMatrix and LMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs DMatrix and rhs LMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
LMatrix<T> operator+(const DMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (matrix and DMatrix)
 * @pre Matrix and DMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs Matrix and rhs DMatrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate addition of the two matricies (DMatrix and matrix)
 * @pre DMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error is thrown. T types must be the same
 * @post Calculates the lhs DMatrix and rhs Matrix to return the addition
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing addition of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator+(const DMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs SMatrix
 * @return SMatrix<T> A SMatrix object 
 */
template <typename T>
SMatrix<T> operator+(const DMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs DMatrix
 * @return SMatrix<T> A SMatrix object 
 */
template <typename T>
SMatrix<T> operator+(const SMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs UMatrix
 * @return UMatrix<T> A UMatrix object 
 */
template <typename T>
UMatrix<T> operator+(const DMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate the addition of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Adds
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs TMatrix
 * @return TMatrix<T> A TMatrix object 
 */
template <typename T>
TMatrix<T> operator+(const DMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Calculate DMatrix subtraction of two matricies
 * @pre Two DMatrix object's are created and the lhs column size is the same as
 * the rhs row size.
 * @post Calculates the lhs DMatrix and rhs DMatrix to return the subtraction
 * DMatrix of the 2 matricies and returns it as a DMatrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs DMatrix object of the right hand side
 * @return DMatrix<T> A DMatrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
DMatrix<T> operator-(const DMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (DMatrix and Lmatrix)
 * @pre LMatrix and DMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs DMatrix and rhs LMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs LMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
LMatrix<T> operator-(const DMatrix<T> &lhs, const LMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (matrix and DMatrix)
 * @pre Matrix and DMatrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs Matrix and rhs DMatrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs Matrix object of the left hand side
 * @param rhs DMatrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate subtraction of two matricies (DMatrix and matrix)
 * @pre DMatrix and Matrix objects are created and the lhs column size is the same as
 * the rhs row size otherwise error will be thrown. T types must be the same. 
 * @post Calculates the lhs DMatrix and rhs Matrix to return the subtraction
 * Matrix of the 2 matricies and returns it as a Matrix object. Throws an error
 * the sizes of the matricies don't line up
 * @tparam T template T
 * @param lhs DMatrix object of the left hand side
 * @param rhs Matrix object of the right hand side
 * @return Matrix<T> A Matrix that has been calculate by doing subtraction of
 * the lhs and rhs matricies
 */
template <typename T>
Matrix<T> operator-(const DMatrix<T> &lhs, const Matrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs SMatrix
 * @return SMatrix<T> A SMatrix object 
 */
template <typename T>
SMatrix<T> operator-(const DMatrix<T> &lhs, const SMatrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs SMatrix
 * @param rhs DMatrix
 * @return SMatrix<T> A SMatrix object 
 */
template <typename T>
SMatrix<T> operator-(const SMatrix<T> &lhs, const DMatrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs UMatrix
 * @return UMatrix<T> A UMatrix object 
 */
template <typename T>
UMatrix<T> operator-(const DMatrix<T> &lhs, const UMatrix<T> &rhs);
/**
 * @brief Calculate the subtraction of the two matrix objects.
 * @pre Both objects must be created and of the same type T=T
 * @post Will throw an error if the matricies are not the same size. Subtracts
 * both matricies together and returns another matrix object.
 * 
 * @tparam T template type T
 * @param lhs DMatrix
 * @param rhs TMatrix
 * @return TMatrix<T> A TMatrix object 
 */
template <typename T>
TMatrix<T> operator-(const DMatrix<T> &lhs, const TMatrix<T> &rhs);
/**
 * @brief Outputs every value within the columns and rows of the DMatrix object
 * @pre A DMatrix object is created
 * @post Outputs every value that is within the DMatrix object
 * @tparam T template T
 * @param out std::ostream object
 * @param source The DMatrix object
 * @return std::ostream& The contents within the DMatrix object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const DMatrix<T> &source);
/**
 * @brief Able to input values into the DMatrix
 * @pre A DMatrix object is created
 * @post Inputs values into the DMatrix object
 * @tparam T template T
 * @param in std::istream object
 * @param source The DMatrix object
 * @return std::istream& Sets the values of the DMatrix object
 */
template <typename T>
std::istream &operator>>(std::istream &in, DMatrix<T> &source);

#include "DMatrix.hpp"
