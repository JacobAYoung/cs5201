template <class T>
LMatrix<T>::LMatrix()
{
    MatrixController<LMatrix<T>, T> mc;
    my_controller = mc;
}

template <class T>
LMatrix<T>::LMatrix(int rows, int columns)
{
    MatrixController<LMatrix<T>, T> mc(rows, columns, MatrixController<LMatrix<T>, T>::LMatrix);
    my_controller = mc;
}

template <class T>
LMatrix<T>::LMatrix(const Matrix<T> &source)
{
    MatrixController<LMatrix<T>, T> mc(source.GetRows(), source.GetColumns(), MatrixController<LMatrix<T>, T>::LMatrix);
    my_controller = mc;
    CalculateLower(source);
}

template <class T>
LMatrix<T>::LMatrix(const LMatrix<T> &source)
{
    MatrixController<LMatrix<T>, T> mc(source.GetRows(), source.GetColumns(), MatrixController<LMatrix<T>, T>::LMatrix);
    mc.copy(source);
    my_controller = mc;
}

template <class T>
LMatrix<T>::~LMatrix() {}

template <class T>
LMatrix<T>::LMatrix(LMatrix<T> &&source)
{
    my_controller.SetRows(source.GetRows());
    my_controller.SetColumns(source.GetColumns());
    std::swap(my_controller, source.my_controller);
    source.my_controller.SetRows(0);
    source.my_controller.SetColumns(0);
}

template <class T>
int LMatrix<T>::GetRows() const
{
    return my_controller.GetRows();
}

template <class T>
int LMatrix<T>::GetColumns() const
{
    return my_controller.GetColumns();
}

template <class T>
UMatrix<T> LMatrix<T>::Transpose()
{
    UMatrix<T> temp(this->GetColumns(), this->GetRows());
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
MyVector<T> &LMatrix<T>::operator[](const int &i)
{
    return my_controller[i];
}

template <class T>
MyVector<T> &LMatrix<T>::operator[](const int &i) const
{
    return my_controller[i];
}

template <class T>
void LMatrix<T>::CalculateLower(const Matrix<T> &source)
{
    Matrix<T> m = source;
    //Set all the values to 0 or 1 depending on the location.
    //This is just reassurance before calculating the values
    for (int i = 0; i < my_controller.GetRows(); i++)
    {
        for (int j = 0; j < my_controller.GetColumns(); j++)
        {
            if (j < i)
            {
                my_controller[i][j] = 0;
            }
            else if (i == j)
            {
                my_controller[i][j] = 1;
            }
        }
    }
    //Calculate the upper values to get the lower values and set them to our data.
    for (int i = 0; i < source.GetRows() - 1; i++)
    {
        for (int k = i + 1; k < source.GetColumns(); k++)
        {
            T t = m[k][i] / m[i][i];
            my_controller[k][i] = t;
            for (int j = 0; j < source.GetRows(); j++)
            {
                m[k][j] = m[k][j] - t * m[i][j];
            }
        }
    }
    return;
}

template <class T>
void LMatrix<T>::PushBack(const MyVector<T> &source)
{
    my_controller.PushBack(source);
    return;
}

template <class T>
LMatrix<T> LMatrix<T>::operator*(const T &val) const
{
    return my_controller * val;
}

template <class T>
LMatrix<T> &LMatrix<T>::operator=(const LMatrix<T> &source)
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
LMatrix<T> &LMatrix<T>::operator=(const Matrix<T> &source)
{
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
        {
            if (j <= i)
            {
                my_controller[i][j] = source[i][j];
            }
        }
    }
    return *this;
}

