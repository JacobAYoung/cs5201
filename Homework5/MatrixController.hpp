template <class M, class T>
MatrixController<M, T>::MatrixController()
{
    numRows = 1;
    numColumns = 1;
    MyVector<T> tempVect(1);
    tempVect[0] = 0;
    m_type = 0;
    myVect.PushBack(tempVect);
}

template <class M, class T>
MatrixController<M, T>::MatrixController(int rows, int columns, int type)
{
    numRows = rows;
    numColumns = columns;
    //make sure to dynamically change this
    m_type = type;
    if (type == 0)
    {
        for (int i = 0; i < rows; i++)
        {
            MyVector<T> tempVect(i + 1);
            for (int j = 0; j < tempVect.GetNumElements(); j++)
            {
                tempVect[j] = 0;
                if (j + 1 == tempVect.GetNumElements())
                {
                    tempVect[j] = 1;
                }
            }
            myVect.PushBack(tempVect);
        }
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            MyVector<T> tempVect(columns);
            for (int j = 0; j < tempVect.GetNumElements(); j++)
            {
                tempVect[j] = 0;
            }
            myVect.PushBack(tempVect);
            if (i != 0)
            {
                myVect[i].deletePointer(i);
            }
        }
    }
}

template <class M, class T>
MatrixController<M, T>::~MatrixController() {}

template <class M, class T>
void MatrixController<M, T>::PushBack(const MyVector<T> &source)
{
    int counter = 0;
    if (m_type == 0)
    {
        for (int i = 0; i < this->GetColumns(); i++)
        {
            for (int j = 0; j < this->GetRows(); j++)
            {
                if (j <= i)
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
    if (m_type == 0)
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
    if (m_type == 0)
    {
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (j < i)
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