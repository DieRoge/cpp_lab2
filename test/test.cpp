#include <stdexcept>
#include <hex.h>
#include <array.h>
#include <gtest/gtest.h>

// Тест конструктора по умолчанию
TEST(HexTest, DefaultConstructor) {
    Hex hex;
}

// Тест конструктора из строки
TEST(HexTest, StringConstructor) {
    Hex hex1("1A2B");
    Hex hex2("abc");
    Hex hex3("123456");
}

// Тест конструктора из строки с ошибками
TEST(HexTest, StringConstructorInvalid) {
    EXPECT_THROW(Hex hex("1G2B"), std::invalid_argument); // Невалидный символ
    EXPECT_THROW(Hex hex(""), std::invalid_argument);     // Пустая строка
}

// Тест конструктора из списка инициализации
TEST(HexTest, InitializerListConstructor) {
    Hex hex{'1', 'A', 'f', '0'};
}

// Тест конструктора из списка с ошибками
TEST(HexTest, InitializerListConstructorInvalid) {
    EXPECT_THROW(Hex hex({'1', 'G', '2'}), std::invalid_argument);
}

// Тест копирования
TEST(HexTest, CopyConstructor) {
    Hex hex1("1A2B");
    Hex hex2(hex1);
}

// Тест перемещения
TEST(HexTest, MoveConstructor) {
    Hex hex1("1A2B");
    Hex hex2(std::move(hex1));
}

TEST(HexTest, Add_Basic) {
    Hex hex1("1");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "2");
}

TEST(HexTest, Add_SingleDigit) {
    Hex hex1("A");
    Hex hex2("5");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "F");
}

TEST(HexTest, Add_WithCarry) {
    Hex hex1("F");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "10");
}

TEST(HexTest, Add_MultipleDigits) {
    Hex hex1("A");
    Hex hex2("B");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "15");
}

TEST(HexTest, Add_LargeNumbers) {
    Hex hex1("FF");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "100");
}

TEST(HexTest, Add_ThreeDigitNumbers) {
    Hex hex1("1A3");
    Hex hex2("2B4");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "457"); // 1A3 + 2B4 = 457 в hex
}

TEST(HexTest, Add_DifferentLengths) {
    Hex hex1("ABC");
    Hex hex2("123");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "BDF"); // ABC + 123 = BDF в hex
}

TEST(HexTest, Add_WithLowerCase) {
    Hex hex1("abc");
    Hex hex2("123");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "BDF"); // abc + 123 = BDF в hex
}

TEST(HexTest, Add_MaxSingleByte) {
    Hex hex1("FE");
    Hex hex2("2");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "100");
}

TEST(HexTest, Add_Zero) {
    Hex hex1("1A2B");
    Hex hex2("0");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "1A2B");
}

TEST(HexTest, Add_BothZero) {
    Hex hex1("0");
    Hex hex2("0");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "0");
}

TEST(HexTest, Add_LargeCarry) {
    Hex hex1("FFF");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "1000");
}

TEST(HexTest, Add_ComplexCase) {
    Hex hex1("7D9");
    Hex hex2("8E6");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(result.hexToString(), "10BF"); // 7D9 + 8E6 = 10BF в hex
}

TEST(HexTest, Subtract_Basic) {
    Hex hex1("2");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "1");
}

TEST(HexTest, Subtract_SingleDigit) {
    Hex hex1("F");
    Hex hex2("5");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "A");
}

TEST(HexTest, Subtract_WithBorrow) {
    Hex hex1("10");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "F");
}

TEST(HexTest, Subtract_MultipleDigits) {
    Hex hex1("15");
    Hex hex2("B");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "A");
}

TEST(HexTest, Subtract_LargeNumbers) {
    Hex hex1("100");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "FF");
}

TEST(HexTest, Subtract_ThreeDigitNumbers) {
    Hex hex1("457");
    Hex hex2("2B4");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "1A3"); // 457 - 2B4 = 1A3 в hex
}

TEST(HexTest, Subtract_DifferentLengths) {
    Hex hex1("BDF");
    Hex hex2("123");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "ABC"); // BDF - 123 = ABC в hex
}

TEST(HexTest, Subtract_WithLowerCase) {
    Hex hex1("bdf");
    Hex hex2("123");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "ABC"); // bdf - 123 = ABC в hex
}

TEST(HexTest, Subtract_MaxSingleByte) {
    Hex hex1("100");
    Hex hex2("2");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "FE");
}

TEST(HexTest, Subtract_Zero) {
    Hex hex1("1A2B");
    Hex hex2("0");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "1A2B");
}

TEST(HexTest, Subtract_FromZero) {
    Hex hex1("0");
    Hex hex2("0");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "0");
}

TEST(HexTest, Subtract_LargeBorrow) {
    Hex hex1("1000");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "FFF");
}

TEST(HexTest, Subtract_ComplexCase) {
    Hex hex1("10BF");
    Hex hex2("8E6");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "7D9"); // 10BF - 8E6 = 7D9 в hex
}

TEST(HexTest, Subtract_EqualNumbers) {
    Hex hex1("ABC");
    Hex hex2("ABC");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "0");
}

TEST(HexTest, Subtract_SmallFromLarge) {
    Hex hex1("A");
    Hex hex2("9");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "1");
}

TEST(HexTest, Subtract_ResultSingleDigit) {
    Hex hex1("F");
    Hex hex2("E");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(result.hexToString(), "1");
}

TEST(HexTest, Subtract_NegativeResult) {
    Hex hex1("1");
    Hex hex2("2");
    EXPECT_THROW(hex1.subtract(hex2), std::invalid_argument);
}

TEST(HexTest, Subtract_LargerFromSmaller) {
    Hex hex1("A");
    Hex hex2("F");
    EXPECT_THROW(hex1.subtract(hex2), std::invalid_argument);
}

// Тест методов get/set
TEST(HexTest, GetSetHexArray) {
    Hex hex1("1A2B");
    Array arr = hex1.getHexArray();
    Hex hex2;
    hex2.setHexArray(arr);
}