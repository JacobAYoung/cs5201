template <class T>
DMatrix<T>::DMatrix()
{
    MatrixController<DMatrix<T>, T> mc;
    my_controller = mc;
}

template <class T>
DMatrix<T>::DMatrix(int rows, int columns)
{
    MatrixController<DMatrix<T>, T> mc(rows, columns, MatrixController<DMatrix<T>, T>::DMatrix);
    my_controller = mc;
}

template <class T>
DMatrix<T>::DMatrix(const Matrix<T> &source)
{
    MatrixController<DMatrix<T>, T> mc(source.GetRows(), source.GetColumns(), MatrixController<DMatrix<T>, T>::DMatrix);
    mc.copy(source);
    my_controller = mc;
}

template <class T>
DMatrix<T>::DMatrix(const DMatrix<T> &source)
{
    MatrixController<DMatrix<T>, T> mc(source.GetRows(), source.GetColumns(), MatrixController<DMatrix<T>, T>::DMatrix);
    mc.copy(source);
    my_controller = mc;
}

template <class T>
DMatrix<T>::~DMatrix() {}

template <class T>
DMatrix<T>::DMatrix(DMatrix<T> &&source)
{
    my_controller.SetRows(source.GetRows());
    my_controller.SetColumns(source.GetColumns());
    std::swap(my_controller, source.my_controller);
    source.my_controller.SetRows(0);
    source.my_controller.SetColumns(0);
}

template <class T>
int DMatrix<T>::GetRows() const
{
    return my_controller.GetRows();
}

template <class T>
int DMatrix<T>::GetColumns() const
{
    return my_controller.GetColumns();
}

