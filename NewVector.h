#ifndef NEWVECTOR_H
#define NEWVECTOR_H

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class NewVector {
private:
    T* data;                           // the array that holds the elements
    size_t capacity;                   // the number of elements the vector can hold
    size_t current;                    // the number of elements in the vector   

public: 
    NewVector();                       // default constructor
    ~NewVector();                      // destructor
    NewVector(const NewVector<T>&);    // copy constructor
    NewVector(NewVector<T>&&);         // move constructor

    NewVector<T>& operator=(const NewVector<T>&);    // copy assignment
    NewVector<T>& operator=(NewVector<T>&&);         // move assignment

    void push_back(const T& value);    // add an element to the end of the vector
    void reserve(size_t new_capacity); // reserve memory for new_capacity elements
    size_t size() const;               // return the number of elements in the vector
    size_t max_size() const;           // return the maximum number of elements the vector can hold
    T& operator[](size_t index);       // return the element at index
};

#include "NewVector.inl"

#endif