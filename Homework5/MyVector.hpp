template <class T>
MyVector<T>::MyVector()
{
    numElements = 0;
    this->ptr_to_data = 0;
}

template <class T>
MyVector<T>::MyVector(int size)
{
    if (size < 0)
    {
        throw std::range_error("Cannot have negative size");
    }
    numElements = size;
    ptr_to_data = new T[size];
    for (int i = 0; i < size; i++)
    {
        this->ptr_to_data[i] = 0;
    }
}

template <class T>
MyVector<T>::MyVector(const MyVector<T> &source)
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
MyVector<T>::MyVector(MyVector<T> &&source)
{
    this->numElements = source.numElements;
    this->ptr_to_data = std::move(source.ptr_to_data);

    source.numElements = 0;
    source.ptr_to_data = nullptr;
}

template <class T>
void MyVector<T>::copy(const MyVector<T> &source)
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
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &source)
{
    if (this->ptr_to_data != source.ptr_to_data)
    {
        SetSize(source.numElements);
        copy(source);
    }
    return (*this);
}

template <class T>
int MyVector<T>::GetNumElements() const
{
    return numElements;
}

template <class T>
void MyVector<T>::SetSize(const int size)
{
    if (size < 0)
    {
        throw std::range_error("Cannot have negative size");
    }
    if (size != numElements)
    {
        delete[] ptr_to_data;
        numElements = size;
        this->ptr_to_data = new T[numElements];
        for (int i = 0; i < numElements; i++)
        {
            this->ptr_to_data[i] = 0;
        }
    }
    return;
}

template <class T>
void MyVector<T>::PushBack(const MyVector<double> &source)
{
    MyVector<T> temp(this->GetNumElements() + 1);
    temp.copy(*this);
    this->SetSize(this->GetNumElements() + 1);
    for (int i = 0; i < GetNumElements() - 1; i++)
    {
        this->ptr_to_data[i] = temp.ptr_to_data[i];
    }
    this->ptr_to_data[this->GetNumElements() - 1] = source;
    return;
}

template <typename T>
bool operator==(const MyVector<T> &lhs, const MyVector<T> &rhs)
{
    bool equal = false;
    if (lhs.GetNumElements() == rhs.GetNumElements())
    {
        for (int i = 0; i < rhs.GetNumElements(); i++)
        {
            if (abs(lhs[i] - rhs[i]) < .001)
            {
                equal = true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return equal;
}

template <typename T>
bool operator!=(const MyVector<T> &lhs, const MyVector<T> &rhs)
{
    bool notEqual = false;
    if (lhs.GetNumElements() == rhs.GetNumElements())
    {
        for (int i = 0; i < rhs.GetNumElements(); i++)
        {
            if (abs(lhs[i] - rhs[i]) < .001)
            {
                notEqual = false;
            }
            else
            {
                return true;
            }
        }
    }
    else
    {
        return true;
    }
    return notEqual;
}

template <typename T>
MyVector<T> operator+(const MyVector<T> &lhs, const MyVector<T> &rhs)
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

template <typename T>
MyVector<T> operator-(const MyVector<T> &lhs, const MyVector<T> &rhs)
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

template <typename T>
MyVector<T> operator-(const MyVector<T> &source)
{
    MyVector<T> temp(source);
    for (int i = 0; i < temp.GetNumElements(); i++)
    {
        temp[i] *= -1;
    }
    return temp;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &source)
{
    for (int i = 0; i < source.GetNumElements(); i++)
    {
        out << source[i] << " ";
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &in, const MyVector<T> &source)
{
    for (int i = 0; i < source.GetNumElements(); i++)
    {
        in >> source[i];
    }

    return in;
}