template <class T>
DMatrix<T> DMatrix<T>::Transpose()
{
    DMatrix<T> temp(this->GetColumns(), this->GetRows());
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
MyVector<T> &DMatrix<T>::operator[](const int &i)
{
    return my_controller[i];
}

template <class T>
MyVector<T> &DMatrix<T>::operator[](const int &i) const
{
    return my_controller[i];
}

template <class T>
T &DMatrix<T>::operator()(const int &i, const int &j)
{
    if (i <= GetRows())
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
            if (i == j)
            {
                return my_controller[i][0];
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
T &DMatrix<T>::operator()(const int &i, const int &j) const
{
    if (i <= GetRows())
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
            if (i == j)
            {
                return my_controller[i][0];
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
void DMatrix<T>::PushBack(const MyVector<T> &source)
{
    my_controller.PushBack(source);
    return;
}

template <class T>
DMatrix<T> DMatrix<T>::operator*(const T &val) const
{
    return my_controller * val;
}

template <class T>
DMatrix<T> &DMatrix<T>::operator=(const DMatrix<T> &source)
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
DMatrix<T> &DMatrix<T>::operator=(const Matrix<T> &source)
{
    for (int i = 0; i < source.GetRows(); i++)
    {
        my_controller[i][0] = source[i][i];
    }
    return *this;
}

template <typename T>
bool operator==(const DMatrix<T> &lhs, const DMatrix<T> &rhs)
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
bool operator==(const DMatrix<T> &lhs, const LMatrix<T> &rhs)
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
                    if (rhs(j, i) != 0)
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
bool operator==(const DMatrix<T> &lhs, const Matrix<T> &rhs)
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
                    if (rhs[j][i] != 0)
                    {
                        return false;
                    }
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
bool operator==(const Matrix<T> &lhs, const DMatrix<T> &rhs)
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
                for (int j = i + 1; j < lhs.GetColumns(); j++)
                {
                    if (lhs[j][i] != 0)
                    {
                        return false;
                    }
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
bool operator==(const DMatrix<T> &lhs, const SMatrix<T> &rhs)
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
                    if (rhs[j][i] != 0)
                    {
                        return false;
                    }
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
bool operator==(const SMatrix<T> &lhs, const DMatrix<T> &rhs)
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
                for (int j = i + 1; j < lhs.GetColumns(); j++)
                {
                    if (lhs[j][i] != 0)
                    {
                        return false;
                    }
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
bool operator==(const DMatrix<T> &lhs, const UMatrix<T> &rhs)
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
                    if (rhs(i, j) != 0)
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
DMatrix<T> operator-(const DMatrix<T> &source)
{
    DMatrix<T> temp(source.GetRows(), source.GetColumns());
    for (int i = 0; i < source.GetRows(); i++)
    {
        if (source(i, i) != 0)
        {
            temp(i, i) = -1 * source(i, i);
        }
    }
    return temp;
}

template <typename T>
bool operator!=(const DMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                if (lhs(i, i) != rhs(i, i))
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

template <typename T>
bool operator!=(const DMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs(i, j) != rhs(i, j))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

template <typename T>
bool operator!=(const DMatrix<T> &lhs, const Matrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs(i, j) != rhs[i][j])
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

template <typename T>
bool operator!=(const Matrix<T> &lhs, const DMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs[i][j] != rhs(i, j))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

template <typename T>
bool operator!=(const DMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs(i, j) != rhs[i][j])
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

template <typename T>
bool operator!=(const SMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs[i][j] != rhs(i, j))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

template <typename T>
bool operator!=(const DMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs(i, j) != rhs(i, j))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

template <typename T>
DMatrix<T> operator*(const DMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    DMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            temp(i, i) += lhs(i, i) * rhs(i, i);
        }
    }
    else
    {
        throw std::length_error("Matrix sizes don't match.");
    }
    return temp;
}

template <typename T>
LMatrix<T> operator*(const DMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            temp(i, i) = lhs(i, i) * rhs(i, i);
            for (int j = 0; j < i; j++)
            {
                temp(i, j) += lhs(i, i) * rhs(i, j);
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
Matrix<T> operator*(const Matrix<T> &lhs, const DMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                temp[i][j] += lhs[i][j] * rhs(j, j);
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
Matrix<T> operator*(const DMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetColumns(); i++)
        {
            for (int j = 0; j < rhs.GetRows(); j++)
            {
                temp[j][i] += lhs(j, j) * rhs[j][i];
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
SMatrix<T> operator*(const DMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetColumns(); i++)
        {
            for (int j = 0; j < rhs.GetRows(); j++)
            {
                temp[j][i] += lhs(j, j) * rhs[j][i];
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
SMatrix<T> operator*(const SMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                temp[i][j] += lhs[i][j] * rhs(j, j);
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
UMatrix<T> operator*(const DMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    UMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            temp(i, i) = lhs(i, i) * rhs(i, i);
            for (int j = i; j < rhs.GetColumns(); j++)
            {
                temp(i, j) += lhs(i, i) * rhs(i, j);
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
DMatrix<T> operator+(const DMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    DMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) + rhs(i, i);
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
LMatrix<T> operator+(const DMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) + rhs(i, i);
                for (int j = 0; j < lhs.GetRows(); j++)
                {
                    if (i > j)
                    {
                        temp(i, j) = rhs(i, j);
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
Matrix<T> operator+(const Matrix<T> &lhs, const DMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] + rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = lhs[i][j];
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
Matrix<T> operator+(const DMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs(i, i) + rhs[i][i];
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = rhs[i][j];
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
SMatrix<T> operator+(const DMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs(i, i) + rhs[i][i];
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = rhs[i][j];
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
SMatrix<T> operator+(const SMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] + rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = lhs[i][j];
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
UMatrix<T> operator+(const DMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    UMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) + rhs(i, i);
                for (int j = rhs.GetColumns() - 1; j > i; j--)
                {
                    temp(i, j) = rhs(i, j);
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
DMatrix<T> operator-(const DMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    DMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) - rhs(i, i);
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
LMatrix<T> operator-(const DMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) - rhs(i, i);
                for (int j = 0; j < lhs.GetRows(); j++)
                {
                    if (i > j)
                    {
                        temp(i, j) = 0 - rhs(i, j);
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
Matrix<T> operator-(const Matrix<T> &lhs, const DMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] - rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = lhs[i][j];
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
Matrix<T> operator-(const DMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs(i, i) - rhs[i][i];
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = 0 - rhs[i][j];
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
SMatrix<T> operator-(const DMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs(i, i) - rhs[i][i];
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = 0 - rhs[i][j];
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
SMatrix<T> operator-(const SMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp[i][i] = lhs[i][i] - rhs(i, i);
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (i != j)
                    {
                        temp[i][j] = lhs[i][j];
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
UMatrix<T> operator-(const DMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    UMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                temp(i, i) = lhs(i, i) - rhs(i, i);
                for (int j = 0; j < lhs.GetRows(); j++)
                {
                    if (i < j)
                    {
                        temp(i, j) = 0 - rhs(i, j);
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
std::ostream &operator<<(std::ostream &out, const DMatrix<T> &source)
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
std::istream &operator>>(std::istream &in, DMatrix<T> &source)
{
    MyVector<double> temp(source.GetColumns());
    for (int i = 0; i < source.GetColumns(); i++)
    {
        in >> temp[i];
    }
    source.PushBack(temp);
    return in;
}