#include <gtest/gtest.h>
#include <hex.h>
#include <array.h>
#include <stdexcept>

class HexTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Общие настройки для тестов
    }

    void TearDown() override {
        // Очистка после тестов
    }
    
    // Вспомогательная функция для получения строкового представления Hex
    std::string hexToString(Hex& hex) {
        std::stringstream ss;
        for (size_t i = 0; i < hex.getHexArray().getSize(); i++) {
            ss << hex.getHexArray().getData()[i];
        }
        return ss.str();
    }
};

// Тест конструктора по умолчанию
TEST_F(HexTest, DefaultConstructor) {
    Hex hex;
    SUCCEED(); // Просто проверяем что не падает
}

// Тест конструктора из строки
TEST_F(HexTest, StringConstructor) {
    Hex hex1("1A2B");
    Hex hex2("abc");
    Hex hex3("123456");
    SUCCEED();
}

// Тест конструктора из строки с ошибками
TEST_F(HexTest, StringConstructorInvalid) {
    EXPECT_THROW(Hex hex("1G2B"), std::invalid_argument); // Невалидный символ
    EXPECT_THROW(Hex hex(""), std::invalid_argument);     // Пустая строка
}

// Тест конструктора из списка инициализации
TEST_F(HexTest, InitializerListConstructor) {
    Hex hex{'1', 'A', 'f', '0'};
    SUCCEED();
}

// Тест конструктора из списка с ошибками
TEST_F(HexTest, InitializerListConstructorInvalid) {
    EXPECT_THROW(Hex hex({'1', 'G', '2'}), std::invalid_argument);
}

// Тест копирования
TEST_F(HexTest, CopyConstructor) {
    Hex hex1("1A2B");
    Hex hex2(hex1);
    SUCCEED();
}

// Тест перемещения
TEST_F(HexTest, MoveConstructor) {
    Hex hex1("1A2B");
    Hex hex2(std::move(hex1));
    SUCCEED();
}

TEST_F(HexTest, Add_Basic) {
    Hex hex1("1");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "2");
}

TEST_F(HexTest, Add_SingleDigit) {
    Hex hex1("A");
    Hex hex2("5");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "F");
}

TEST_F(HexTest, Add_WithCarry) {
    Hex hex1("F");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "10");
}

TEST_F(HexTest, Add_MultipleDigits) {
    Hex hex1("A");
    Hex hex2("B");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "15");
}

TEST_F(HexTest, Add_LargeNumbers) {
    Hex hex1("FF");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "100");
}

TEST_F(HexTest, Add_ThreeDigitNumbers) {
    Hex hex1("1A3");
    Hex hex2("2B4");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "457"); // 1A3 + 2B4 = 457 в hex
}

TEST_F(HexTest, Add_DifferentLengths) {
    Hex hex1("ABC");
    Hex hex2("123");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "BDF"); // ABC + 123 = BDF в hex
}

TEST_F(HexTest, Add_WithLowerCase) {
    Hex hex1("abc");
    Hex hex2("123");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "BDF"); // abc + 123 = BDF в hex
}

TEST_F(HexTest, Add_MaxSingleByte) {
    Hex hex1("FE");
    Hex hex2("2");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "100");
}

TEST_F(HexTest, Add_Zero) {
    Hex hex1("1A2B");
    Hex hex2("0");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "1A2B");
}

TEST_F(HexTest, Add_BothZero) {
    Hex hex1("0");
    Hex hex2("0");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "0");
}

TEST_F(HexTest, Add_LargeCarry) {
    Hex hex1("FFF");
    Hex hex2("1");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "1000");
}

TEST_F(HexTest, Add_ComplexCase) {
    Hex hex1("7D9");
    Hex hex2("8E6");
    Hex result = hex1.add(hex2);
    EXPECT_EQ(hexToString(result), "10BF"); // 7D9 + 8E6 = 10BF в hex
}

TEST_F(HexTest, Subtract_Basic) {
    Hex hex1("2");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "1");
}

TEST_F(HexTest, Subtract_SingleDigit) {
    Hex hex1("F");
    Hex hex2("5");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "A");
}

TEST_F(HexTest, Subtract_WithBorrow) {
    Hex hex1("10");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "F");
}

TEST_F(HexTest, Subtract_MultipleDigits) {
    Hex hex1("15");
    Hex hex2("B");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "A");
}

TEST_F(HexTest, Subtract_LargeNumbers) {
    Hex hex1("100");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "FF");
}

TEST_F(HexTest, Subtract_ThreeDigitNumbers) {
    Hex hex1("457");
    Hex hex2("2B4");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "1A3"); // 457 - 2B4 = 1A3 в hex
}

TEST_F(HexTest, Subtract_DifferentLengths) {
    Hex hex1("BDF");
    Hex hex2("123");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "ABC"); // BDF - 123 = ABC в hex
}

TEST_F(HexTest, Subtract_WithLowerCase) {
    Hex hex1("bdf");
    Hex hex2("123");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "ABC"); // bdf - 123 = ABC в hex
}

TEST_F(HexTest, Subtract_MaxSingleByte) {
    Hex hex1("100");
    Hex hex2("2");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "FE");
}

TEST_F(HexTest, Subtract_Zero) {
    Hex hex1("1A2B");
    Hex hex2("0");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "1A2B");
}

TEST_F(HexTest, Subtract_FromZero) {
    Hex hex1("0");
    Hex hex2("0");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "0");
}

TEST_F(HexTest, Subtract_LargeBorrow) {
    Hex hex1("1000");
    Hex hex2("1");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "FFF");
}

TEST_F(HexTest, Subtract_ComplexCase) {
    Hex hex1("10BF");
    Hex hex2("8E6");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "7D9"); // 10BF - 8E6 = 7D9 в hex
}

TEST_F(HexTest, Subtract_EqualNumbers) {
    Hex hex1("ABC");
    Hex hex2("ABC");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "0");
}

TEST_F(HexTest, Subtract_SmallFromLarge) {
    Hex hex1("A");
    Hex hex2("9");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "1");
}

TEST_F(HexTest, Subtract_ResultSingleDigit) {
    Hex hex1("F");
    Hex hex2("E");
    Hex result = hex1.subtract(hex2);
    EXPECT_EQ(hexToString(result), "1");
}

TEST_F(HexTest, Subtract_NegativeResult) {
    Hex hex1("1");
    Hex hex2("2");
    EXPECT_THROW(hex1.subtract(hex2), std::invalid_argument);
}

TEST_F(HexTest, Subtract_LargerFromSmaller) {
    Hex hex1("A");
    Hex hex2("F");
    EXPECT_THROW(hex1.subtract(hex2), std::invalid_argument);
}

// Тест методов get/set
TEST_F(HexTest, GetSetHexArray) {
    Hex hex1("1A2B");
    Array arr = hex1.getHexArray();
    Hex hex2;
    hex2.setHexArray(arr);
    SUCCEED();
}