#include "NewVector.h"

// Default constructor
template <typename T>
NewVector<T>::NewVector()
    : data(nullptr), capacity(0), current(0) {}

// Destructor
template <typename T>
NewVector<T>::~NewVector() {
    delete[] data;
}

// Copy constructor
template <typename T>
NewVector<T>::NewVector(const NewVector<T>& old)
    : data(new T[old.capacity]), capacity(old.capacity), current(old.current) {
    std::copy(old.data, old.data + old.current, data);
}

// Move constructor
template <typename T>
NewVector<T>::NewVector(NewVector<T>&& old)
    : data(old.data), capacity(old.capacity), current(old.current) {
    old.data = nullptr;
    old.capacity = 0;
    old.current = 0;
}

// Copy assignment
template <typename T>
NewVector<T>& NewVector<T>::operator=(const NewVector<T>& old) {
    if (this != &old) {
        delete[] data;
        data = new T[old.capacity];
        capacity = old.capacity;
        current = old.current;
        std::copy(old.data, old.data + old.current, data);
    }
    return *this;
}

// Move assignment
template <typename T>
NewVector<T>& NewVector<T>::operator=(NewVector<T>&& old) {
    if (this != &old) {
        delete[] data;
        data = old.data;
        capacity = old.capacity;
        current = old.current;
        old.data = nullptr;
        old.capacity = 0;
        old.current = 0;
    }
    return *this;
}

// Push_back method
template <typename T>
void NewVector<T>::push_back(const T& value) {
    if (current == capacity)
        reserve(capacity == 0 ? 1 : 2 * capacity);

    data[current++] = value;
}

// Reserve method
template <typename T>
void NewVector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity) {
        T* new_data = new T[new_capacity];
        std::copy(data, data + current, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
}

// Size method
template <typename T>
size_t NewVector<T>::size() const {
    return current;
}

// Max_size method
template <typename T>
size_t NewVector<T>::max_size() const {
    return capacity;
}

// Operator[] method
template <typename T>
T& NewVector<T>::operator[](size_t index) {
    if (index >= current) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
