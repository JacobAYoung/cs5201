#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"

using namespace std;

/**
 * @file MatrixController.h
 * @class MatrixController
 * @author Jake Young
 * @pre Some Matrix object is created
 * @post Matrix can do calculations and can be used as any kind of matrix
 * @brief This class acts as a base class for many matrix classes
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class M, class T>
class MatrixController
{
private:
  /**
 * @brief number of rows
 * 
 */
  int numRows;
  // enum typeEnum m_type;
  /**
     * @brief Number of columns
     * 
     */
  int numColumns;
  /**
   * @brief A MyVector of MyVectors to store the data.
   * 
   */
  MyVector<MyVector<T>> myVect;
  /**
   * @brief a private member function meant to copy all the values from the
   * matrix controller.
   * @pre A matrixcontroller object is created and is being copied from another
   * matrixcontroller with similar types.
   * @post the data from the matrix controller is copied from the rhs
 * @param source a matrixcontroller object
 */
  void copy(const MatrixController<M, T> &source);

public:
  enum typeEnum
  {
    LMatrix,
    UMatrix,
    DMatrix
  } m_type;
  /**
   * 
   * @pre Construct a new LMatrix object
   * @post A new LMatrix object is created
   * @brief Construct a new LMatrix object
   * 
   */
  MatrixController();
  /**
     * 
     * @pre Construct a new LMatrix object with set sizes
     * @post A new LMatrix object is created
     * @brief Construct a new LMatrix object
     * 
     * @param rows Number of rows
     * @param columns Number of columns
     * @param type type of matrix
     */
  MatrixController(int rows, int columns, typeEnum type);
  /**
     * @brief Copy constructor
     * @pre A c.o. LMatrix is created and a source LMatrix object is created to be
     * copied from
     * @post Copies the source LMatrix object to the c.o.
     * @param source LMatrix object
     */
  MatrixController(const MatrixController<M, T> &source);
  /**
     * @brief Destroy the LMatrix object
     * @pre LMatrix object is created
     * @post c.o. LMatrix will be destroyed and deleted from memory.
     */
  ~MatrixController();
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
   * @brief Set the Rows object
   * @pre The value of rows needs to be changed. Size needs to be >=0
   * @post The value of rows is changed
   * @param rows number of rows
   */
  void SetRows(const int &rows);
  /**
   * @brief Set the Columns object
   * @pre The value of columns needs to be changed. Size needs to be >=0
   * @post The value of columns is changed
   * 
   * @param columns number of columns
   */
  void SetColumns(const int &columns);

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
  M operator*(const T &val) const;
  /**
     * @brief Assignment operator that sets the rhs LMatrix object to the c.o.
     * @pre A LMatrix object is created and another to be copied from
     * @post Copies the rhs LMatrix object to the LMatrix c.o.
     * @param source LMatrix object
     * @return LMatrix<T> The c.o. is now equal to the rhs LMatrix object
     */
  MatrixController<M, T> &operator=(const M &source);
  /**
     * @brief Copy function that copies all the data from the source to the c.o.
     * LMatrix
     * @pre LMatrix object is created and another LMatrix object is created to be
     * copied from
     * @post Copies all the data from the source LMatrix object and replaces the
     * c.o. data values
     * @param source LMatrix object
     */
  void copy(const M &source);
};

#include "MatrixController.hpp"