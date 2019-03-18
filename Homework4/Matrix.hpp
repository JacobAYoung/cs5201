/**
 * @file Matrix.h
 * @author Jake Young
 * @pre Matrix object is created
 * @post Matrix can do calculations and can be used as a regular matrix
 * @brief Creates a matrix that has multiple methods of doing calculations for
 * that matrix
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
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
Matrix<T>::Matrix(const Matrix<T> &source)
{
    numRows = source.numRows;
    numColumns = source.numColumns;
    for (int i = 0; i < numRows; i++)
    {
        MyVector<double> tempVect(numColumns);
        myVect.PushBack(tempVect);
    }
    copy(source);
}

template <class T>
Matrix<T>::~Matrix() {}

template <class T>
void Matrix<T>::copy(const Matrix<T> &source)
{
    for (int i = 0; i < GetRows(); i++)
    {
        for (int j = 0; j < GetColumns(); j++)
        {
            myVect[i][j] = source[i][j];
        }
    }
    return;
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
Matrix<T> Matrix<T>::Transpose()
{
    Matrix<T> temp(this->GetColumns(), this->GetRows());
    for (int i = 0; i < this->GetRows(); i++)
    {
        for (int j = 0; j < this->GetColumns(); j++)
        {
            temp[j][i] = myVect[i][j];
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
    if (GetColumns() == B.GetNumElements())
    {
        GaussElimination<T> source;
        return source.GaussEliminate(myVect, B);
    }
    else
    {
        throw std::range_error("Sizes don't match");
    }
}

template <class T>
Matrix<T> Matrix<T>::operator*(const T &val)
{
    Matrix<T> temp(GetRows(), GetColumns());
    for (int i = 0; i < GetRows(); i++)
    {
        for (int j = 0; j < GetColumns(); j++)
        {
            temp[i][j] = val * myVect[i][j];
        }
    }
    return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &source)
{
    if (*this != source)
    {
        numColumns = source.numColumns;
        numRows = source.numRows;
        myVect = source.myVect;
    }
    return (*this);
}

template <typename T>
bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs[i][j] != rhs[i][j])
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
bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs)
{
    if (lhs.GetColumns() == rhs.GetColumns())
    {
        if (lhs.GetRows() == rhs.GetRows())
        {
            for (int i = 0; i < lhs.GetRows(); i++)
            {
                for (int j = 0; j < lhs.GetColumns(); j++)
                {
                    if (lhs[i][j] != rhs[i][j])
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
Matrix<T> operator-(const Matrix<T> &source)
{
    Matrix<T> temp(source.GetRows(), source.GetColumns());
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
        {
            temp[i][j] = -1 * source[i][j];
        }
    }
    return temp;
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

template <typename T>
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

template <typename T>
std::istream &operator>>(std::istream &in, const Matrix<T> &source)
{
    Matrix<T> temp(1, source.GetColumns());
    for (int i = 0; i < source.GetColumns(); i++)
    {
        in >> temp[0][i];
    }
    source.PushBack(temp);
    return in;
}