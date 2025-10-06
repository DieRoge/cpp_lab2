#pragma once
#include <iostream>
#include <string>
#include <array.h>

class Hex {

public:

    Hex();
    Hex(const std::string& srcString);
    Hex(const std::initializer_list<unsigned char>& initialValues);

    Hex(const Array& arr);

    Hex(const Hex& other);

    Hex(Hex&& other) noexcept;

    ~Hex() noexcept;

    Array getHexArray();
    
    void setHexArray(Array newHexArray);

    Hex add(Hex& other);
    Hex subtract(Hex& other);

    void print() const;

    static bool validCharacter(char c);

private:

    Array hexArray;
    
    

    int hexToInt (Array& hexNum);
    int charToInt (char c);
    char intToChar (int n);
    Array intToHex(int n);

};