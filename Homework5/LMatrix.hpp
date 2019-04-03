// template <class T>
// LMatrix<T>::LMatrix()
// {
//     MatrixController<LMatrix<T>, T> mc;
//     my_controller = mc;
//     // numRows = 1;
//     // numColumns = 1;
//     // MyVector<T> tempVect(1);
//     // myVect.PushBack(tempVect);
// }

template <class T>
LMatrix<T>::LMatrix(int rows, int columns)
{
    MatrixController<LMatrix<T>, T> mc(rows, columns);
    int counter = 1;
    for (int i = 0; i < rows; i++)
    {
        MyVector<T> temp(counter);
        for (int j = 0; j < counter; j++)
        {
            temp[j] = 0;
        }
        counter++;
        mc.PushBack(temp);
    }
    my_controller = mc;
}

template <class T>
LMatrix<T>::LMatrix(const Matrix<T> &source)
{
    MatrixController<LMatrix<T>, T> mc(source.GetRows(), source.GetColumns());
    my_controller = mc;
    CalculateLower(source);
}

// template <class T>
// LMatrix<T>::LMatrix(const LMatrix<T> &source)
// {
//     MatrixController<LMatrix<T>, T> mc(source.numRows, source.numColumns);
//     //mc do a copy here to copy all the contents from the source to the mc
//     //mc.copy then we shouldn't need a copy in the matrix class
//     mc.copy(source);
//     my_controller = mc;
//     // numRows = source.numRows;
//     // numColumns = source.numColumns;
//     // for (int i = 0; i < numRows; i++)
//     // {
//     //     MyVector<T> tempVect(numColumns);
//     //     myVect.PushBack(tempVect);
//     // }
// }

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
LMatrix<T> LMatrix<T>::Transpose()
{
    return my_controller.Transpose();
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