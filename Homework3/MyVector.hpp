template <class T>
MyVector<T>::MyVector()
{
    numElements = 0;
    this->ptr_to_data = 0;
}

template <class T>
MyVector<T>::MyVector(int n)
{
    numElements = n;
    ptr_to_data = new T[n];
    for (int i = 0; i < n; i++)
    {
        this->ptr_to_data[i] = 0;
    }
}

template <class T>
MyVector<T>::MyVector(const MyVector &source)
{

    numElements = source.numElements;
    this->ptr_to_data = new T[numElements];
    for (int i = 0; i < numElements; i++)
    {
        this->ptr_to_data[i] = 0;
    }
    copy(source);
}

template <class T>
void MyVector<T>::copy(const MyVector &source)
{
    for (int i = 0; i < source.GetNumElements(); i++)
    {
        this->ptr_to_data[i] = source.ptr_to_data[i];
    }
    return;
}

template <class T>
MyVector<T>::~MyVector()
{
    delete[] ptr_to_data;
}

template <class T>
T &MyVector<T>::operator[](const int &i)
{
    if (i >= 0 && i <= GetNumElements())
    {
        return this->ptr_to_data[i];
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
T &MyVector<T>::operator[](const int &i) const
{
    if (i >= 0 && i <= GetNumElements())
    {
        return this->ptr_to_data[i];
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
MyVector<T> &MyVector<T>::operator=(const MyVector &source)
{
    if (this->ptr_to_data != source.ptr_to_data)
    {
        SetSize(source.numElements);
        copy(source);
    }
    return (*this);
}

template <class T>
void MyVector<T>::SetSize(const int size)
{
    if (size != numElements)
    {
        delete[] ptr_to_data;
        numElements = size;
        this->ptr_to_data = new T[numElements];
    }
    return;
}

template <class T>
MyVector<T> &MyVector<T>::operator=(const T val)
{
    for (int i = 0; i < numElements; i++)
    {
        this->ptr_to_data[i] = val;
    }
    return (*this);
}

template <class T>
int MyVector<T>::GetNumElements() const
{
    return numElements;
}

// template <class T>
// bool operator==(const MyVector<T> &lhs, const MyVector<T> &rhs)
// {
//     if ((lhs.GetR() == rhs.GetR()) && (lhs.GetTheta() == rhs.GetTheta()) && (lhs.GetZ() == rhs.GetZ()))
//     {
//         return true;
//     }
//     return false;
// }

// template <class T>
// bool operator!=(const MyVector<T> &lhs, const MyVector<T> &rhs)
// {
//     if ((lhs.GetR() != rhs.GetR()) || (lhs.GetTheta() != rhs.GetTheta()) || (lhs.GetZ() != rhs.GetZ()))
//     {
//         return true;
//     }
//     return false;
// }

template <class T>
MyVector<T> &operator+(const MyVector<T> &lhs, const MyVector<T> &rhs)
{
    MyVector<T> temp(lhs.GetNumElements());
    if (lhs.GetNumElements() == rhs.GetNumElements())
    {
        for (int i = 0; i < temp.GetNumElements(); i++)
        {
            temp[i] = lhs[i] + rhs[i];
        }
    }
    else
    {
        throw std::range_error("Vectors are not same size.");
    }
    return temp;
}

template <class T>
MyVector<T> &operator-(const MyVector<T> &lhs, const MyVector<T> &rhs)
{
    MyVector<T> temp(lhs.GetNumElements());
    if (lhs.GetNumElements() == rhs.GetNumElements())
    {
        for (int i = 0; i < temp.GetNumElements(); i++)
        {
            temp[i] = lhs[i] - rhs[i];
        }
    }
    else
    {
        throw std::range_error("Vectors are not same size.");
    }
    return temp;
}

template <class T>
MyVector<T> &operator-(const MyVector<T> &source)
{
    MyVector<T> temp(source);
    for (int i = 0; i < temp.GetNumElements(); i++)
    {
        temp[i] *= -1;
    }
    return temp;
}

template <typename T>
T operator*(const MyVector<T> &lhs, const MyVector<T> &rhs)
{
    T total = 0;
    if (lhs.GetNumElements() == rhs.GetNumElements())
    {
        for (int i = 0; i < lhs.GetNumElements(); i++)
        {
            total += lhs[i] * rhs[i];
        }
    }
    else
    {
        throw std::range_error("Vectors are not same size.");
    }
    return total;
}

template <class T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &source)
{
    return out << "(" << source[0] << " " << source[1] << " " << source[2] << " " << source[3] << ")";
}

template <class T>
std::istream &operator>>(std::istream &in, const MyVector<T> &source)
{
    in >> source[0];
    in >> source[1];
    in >> source[2];
    in >> source[3];
    return in;
}