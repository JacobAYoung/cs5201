template <class T, class U>
T Norm<T, U>::operator()(const vector<U> &vect) const
{
    double magnitude = 0;
    for (unsigned int i = 0; i < vect.size(); i++)
    {
        magnitude += ~vect[i];
    }
    return magnitude;
}