#include <hex.h>
#include <array.h>
#include <iostream>
#include <string>


bool Hex::validCharacter(char c) {
    return (c >= '0' && c <= '9') ||
    (c >= 'A' && c <= 'F') ||
    (c >= 'a' && c <= 'f');
}

Hex::Hex(): hexArray() {}

Hex::Hex(const Array& arr) : hexArray(arr) {}

Hex::Hex(const std::initializer_list<unsigned char>& initialValues) {
    for (const auto& c : initialValues) {
        if (!validCharacter(c)) {
            throw std::invalid_argument("Invalid characters entered");
        }
    }
    new (&hexArray) Array(initialValues);
}

Hex::Hex(const std::string& srcString) {
    if (srcString.empty()) {
        throw std::invalid_argument("Empty string");
    }
    for (char c : srcString) {
        if (!validCharacter(c)) {
            throw std::invalid_argument("Invalid characters entered");
        }
    }
    new (&hexArray) Array(srcString);
}   

Hex::Hex(const Hex& other) {
    new (&hexArray) Array(other.hexArray);
}

Hex::Hex(Hex&& other) noexcept {
    new (&hexArray) Array(std::move(other.hexArray));
}

Hex::~Hex() noexcept {
    if (hexArray.getData() != nullptr) {
        delete[] hexArray.getData();
        hexArray.setData(nullptr);
    }
    hexArray.setSize(0);
}

Array Hex::getHexArray() {
    return hexArray;
}

void Hex::setHexArray(Array newHexArray) {
    new (&hexArray) Array(newHexArray);
}

Hex Hex::add(Hex& other) {
    int num1 = hexToInt(hexArray);
    int num2 = hexToInt(other.hexArray);
    int sum = num1 + num2;
    
    Hex result(intToHex(sum));
    
    return result;
}

Hex Hex::subtract(Hex& other) {
    int num1 = hexToInt(hexArray);
    int num2 = hexToInt(other.hexArray);
    int difference = num1 - num2;
    
    // Проверка на отрицательный результат
    if (difference < 0) {
        throw std::invalid_argument("Result of subtraction is negative");
    }
    
    Hex result(intToHex(difference));
    
    return result;
}

int Hex::hexToInt(Array& hexNum) {
    int result = 0;
    int hexSize = hexNum.getSize();
    
    for (int i = 0; i < hexSize; ++i) {
        int digit = charToInt(hexNum.getData()[i]);
        int power = hexSize - 1 - i;
        result += digit * (1 << (4 * power));
    }
    return result;
}

Array Hex::intToHex(int n) {
    if (n == 0) {
        Array result(1);
        result.insertAt(0, '0');
        return result;
    }
    int temp = n;
    int hexLen = 0;
    while (temp > 0) {
        temp /= 16;
        hexLen++;
    }
    Array resultDigits(hexLen);
    int index = hexLen - 1;
    temp = n;
    while (temp > 0) {
        int digit = temp % 16;
        temp /= 16;
        resultDigits.insertAt(index, intToChar(digit));
        index--;
    }
    
    return resultDigits;
}

int Hex::charToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
}

char Hex::intToChar(int n) {
    if (n < 0 || n > 15) throw std::invalid_argument("Invalid value");
    if (n < 10) return '0' + n;
    return 'A' + (n - 10);
}

void Hex::print() const {
    for (size_t i = 0; i < hexArray.getSize(); i++) {
        std::cout << hexArray.getData()[i];
    }
    std::cout << std::endl;
}
