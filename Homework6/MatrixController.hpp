template <class M, class T>
MatrixController<M, T>::MatrixController()
{
    numRows = 1;
    numColumns = 1;
    MyVector<T> tempVect(1);
    tempVect[0] = 0;
    m_type = typeEnum::LMatrix;
    myVect.PushBack(tempVect);
}

template <class M, class T>
MatrixController<M, T>::MatrixController(int rows, int columns, typeEnum type)
{
    numRows = rows;
    numColumns = columns;
    m_type = type;
    switch (type)
    {
    case MatrixController<M, T>::LMatrix:
        for (int i = 0; i < rows; i++)
        {
            MyVector<T> tempVect(i + 1);
            for (int j = 0; j < tempVect.GetNumElements(); j++)
            {
                tempVect[j] = 0;
            }
            myVect.PushBack(tempVect);
        }
        break;
    case MatrixController<M, T>::UMatrix:
        for (int i = 0; i < rows; i++)
        {
            MyVector<T> tempVect(columns - i);
            for (int j = 0; j < tempVect.GetNumElements(); j++)
            {
                tempVect[j] = 0;
            }
            myVect.PushBack(tempVect);
        }
        break;
    case MatrixController<M, T>::DMatrix:
        for (int i = 0; i < rows; i++)
        {
            MyVector<T> tempVect(1);
            tempVect[0] = 0;
            myVect.PushBack(tempVect);
        }
        break;
    case MatrixController<M, T>::TMatrix:
        for (int i = 0; i < rows; i++)
        {
            if (i == 0 || i == (rows - 1))
            {
                MyVector<T> tempVect(2);
                for (int j = 0; j < tempVect.GetNumElements(); j++)
                {
                    tempVect[j] = 0;
                }
                myVect.PushBack(tempVect);
            }
            else
            {
                MyVector<T> tempVect(3);
                for (int j = 0; j < tempVect.GetNumElements(); j++)
                {
                    tempVect[j] = 0;
                }
                myVect.PushBack(tempVect);
            }
        }
        break;
    }
}

template <class M, class T>
MatrixController<M, T>::~MatrixController() {}

template <class M, class T>
MatrixController<M, T>::MatrixController(const MatrixController<M, T> &source)
{
    numRows = source.numRows;
    m_type = source.m_type;
    numColumns = source.numColumns;
    for (int i = 0; i < numRows; i++)
    {
        MyVector<T> tempVect(numColumns);
        myVect.PushBack(tempVect);
    }
    copy(source);
}

template <class M, class T>
void MatrixController<M, T>::copy(const MatrixController<M, T> &source)
{
    if (m_type == typeEnum::LMatrix)
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (j <= i)
                {
                    myVect[i][j] = source[i][j];
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (i <= j)
                {
                    myVect[i][j] = source[i][j];
                }
            }
        }
    }
    return;
}

template <class M, class T>
void MatrixController<M, T>::PushBack(const MyVector<T> &source)
{
    int counter = 0;
    if (m_type == typeEnum::LMatrix)
    {
        for (int i = 0; i < this->GetColumns(); i++)
        {
            for (int j = 0; j < this->GetRows(); j++)
            {
                if (j < i)
                {
                    if (myVect[i][j] == 0)
                    {
                        counter++;
                    }
                }
            }
            if (counter == this->GetRows())
            {
                for (int j = 0; j < this->GetRows(); j++)
                {
                    if (j <= i)
                    {
                        myVect[i][j] = source[j];
                    }
                }
                return;
            }
            counter = 0;
        }

        myVect.PushBack(source);
        return;
    }
    else
    {
        for (int i = 0; i < this->GetColumns(); i++)
        {
            for (int j = 0; j < this->GetRows(); j++)
            {
                if (i < j)
                {
                    if (myVect[i][j] == 0)
                    {
                        counter++;
                    }
                }
            }
            if (counter == this->GetRows())
            {
                for (int j = 0; j < this->GetRows(); j++)
                {
                    if (i < j)
                    {
                        myVect[i][j] = source[j];
                    }
                }
                return;
            }
            counter = 0;
        }

        myVect.PushBack(source);
        return;
    }
}

template <class M, class T>
int MatrixController<M, T>::GetRows() const
{
    return numRows;
}

template <class M, class T>
int MatrixController<M, T>::GetColumns() const
{
    return numColumns;
}

template <class M, class T>
void MatrixController<M, T>::SetRows(const int &rows)
{
    if (rows >= 0)
    {
        numRows = rows;
    }
    else
    {
        throw std::range_error("Out of range.");
    }
    return;
}

template <class M, class T>
void MatrixController<M, T>::SetColumns(const int &columns)
{
    if (columns >= 0)
    {
        numColumns = columns;
    }
    else
    {
        throw std::range_error("Out of range.");
    }
    return;
}

template <class M, class T>
MyVector<T> &MatrixController<M, T>::operator[](const int &i)
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

template <class M, class T>
MyVector<T> &MatrixController<M, T>::operator[](const int &i) const
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

template <class M, class T>
M MatrixController<M, T>::operator*(const T &val) const
{
    M temp(GetRows(), GetColumns());
    if (m_type == typeEnum::LMatrix)
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (j <= i)
                {
                    temp[i][j] = val * myVect[i][j];
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (i <= j)
                {
                    temp[i][j] = val * myVect[i][j];
                }
            }
        }
    }
    return temp;
}

template <class M, class T>
MatrixController<M, T> &MatrixController<M, T>::operator=(const M &source)
{
    if (*this != source)
    {
        numColumns = source.numColumns;
        numRows = source.numRows;
        myVect = source.myVect;
    }
    return (*this);
}

template <class M, class T>
void MatrixController<M, T>::copy(const M &source)
{
    switch (m_type)
    {
    case MatrixController<M, T>::LMatrix:
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (j <= i)
                {
                    myVect[i][j] = source[i][j];
                }
            }
        }
        break;
    case MatrixController<M, T>::UMatrix:
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (i <= j)
                {
                    myVect[i][j] = source[i][j];
                }
            }
        }
        break;
    case MatrixController<M, T>::DMatrix:
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (i == j)
                {
                    myVect[i][0] = source[i][j];
                }
            }
        }
        break;
    }
    return;
}
