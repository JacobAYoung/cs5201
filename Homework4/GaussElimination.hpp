/**
 * @file GaussElimination.h
 * @author Jake Young
 * @pre GaussElimination object is created and matrix object is created along
 * with a b vector
 * @post Can calcuate the forward elimination of a matrix and b vector
 * @brief File for calculating forward elimination of a matrix and b vector
 * @version 0.1
 * @date 2019-03-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
template <class T>
MyVector<MyVector<T>> GaussElimination<T>::ForwardElimination(const MyVector<MyVector<T>> &A, const MyVector<T> &B)
{
    int numElements = A.GetNumElements();
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
MyVector<T> GaussElimination<T>::GaussEliminate(const MyVector<MyVector<T>> &A, const MyVector<T> &B)
{
    int numElements = A.GetNumElements();
    //Create a vector x to be returned
    MyVector<T> x(A.GetNumElements());
    MyVector<MyVector<T>> temp = ForwardElimination(A, B);
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