#ifndef ARRAY2D_H__
#define ARRAY2D_H__

#include "define.h"

template <class T>
class Array2d
{
public:
    Array2d(int x, int y);
    ~Array2d();
    Array2d(const Array2d &other);

    void Set(int x, int y, const T& value);
    const T& Get(int x, int y) const;

    void Reset(const T& value );

private:
    int GetIndex(int x, int y) const;
    T *m_blocks;
    int m_x, m_y;
};

template <class T>
Array2d<T>::Array2d(int x, int y)
{
    m_blocks = new T[x * y ];
    Reset(T());
}

template <class T>
Array2d<T>::~Array2d()
{
    delete[] m_blocks;
}

template <class T>
Array2d<T>::Array2d(const Array2d &other)
{
    m_blocks = new T[m_x * m_y ];
    for(int i = 0; i < m_x * m_y ; i++)
        m_blocks[i] = other.m_blocks[i];
}

template <class T>
void Array2d<T>::Set(int x, int y, const T& value )
{
    m_blocks[GetIndex(x, y)] = value ;
}

template <class T>
const T& Array2d<T>::Get(int x, int y) const
{
    return m_blocks[GetIndex(x, y)];
}

template <class T>
void Array2d<T>::Reset(const T& value )
{
    for(int i = 0; i < m_x * m_y ; i++)
        m_blocks[i] = value;
}

template <class T>
int Array2d<T>::GetIndex(int x, int y) const
{
    return x + (y * m_x) ;
}

#endif // ARRAY2D_H__