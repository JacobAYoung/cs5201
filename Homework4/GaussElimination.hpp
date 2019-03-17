template <class T>
MyVector<T> GaussElimination<T>::GaussEliminate(const MyVector<MyVector<T>> &A, const MyVector<T> &B)
{
    int numElements = A.GetNumElements();
    //Create a vector x to be returned
    MyVector<T> x(A.GetNumElements());
    //Create a copy of the matrix A
    MyVector<MyVector<T>> temp = A;

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

    //Solve for x values
    for (int i = numElements - 1; i >= 0; i--)
    {
        x[i] = B[i] / temp[i][i];
        for (int j = i - 1; j >= 0; j--)
        {
            B[j] -= temp[j][i] * x[i];
        }
    }
    return x;
}