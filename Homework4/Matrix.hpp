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
}

template <class T>
void Matrix<T>::PushBack(const MyVector<T> &source)
{
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