#pragma once
#include <iostream>
#include <string>


class Array {

public:

    // Конструкторы
    
    Array();
    Array(const size_t& arraySize, unsigned char arrayValue = '0');
    Array(const std::initializer_list<unsigned char>& initialValues);
    Array(const std::string& srcString);
    
    // Конструктор копирования
    
    Array(const Array& other);
    
    // Конструктор перемещения
    
    Array(Array&& other) noexcept;
    
    // Деструктор
    
    virtual ~Array() noexcept;
    
    // Базовые функции
    
    // Array add(const Array& other);
    // Array remove(const Array& other);
    bool equals(const Array& other);
    void insertAt(size_t index, const char insertValue);
    
    // Вывод
    
    std::ostream& print(std::ostream& outputStream);
    
    // Геттеры
    
    size_t getSize() const;
    unsigned char* getData() const;

    // Сеттеры
    
    void setSize(size_t newSize);
    void setData(unsigned char* newData);

    
private:
    // Атрибуты - размер и данные
    size_t size;
    unsigned char* data;

};