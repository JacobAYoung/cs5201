#ifndef IMATRIX_H
#define IMATRIX_H

#include "MyVector.h"

/**
 * @file IMatrix.h
 * @class IMatrix
 * @author Jake Young
 * @pre A class that will inherit from this class is created
 * @post This class contains the definitions of functions to be used within the
 * inherited classes.
 * @brief This abstract class is used to define a matrix
 * that Matrix. 
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

template <class T>
class Matrix;

template <class M, class T>
class IMatrix
{
public:
  /**
     * @brief Add a vector onto the Matrix
     * @pre A Matrix object is created
     * @post The vector has been added to the c.o. Matrix
     * 
     * @param source The vector that wants to be added to the c.o. Matrix
     */
  virtual void PushBack(const MyVector<T> &source) = 0;

  //virtual Matrix<T> operator*(const IMatrix<M, T> &source) = 0;
  /**
     * @brief Get the Rows object
     * @pre Matrix object is created
     * @post Gets the number of rows from the Matrix object
     * @return int Number of rows within the Matrix
     */
  virtual int GetRows() const = 0;
  /**
     * @brief Get the Columns object
     * @pre Matrix object is created
     * @post Gets the number of columns from the Matrix object
     * @return int Number of columns within the Matrix
     */
  virtual int GetColumns() const = 0;
  /**
     * @brief [] operator that returns the data of the pointer at the specified position
     * @pre: The position of the data is known and Matrix object is created.
     * @post: Returns the data from the pointer of the specified position.
     * Throws an error if the position is out of the Matrix's size.
     * @param i Position number
     * @return MyVector<T>& Returns the data from the pointer at the specific position
     */
  virtual MyVector<T> &operator[](const int &i) = 0;
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
  virtual MyVector<T> &operator[](const int &i) const = 0;
  /**
     * @brief Assignment operator that sets the rhs Matrix object to the c.o.
     * @pre A Matrix object is created and another to be copied from
     * @post Copies the rhs Matrix object to the Matrix c.o.
     * @param source Matrix object
     * @return Matrix<T> The c.o. is now equal to the rhs Matrix object
     */
  virtual M &operator=(const M &source) = 0;
  /**
     * @brief Scalar multiplcation of a Matrix and a T value. The T value must
     * be on the right side of the multiplcation equation.
     * @pre Matrix object is created
     * @post Matrix c.o. is multiplied by the value
     * @param val Value to be multiplied against Matrix
     * @return Matrix<T> A Matrix that has been multiplied by the value
     */
  virtual M operator*(const T &val) const = 0;
  /**
   * @brief Works as the [] operator. To get data from the matrix.
   * @pre A matrix must be created and have data stored within it. i and j must
   * be positive and within the bounds of the matrix otherwise it will throw an error.
   * @post Data at position i and j will be returned. 
   * 
   * @param i int value at position i
   * @param j int value at position j
   * @return T& A element at the data position
   */
  virtual T &operator()(const int &i, const int &j) = 0;
  /**
   * @brief Works as the [] operator. To get data from the matrix as a constant value.
   * @pre A matrix must be created and have data stored within it. i and j must
   * be positive and within the bounds of the matrix otherwise it will throw an error.
   * @post Data at position i and j will be returned as a constant value. 
   * 
   * @param i int value at position i
   * @param j int value at position j
   * @return T& A element at the data position as a constant value
   */
  virtual T &operator()(const int &i, const int &j) const = 0;
  /**
 * @brief Works as a addition between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be added.
 * @post Returns the addition of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  virtual Matrix<T> add(const IMatrix<M, T> &source) const = 0;
  /**
 * @brief Works as a subtraction between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be subtracted.
 * @post Returns the subtraction of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  virtual Matrix<T> subtract(const IMatrix<M, T> &source) const = 0;
  /**
 * @brief Works as a multiplcation between 2 IMatrix objects.
 * @pre Two IMatrix objects must be created and data filled within them to be multipled.
 * @post Returns the multiplcation of two IMatrix objects. T = T and will throw an
 * error if the sizes are off.
 * 
 * @param source A IMatrix object
 * @return Matrix<T> A dense matrix object.
 */
  virtual Matrix<T> multiply(const IMatrix<M, T> &source) const = 0;
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
  virtual bool equals(const IMatrix<M, T> &source) const = 0;
  /**
   * @brief Destroy the IMatrix object
   * @pre IMatrix object is created to be destroyed from
   * @post Imatrix object is destroyed
   * 
   */
  virtual ~IMatrix() {}
};

#endif