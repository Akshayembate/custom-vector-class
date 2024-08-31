#pragma once

template<typename T>
class Vector
{
private:
    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;

private:
    void reAlloc(size_t newCapacity)
    { 
        // 1 . allocate the new block of memory
        // 2 . copy/ move old elements in to the new memory 
        // 3 . delete

        T* newBlock = new T[newCapacity];

        if (newCapacity < m_Size)
        {
            m_Size = newCapacity;
        }

        for (size_t i = 0; i < m_Size; i++)
        {
            newBlock[i] = std::move(m_Data[i]);
        }

        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
public:
    Vector()
    {
        // allocating memory in the constructor
        reAlloc(2);
    }

    void pushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
        {
            reAlloc(m_Capacity + m_Capacity / 2);
        }

        m_Data[m_Size] = value;
        m_Size++;
    }

    void pushBack(T&& value)
    {
        if (m_Size >= m_Capacity)
        {
            reAlloc(m_Capacity + m_Capacity / 2);
        }

        m_Data[m_Size] = std::move(value);
        m_Size++;
    }

    // index operation for getting the data from the vector 
    T& operator[](size_t index)
    {
        return m_Data[index];
    }

    // constant version of the index operation
    const T& operator[](size_t index) const
    {
        return m_Data[index];
    }

    size_t Size() const
    {
        return m_Size;
    }

    //~Vector();
};
