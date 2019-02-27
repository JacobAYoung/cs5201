#pragma once

#include <cmath>
#include <iomanip>
#include <utility>

using namespace std;

template <class T>
class MyVector
{
private:
  int numElements;
  T *ptr_to_data;
  void copy(const MyVector<T> &source);

public:
  MyVector();
  MyVector(int n);
  MyVector(const MyVector<T> &source);
  MyVector(MyVector<T> &&source);
  ~MyVector();
  T &operator[](const int &i);
  T &operator[](const int &i) const;
  int GetNumElements() const;
  MyVector<T> &operator=(const MyVector<T> &source);
  MyVector<T> &operator=(const T val);
  void SetSize(const int n);
};
//operator==: == operator that checks to see if both the lhs Cylindrical object and rhs Cylindrical object are the same.
//Param1: Cylindrical object
//Pre: The Cylindrical object is created
//Post: Returns a boolean value dependent on whether the two Cylindrical objects are the exact same
template <class T>
bool operator==(const MyVector<T> &lhs, const MyVector<T> &rhs);

//operator!=: != operator that checks to see if both the lhs Cylindrical object and rhs Cylindrical object are not the same.
//Param1: Cylindrical object
//Pre: The Cylindrical object is created
//Post: Returns a boolean value dependent on whether the two Cylindrical objects are not the same
template <class T>
bool operator!=(const MyVector<T> &lhs, const MyVector<T> &rhs);

template <class T>
MyVector<T> operator+(const MyVector<T> &lhs, const MyVector<T> &rhs);

//operator-: - operator That finds the reflection through the origin
//Pre: The data pointer must be constructed and filled with data to find the reflection through the origin
//Post: Returns a Cylindrical object of type T that has the adjusted coordinates for the reflection through the origin
template <typename T>
MyVector<T> operator-(const MyVector<T> &source);

template <typename T>
MyVector<T> operator-(const MyVector<T> &lhs, const MyVector<T> &rhs);

template <typename T>
T operator*(const MyVector<T> &lhs, const MyVector<T> &rhs);

template <typename T>
MyVector<T> operator*(const T &lhs, const MyVector<T> &rhs);

//operator<<: << operator that directs the output of the cylindrical object
//Pre: The Cylindrical object is created
//Post: Returns the ostream of the radius, theta and z values
template <class T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &source);

//operator>>: >> operator that directs the input of data to the Cylindrical object data
//Pre: The Cylindrical object is created and theres data being streamed into the object
//Post: Sets the radius, theta and z values in the Cylindrical object
template <class T>
std::istream &operator>>(std::istream &in, const MyVector<T> &source);

#include "MyVector.hpp"