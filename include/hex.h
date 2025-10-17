#pragma once

#include <iostream>
#include <string>
#include <array.h>

class Hex {
public:
    //Конструкторы
    Hex();
    Hex(const std::string& srcString);
    Hex(const std::initializer_list<unsigned char>& initialValues);
    Hex(const Array& arr);
    //Конструктор копирования
    Hex(const Hex& other);
    //Конструктор перемещения
    Hex(Hex&& other) noexcept;
    //Деструктор
    ~Hex() noexcept;
    //Геттер
    const Array& getHexArray() const;
    //Сеттер
    void setHexArray(Array newHexArray);
    //Методы сложения и вычитания
    Hex add(Hex& other);
    Hex subtract(Hex& other);
    //Вывод
    std::ostream& print(std::ostream& outputStream) const;
    //Вспомогательная проверка
    static bool validCharacter(char c);
    std::string hexToString();

private:
    //Атрибут класса
    Array hexArray;
    //Внутренние методы класса
    static int hexToInt (const Array& hexNum);
    static int charToInt (char c);
    static char intToChar (int n);
    static Array intToHex(int n); 
};