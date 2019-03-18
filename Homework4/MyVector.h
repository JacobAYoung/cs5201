///Author: Jake Young
///Date: 2-29-2019
///PRE: MyVector object is created
/// POST: Creates a MyVector object for which you can call any function within
/// the class and use it to mess with vectors

#pragma once

#include <cmath>
#include <iomanip>
#include <utility>

using namespace std;

template <class T>
class MyVector
{
private:
  /**
   * @brief Number of elements for each vector
   * 
   */
  int numElements;
  /**
   * @brief The pointer that points to each of my data.
   * 
   */
  T *ptr_to_data;
  /**
   * @brief Copy function that copys the MyVector object to the calling object
   * 
   * //Pre: We have a MyVector object that we want to copy from
   * //Post: We copy the MyVector source to the calling object
   * @param source: The MyVector object that we will be copying from
   */
  void copy(const MyVector<T> &source);

public:
  /**
   * @brief Construct a new My Vector object
   * 
   * //Pre: Construct a new MyVector object
   * //Post: A new MyVector object is created
   */
  MyVector();
  /**
   * @brief Construct a new My Vector object
   * 
   * //Pre: Construct a new MyVector object with the known size of a vector.
   * Size cannot be < 0
   * //Post: A new MyVector object is created with a certain vector size
   * @param size: Size of the vector
   */
  MyVector(int size);
  /**
   * @brief Copy constructor
   * 
   * //Pre: MyVector object is being copied
   * //Post: A new MyVector object is created with a certain vector size
   * @param source The MyVector object that will be copied from
   */
  MyVector(const MyVector<T> &source);

  MyVector(MyVector<T> &&source);
  /**
   * @brief Destroy the My Vector object
   * 
   * //Pre: MyVector object will be destroied
   * //Post: The MyVector object is deallocated from memory
   */
  ~MyVector();
  /**
   * @brief operator[]: [] operator that returns the data of the pointer at the specified position
   * 
   * //Pre: The position of the data is known
   * //Post: Returns the data from the pointer of the specified position
   * @param i Position number
   * @return T& Returns the data from the pointer at the specific position
   */
  T &operator[](const int &i);
  /**
   * @brief operator[]: [] operator that returns the data of the pointer at the
   * specified position but it's a constant value
   * 
   * //Pre: The position of the data is known
   * //Post: Returns the data from the pointer of the specified position as a
   * constant value
   * @param i Position number
   * @return T& Returns the data from the pointer at the specific position as a
   * constant value
   */
  T &operator[](const int &i) const;
  /**
   * @brief Assignment operator for assigning a MyVector object to another.
   * 
   * //Pre: MyVector object is created and want's to be assigned to calling object
   * //Post: Sets the calling object MyVector object to the source MyVector object
   * @param source MyVector object
   * @return MyVector<T>& Assigns the MyVector object source to the calling object
   */
  MyVector<T> &operator=(const MyVector<T> &source);
  /**
   * @brief Get the Num Elements object
   * 
   * //Pre: MyVector object is created
   * //Post: Returns the number of elements within the MyVector object
   * @return int The value of the MyVector object's number of elements within
   * the vector
   */
  int GetNumElements() const;
  /**
   * @brief Set the Size of the object
   * 
   * //Pre: MyVector object is created and want's to set the size
   * //Post: Sets the calling object's size to the value of n
   * @param n size
   */
  void SetSize(const int n);

  void PushBack(const MyVector<double> &source);
};
/**
 * @brief operator==: == operator that checks to see if both the lhs MyVector
 * object and rhs MyVector object are the same.
 * //Pre: The MyVector object is created
 * //Post: Returns a boolean value dependent on whether the two MyVector
 * //objects are the exact same
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return true if they are equal
 * @return false if they are not equal
 */
template <class T>
bool operator==(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief operator!=: != operator that checks to see if both the lhs MyVector object
 * // and rhs MyVector object are not the same.
 * 
 * //Pre: The MyVector object is created
 * //Post: Returns a boolean value dependent on whether the two MyVector objects
 * are not the same
 * 
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return true if they are not equal
 * @return false if they are equal
 */
template <class T>
bool operator!=(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Adds the two vector objects together
 * 
 * //Pre: There are two MyVector objects created that have the exact same amount
 * of elements within them
 * //Post: Returns a MyVector object of the two added vectors
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return MyVector<T> A MyVector object of the 2 added vectors
 */
template <class T>
MyVector<T> operator+(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Subtracts the two vector objects
 * 
 * //Pre: There are two MyVector objects created that have the exact same amount
 * of elements within them
 * //Post: Returns a MyVector object of the two subtracted vectors
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return MyVector<T> A MyVector object of the 2 subtracted vectors
 */
template <typename T>
MyVector<T> operator-(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Dot product of 2 vectors
 * 
 * //Pre: There are two MyVector objects created that have the exact same amount
 * of elements within them
 * //Post: Returns a T value of the 2 vectors that have been dotted together
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return T Returns a T value of the 2 vectors that have been dotted together
 */
template <typename T>
T operator*(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Negates the values within the MyVector object
 * 
 * //Pre: A MyVector object has been created with values
 * //Post: Returns a MyVector object that has all of it's values negated
 * @param source A MyVector object
 * @return MyVector<T> A MyVector object with all it's values negated
 */
template <typename T>
MyVector<T> operator-(const MyVector<T> &source);
//operator<<: << operator that directs the output of the MyVector object
//Pre: The MyVector object is created
//Post: Returns the elements of the MyVector object
/**
 * @brief operator<<: << operator that directs the output of the MyVector object
 * 
 * //Pre: The MyVector object is created
 * //Post: Returns the elements of the MyVector object
 * @param out std::ostream output
 * @param source MyVector object
 * @return std::ostream& Returns the elements of the MyVector object as an
 * ostream object
 */
template <class T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &source);
/**
 * @brief operator>>: >> operator that directs the input of data to the MyVector object data
 * 
 * //Pre: The MyVector object is created and theres data being streamed into the object
 * //Post: Sets the element values of the MyVector object
 * @param in std::istream object
 * @param source MyVector object
 * @return std::istream& Sets the element values of the MyVector object
 */
template <class T>
std::istream &operator>>(std::istream &in, const MyVector<T> &source);

#include "MyVector.hpp"