#pragma once

template<typename Vector>
class vectorIterator
{
private:
    // private variables 
    //pointerType = m_Ptr;
public:
    // public variables
    using valueType = typename Vector::valueType;
    using pointerType = valueType*;
    using refernceType = valueType&;

    pointerType m_Ptr;

public:
    // public methodes
    // constructor
    vectorIterator(pointerType ptr)
        : m_Ptr(ptr)
    {}
    

    // operator++
    vectorIterator& operator++()
    {
        m_Ptr++;
        return *this;   
    }

    vectorIterator operator++(int)
    {
        vectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    // decrement operator
    vectorIterator operator--()
    {
        m_Ptr--;
        return *this;
    }

    vectorIterator operator--(int)
    {
        vectorIterator iterator = *this;
        --(*this);
        return iterator;
    }

    // decrement operator
    refernceType operator[](int index)
    {
        return *(m_Ptr + index);
    }

    // arrow operator
    pointerType operator->()
    {
        return m_Ptr;
    }

    // * operator
    refernceType operator*()
    {
        return *m_Ptr;
    }

    // == operator
    bool operator==(const vectorIterator& other) const
    {
        return m_Ptr == other.m_Ptr;
    }

    // notequalsto opeartor
    bool operator!=(const vectorIterator& other) const
    {
        return !(*this == other);
    }

    //~vectorIterator();
};

template<typename T>
class Vector
{
private:
    // private class member
    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;

private:
    // private methode
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
            new (&newBlock[i]) T(std::move(m_Data[i]));
        }

        // delete the old size 
        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i].~T();
        }

        ::operator delete(m_Data, m_Capacity * sizeof(T));

        // reassigning the pointers to the class variables 
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
public:
    // public variables 
    using valueType = T;
    using iterator = vectorIterator<Vector<T>>;
public:
    // public method
    // constructor for allocating the initial memory 
    Vector()
    {
        // allocating memory in the constructor
        reAlloc(2);
    }

    // pushBack function with const 
    void pushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
        {
            reAlloc(m_Capacity + m_Capacity / 2);
        }

        m_Data[m_Size] = value;
        m_Size++;
    }

    // pushBack function by using std::move
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
        //std::cout << "before emplaceback - size :" << m_Size << ", capacity :" << m_Capacity << "\n";
        if (m_Size >= m_Capacity)
        {
            reAlloc(m_Capacity + m_Capacity / 2);
        }
        new (&m_Data[m_Size])  T(std::forward<Args>(args)...);

        //std::cout << "after emplacebck - size :" << m_Size << ", capacity :" << m_Capacity << "\n";
        return m_Data[m_Size++];
    }

    // popback(removing one element in the vector )
    void popBack()
    {
        if (m_Size > 0)
        {
            m_Size--;
            m_Data[m_Size].~T();
        }
    }

    // clear (clear all the element from the vector class)
    void clear()
    {
        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i].~T();
        }
        m_Size = 0;
    }

    // begain function
    iterator begin()
    {
        return iterator(m_Data);
    }

    // end function
    iterator end()
    {
        return iterator(m_Data + m_Size);
    }

    // distructor
    ~Vector()
    {
        clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }
};
