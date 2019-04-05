template <class T>
Matrix<T> GaussElimination<T>::ForwardElimination(const Matrix<T> &source, const MyVector<T> &B) const
{
    int numElements = source.GetRows();
    //Create a copy of the matrix A
    Matrix<T> temp = source;

    for (int i = 0; i < numElements; i++)
    {
        T maxValue = abs(temp[i][i]);
        int maxRow = i;
        //Find largest value in row
        for (int j = i + 1; j < numElements; j++)
        {
            if (abs(temp[j][i]) > maxValue)
            {
                maxValue = abs(temp[j][i]);
                maxRow = j;
            }
        }
        //Solve for values
        for (int j = i; j < numElements + 1; j++)
        {
            T tmp;
            if (j == numElements)
            {
                tmp = B[maxRow];
                B[maxRow] = B[i];
                B[i] = tmp;
            }
            else
            {
                tmp = temp[maxRow][j];
                temp[maxRow][j] = temp[i][j];
                temp[i][j] = tmp;
            }
        }
        //Forward elimination: Set all the lower values to 0
        for (int j = i + 1; j < numElements; j++)
        {
            T c = -temp[j][i] / temp[i][i];
            for (int k = i; k < numElements + 1; k++)
            {
                if (i == k)
                {
                    temp[j][k] = 0;
                }
                else
                {
                    if (k == numElements)
                    {
                        B[j] += c * B[i];
                    }
                    else
                    {
                        temp[j][k] += c * temp[i][k];
                    }
                }
            }
        }
    }
    return temp;
}

template <class T>
MyVector<T> GaussElimination<T>::GaussEliminate(const Matrix<T> &source, const MyVector<T> &B) const
{
    int numElements = source.GetRows();
    //Create a vector x to be returned
    MyVector<T> x(numElements);
    Matrix<T> temp = ForwardElimination(source, B);
    for (int i = numElements - 1; i >= 0; i--)
    {
        //Solve for x values
        x[i] = B[i] / temp[i][i];
        for (int j = i - 1; j >= 0; j--)
        {
            //Calculate new B vector values
            B[j] -= temp[j][i] * x[i];
        }
    }
    return x;
}

template <class T>
MyVector<T> GaussElimination<T>::BackSub(const UMatrix<T> &A, const MyVector<T> &B) const
{
    int numElements = A.GetRows();
    MyVector<T> x(numElements);
    UMatrix<T> temp(A);
    for (int i = numElements - 1; i >= 0; i--)
    {
        if (temp(i, i) == 0)
        {
            throw std::logic_error("Zero in main diagonal");
        }
        x[i] = B[i] / temp(i, i);
        for (int j = i - 1; j >= 0; j--)
        {
            B[j] -= temp(j, i) * x[i];
        }
    }
    return x;
}

template <class T>
MyVector<T> GaussElimination<T>::ForwardSub(const LMatrix<T> &A, const MyVector<T> &B) const
{
    int numElements = A.GetRows();
    MyVector<T> x = B;
    LMatrix<T> temp(A);
    for (int i = 0; i < numElements; i++)
    {
        if (temp(i, i) == 0)
        {
            throw std::logic_error("Zero in main diagonal");
        }
        for (int j = 0; j < i; j++)
        {
            x[i] = x[i] - (temp(i, j) * x[j]);
        }
        x[i] = x[i] / temp(i, i);
    }
    return x;
}