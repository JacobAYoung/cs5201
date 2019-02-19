MyVector::MyVector()
{
}

MyVector::MyVector(const MyVector &source)
{
    numElements = source.numElements;
    ptr_to_data = new float[numElements];
    copy(source);
}

void MyVector::copy(const MyVector &source)
{
    for (int i = 0; i < numElements; i++)
    {
        ptr_to_data[i] = source.ptr_to_data[i];
    }
    return;
}

MyVector::~MyVector()
{
    delete[] ptr_to_data;
}

float &MyVector::operator[](int i)
{
    return ptr_to_data[i];
}

MyVector &MyVector::operator=(const MyVector &source)
{
    if (ptr_to_data != source.ptr_to_data)
    {
        SetSize(source.numElements);
        copy(source);
    }
    return (*this);
}

void MyVector::SetSize(const int size)
{
    if (size != numElements)
    {
        delete[] ptr_to_data;
        numElements = size;
        ptr_to_data = new float[numElements];
    }
    return;
}

MyVector &MyVector::operator=(const float val)
{
    for (int i = 0; i < numElements; i++)
    {
        ptr_to_data[i] = val;
    }
    return (*this);
}

int MyVector::GetNumElements()
{
    return numElements;
}