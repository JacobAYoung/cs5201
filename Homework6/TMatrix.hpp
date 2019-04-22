template <class T>
TMatrix<T>::TMatrix()
{
    MatrixController<TMatrix<T>, T> mc;
    my_controller = mc;
}

template <class T>
TMatrix<T>::TMatrix(int rows, int columns)
{
    MatrixController<TMatrix<T>, T> mc(rows, columns, MatrixController<TMatrix<T>, T>::TMatrix);
    my_controller = mc;
}

template <class T>
TMatrix<T>::TMatrix(const TMatrix<T> &source)
{
    MatrixController<TMatrix<T>, T> mc(source.GetRows(), source.GetColumns(), MatrixController<TMatrix<T>, T>::TMatrix);
    mc.copy(source);
    my_controller = mc;
}

template <class T>
TMatrix<T>::~TMatrix() {}

template <class T>
TMatrix<T>::TMatrix(TMatrix<T> &&source)
{
    my_controller.SetRows(source.GetRows());
    my_controller.SetColumns(source.GetColumns());
    std::swap(my_controller, source.my_controller);
    source.my_controller.SetRows(0);
    source.my_controller.SetColumns(0);
}

template <class T>
int TMatrix<T>::GetRows() const
{
    return my_controller.GetRows();
}

template <class T>
int TMatrix<T>::GetColumns() const
{
    return my_controller.GetColumns();
}

template <class T>
TMatrix<T> TMatrix<T>::Transpose()
{
    TMatrix<T> temp(this->GetColumns(), this->GetRows());
    for (int i = 0; i < this->GetRows(); i++)
    {
        for (int j = 0; j < this->GetColumns(); j++)
        {
            temp(j, i) = operator()(i, j);
        }
    }
    return temp;
}

template <class T>
MyVector<T> &TMatrix<T>::operator[](const int &i)
{
    return my_controller[i];
}

template <class T>
MyVector<T> &TMatrix<T>::operator[](const int &i) const
{
    return my_controller[i];
}

