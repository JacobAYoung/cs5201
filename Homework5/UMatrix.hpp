template <class T>
UMatrix<T>::UMatrix()
{
    MatrixController<UMatrix<T>, T> mc;
    my_controller = mc;
}

template <class T>
UMatrix<T>::UMatrix(int rows, int columns)
{
    MatrixController<UMatrix<T>, T> mc(rows, columns, 1);
    my_controller = mc;
}

template <class T>
UMatrix<T>::UMatrix(const Matrix<T> &source)
{
    MatrixController<UMatrix<T>, T> mc(source.GetRows(), source.GetColumns(), 1);
    my_controller = mc;
    CalculateUpper(source);
}

template <class T>
UMatrix<T>::UMatrix(const UMatrix<T> &source)
{
    MatrixController<UMatrix<T>, T> mc(source.numRows, source.numColumns, 1);
    mc.copy(source);
    my_controller = mc;
}

template <class T>
UMatrix<T>::~UMatrix() {}

template <class T>
int UMatrix<T>::GetRows() const
{
    return my_controller.GetRows();
}

template <class T>
int UMatrix<T>::GetColumns() const
{
    return my_controller.GetColumns();
}

template <class T>
UMatrix<T> UMatrix<T>::Transpose()
{
    return my_controller.Transpose();
}

template <class T>
MyVector<T> &UMatrix<T>::operator[](const int &i)
{
    return my_controller[i];
}

template <class T>
MyVector<T> &UMatrix<T>::operator[](const int &i) const
{
    return my_controller[i];
}

template <class T>
void UMatrix<T>::CalculateUpper(const Matrix<T> &source)
{
    Matrix<T> m = source;
    //Set all the values to 0 or 1 depending on the location.
    //This is just reassurance before calculating the values
    for (int i = 0; i < my_controller.GetRows(); i++)
    {
        for (int j = 0; j < my_controller.GetColumns(); j++)
        {
            if (i < j)
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
            for (int j = 0; j < source.GetRows(); j++)
            {
                m[k][j] = m[k][j] - t * m[i][j];
            }
        }
    }
    for (int i = 0; i < my_controller.GetRows(); i++)
    {
        for (int j = 0; j < my_controller.GetColumns(); j++)
        {
            if (i <= j)
            {
                my_controller[i][j] = m[i][j];
            }
        }
    }
    return;
}

template <class T>
T &UMatrix<T>::operator()(const int &i, const int &j)
{
    if (i <= j)
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
T &UMatrix<T>::operator()(const int &i, const int &j) const
{
    if (i <= j)
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
void UMatrix<T>::PushBack(const MyVector<T> &source)
{
    my_controller.PushBack(source);
    return;
}

template <class T>
UMatrix<T> UMatrix<T>::operator*(const T &val)
{
    return my_controller * val;
}

template <typename T>
UMatrix<T> operator*(const UMatrix<T> &lhs, const UMatrix<T> &rhs)
{
    UMatrix<T> temp(lhs.GetRows(), lhs.GetColumns());
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

template <class T>
UMatrix<T> &UMatrix<T>::operator=(const UMatrix<T> &source)
{
    if (*this != source)
    {
        my_controller = source.my_controller;
    }
    return (*this);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const UMatrix<T> &source)
{
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
        {
            if (i <= j)
            {
                cout << source(i, j) << " ";
            }
        }
        cout << endl;
        for (int j = 1; j <= i + 1; j++)
        {
            cout << "\t";
        }
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &in, UMatrix<T> &source)
{
    MyVector<double> temp(source.GetColumns());
    for (int i = 0; i < source.GetColumns(); i++)
    {
        in >> temp[i];
    }
    source.PushBack(temp);
    return in;
}