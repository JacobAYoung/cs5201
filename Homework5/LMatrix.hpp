template <class T>
LMatrix<T>::LMatrix()
{
    MatrixController<LMatrix<T>, T> mc;
    my_controller = mc;
}

template <class T>
LMatrix<T>::LMatrix(int rows, int columns)
{
    MatrixController<LMatrix<T>, T> mc(rows, columns, 0);
    my_controller = mc;
}

template <class T>
LMatrix<T>::LMatrix(const Matrix<T> &source)
{
    MatrixController<LMatrix<T>, T> mc(source.GetRows(), source.GetColumns(), 0);
    my_controller = mc;
    CalculateLower(source);
}

template <class T>
LMatrix<T>::LMatrix(const LMatrix<T> &source)
{
    MatrixController<LMatrix<T>, T> mc(source.numRows, source.numColumns, 0);
    mc.copy(source);
    my_controller = mc;
}

template <class T>
LMatrix<T>::~LMatrix() {}

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
LMatrix<T> LMatrix<T>::operator*(const T &val)
{
    return my_controller * val;
}

template <class T>
LMatrix<T> &LMatrix<T>::operator=(const LMatrix<T> &source)
{
    if (*this != source)
    {
        my_controller = source.my_controller;
    }
    return (*this);
}

template <class T>
T &LMatrix<T>::operator()(const int &i, const int &j)
{
    if (j <= i)
    {
        return my_controller[i][j];
    }
    else
    {
        T *temp = new double();
        return *temp;
    }
}

template <class T>
T &LMatrix<T>::operator()(const int &i, const int &j) const
{
    if (j <= i)
    {
        return my_controller[i][j];
    }
    else
    {
        T *temp = new double();
        return *temp;
    }
}

template <typename T>
LMatrix<T> operator-(const LMatrix<T> &source)
{
    LMatrix<T> temp(source.GetRows(), source.GetColumns());
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
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
                for (int j = 0; j < lhs.GetColumns(); j++)
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
bool operator!=(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
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
LMatrix<T> operator*(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = 0; k < lhs.GetColumns(); k++)
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
                for (int k = 0; k < lhs.GetColumns(); k++)
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
Matrix<T> operator*(const UMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = 0; k < lhs.GetColumns(); k++)
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
                for (int k = 0; k < lhs.GetColumns(); k++)
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
                for (int k = 0; k < lhs.GetColumns(); k++)
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
LMatrix<T> operator+(const LMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    LMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
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
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs(i, j) + rhs(i, j);
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
Matrix<T> operator+(const UMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs(i, j) + rhs(i, j);
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
                for (int j = 0; j < lhs.GetColumns(); j++)
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
                for (int j = 0; j < lhs.GetColumns(); j++)
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
                for (int j = 0; j < lhs.GetColumns(); j++)
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
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs(i, j) - rhs(i, j);
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
Matrix<T> operator-(const UMatrix<T> &lhs, const LMatrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), lhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    temp[i][j] = lhs(i, j) - rhs(i, j);
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
                for (int j = 0; j < lhs.GetColumns(); j++)
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
                for (int j = 0; j < lhs.GetColumns(); j++)
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
std::ostream &operator<<(std::ostream &out, const LMatrix<T> &source)
{
    for (int i = 0; i < source.GetRows(); i++)
    {
        out << source[i];
        if (i + 1 < source.GetRows())
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