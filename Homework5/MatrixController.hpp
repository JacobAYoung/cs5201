template <class M, class T>
MatrixController<M, T>::MatrixController()
{
    numRows = 1;
    numColumns = 1;
    MyVector<T> tempVect(1);
    tempVect[0] = 0;
    myVect.PushBack(tempVect);
}

template <class M, class T>
MatrixController<M, T>::MatrixController(int rows, int columns)
{
    numRows = rows;
    numColumns = columns;
    int type = 0;
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
        int counter = rows;
        for (int i = 0; i < rows; i++)
        {
            MyVector<T> tempVect(counter);
            for (int j = 0; j < tempVect.GetNumElements(); j++)
            {
                if (i < j)
                {
                    tempVect[j] = 0;
                }
                if (j + 1 == tempVect.GetNumElements())
                {
                    tempVect[j] = 1;
                }
            }
            counter--;
            myVect.PushBack(tempVect);
        }
    }
}

template <class M, class T>
MatrixController<M, T>::~MatrixController() {}

template <class M, class T>
void MatrixController<M, T>::PushBack(const MyVector<T> &source)
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
M MatrixController<M, T>::Transpose()
{
    M temp(this->GetColumns(), this->GetRows());
    for (int i = 0; i < this->GetRows(); i++)
    {
        for (int j = 0; j < this->GetColumns(); j++)
        {
            temp[j][i] = myVect[i][j];
        }
    }
    return temp;
}

template <class M, class T>
MyVector<T> &MatrixController<M, T>::operator[](const int &i)
{
    try
    {
        cout << "gong here" << endl;
        if (i >= 0 && i <= GetRows())
        {
            try
            {
                return this->myVect[i];
            }
            catch (const std::exception &e)
            {
                cout << "hit this catch" << endl;
                MyVector<T> *temp = new MyVector<T>();
                temp[0] = 0;
                return *temp;
            }
        }
        else
        {
            cout << "Hit here" << endl;
            cout << GetRows() << endl;
            throw std::range_error("Out of bounds");
        }
    }
    catch (...)
    {
        cout << "hit this catch" << endl;
        MyVector<T> *temp = new MyVector<T>();
        temp[0] = 0;
        return *temp;
    }
}

template <class M, class T>
MyVector<T> &MatrixController<M, T>::operator[](const int &i) const
{
    cout << "Not here" << endl;
    if (i >= 0 && i <= GetRows())
    {
        return this->myVect[i];
    }
    else
    {
        cout << "Hit here1" << endl;
        cout << GetRows() << endl;
        throw std::range_error("Out of bounds");
    }
}

template <class M, class T>
M MatrixController<M, T>::operator*(const T &val)
{
    M temp(GetRows(), GetColumns());
    cout << "Got here" << endl;
    m_type = 0;
    if (m_type == 0)
    {
        cout << "Should go here" << endl;
        for (int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (j < i)
                {
                    temp[i][j] = val * myVect[i][j];
                }
            }
        }
    }
    else
    {
        cout << "but went here" << endl;
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