template <class T>
T &TMatrix<T>::operator()(const int &i, const int &j)
{
    if (i < GetRows())
    {
        if (j > GetColumns())
        {
            throw std::range_error("Out of bounds");
        }
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
    if (i >= 0)
    {
        if (j >= 0)
        {
            if (i == 0 && j < 2)
            {
                return my_controller[i][j];
            }
            else if (i == GetRows() - 1 && j > GetRows() - 3)
            {
                if (j >= i)
                {
                    return my_controller[i][j - i + 1];
                }
                else
                {
                    return my_controller[i][i - j - 1];
                }
            }
            else if (j >= i - 1 && j <= i + 1)
            {
                return my_controller[i][j - i + 1];
            }
            else
            {
                static T temp;
                return temp;
            }
        }
        else
        {
            throw std::range_error("Out of bounds");
        }
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
T &TMatrix<T>::operator()(const int &i, const int &j) const
{
    if (i < GetRows())
    {
        if (j > GetColumns())
        {
            throw std::range_error("Out of bounds");
        }
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
    if (i >= 0)
    {
        if (j >= 0)
        {
            if (i == 0 && j < 2)
            {
                return my_controller[i][j];
            }
            else if (i == GetRows() - 1 && j > GetRows() - 3)
            {
                if (j >= i)
                {
                    return my_controller[i][j - i + 1];
                }
                else
                {
                    return my_controller[i][i - j - 1];
                }
            }
            else if (j >= i - 1 && j <= i + 1)
            {
                return my_controller[i][j - i + 1];
            }
            else
            {
                static T temp;
                return temp;
            }
        }
        else
        {
            throw std::range_error("Out of bounds");
        }
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
void TMatrix<T>::PushBack(const MyVector<T> &source)
{
    my_controller.PushBack(source);
    return;
}

template <class T>
TMatrix<T> TMatrix<T>::operator*(const T &val) const
{
    return my_controller * val;
}

template <class T>
TMatrix<T> &TMatrix<T>::operator=(const TMatrix<T> &source)
{
    if (*this != source)
    {
        my_controller.SetRows(source.GetRows());
        my_controller.SetColumns(source.GetColumns());
        my_controller = source.my_controller;
    }
    return (*this);
}

template <class T>
TMatrix<T> &TMatrix<T>::operator=(const Matrix<T> &source)
{
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
        {
            if (i == 0 && j < 2)
            {
                operator()(i, j) = source[i][j];
            }
            else if (i == 0 && j >= 2)
            {
                continue;
            }
            else if (i == (source.GetRows() - 1) && j < source.GetColumns() - 2)
            {
                continue;
            }
            else if (i == GetRows() - 1 && j > GetRows() - 3)
            {
                if (j >= i)
                {
                    operator()(i, j) = source[i][j];
                }
                else if ((j + 1) == (source.GetColumns() - 1))
                {
                    operator()(i, j) = source[i][j];
                }
            }
            else if (j >= i - 1 && j <= i + 1)
            {
                operator()(i, j) = source[i][j];
            }
        }
    }
    return *this;
}

template <class T>
Matrix<T> TMatrix<T>::add(const IMatrix<Matrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) + source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::subtract(const IMatrix<Matrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) - source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::multiply(const IMatrix<Matrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetRows())
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < source.GetColumns(); j++)
            {
                for (int k = 0; k < GetColumns(); k++)
                {
                    temp(i, j) += operator()(i, k) * source(k, j);
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
bool TMatrix<T>::equals(const IMatrix<Matrix<T>, T> &source) const
{
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    if (operator()(i, j) != source(i, j))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <class T>
Matrix<T> TMatrix<T>::add(const IMatrix<TMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) + source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::subtract(const IMatrix<TMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) - source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::multiply(const IMatrix<TMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetRows())
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < source.GetColumns(); j++)
            {
                for (int k = 0; k < GetColumns(); k++)
                {
                    temp(i, j) += operator()(i, k) * source(k, j);
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
bool TMatrix<T>::equals(const IMatrix<TMatrix<T>, T> &source) const
{
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    if (operator()(i, j) != source(i, j))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <class T>
Matrix<T> TMatrix<T>::add(const IMatrix<LMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) + source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::subtract(const IMatrix<LMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) - source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::multiply(const IMatrix<LMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetRows())
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < source.GetColumns(); j++)
            {
                for (int k = 0; k < GetColumns(); k++)
                {
                    temp(i, j) += operator()(i, k) * source(k, j);
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
bool TMatrix<T>::equals(const IMatrix<LMatrix<T>, T> &source) const
{
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    if (operator()(i, j) != source(i, j))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <class T>
Matrix<T> TMatrix<T>::add(const IMatrix<UMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) + source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::subtract(const IMatrix<UMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) - source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::multiply(const IMatrix<UMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetRows())
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < source.GetColumns(); j++)
            {
                for (int k = 0; k < GetColumns(); k++)
                {
                    temp(i, j) += operator()(i, k) * source(k, j);
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
bool TMatrix<T>::equals(const IMatrix<UMatrix<T>, T> &source) const
{
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    if (operator()(i, j) != source(i, j))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <class T>
Matrix<T> TMatrix<T>::add(const IMatrix<SMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) + source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::subtract(const IMatrix<SMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) - source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::multiply(const IMatrix<SMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetRows())
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < source.GetColumns(); j++)
            {
                for (int k = 0; k < GetColumns(); k++)
                {
                    temp(i, j) += operator()(i, k) * source(k, j);
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
bool TMatrix<T>::equals(const IMatrix<SMatrix<T>, T> &source) const
{
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    if (operator()(i, j) != source(i, j))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <class T>
Matrix<T> TMatrix<T>::add(const IMatrix<DMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) + source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::subtract(const IMatrix<DMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    temp(i, j) = operator()(i, j) - source(i, j);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
Matrix<T> TMatrix<T>::multiply(const IMatrix<DMatrix<T>, T> &source) const
{
    Matrix<T> temp(GetRows(), source.GetColumns());
    if (GetColumns() == source.GetRows())
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < source.GetColumns(); j++)
            {
                for (int k = 0; k < GetColumns(); k++)
                {
                    temp(i, j) += operator()(i, k) * source(k, j);
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
bool TMatrix<T>::equals(const IMatrix<DMatrix<T>, T> &source) const
{
    if (GetColumns() == source.GetColumns())
    {
        if (GetRows() == source.GetRows())
        {
            for (int i = 0; i < GetRows(); i++)
            {
                for (int j = 0; j < GetColumns(); j++)
                {
                    if (operator()(i, j) != source(i, j))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const TMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs(i, i) != rhs(i, i))
                {
                    return false;
                }
                if (i < lhs.GetColumns() - 1)
                {
                    if (lhs(i, i + 1) != rhs(i, i + 1))
                    {
                        return false;
                    }
                }
                if (i > 0)
                {
                    if (lhs(i, i - 1) != rhs(i, i - 1))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const TMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs(i, i) != rhs(i, i))
                {
                    return false;
                }
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (j < i)
                    {
                        if (lhs(i, j) != rhs(i, j))
                        {
                            return false;
                        }
                    }
                    else if (j > i)
                    {
                        if (lhs(i, j) != 0)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const TMatrix<T> &lhs, const Matrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (rhs[i][i] != lhs(i, i))
                {
                    return false;
                }
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        if (rhs[i][j] != 0)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (rhs[i][j] != lhs(i, j))
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const Matrix<T> &lhs, const TMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs[i][i] != rhs(i, i))
                {
                    return false;
                }
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        if (lhs[i][j] != 0)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (lhs[i][j] != rhs(i, j))
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const TMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (rhs[i][i] != lhs(i, i))
                {
                    return false;
                }
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        if (rhs[i][j] != 0)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (rhs[i][j] != lhs(i, j))
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const SMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs[i][i] != rhs(i, i))
                {
                    return false;
                }
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        if (lhs[i][j] != 0)
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (lhs[i][j] != rhs(i, j))
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const TMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs(i, i) != rhs(i, i))
                {
                    return false;
                }
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (!((j > i + 1) || (i > j + 1)))
                    {
                        if (lhs[i][j] != 0)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator==(const TMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs(i, i) != rhs(i, i))
                {
                    return false;
                }
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (j > i)
                    {
                        if (lhs(i, j) != rhs(i, j))
                        {
                            return false;
                        }
                    }
                    else if (j < i)
                    {
                        if (lhs(i, j) != 0)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

template <typename T>
bool operator!=(const TMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const TMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const TMatrix<T> &lhs, const Matrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const Matrix<T> &lhs, const TMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const TMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const SMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const TMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const TMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
TMatrix<T> operator-(const TMatrix<T> &source)
{
    TMatrix<T> temp(source.GetRows(), source.GetColumns());
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = i; j < source.GetColumns(); j++)
        {
            if (source(i, j) != 0)
            {
                temp(i, j) = -1 * source(i, j);
            }
        }
    }
    return temp;
}

template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    int rows = lhs.GetRows();
    int columns = lhs.GetColumns();
    Matrix<T> temp(rows, columns);
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < rows; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k <= i + 1; k++)
                    {
                        if (j == 2)
                        {
                            if (k == 0)
                            {
                                continue;
                            }
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                        else
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
            }
            else if (i == (rows - 1))
            {
                for (int j = i - 2; j < rows; j++)
                {
                    if (j == rows - 3)
                    {
                        int k = rows - 2;
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                    else
                    {
                        for (int k = rows - 2; k < rows; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
            }
            else if (i == 1)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (j == 0)
                    {
                        for (int k = 0; k < 2; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                    else if (j == 1)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                    else if (j == 2)
                    {
                        for (int k = 1; k < 3; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                    else if (j == 3)
                    {
                        for (int k = 2; k < 4; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
            }
            else
            {
                int counter = 0;
                for (int j = i - 2; j < rows; j++)
                {
                    if (counter == 0)
                    {
                        temp[i][j] += lhs(i, j + 1) * rhs(j + 1, j);
                    }
                    else if (counter == 1)
                    {
                        for (int k = j; k <= j + 1; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                    else if (counter == 2)
                    {
                        for (int k = j - 1; k < j + 2; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                    else
                    {
                        for (int k = j - 1; k < j + 1; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                    counter++;
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            int counter = 0;
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                if (i == 0)
                {
                    for (int k = counter; k <= i + 1; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                    counter++;
                }
                else if (i == (lhs.GetColumns() - 1))
                {
                    for (int k = i - 1; k < lhs.GetColumns(); k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                }
                else if (i == 1)
                {
                    if (j <= 2)
                    {
                        for (int k = j; k < 3; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
                else
                {
                    for (int k = j; k < rhs.GetColumns(); k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                if (i == 0)
                {
                    if (j == 0)
                    {
                        temp[i][j] += lhs(i, i) * rhs(i, i);
                    }
                    else
                    {
                        for (int k = i; k < 2; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
                else if (i == (lhs.GetColumns() - 1))
                {
                    for (int k = i - 1; k < lhs.GetColumns(); k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                }
                else if (i == 1)
                {
                    int max = j + 1;
                    if (max == 4)
                    {
                        max = 3;
                    }
                    for (int k = 0; k < max; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                }
                else
                {
                    for (int k = i - 1; k <= i + 1; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &lhs, const TMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetColumns(); i++)
        {
            for (int j = 0; j < lhs.GetColumns(); j++)
            {
                if (j == 0)
                {
                    for (int k = j; k < 2; k++)
                    {
                        temp[i][j] += lhs[i][k] * rhs(k, j);
                    }
                }
                else if (j == lhs.GetColumns() - 1)
                {
                    for (int k = lhs.GetColumns() - 2; k <= lhs.GetColumns() - 1; k++)
                    {
                        temp[i][j] += lhs[i][k] * rhs(k, j);
                    }
                }
                else
                {
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        temp[i][j] += lhs[i][k] * rhs(k, j);
                    }
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetColumns(); i++)
        {
            for (int j = 0; j < lhs.GetColumns(); j++)
            {
                if (i == 0)
                {
                    for (int k = i; k <= i + 1; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs[k][j];
                    }
                }
                else if (i == lhs.GetColumns() - 1)
                {
                    for (int k = i - 1; k <= i; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs[k][j];
                    }
                }
                else
                {
                    for (int k = i - 1; k <= i + 1; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs[k][j];
                    }
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator*(const TMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                if (i == 0)
                {
                    for (int k = i; k <= i + 1; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs[k][j];
                    }
                }
                else if (i == lhs.GetColumns() - 1)
                {
                    for (int k = i - 1; k <= i; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs[k][j];
                    }
                }
                else
                {
                    for (int k = i - 1; k <= i + 1; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs[k][j];
                    }
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator*(const SMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                if (j == 0)
                {
                    for (int k = j; k < 2; k++)
                    {
                        temp[i][j] += lhs[i][k] * rhs(k, j);
                    }
                }
                else if (j == lhs.GetColumns() - 1)
                {
                    for (int k = lhs.GetColumns() - 2; k <= lhs.GetColumns() - 1; k++)
                    {
                        temp[i][j] += lhs[i][k] * rhs(k, j);
                    }
                }
                else
                {
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        temp[i][j] += lhs[i][k] * rhs(k, j);
                    }
                }
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
TMatrix<T> operator*(const TMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    TMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetColumns(); i++)
        {
            temp(i, i) = lhs(i, i) * rhs(i, i);
            if (i < lhs.GetColumns() - 1)
            {
                temp(i, i + 1) = lhs(i, i + 1) * rhs(i, i);
            }
            if (i > 0)
            {
                temp(i, i - 1) = lhs(i, i - 1) * rhs(i, i);
            }
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
TMatrix<T> operator+(const TMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    TMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) + rhs(i, i);
                if (i < lhs.GetColumns() - 1)
                {
                    temp(i, i + 1) = lhs(i, i + 1) + rhs(i, i + 1);
                }
                if (i > 0)
                {
                    temp(i, i - 1) = lhs(i, i - 1) + rhs(i, i - 1);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs(i, i) + rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (j < i)
                    {
                        temp[i][j] = lhs(i, j) + rhs(i, j);
                    }
                    else if (j > i)
                    {
                        temp[i][j] = lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator+(const Matrix<T> &lhs, const TMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] + rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = lhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = lhs[i][j] + rhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = rhs[i][i] + lhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = rhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = rhs[i][j] + lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = rhs[i][i] + lhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = rhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = rhs[i][j] + lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator+(const SMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] + rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = lhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = lhs[i][j] + rhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
TMatrix<T> operator+(const TMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    TMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) + rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (!((j > i + 1) || (i > j + 1)) && i != j)
                    {
                        temp(i, j) = lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator+(const TMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) + rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (j > i)
                    {
                        temp[i][j] = lhs(i, j) + rhs(i, j);
                    }
                    else if (!((j > i + 1) || (i > j + 1)) && i != j)
                    {
                        temp[i][j] = lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <class T>
TMatrix<T> operator-(const TMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    TMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) - rhs(i, i);
                if (i < lhs.GetColumns() - 1)
                {
                    temp(i, i + 1) = lhs(i, i + 1) - rhs(i, i + 1);
                }
                if (i > 0)
                {
                    temp(i, i - 1) = lhs(i, i - 1) - rhs(i, i - 1);
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs(i, i) - rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (j < i)
                    {
                        temp[i][j] = lhs(i, j) - rhs(i, j);
                    }
                    else if (j > i)
                    {
                        temp[i][j] = lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator-(const Matrix<T> &lhs, const TMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] - rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = lhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = lhs[i][j] - rhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = rhs[i][i] + lhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = 0 - rhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = lhs(i, j) - rhs[i][j];
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = rhs[i][i] - lhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = 0 - rhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = lhs(i, j) - rhs[i][j];
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator-(const SMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] - rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if ((j > i + 1) || (i > j + 1))
                    {
                        temp[i][j] = lhs[i][j];
                    }
                    else
                    {
                        temp[i][j] = lhs[i][j] - rhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
TMatrix<T> operator-(const TMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    TMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) - rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (!((j > i + 1) || (i > j + 1)) && i != j)
                    {
                        temp(i, j) = lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
Matrix<T> operator-(const TMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) - rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (j > i)
                    {
                        temp[i][j] = lhs(i, j) - rhs(i, j);
                    }
                    else if (!((j > i + 1) || (i > j + 1)) && i != j)
                    {
                        temp[i][j] = lhs(i, j);
                    }
                }
            }
        }
        else
        {
            throw std::length_error("Matrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const TMatrix<T> &source)
{
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
        {
            cout << source(i, j) << " ";
        }
        if (i != source.GetRows() - 1)
        {
            cout << endl;
        }
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &in, TMatrix<T> &source)
{
    MyVector<double> temp(source.GetColumns());
    for (int i = 0; i < source.GetColumns(); i++)
    {
        in >> temp[i];
    }
    source.PushBack(temp);
    return in;
}