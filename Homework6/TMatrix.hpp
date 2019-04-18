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
    LMatrix<T> temp(this->GetColumns(), this->GetRows());
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
            throw std::range_error("Out of bounds1");
        }
    }
    else
    {
        throw std::range_error("Out of bounds2");
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
            throw std::range_error("Out of bounds3");
        }
    }
    else
    {
        throw std::range_error("Out of bounds4");
    }
}

template <class T>
T &TMatrix<T>::operator()(const int &i, const int &j) const
{
    if (i < GetRows())
    {
        if (j > GetColumns())
        {
            throw std::range_error("Out of bounds5");
        }
    }
    else
    {
        throw std::range_error("Out of bounds6");
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
            throw std::range_error("Out of bounds7");
        }
    }
    else
    {
        throw std::range_error("Out of bounds8");
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

template <typename T>
bool operator==(const TMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    if (lhs(i, j) != rhs(i, j))
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
                for (int j = i + 1; j < lhs.GetColumns(); j++)
                {
                    if (rhs(j, i) != 0)
                    {
                        return false;
                    }
                    if (lhs(i, j) != 0)
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
bool operator==(const TMatrix<T> &lhs, const Matrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs(i, i) != rhs[i][i])
                {
                    return false;
                }
                for (int j = i + 1; j < lhs.GetColumns(); j++)
                {
                    //Check if upper bounds for upper is 0
                    if (lhs(i, j) != 0)
                    {
                        return false;
                    }
                    //Check if lower bounds for dense is 0
                    if (rhs[j][i] != 0)
                    {
                        return false;
                    }
                    //Check if upper bounds for dense is 0
                    if (rhs[i][j] != 0)
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
bool operator==(const Matrix<T> &lhs, const TMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (rhs(i, i) != lhs[i][i])
                {
                    return false;
                }
                for (int j = i + 1; j < lhs.GetColumns(); j++)
                {
                    //Check if upper bounds for upper is 0
                    if (rhs(i, j) != 0)
                    {
                        return false;
                    }
                    //Check if lower bounds for dense is 0
                    if (lhs[j][i] != 0)
                    {
                        return false;
                    }
                    //Check if upper bounds for dense is 0
                    if (lhs[i][j] != 0)
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
bool operator==(const TMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs(i, i) != rhs[i][i])
                {
                    return false;
                }
                for (int j = i + 1; j < lhs.GetColumns(); j++)
                {
                    //Check if upper bounds for upper is 0
                    if (lhs(i, j) != 0)
                    {
                        return false;
                    }
                    //Check if lower bounds for symmetric is 0
                    if (rhs[j][i] != 0)
                    {
                        return false;
                    }
                    //Check if upper bounds for symmetric is 0
                    if (rhs[i][j] != 0)
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
bool operator==(const SMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (rhs(i, i) != lhs[i][i])
                {
                    return false;
                }
                for (int j = i + 1; j < lhs.GetColumns(); j++)
                {
                    //Check if upper bounds for upper is 0
                    if (rhs(i, j) != 0)
                    {
                        return false;
                    }
                    //Check if lower bounds for symmetric is 0
                    if (lhs[j][i] != 0)
                    {
                        return false;
                    }
                    //Check if upper bounds for symmetric is 0
                    if (lhs[i][j] != 0)
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
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    if (lhs(i, j) != 0)
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
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = i; j < rhs.GetColumns(); j++)
            {
                for (int k = i; k <= j; k++)
                {
                    temp[i][j] += lhs(i, k) * rhs(k, j);
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
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = i; k < rhs.GetColumns(); k++)
                {
                    temp[i][j] += lhs(i, k) * rhs(k, j);
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
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = 0; k <= j; k++)
                {
                    temp[i][j] += lhs[i][k] * rhs(k, j);
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
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = i; k < lhs.GetColumns(); k++)
                {
                    temp[i][j] += lhs(i, k) * rhs[k][j];
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
                for (int k = i; k < lhs.GetColumns(); k++)
                {
                    temp[i][j] += lhs(i, k) * rhs[k][j];
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
                for (int k = 0; k <= j; k++)
                {
                    temp[i][j] += lhs[i][k] * rhs(k, j);
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
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = i; j < lhs.GetColumns(); j++)
            {
                temp(i, j) += lhs(i, j) * rhs(j, j);
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp(i, j) = lhs(i, j) + rhs(i, j);
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
                        temp[i][j] = rhs(i, j);
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = lhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs[i][j] + rhs(i, j);
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = rhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs(i, j) + rhs[i][j];
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = rhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs(i, j) + rhs[i][j];
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = lhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs[i][j] + rhs(i, j);
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
                for (int j = rhs.GetColumns(); j > i; j--)
                {
                    temp(i, j) = lhs(i, j);
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp(i, j) = lhs(i, j) - rhs(i, j);
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
                        temp[i][j] = 0 - rhs(i, j);
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = lhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs[i][j] - rhs(i, j);
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = 0 - rhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs(i, j) - rhs[i][j];
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = 0 - rhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs(i, j) - rhs[i][j];
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
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[j][i] = lhs[j][i];
                }
                for (int j = rhs.GetColumns() - 1; j >= i; j--)
                {
                    temp[i][j] = lhs[i][j] - rhs(i, j);
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
                for (int j = rhs.GetColumns(); j > i; j--)
                {
                    temp(i, j) = lhs(i, j);
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
        cout << endl;
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