template <class T>
T &LMatrix<T>::operator()(const int &i, const int &j)
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
    if (j >= 0)
    {
        if (i >= 0)
        {
            if (j <= i)
            {
                return my_controller[i][j];
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
T &LMatrix<T>::operator()(const int &i, const int &j) const
{
    if (j >= 0)
    {
        if (i >= 0)
        {
            if (j <= i)
            {
                return my_controller[i][j];
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
Matrix<T> LMatrix<T>::add(const IMatrix<Matrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::subtract(const IMatrix<Matrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::multiply(const IMatrix<Matrix<T>, T> &source) const
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
bool LMatrix<T>::equals(const IMatrix<Matrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::add(const IMatrix<TMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::subtract(const IMatrix<TMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::multiply(const IMatrix<TMatrix<T>, T> &source) const
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
bool LMatrix<T>::equals(const IMatrix<TMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::add(const IMatrix<LMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::subtract(const IMatrix<LMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::multiply(const IMatrix<LMatrix<T>, T> &source) const
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
bool LMatrix<T>::equals(const IMatrix<LMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::add(const IMatrix<UMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::subtract(const IMatrix<UMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::multiply(const IMatrix<UMatrix<T>, T> &source) const
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
bool LMatrix<T>::equals(const IMatrix<UMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::add(const IMatrix<SMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::subtract(const IMatrix<SMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::multiply(const IMatrix<SMatrix<T>, T> &source) const
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
bool LMatrix<T>::equals(const IMatrix<SMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::add(const IMatrix<DMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::subtract(const IMatrix<DMatrix<T>, T> &source) const
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
Matrix<T> LMatrix<T>::multiply(const IMatrix<DMatrix<T>, T> &source) const
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
bool LMatrix<T>::equals(const IMatrix<DMatrix<T>, T> &source) const
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
LMatrix<T> operator-(const LMatrix<T> &source)
{
    LMatrix<T> temp(source.GetRows(), source.GetColumns());
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j <= i; j++)
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
bool operator==(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j <= i; j++)
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
bool operator==(const LMatrix<T> &lhs, const UMatrix<T> &rhs)
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
                    if (lhs(j, i) != 0)
                    {
                        return false;
                    }
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
bool operator==(const LMatrix<T> &lhs, const Matrix<T> &rhs)
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
                    //Check if lower bounds for lower is 0
                    if (lhs(j, i) != 0)
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
bool operator==(const Matrix<T> &lhs, const LMatrix<T> &rhs)
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
                    //Check if lower bounds for lower is 0
                    if (rhs(j, i) != 0)
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
bool operator==(const LMatrix<T> &lhs, const SMatrix<T> &rhs)
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
                    //Check if lower bounds for lower is 0
                    if (lhs(j, i) != 0)
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
bool operator==(const SMatrix<T> &lhs, const LMatrix<T> &rhs)
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
                    //Check if lower bounds for lower is 0
                    if (rhs(j, i) != 0)
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
bool operator==(const LMatrix<T> &lhs, const DMatrix<T> &rhs)
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
                    if (lhs(j, i) != 0)
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
bool operator==(const LMatrix<T> &lhs, const TMatrix<T> &rhs)
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
                        if (rhs(i, j) != 0)
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
bool operator!=(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const Matrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const Matrix<T> &lhs, const LMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const SMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator!=(const LMatrix<T> &lhs, const TMatrix<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
LMatrix<T> operator*(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j <= i; j++)
            {
                for (int k = j; k <= i; k++)
                {
                    temp(i, j) += lhs(i, k) * rhs(k, j);
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
Matrix<T> operator*(const LMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = 0; k <= i; k++)
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
Matrix<T> operator*(const Matrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = j; k < rhs.GetColumns(); k++)
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
Matrix<T> operator*(const LMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = 0; k <= i; k++)
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
Matrix<T> operator*(const LMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = 0; k <= i; k++)
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
Matrix<T> operator*(const SMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = j; k < rhs.GetColumns(); k++)
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
LMatrix<T> operator*(const LMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            temp(i, i) = lhs(i, i) * rhs(i, i);
            for (int j = 0; j < i; j++)
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
Matrix<T> operator*(const LMatrix<T> &lhs, const TMatrix<T> &rhs)
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
                    if (j < 2)
                    {
                        for (int k = i; k < j + 2; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                    else
                    {
                        for (int k = j - 1; k < 4; k++)
                        {
                            temp[i][j] += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
                else if (i == (lhs.GetColumns() - 1))
                {
                    for (int k = 0; k < i + 1; k++)
                    {
                        temp[i][j] += lhs(i, k) * rhs(k, j);
                    }
                }
                else
                {
                    for (int k = j - 1; k <= j + 1; k++)
                    {
                        if (k < 0 || k > (lhs.GetRows() - 1))
                        {
                            continue;
                        }
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
LMatrix<T> operator+(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j <= i; j++)
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
Matrix<T> operator+(const LMatrix<T> &lhs, const UMatrix<T> &rhs)
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
                    if (j > i)
                    {
                        temp[i][j] = rhs(i, j);
                    }
                    else if (j < i)
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
Matrix<T> operator+(const Matrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs[i][j];
                }
                for (int j = 0; j <= i; j++)
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
Matrix<T> operator+(const LMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = rhs[i][j];
                }
                for (int j = 0; j <= i; j++)
                {
                    temp[i][j] = rhs[i][j] + lhs(i, j);
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
Matrix<T> operator+(const LMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = rhs[i][j];
                }
                for (int j = 0; j <= i; j++)
                {
                    temp[i][j] = rhs[i][j] + lhs(i, j);
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
Matrix<T> operator+(const SMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs[i][j];
                }
                for (int j = 0; j <= i; j++)
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
LMatrix<T> operator+(const LMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
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
Matrix<T> operator+(const LMatrix<T> &lhs, const TMatrix<T> &rhs)
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
                        temp[i][j] = rhs(i, j);
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
LMatrix<T> operator-(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j <= i; j++)
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
Matrix<T> operator-(const LMatrix<T> &lhs, const UMatrix<T> &rhs)
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
                    if (j > i)
                    {
                        temp[i][j] = 0 - rhs(i, j);
                    }
                    else if (j < i)
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
Matrix<T> operator-(const Matrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs[i][j];
                }
                for (int j = 0; j <= i; j++)
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
Matrix<T> operator-(const LMatrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = 0 - rhs[i][j];
                }
                for (int j = 0; j <= i; j++)
                {
                    temp[i][j] = rhs[i][j] - lhs(i, j);
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
Matrix<T> operator-(const LMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = 0 - rhs[i][j];
                }
                for (int j = 0; j <= i; j++)
                {
                    temp[i][j] = rhs[i][j] - lhs(i, j);
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
Matrix<T> operator-(const SMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = i + 1; j < rhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs[i][j];
                }
                for (int j = 0; j <= i; j++)
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
LMatrix<T> operator-(const LMatrix<T> &lhs, const DMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
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
Matrix<T> operator-(const LMatrix<T> &lhs, const TMatrix<T> &rhs)
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
                        temp[i][j] = 0 - rhs(i, j);
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
std::ostream &operator<<(std::ostream &out, const LMatrix<T> &source)
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
std::istream &operator>>(std::istream &in, LMatrix<T> &source)
{
    MyVector<double> temp(source.GetColumns());
    for (int i = 0; i < source.GetColumns(); i++)
    {
        in >> temp[i];
    }
    source.PushBack(temp);
    return in;
}