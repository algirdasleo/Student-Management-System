#include "NewVector.h"

// Default constructor
template <typename T>
NewVector<T>::NewVector()
    : dataStart(nullptr), capacity(0), currentSize(0) {}

// Destructor
template <typename T>
NewVector<T>::~NewVector() {
    delete[] dataStart;
}

// Initializer list constructor
template <typename T>
NewVector<T>::NewVector(std::initializer_list<T> list)
    : dataStart(new T[list.size()]), capacity(list.size()), currentSize(list.size()) {
    std::copy(list.begin(), list.end(), dataStart);
}

// Copy constructor
template <typename T>
NewVector<T>::NewVector(const NewVector<T>& old)
    : dataStart(new T[old.capacity]), capacity(old.capacity), currentSize(old.currentSize) {
    std::copy(old.dataStart, old.dataStart + old.currentSize, dataStart);
}

// Move constructor
template <typename T>
NewVector<T>::NewVector(NewVector<T>&& old)
    : dataStart(old.dataStart), capacity(old.capacity), currentSize(old.currentSize) {
    old.dataStart = nullptr;
    old.capacity = 0;
    old.currentSize = 0;
}

// Copy assignment
template <typename T>
NewVector<T>& NewVector<T>::operator=(const NewVector<T>& old) {
    if (this != &old) {
        delete[] dataStart;
        dataStart = new T[old.capacity];
        capacity = old.capacity;
        currentSize = old.currentSize;
        std::copy(old.dataStart, old.dataStart + old.currentSize, dataStart);
    }
    return *this;
}

// Move assignment
template <typename T>
NewVector<T>& NewVector<T>::operator=(NewVector<T>&& old) {
    if (this != &old) {
        delete[] dataStart;
        dataStart = old.dataStart;
        capacity = old.capacity;
        currentSize = old.currentSize;
        old.dataStart = nullptr;
        old.capacity = 0;
        old.currentSize = 0;
    }
    return *this;
}

// Comparison operator
template <typename T>
bool NewVector<T>::operator==(const NewVector<T>& other) const {
    if (currentSize != other.currentSize)
        return false;

    for (size_t i = 0; i < currentSize; ++i) {
        if (dataStart[i] != other.dataStart[i])
            return false;
    }

    return true;
}

// Operator[] method
template <typename T>
T& NewVector<T>::operator[](size_t index) {
    if (index >= currentSize)
        throw std::out_of_range("Index out of range");

    return dataStart[index];
}

// Operator[] method. Const version
template <typename T>
const T& NewVector<T>::operator[](size_t index) const {
    if (index >= currentSize)
        throw std::out_of_range("Index out of range");

    return dataStart[index];
}

// Front method
template <typename T>
T& NewVector<T>::front() {
    if (currentSize == 0)
        throw std::out_of_range("Vector is empty");

    return dataStart[0];
}

// Front method. Const version
template <typename T>
const T& NewVector<T>::front() const {
    if (currentSize == 0)
        throw std::out_of_range("Vector is empty");

    return dataStart[0];
}

// Back method
template <typename T>
T& NewVector<T>::back() {
    if (currentSize == 0)
        throw std::out_of_range("Vector is empty");

    return dataStart[currentSize - 1];
}

// Back method. Const version
template <typename T>
const T& NewVector<T>::back() const {
    if (currentSize == 0)
        throw std::out_of_range("Vector is empty");

    return dataStart[currentSize - 1];
}

// Begin method
template <typename T>
T* NewVector<T>::begin() {
    return dataStart;
}

// Begin method. Const version
template <typename T>
const T* NewVector<T>::begin() const {
    return dataStart;
}

// End method
template <typename T>
T* NewVector<T>::end() {
    return dataStart + currentSize;
}

// End method. Const version
template <typename T>
const T* NewVector<T>::end() const {
    return dataStart + currentSize;
}

// Empty method
template <typename T>
bool NewVector<T>::empty() const {
    return currentSize == 0;
}

// Size method
template <typename T>
size_t NewVector<T>::size() const {
    return currentSize;
}

// Max_size method
template <typename T>
size_t NewVector<T>::max_size() const {
    return capacity;
}

// Reserve method
template <typename T>
void NewVector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= capacity)
        return;

    T* new_dataStart = new T[new_capacity];
    std::copy(dataStart, dataStart + currentSize, new_dataStart);
    delete[] dataStart;
    dataStart = new_dataStart;
    capacity = new_capacity;
}

// Shrink_to_fit method
template <typename T>
void NewVector<T>::shrink_to_fit() {
    reserve(currentSize);
}

// Clear method
template <typename T>
void NewVector<T>::clear() {
    currentSize = 0;
}

// Push_back method
template <typename T>
void NewVector<T>::push_back(const T& value) {
    if (currentSize == capacity)
        reserve(capacity == 0 ? 1 : 2 * capacity);

    dataStart[currentSize++] = value;
}

// Pop_back method
template <typename T>
void NewVector<T>::pop_back() {
    if (currentSize == 0)
        throw std::out_of_range("Vector is empty");

    --currentSize;
}

// Erase method
template <typename T>
void NewVector<T>::erase(T* pos) {
    if (pos < dataStart || pos >= dataStart + currentSize)
        throw std::out_of_range("Invalid position");

    std::copy(pos + 1, dataStart + currentSize, pos);
    --currentSize;
}

// Erase method
template <typename T>
void NewVector<T>::erase(T* start, T* end) {
    if (start < dataStart || start >= dataStart + currentSize || end < dataStart || end > dataStart + currentSize || start >= end)
        throw std::out_of_range("Invalid range");

    std::copy(end, dataStart + currentSize, start);
    currentSize -= end - start;
}

// Insert method
template <typename T>
void NewVector<T>::insert(T* insert_pos, T* start, T* end) {
    if (insert_pos < dataStart || insert_pos > dataStart + currentSize)
        throw std::out_of_range("Insert position out of range");

    size_t insertCount = end - start;        // Number of elements to insert
    size_t newPos = insert_pos - dataStart;  // Position to insert in terms of index

    if (currentSize + insertCount > capacity) {
        reserve(std::max(capacity * 2, currentSize + insertCount));
    }

    std::copy_backward(dataStart + newPos, dataStart + currentSize, dataStart + currentSize + insertCount);
    std::copy(start, end, dataStart + newPos);
    currentSize += insertCount;
}
