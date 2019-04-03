#include "MyVector.h"

template <class M, class T>
class IMatrix
{
public:
  // virtual void PushBack(const MyVector<T> &source) = 0;
  // virtual int GetRows() const = 0;
  // virtual int GetColumns() const = 0;
  virtual bool operator==(const M &source) = 0;
  virtual bool operator!=(const M &source) = 0;
  virtual M operator*(const T &val) = 0;
  // virtual M operator-() = 0;
  virtual ~IMatrix() {}
};
