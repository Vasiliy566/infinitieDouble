#include <iostream>
#include "gtest/gtest.h"
#include "../src/infiniteDouble.h"

TEST(infititeDouble, main) {
    InfiniteDouble a = InfiniteDouble("0.1234567");
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble("123.1234");
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble("-0.1234567");
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble("-123.1234567");
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble("0.0012345");
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble("-0.0012345");
    std::cout << "[" << a << "]" << std::endl;

    a = InfiniteDouble(0.123);
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble(-0.123);
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble(123.123);
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble(-123.123);
    std::cout << "[" << a << "]" << std::endl;
}

TEST(infititeDouble, mul) {
    std::string testData[5][3] = {
            {"1.2", "1.2", "1.44"},
            { "11.999", "9.99", "119.87001" },
            { "18.222", "2.888", "52.625136" },
            { "5.17", "1.11", "5.7387" },
            { "0.02", "0.1", "0.002" },
    };
    for (int i = 0; i < 5; i++) {
        InfiniteDouble a = InfiniteDouble(testData[i][0]);
        InfiniteDouble b = InfiniteDouble(testData[i][1]);
        InfiniteDouble c = InfiniteDouble(testData[i][2]);
        InfiniteDouble mul = a * b;
        ASSERT_EQ(mul, c);
    }
}

TEST(infititeDouble, sum) {
    std::string testData[5][3] = {
            {"1.2", "1.2", "2.4"},
            { "11.999", "9.99", "21.989" },
            { "18.222", "2.888", "21.11" },
            { "5.17", "1.11", "6.28" },
            { "0.001", "0.001", "0.002" },
    };



    for (int i = 0; i < 5; i++) {
        InfiniteDouble a = InfiniteDouble(testData[i][0]);
        InfiniteDouble b = InfiniteDouble(testData[i][1]);
        InfiniteDouble c = InfiniteDouble(testData[i][2]);
        InfiniteDouble sum = a + b;
        ASSERT_EQ(sum, c);
    }

}