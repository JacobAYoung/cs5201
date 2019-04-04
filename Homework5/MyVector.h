#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <utility>

/**
 * @file MyVector.h
 * @class MyVector
 * @author Jake Young
 * @pre MyVector object is created
 * @pre Creates a MyVector object for which you can call any function within 
 * the class and use it to mess with vectors
 * @brief A similar concept to the std::vector object that can do specific
 * calculations and operations.
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
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
   * @pre: We have a MyVector object that we want to copy from
   * @post: We copy the MyVector source to the calling object
   * @param source: The MyVector object that we will be copying from
   */
  void copy(const MyVector<T> &source);

public:
  /**
   * @brief Construct a new My Vector object
   * 
   * @pre: Construct a new MyVector object
   * @post: A new MyVector object is created
   */
  MyVector();
  /**
   * @brief Construct a new My Vector object
   * 
   * @pre: Construct a new MyVector object with the known size of a vector.
   * Size cannot be < 0
   * @post: A new MyVector object is created with a certain vector size
   * @param size: Size of the vector
   */
  MyVector(int size);
  /**
   * @brief Copy constructor
   * 
   * @pre: MyVector object is being copied
   * @post: A new MyVector object is created with a certain vector size. Throws
   * an error if the size is below 0
   * @param source The MyVector object that will be copied from
   */
  MyVector(const MyVector<T> &source);
  /**
   * @brief Construct a new My Vector object
   * @pre A MyVector object is created and a temporary object is created
   * @post Allocates memory for a MyVector object
   * @param source 
   */
  MyVector(MyVector<T> &&source);
  /**
   * @brief Destroy the My Vector object
   * 
   * @pre: MyVector object will be destroied
   * @post: The MyVector object is deallocated from memory
   */
  ~MyVector();
  /**
   * @brief operator[]: [] operator that returns the data of the pointer at the specified position
   * 
   * @pre: The position of the data is known
   * @post: Returns the data from the pointer of the specified position. Throws
   * an error if the position is out of the size.
   * @param i Position number
   * @return T& Returns the data from the pointer at the specific position
   */
  T &operator[](const int &i);
  /**
   * @brief operator[]: [] operator that returns the data of the pointer at the
   * specified position but it's a constant value
   * 
   * @pre: The position of the data is known
   * @post: Returns the data from the pointer of the specified position as a
   * constant value. Throws an error if the position is out of the size.
   * @param i Position number
   * @return T& Returns the data from the pointer at the specific position as a
   * constant value
   */
  T &operator[](const int &i) const;
  /**
   * @brief Assignment operator for assigning a MyVector object to another.
   * 
   * @pre: MyVector object is created and want's to be assigned to calling object
   * @post: Sets the calling object MyVector object to the source MyVector object
   * @param source MyVector object
   * @return MyVector<T>& Assigns the MyVector object source to the calling object
   */
  MyVector<T> &operator=(const MyVector<T> &source);
  /**
   * @brief Get the Num Elements object
   * 
   * @pre: MyVector object is created
   * @post: Returns the number of elements within the MyVector object
   * @return int The value of the MyVector object's number of elements within
   * the vector
   */
  int GetNumElements() const;
  /**
   * @brief Set the Size of the object
   * 
   * @pre: MyVector object is created and want's to set the size
   * @post: Sets the calling object's size to the value of n. Throws an error
   * if the size is below 0
   * @param n size
   */
  void SetSize(const int n);
  /**
   * @brief Adds values onto the MyVector object. I had to declare it as a
   * double because there was no easy way of me using a template value with it.
   * It would use MyVector<MyVector<T>> instead of just the T which I would need
   * it to be a double for this to work...
   * @pre A MyVector object is created
   * @post Add's a MyVector object onto the MyVector<MyVector<T>> object
   * 
   * @param source MyVector object
   */
  void PushBack(const MyVector<double> &source);
  void deletePointer(const int &n);
};
/**
 * @brief operator==: == operator that checks to see if both the lhs MyVector
 * object and rhs MyVector object are the same.
 * @pre: The MyVector object is created
 * @post: Returns a boolean value dependent on whether the two MyVector
 * objects are the exact same
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return true if they are equal
 * @return false if they are not equal
 */
template <typename T>
bool operator==(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief operator!=: != operator that checks to see if both the lhs MyVector
 * object and rhs MyVector object are not the same.
 * 
 * @pre: The MyVector object is created
 * @post: Returns a boolean value dependent on whether the two MyVector objects
 * are not the same
 * 
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return true if they are not equal
 * @return false if they are equal
 */
template <typename T>
bool operator!=(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Adds the two vector objects together
 * 
 * @pre: There are two MyVector objects created that have the exact same amount
 * of elements within them
 * @post: Returns a MyVector object of the two added vectors. Throws an error
 * if the vectors aren't the same size.
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return MyVector<T> A MyVector object of the 2 added vectors
 */
template <typename T>
MyVector<T> operator+(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Subtracts the two vector objects
 * 
 * @pre: There are two MyVector objects created that have the exact same amount
 * of elements within them
 * @post: Returns a MyVector object of the two subtracted vectors. Throws an
 * error if the vectors aren't the same size.
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return MyVector<T> A MyVector object of the 2 subtracted vectors
 */
template <typename T>
MyVector<T> operator-(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Dot product of 2 vectors
 * 
 * @pre: There are two MyVector objects created that have the exact same amount
 * of elements within them
 * @post: Returns a T value of the 2 vectors that have been dotted together.
 * Throws an error if the vector sizes aren't the same size.
 * @param lhs MyVector object on the left side
 * @param rhs MyVector object on the right side
 * @return T Returns a T value of the 2 vectors that have been dotted together
 */
template <typename T>
T operator*(const MyVector<T> &lhs, const MyVector<T> &rhs);
/**
 * @brief Negates the values within the MyVector object
 * 
 * @pre: A MyVector object has been created with values
 * @post: Returns a MyVector object that has all of it's values negated. Throws
 * an error if the vectors aren't the same size
 * @param source A MyVector object
 * @return MyVector<T> A MyVector object with all it's values negated
 */
template <typename T>
MyVector<T> operator-(const MyVector<T> &source);
/**
 * @brief operator<<: << operator that directs the output of the MyVector object
 * 
 * @pre: The MyVector object is created
 * @post: Returns the elements of the MyVector object
 * @param out std::ostream output
 * @param source MyVector object
 * @return std::ostream& Returns the elements of the MyVector object as an
 * ostream object
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &source);
/**
 * @brief operator>>: >> operator that directs the input of data to the MyVector object data
 * 
 * @pre: The MyVector object is created and theres data being streamed into the object
 * @post: Sets the element values of the MyVector object
 * @param in std::istream object
 * @param source MyVector object
 * @return std::istream& Sets the element values of the MyVector object
 */
template <typename T>
std::istream &operator>>(std::istream &in, const MyVector<T> &source);

#include "MyVector.hpp"