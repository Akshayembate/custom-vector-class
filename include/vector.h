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

        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

        if (newCapacity < m_Size)
        {
            m_Size = newCapacity;
        }

        for (size_t i = 0; i < m_Size; i++)
        {
            newBlock[i] = std::move(m_Data[i]);
        }

        // delete the old size 
        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i].~T();
        }

        ::operator delete(m_Data, m_Capacity * sizeof(T));
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

    // function for reserving the capacity manually
    void reserve(size_t capacity)
    {
        if (capacity > m_Capacity)
        {
            reAlloc(capacity);
        }
    }

    // emplaceback function
    template<typename...Args>
    T& emplaceBack(Args&&...args)
    {
        std::cout << "before emplaceback - size :" << m_Size << ", capacity :" << m_Capacity << "\n";
        if (m_Size >= m_Capacity)
        {
            reAlloc(m_Capacity + m_Capacity / 2);
        }
        new (&m_Data[m_Size])  T(std::forward<Args>(args)...);

        std::cout << "after emplacebck - size :" << m_Size << ", capacity :" << m_Capacity << "\n";
        return m_Data[m_Size++];
    }

    // popback
    void popBack()
    {
        if (m_Size > 0)
        {
            m_Size--;
            m_Data[m_Size].~T();
        }
    }

    // clear
    void clear()
    {
        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i].~T();
        }
        m_Size = 0;
    }

    // distructor 
    ~Vector()
    {
        clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }
};
