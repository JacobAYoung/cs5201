template <class T>
SMatrix<T>::SMatrix()
{
    numRows = 1;
    numColumns = 1;
    MyVector<T> tempVect(1);
    myVect.PushBack(tempVect);
}

template <class T>
SMatrix<T>::SMatrix(int rows, int columns)
{
    numRows = rows;
    numColumns = columns;
    for (int i = 0; i < rows; i++)
    {
        MyVector<T> tempVect(columns);
        myVect.PushBack(tempVect);
    }
}

template <class T>
SMatrix<T>::SMatrix(const SMatrix<T> &source)
{
    numRows = source.numRows;
    numColumns = source.numColumns;
    for (int i = 0; i < numRows; i++)
    {
        MyVector<T> tempVect(numColumns);
        myVect.PushBack(tempVect);
    }
    copy(source);
}

template <class T>
SMatrix<T>::~SMatrix() {}

template <class T>
SMatrix<T>::SMatrix(SMatrix<T> &&source)
{
    numRows = source.numRows;
    numColumns = source.numColumns;
    std::swap(myVect, source.myVect);
    source.numColumns = 0;
    source.numRows = 0;
}

template <class T>
void SMatrix<T>::copy(const SMatrix<T> &source)
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
void SMatrix<T>::PushBack(const MyVector<T> &source)
{
    int counter = 0;
    if (GetRows() > GetColumns())
    {
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
    }
    else
    {
        for (int i = 0; i < this->GetRows(); i++)
        {
            for (int j = 0; j < this->GetColumns(); j++)
            {
                if (myVect[i][j] == 0)
                {
                    counter++;
                }
            }
            if (counter == this->GetRows())
            {
                for (int j = 0; j < this->GetRows(); j++)
                {
                    myVect[i][j] = source[j];
                }
                return;
            }
            counter = 0;
        }
    }

    myVect.PushBack(source);
    return;
}

template <class T>
int SMatrix<T>::GetRows() const
{
    return numRows;
}

template <class T>
int SMatrix<T>::GetColumns() const
{
    return numColumns;
}

template <class T>
SMatrix<T> SMatrix<T>::Transpose()
{
    SMatrix<T> temp(this->GetColumns(), this->GetRows());
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
MyVector<T> &SMatrix<T>::operator[](const int &i)
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
MyVector<T> &SMatrix<T>::operator[](const int &i) const
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
SMatrix<T> SMatrix<T>::operator*(const T &val) const
{
    SMatrix<T> temp(GetRows(), GetColumns());
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
SMatrix<T> &SMatrix<T>::operator=(const SMatrix<T> &source)
{
    if (*this != source)
    {
        numColumns = source.numColumns;
        numRows = source.numRows;
        myVect = source.myVect;
    }
    return (*this);
}

template <class T>
SMatrix<T> &SMatrix<T>::operator=(const Matrix<T> &source)
{
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
        {
            if (i == j)
            {
                myVect[i][j] = source[i][j];
            }
        }
    }
    return *this;
}

template <typename T>
bool operator==(const SMatrix<T> &lhs, const SMatrix<T> &rhs)
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
bool operator!=(const SMatrix<T> &lhs, const SMatrix<T> &rhs)
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
SMatrix<T> operator-(const SMatrix<T> &source)
{
    SMatrix<T> temp(source.GetRows(), source.GetColumns());
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
SMatrix<T> operator*(const SMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), rhs.GetColumns());
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
        throw std::length_error("SMatrix sizes don't match.");
    }
    return temp;
}

template <class T>
SMatrix<T> operator+(const SMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
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
            throw std::length_error("SMatrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("SMatrix sizes don't match.");
    }
    return temp;
}

template <class T>
SMatrix<T> operator-(const SMatrix<T> &lhs, const SMatrix<T> &rhs)
{
    SMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
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
            throw std::length_error("SMatrix sizes don't match.");
        }
    }
    else
    {
        throw std::length_error("SMatrix sizes don't match.");
    }
    return temp;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const SMatrix<T> &source)
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
std::istream &operator>>(std::istream &in, SMatrix<T> &source)
{
    MyVector<T> temp(source.GetColumns());
    for (int i = 0; i < source.GetColumns(); i++)
    {
        in >> temp[i];
    }
    source.PushBack(temp);
    return in;
}
