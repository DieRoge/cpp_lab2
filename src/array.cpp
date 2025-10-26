#include <array.h>

#include <iostream>
#include <string>


// Конструкторы
Array::Array(): size(0), data(nullptr) {}

Array::Array(const size_t& arraySize, unsigned char arrayValue)
    : size(arraySize)
    , data(new unsigned char[arraySize])
    {
    for(size_t i = 0; i < size; ++i) {
        data[i] = arrayValue;
    }
}

Array::Array(const std::initializer_list<unsigned char>& initialValues) 
    : size(initialValues.size())
    , data(new unsigned char[size])
    {
    size_t index = 0;
    for (const auto& value : initialValues) {
        data[index++] = value;
    }
}

Array::Array(const std::string& srcString)
    : size(srcString.size())
    , data(new unsigned char[size])
    {
    for(size_t i = 0; i < size; ++i) {
        data[i] = static_cast<unsigned char>(srcString[i]);
    }
}

Array::Array(const Array& other) 
    : size(other.size)
    , data(new unsigned char[size])
    {
    for(size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Array::Array(Array&& other) noexcept 
    : size(other.size)
    , data(other.data)
    {
    other.size = 0;
    other.data = nullptr;
}

// Деструктор

Array::~Array() noexcept {
    delete[] data;
    size = 0;
}

// ГЕТТЕРЫ

size_t Array::getSize() const {
    return size;
}

unsigned char* Array::getData() const {
    return data;
}

// СЕТТЕРЫ

void Array::setSize(size_t newSize) {
    size = newSize;
}

void Array::setData(unsigned char* newData) {
    data = newData;
}

//Функционал массива
bool Array::equals(const Array& other) {
    if (size != other.size){
        return false;
    }
    for(size_t i = 0; i < size; ++i) {
        if(data[i] != other.data[i]){
            return false;
        }
    }
    return true;
}

void Array::insertAt(size_t index, const char insertValue) {
    data[index] = static_cast<unsigned char>(insertValue);
}

//Вывод
std::ostream& Array::print(std::ostream& outputStream) const{
    for(size_t i = 0; i < size; ++i){
        outputStream << data[i];
    }
    return outputStream;
}
