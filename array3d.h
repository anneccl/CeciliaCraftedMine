#ifndef ARRAY3D_H
#define ARRAY3D_H

#include <cassert>

template <class T>
class Array3d
{
public:
    Array3d(int x, int y, int z);
    ~Array3d();
    Array3d(const Array3d &other);
    Array3d& operator=(const Array3d &other);

    void Set(int x, int y, int z, const T& value);
    const T& Get(int x, int y, int z) const;

    void Reset(const T& value);

private:
    int GetIndex(int x, int y, int z) const;

    T *m_blocks;
    int m_x, m_y, m_z;
};

template <class T>
Array3d<T>::Array3d(int x, int y, int z)
    : m_blocks(nullptr), m_x(x), m_y(y), m_z(z)
{
    m_blocks = new T[m_x * m_y * m_z];
    Reset(T());
}

template <class T>
Array3d<T>::~Array3d()
{
    delete[] m_blocks;
}

template <class T>
Array3d<T>::Array3d(const Array3d &other)
    : m_blocks(nullptr), m_x(other.m_x), m_y(other.m_y), m_z(other.m_z)
{
    m_blocks = new T[m_x * m_y * m_z];
    for (int i = 0; i < m_x * m_y * m_z; ++i)
        m_blocks[i] = other.m_blocks[i];
}

template <class T>
Array3d<T>& Array3d<T>::operator=(const Array3d &other)
{
    if (this == &other) return *this;
    delete[] m_blocks;
    m_x = other.m_x; m_y = other.m_y; m_z = other.m_z;
    m_blocks = new T[m_x * m_y * m_z];
    for (int i = 0; i < m_x * m_y * m_z; ++i)
        m_blocks[i] = other.m_blocks[i];
    return *this;
}

template <class T>
void Array3d<T>::Set(int x, int y, int z, const T& value)
{
    m_blocks[GetIndex(x, y, z)] = value;
}

template <class T>
const T& Array3d<T>::Get(int x, int y, int z) const
{
    return m_blocks[GetIndex(x, y, z)];
}

template <class T>
void Array3d<T>::Reset(const T& value)
{
    for (int i = 0; i < m_x * m_y * m_z; ++i)
        m_blocks[i] = value;
}

template <class T>
int Array3d<T>::GetIndex(int x, int y, int z) const
{
    assert(x >= 0 && x < m_x);
    assert(y >= 0 && y < m_y);
    assert(z >= 0 && z < m_z);
    return x + (z * m_x) + (y * m_z * m_x);
}

#endif // ARRAY3D_H
