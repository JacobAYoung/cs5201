#pragma once

#include <cmath>
#include <iomanip>
#include <utility>
#include "MyVector.h"

using namespace std;

template <class M, class T>
class MatrixController
{
private:
  int numRows;
  //int m_type;
  /**
     * @brief Number of columns
     * 
     */
  int numColumns;
  MyVector<MyVector<T>> myVect;

public:
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
     */
  MatrixController(int rows, int columns);
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
     * @brief Calculate and returns the transpose of the LMatrix object
     * @pre A LMatrix object is created
     * @post Creates a temporary LMatrix object and returns the transpose of the
     * c.o. LMatrix
     * @return LMatrix<T> A copy of the LMatrix c.o. transpose
     */
  M Transpose();
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
  M operator*(const T &val);
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