///Author: Jake Young
///Date: 2-15-2019
///PRE: Cylindrical object is created
///POST: Creates a Cylindrical object for which you can call any function within the class and use it to calculate and compare Cylindrical objects

#pragma once

#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;
template <class T>
class Cylindrical
{
private:
  //A pointer that contains all data about the Cylindrical object
  T *ptr_to_data;

  //CylindricalCopy: Copys from the Cylindrical object source and applys the data to the current object
  //Param1: Cylindrical object
  //Pre: Cylindrical object is created
  //Post: Copys the source Cylindrical object to the current object
  void CylindricalCopy(const Cylindrical<T> &source);

  //CalculateDistance: Calculates the distance from the origin to the point of the Cylindrical object
  //Param1: Cylindrical object
  //Pre: Cylindrical object is created
  //Post: Returns the calculation of the distance from the origin to the point of the Cylindrical object
  T &CalculateDistance(const Cylindrical<T> &source); //could be T return type

public:
  //Cylindrical: Default constructor that initializes the pointer of data
  //Pre: The object is being created without a radius, theta or z information
  //Post: Creates the Cylindrical object with default data as 0
  Cylindrical();

  //Cylindrical: Constructor that initializes the pointer of data with the given parameters
  //Param1: Radius
  //Param2: Theta
  //Param3: Z
  //Pre: The object is being created with a radius, theta or z information
  //Post: Creates the Cylindrical object with the parameter data and calculates the x and y coordinates
  //Stores everything within the ptr_to_data array
  Cylindrical(const T &radius, const T &theta, const T &z);

  Cylindrical(const Cylindrical<T> &source);

  //~Cylindrical: Destructs the created object
  //Pre: Cylindrical object was created
  //Post: Deallocates the memory of the object and cleans up the pointer array
  ~Cylindrical();

  //operator[]: [] operator that returns the data of the pointer at the specified position
  //Param1: Position number
  //Pre: The position of the data is known
  //Post: Returns the data from the pointer of the specified position
  T &operator[](const int &i);

  T &operator[](const int i) const;

  //operator=: = operator that sets the rhs Cylindrical object equal to the lhs Cylindrical object
  //Param1: Cylindrical object
  //Pre: The Cylindrical object is created
  //Post: Returns a Cylindrical object that has the data of the source Cylindrical object
  Cylindrical<T> &operator=(const Cylindrical<T> &source);

  //GetR: Accessor of the Radius data from the data array pointer
  //Pre: The Cylindrical object is created
  //Post: Returns the Radius data from the data array pointer
  T GetR() const;

  //GetTheta: Accessor of the Theta data from the data array pointer
  //Pre: The Cylindrical object is created
  //Post: Returns the Theta data from the data array pointer
  T GetTheta() const;

  //GetX: Accessor of the X data from the data array pointer
  //Pre: The Cylindrical object is created
  //Post: Returns the X data from the data array pointer
  T GetX() const;

  //GetY: Accessor of the Y data from the data array pointer
  //Pre: The Cylindrical object is created
  //Post: Returns the Y data from the data array pointer
  T GetY() const;

  //GetZ: Accessor of the Z data from the data array pointer
  //Pre: The Cylindrical object is created
  //Post: Returns the Z data from the data array pointer
  T GetZ() const;

  string PrintPoints() const;
};

//operator<: < operator that checks the distance of two Cylindrical objects and compares to see which is closer to the origin
//Param1: Cylindrical object
//Pre: The Cylindrical object is created
//Post: Returns a boolean value to see if the lhs Cylindrical object is closer to the origin
template <class T>
bool operator<(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs);

//operator>: > operator that checks the distance of two Cylindrical objects and compares to see which is closer to the origin
//Param1: Cylindrical object
//Pre: The Cylindrical object is created
//Post: Returns a boolean value to see if the rhs Cylindrical object is closer to the origin
template <class T>
bool operator>(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs);

//operator==: == operator that checks to see if both the lhs Cylindrical object and rhs Cylindrical object are the same.
//Param1: Cylindrical object
//Pre: The Cylindrical object is created
//Post: Returns a boolean value dependent on whether the two Cylindrical objects are the exact same
template <class T>
bool operator==(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs);

//operator!=: != operator that checks to see if both the lhs Cylindrical object and rhs Cylindrical object are not the same.
//Param1: Cylindrical object
//Pre: The Cylindrical object is created
//Post: Returns a boolean value dependent on whether the two Cylindrical objects are not the same
template <class T>
bool operator!=(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs);

//operator~: ~ operator That calculates the magnitude of the Cylindrical object
//Pre: The data pointer must be constructed and filled with data to calculate the magnitude
//Post: Returns the calcuation of the magnitude for the Cylindrical object
template <typename T>
double operator~(const Cylindrical<T> &source);

//operator-: - operator That finds the reflection through the origin
//Pre: The data pointer must be constructed and filled with data to find the reflection through the origin
//Post: Returns a Cylindrical object of type T that has the adjusted coordinates for the reflection through the origin
template <typename T>
Cylindrical<T> operator-(const Cylindrical<T> &source);

//operator!: ! operator That finds the reflection through the z axis
//Pre: The data pointer must be constructed and filled with data to find the reflection through the z axis
//Post: Returns a Cylindrical object of type T that has the adjusted coordinates for the reflection through the z axis
template <typename T>
Cylindrical<T> operator!(const Cylindrical<T> &source);

template <class T>
std::ostream &operator<<(std::ostream &out, const Cylindrical<T> &source);

template <class T>
std::istream &operator>>(std::istream &in, const Cylindrical<T> &source);

#include "Cylindrical.hpp"