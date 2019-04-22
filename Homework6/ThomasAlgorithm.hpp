template <class T>
MyVector<T> ThomasAlgorithm<T>::ThomasAlg(const TMatrix<T> &source, const MyVector<T> b) const
{
    int size = source.GetRows();
    //These are the names for each diagonal for the tridiagonal matrix
    TMatrix<T> temp(source);
    DMatrix<T> a(size, size);
    DMatrix<T> bb(size, size);
    DMatrix<T> c(size, size);
    DMatrix<T> d(size, size);
    MyVector<T> x_values(size);

    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            a(0, 0) = 0;
        }
        else
        {
            a(i, i) = source(i, i - 1);
        }
    }

    for (int i = 0; i < size; i++)
    {
        bb(i, i) = source(i, i);
    }

    for (int i = 0; i < size; i++)
    {
        if (i == size - 1)
        {
            c(i, i) = 0;
        }
        else
        {
            c(i, i) = source(i, i + 1);
        }
    }

    for (int i = 0; i < size; i++)
    {
        d(i, i) = b[i];
    }

    size--;
    c(0, 0) /= bb(0, 0);
    d(0, 0) /= bb(0, 0);
    for (int i = 1; i < size; i++)
    {
        c(i, i) /= bb(i, i) - a(i, i) * c(i - 1, i - 1);
        d(i, i) = (d(i, i) - a(i, i) * d(i - 1, i - 1)) / (bb(i, i) - a(i, i) * c(i - 1, i - 1));
    }
    d(size, size) = (d(size, size) - a(size, size) * d(size - 1, size - 1)) /
                    (bb(size, size) - a(size, size) * c(size - 1, size - 1));
    for (int i = size; i-- > 0;)
    {
        d(i, i) -= c(i, i) * d(i + 1, i + 1);
    }
    for (int i = 0; i < size + 1; i++)
    {
        x_values[i] = d(i, i);
    }
    return x_values;
}