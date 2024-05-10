#ifndef NEWVECTOR_H
#define NEWVECTOR_H

#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class NewVector {
private:
    T* dataStart;                                 // pointer to the first element of the vector
    size_t capacity;                              // the number of elements the vector can hold
    size_t currentSize;                           // the number of elements in the vector   

public: 
    // Constructors and destructor
    NewVector();                                  // default constructor
    ~NewVector();                                 // destructor
    NewVector(const NewVector<T>&);               // copy constructor
    NewVector(NewVector<T>&&);                    // move constructor

    // Copy and move assignment operators
    NewVector<T>& operator=(const NewVector<T>&); // copy assignment
    NewVector<T>& operator=(NewVector<T>&&);      // move assignment
    
    // Element access
    T& operator[](size_t index);                  // return the element at index
    T& front();                                   // return the first element  
    T& back();                                    // return the last element
        
    // Iterators              
    T* begin();                                   // return a pointer to the first element
    T* end();                                     // return a pointer to one past the last element
        
    // Capacity           
    bool empty() const;                           // check if the vector is empty
    size_t size() const;                          // return the number of elements in the vector
    size_t max_size() const;                      // return the maximum number of elements the vector can hold
    size_t capacity() const;                      // return the number of elements the vector can hold
    void reserve(size_t new_capacity);            // increase the capacity of the vector to new_capacity
    void shrink_to_fit();                         // reduce the capacity to the number of elements in the vector

    // Modifiers
    void clear();                                 // remove all elements from the vector
    void push_back(const T& value);               // add an element to the end of the vector
    void pop_back();                              // remove the last element from the vector
    void erase(T* start, T* end);                 // remove elements in the range [start, end)
    void insert(T* insert_pos, T* start, T* end); // inserts elements after insert_pos from the range [start, end)
};

#include "NewVector.inl"

#endif