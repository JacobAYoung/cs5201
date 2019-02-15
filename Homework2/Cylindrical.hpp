template <class T>
Cylindrical<T>::Cylindrical()
{
    const T INIT = 0;
    this->ptr_to_data = new T[3];
    this->ptr_to_data[0] = INIT;
    this->ptr_to_data[1] = INIT;
    this->ptr_to_data[2] = INIT;
}

template <class T>
Cylindrical<T>::Cylindrical(const T &radius, const T &theta, const T &z)
{
    this->ptr_to_data = new T[3];
    this->ptr_to_data[0] = radius;
    this->ptr_to_data[1] = theta;
    this->ptr_to_data[2] = z;
}
template <class T>
Cylindrical<T>::Cylindrical(const Cylindrical<T> &source)
{
    this->ptr_to_data = new T[3];
    CylindricalCopy(source);
}

template <class T>
Cylindrical<T>::~Cylindrical()
{
    delete[] this->ptr_to_data;
}

template <class T>
T &Cylindrical<T>::operator[](const int &i)
{
    if (i >= 0 && i <= 2)
    {
        return this->ptr_to_data[i];
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
T &Cylindrical<T>::operator[](const int i) const
{
    if (i >= 0 && i <= 2)
    {
        return this->ptr_to_data[i];
    }
    else
    {
        throw std::range_error("Out of bounds");
    }
}

template <class T>
Cylindrical<T> &Cylindrical<T>::operator=(const Cylindrical<T> &source)
{
    if (ptr_to_data != source.ptr_to_data)
    {
        CylindricalCopy(source);
    }
    return (*this);
}

template <class T>
void Cylindrical<T>::CylindricalCopy(const Cylindrical<T> &source)
{
    for (int i = 0; i < 3; i++)
    {
        ptr_to_data[i] = source.ptr_to_data[i];
    }
    return;
}

template <class T>
T &Cylindrical<T>::CalculateDistance(const Cylindrical<T> &source)
{
    return sqrt(pow(source.ptr_to_data[3], 2) + pow(source.ptr_to_data[4], 2) + pow(source.ptr_to_data[2], 2));
}

template <class T>
T Cylindrical<T>::GetR() const
{
    return ptr_to_data[0];
}

template <class T>
T Cylindrical<T>::GetTheta() const
{
    return ptr_to_data[1];
}

template <class T>
T Cylindrical<T>::GetX() const
{
    T x = GetR() * cos(GetTheta());
    return x;
}

template <class T>
T Cylindrical<T>::GetY() const
{
    T y = GetR() * sin(GetTheta());
    return y;
}

template <class T>
T Cylindrical<T>::GetZ() const
{
    return ptr_to_data[2];
}

template <class T>
string Cylindrical<T>::PrintPoints() const
{
    return ("(" + std::to_string(GetX()) + ", " + std::to_string(GetY()) + ", " + std::to_string(GetZ()) + ")");
}

template <class T>
bool operator<(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs)
{
    if (CalculateDistance(lhs) < CalculateDistance(rhs))
    {
        return true;
    }
    return false;
}

template <class T>
bool operator>(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs)
{
    if (CalculateDistance(lhs) > CalculateDistance(rhs))
    {
        return true;
    }
    return false;
}

template <class T>
bool operator==(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs)
{
    if ((lhs.GetR() == rhs.GetR()) && (lhs.GetTheta() == rhs.GetTheta()) && (lhs.GetZ() == rhs.GetZ()))
    {
        return true;
    }
    return false;
}

template <class T>
bool operator!=(const Cylindrical<T> &lhs, const Cylindrical<T> &rhs)
{
    if ((lhs.GetR() != rhs.GetR()) || (lhs.GetTheta() != rhs.GetTheta()) || (lhs.GetZ() != rhs.GetZ()))
    {
        return true;
    }
    return false;
}

template <class T>
double operator~(const Cylindrical<T> &source)
{
    T val = sqrt(pow(source.GetX(), 2) + pow(source.GetY(), 2) + pow(source.GetZ(), 2));
    return val;
}

template <class T>
Cylindrical<T> operator-(const Cylindrical<T> &source)
{
    T tempR = source.GetR() * -1;
    T tempZ = source.GetZ() * -1;
    return Cylindrical<T>(tempR, source.GetTheta(), tempZ);
}

template <class T>
Cylindrical<T> operator!(const Cylindrical<T> &source)
{
    T tempR = source.GetR() * -1;
    return Cylindrical<T>(tempR, source.GetTheta(), source.GetZ());
}

template <class T>
std::ostream &operator<<(std::ostream &out, const Cylindrical<T> &source)
{
    return out << "(" << source.GetR() << ", " << source.GetTheta() << ", " << source.GetZ() << ")" << endl;
}

template <class T>
std::istream &operator>>(std::istream &in, const Cylindrical<T> &source)
{
    in >> source[0];
    in >> source[1];
    in >> source[2];
    return in;
}
