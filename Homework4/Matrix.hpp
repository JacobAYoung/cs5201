template <class T>
Matrix<T>::Matrix()
{
    numRows = 1;
    numColumns = 1;
    MyVector<double> tempVect(1);
    myVect.PushBack(tempVect);
}

template <class T>
Matrix<T>::Matrix(int rows, int columns)
{
    numRows = rows;
    numColumns = columns;
    for (int i = 0; i < rows; i++)
    {
        MyVector<double> tempVect(columns);
        myVect.PushBack(tempVect);
    }
}

template <class T>
void Matrix<T>::PushBack(const MyVector<T> &source)
{
    int counter = 0;
    for (int i = 0; i < this->GetColumns(); i++)
    {
        for (int j = 0; j < this->GetRows(); j++)
        {
            if (myVect[j][i] == 0)
            {
                counter++;
            }
        }
        if (counter == this->GetRows())
        {
            for (int j = 0; j < this->GetRows(); j++)
            {
                myVect[j][i] = source[j];
            }
            return;
        }
        counter = 0;
    }

    myVect.PushBack(source);
    return;
}

template <class T>
int Matrix<T>::GetRows() const
{
    return numRows;
}

template <class T>
int Matrix<T>::GetColumns() const
{
    return numColumns;
}

template <class T>
Matrix<T> Matrix<T>::Transpose(const Matrix<T> &source)
{
    Matrix<T> temp(source.GetColumns(), source.GetRows());
    for (int i = 0; i < source.GetRows(); ++i)
    {
        for (int j = 0; j < source.GetColumns(); ++j)
        {
            temp[j][i] = source[i][j];
        }
    }
    return temp;
}

template <class T>
MyVector<T> &Matrix<T>::operator[](const int &i)
{
    if (i >= 0 && i <= GetRows())
    {
        return this->myVect[i];
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
MyVector<T> &Matrix<T>::operator[](const int &i) const
{
    if (i >= 0 && i <= GetRows())
    {
        return this->myVect[i];
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
MyVector<T> Matrix<T>::Eliminate(const MyVector<T> &B)
{
    GaussElimination<T> source;
    return source.GaussEliminate(myVect, B);
}

template <class T>
Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    Matrix<T> temp(lhs.GetRows(), rhs.GetColumns());
    if (lhs.GetColumns() == rhs.GetRows())
    {
        for (int i = 0; i < lhs.GetRows(); i++)
        {
            for (int j = 0; j < rhs.GetColumns(); j++)
            {
                for (int k = 0; k < lhs.GetColumns(); k++)
                {
                    temp[i][j] += lhs[i][k] * rhs[k][j];
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
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
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
                    temp[i][j] = lhs[i][j] + rhs[i][j];
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
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
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
                    temp[i][j] = lhs[i][j] - rhs[i][j];
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
std::ostream &operator<<(std::ostream &out, const Matrix<T> &source)
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