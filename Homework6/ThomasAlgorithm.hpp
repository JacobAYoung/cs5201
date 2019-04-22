template <class T>
MyVector<T> ThomasAlgorithm<T>::ThomasAlg(const TMatrix<T> &source, const MyVector<T> b) const
{
    int size = source.GetRows();
    TMatrix<T> temp(source);
    DMatrix<T> a(size - 1, size - 1);
    DMatrix<T> bb(size, size);
    DMatrix<T> c(size - 1, size - 1);
    DMatrix<T> d(size, size);
    MyVector<T> x_values(size);

    for (int i = 1; i < size; i++)
    {
        a(i - 1, i - 1) = source(i, i - 1);
    }

    for (int i = 0; i < size; i++)
    {
        bb(i, i) = source(i, i);
    }

    for (int i = 1; i < size; i++)
    {
        c(i - 1, i - 1) = source(i - 1, i);
    }

    for (int i = 0; i < size; i++)
    {
        d(i, i) = b[i];
    }

    size--; // since we start from x0 (not x1)
    c(0, 0) /= bb(0, 0);
    d(0, 0) /= bb(0, 0);
    for (int i = 1; i < size; i++)
    {
        c(i, i) /= bb(i, i) - a(i, i) * c(i - 1, i - 1);
        d(i, i) = (d(i, i) - a(i, i) * d(i - 1, i - 1)) / (bb(i, i) - a(i, i) * c(i - 1, i - 1));
    }
    d(size, size) = (d(size, size) - a(size - 1, size - 1) * d(size, size)) / (bb(size, size) - a(size - 1, size - 1) * c(size - 1, size - 1));
    for (int i = size; i-- > 0;)
    {
        d(i, i) -= c(i, i) * d(i + 1, i + 1);
    }
    for (int i = 0; i < size; i++)
    {
        x_values[i] = d(i, i);
    }
    return x_values;
}