///Author: Jake Young
///Date: 2-29-2019
///PRE: MyVector object is created and LinearIndependent object is created
/// POST: Creates a LinearIndependent object and calculates the MyVector
/// object's to see if they are Linear Independent or not

#pragma once

#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

template <class T>
class LinearIndependent
{
private:
  /**
   * @brief A vector of the returned data from the Linear Independence checker
   * 
   */
  vector<T> data;

public:
  /**
   * @brief Construct a new LinearIndependent object
   * 
   * //Pre: Construct a new LinearIndependent object
   * //Post: A new LinearIndependent object is created
   */
  LinearIndependent();
  /**
   * @brief Construct a new LinearIndependent object
   * 
   * //Pre: Construct a new LinearIndependent object with the known size of a vector.
   * Size cannot be < 0
   * //Post: A new LinearIndependent object is created with a certain vector size
   * @param size: Size of the vector
   */
  LinearIndependent(int size);
  /**
   * @brief Check if a matrix is linear independent or not
   * 
   * //Pre: A LinearIndependent object has been created and a the matrix has
   * data within it and we know the size of how many vectors
   * //Post: A boolean value depending on if the matrix is linear independent or
   * not
   * @param matrix A matrix of vectors
   * @param size Size of the functions to be tested upon
   * @return true If the matrix is linear dependent
   * @return false If the matrix is linear independent
   */
  bool CheckLinearIndependent(vector<vector<T>> &matrix, const int &size);
  /**
   * @brief Get the Data object
   * 
   * //Pre: A Linear object is created and assumed to have data after checking
   * if it's linear independent or not
   * //Post: Returns the vector of data from being check as linear dependent or not
   * @return vector<T> A vector of data from being check as linear dependent or not
   */
  vector<T> GetData() const;
  /**
   * @brief Get the Epsilon object
   * 
   * //Pre: A linear object is created
   * //Post: Returns the epsilon value
   * @return double returns the epsilon value
   */
  double GetEpsilon() const;
};

#include "LinearIndependent.hpp"