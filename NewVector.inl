#include "NewVector.h" 

template<typename T>
NewVector<T>::NewVector() 
    : data(nullptr), capacity(0), current(0) {}

template<typename T>
NewVector<T>::~NewVector(){
    delete[] data;
}

