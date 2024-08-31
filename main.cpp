#include <iostream>
#include "include/vector.h"

struct Vector3
{
    float x = 0.0f, y = 0.0f, z = 0.0f;

    Vector3() = default;

    Vector3(float scalar)
        : x(scalar), y(scalar), z(scalar)
    {}

    Vector3(float x, float y, float z)
        : x(x), y(y), z(z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
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
        std::cout << "moved \n";
    }

    // move assaignment operator
    Vector3& operator=(Vector3&& other) noexcept
    {
        if (this != &other)
        {
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

    ~Vector3()
    {
        std::cout << "destroyed\n";
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
    Vector<Vector3> vector;
    vector.pushBack(Vector3(1.0f));
    vector.pushBack(Vector3(2, 3, 4));
    vector.pushBack(Vector3());
    vector.pushBack(Vector3(1, 2, 3));
    vector.pushBack(Vector3());
    vector.pushBack(Vector3(1, 2, 3));

    printVector(vector);
    std::cin.get();
    return 0;
}