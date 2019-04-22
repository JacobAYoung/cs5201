template <class T>
LMatrix<T> CholeskyDecomposition<T>::CholeskyDecomp(const SMatrix<T> &source) const
{
    LMatrix<T> temp(source.GetRows(), source.GetColumns());
    for (int i = 0; i < source.GetRows(); i++)
    {
        for (int j = 0; j < source.GetColumns(); j++)
        {
            T sum = 0;
            if (i == j)
            {
                for (int k = 0; k < j; k++)
                {
                    sum += pow(temp(j, k), 2);
                }
                temp(i, i) = sqrt(source[i][i] - sum);
            }
            else
            {
                for (int k = 0; k < j; k++)
                {
                    sum += (temp(i, k) * temp(j, k));
                }
                if (temp(j, j) == 0)
                {
                    throw std::logic_error("Division by zero.");
                }
                temp(i, j) = (source[i][j] - sum) / temp(j, j);
            }
        }
    }
    return temp;
}