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
   * @brief 
   * 
   */
  vector<T> data;
  /**
   * @brief 
   * 
   */
  const double EPSILON = 0.0001;
  /**
   * @brief 
   * 
   */
  const int MAX_ITERATIONS = 500;

public:
  /**
   * @brief Construct a new Linear Independent object
   * 
   */
  LinearIndependent();
  /**
   * @brief Construct a new Linear Independent object
   * 
   * @param size 
   */
  LinearIndependent(int size);

  /**
   * @brief 
   * 
   * @param matrix 
   * @param size 
   * @return true 
   * @return false 
   */
  bool CheckLinearIndependent(vector<vector<T>> &matrix, const int &size);
  /**
   * @brief Get the Data object
   * 
   * @return vector<T> 
   */
  vector<T> GetData() const;
  /**
   * @brief Get the Epsilon object
   * 
   * @return double 
   */
  double GetEpsilon() const;
};

#include "LinearIndependent.hpp"