#include <iostream>
#include "include/vector.h"

struct Vector3
{
    // struct memberrs
    float x = 0.0f, y = 0.0f, z = 0.0f;
    int* m_MemoryBlock = nullptr;

    // default constructor 
    Vector3() = default;

    // scalar constructor
    Vector3(float scalar)
        : x(scalar), y(scalar), z(scalar)
    {
        m_MemoryBlock = new int[5];
    }

    Vector3(float x_, float y_, float z_)
        : x(x_), y(y_), z(z_)
    {
        m_MemoryBlock = new int[5];
    }

    // copy constructor
    Vector3(const Vector3& other)
        : x(other.x), y(other.y), z(other.z)
    {
        std::cout << "copied\n";
    }

    // copy assaignment operator
    Vector3& operator=(const Vector3& other)
    {
        if (this != &other)
        {
            std::cout << "copy using by copy assaignemnt operator\n";
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
    
    // move constructor
    Vector3(Vector3&& other) noexcept
        : x(other.x), y(other.y), z(other.z)
    {
        m_MemoryBlock = other.m_MemoryBlock;

        other.m_MemoryBlock = nullptr;
        std::cout << "moved \n";
    }

    // move assaignment operator
    Vector3& operator=(Vector3&& other) noexcept
    {
        if (this != &other)
        {
            m_MemoryBlock = other.m_MemoryBlock;
            other.m_MemoryBlock = nullptr;

            std::cout << "moved using assaignmet operator\n";

            x = other.x;
            y = other.y;
            z = other.z;

            other.x = 0.0f;
            other.y = 0.0f;
            other.z = 0.0f;
        }
        return *this;
    }

    // distructor 
    ~Vector3()
    {
        std::cout << "destroyed\n";
        delete[] m_MemoryBlock;
    }
};


//template<>
void printVector(const Vector<Vector3>& vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
    {
        std::cout << vector[i].x << "," << vector[i].y << "," << vector[i].z << "\n";
    }
    std::cout << "--------------------------\n";
}

int main()
{
    //std::cout << "hello world \n";
    #if 0
    {
        Vector<Vector3> vector;
        //vector.reserve(10);

        vector.emplaceBack(1.0f);
        vector.emplaceBack(2, 3, 4);
        vector.emplaceBack();
        vector.emplaceBack(1, 2, 3);
        vector.emplaceBack();
        printVector(vector);

        vector.popBack();
        vector.popBack();
        printVector(vector);

        vector.clear();
        vector.emplaceBack(1, 2, 3);

        printVector(vector);
    }
    #endif

    #if 0
    Vector<int> values;
    values.emplaceBack(1);
    values.emplaceBack(2);
    values.emplaceBack(3);
    values.emplaceBack(4);
    values.emplaceBack(5);

    // iterate thrpow the values with using the [] operator
    std::cout << "not using the iterator :\n";
    for (size_t i = 0; i < values.Size(); i++)
    {
        std::cout << values[i] << "\n";
    }
    
    std::cout << "range based for loops :\n";
    for (int value : values)
    {
        std::cout << value << "\n";
    }

    std::cout << "iterator: \n";
    for (Vector<int>::iterator it = values.begin();
    it != values.end(); it++)
    {
        std::cout << *it << "\n";
    }
    #endif

    Vector<std::string> values;
    values.emplaceBack("something");
    values.emplaceBack("cpp");
    values.emplaceBack("vector");
    values.emplaceBack("it");
    values.emplaceBack("null");

    // iterate thrpow the values with using the [] operator
    std::cout << "not using the iterator :\n";
    for (size_t i = 0; i < values.Size(); i++)
    {
        std::cout << values[i] << "\n";
    }
    
    std::cout << "range based for loops :\n";
    for (auto& value : values)
    {
        std::cout << value << "\n";
    }

    std::cout << "iterator: \n";
    for (Vector<std::string>::iterator it = values.begin();
    it != values.end(); it++)
    {
        std::cout << *it << "\n";
    }

    std::cin.get();
    return 0;
}