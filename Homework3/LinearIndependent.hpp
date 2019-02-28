template <class T>
LinearIndependent<T>::LinearIndependent(int size)
{
    for (int i = 0; i < size; i++)
    {
        data.push_back(0);
    }
}

template <class T>
vector<T> LinearIndependent<T>::GetData() const
{
    return data;
}

template <class T>
double LinearIndependent<T>::GetEpsilon() const
{
    return EPSILON;
}

template <class T>
bool LinearIndependent<T>::CheckLinearIndependent(vector<vector<T>> &matrix, const int &size)
{
    int flag = 0, count = 0;

    for (int i = 0; i < size; i++)
    {
        for (int k = i + 1; k < size; k++)
        {
            if (abs(matrix[i][i]) < abs(matrix[k][i]))
            {
                for (int j = 0; j <= size; j++)
                {
                    T temp = matrix[i][j];
                    matrix[i][j] = matrix[k][j];
                    matrix[k][j] = temp;
                }
            }
        }
    }

    while (flag < size)
    {
        for (int i = 0; i < size; i++)
        {
            T temp = data[i];
            data[i] = matrix[i][size];
            for (int j = 0; j < size; j++)
            {
                if (j != i)
                    data[i] = data[i] - matrix[i][j] * data[j];
            }
            data[i] = data[i] / matrix[i][i];
            if (abs(data[i] - temp) <= EPSILON)
                flag++;
        }
        count++;
        if (count == MAX_ITERATIONS)
        {
            return false;
        }
    }
    return true;
}