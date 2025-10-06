#include <iostream>
#include <hex.h>
#include <array.h>

int main() {
    Hex hex1("abcd");
    Hex hex2("123");
    Hex result = hex1.add(hex2);
    result.print();
    return 0;
}