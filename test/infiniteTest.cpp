#include <iostream>
#include "gtest/gtest.h"
#include "../src/infiniteDouble.h"
#include <random>

TEST(infititeDouble, main) {
    InfiniteDouble a = InfiniteDouble("0.12345670");
    std::cout << "[" << a << "]" << std::endl;
    ASSERT_EQ(a, InfiniteDouble("0.1234567"));
    a = InfiniteDouble("123.12304");
    std::cout << "[" << a << "]" << std::endl;
    ASSERT_EQ(a, InfiniteDouble(123.12304));

    a = InfiniteDouble("0.001234500");
    std::cout << "[" << a << "]" << std::endl;
    ASSERT_EQ(a, InfiniteDouble("0.0012345"));
    a = InfiniteDouble("10");
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble("10000");
    std::cout << "[" << a << "]" << std::endl;
    a = InfiniteDouble("0");
    std::cout << "[" << a << "]" << std::endl;

    ASSERT_TRUE(InfiniteDouble("0.001") < InfiniteDouble("0.02"));

    ASSERT_TRUE(InfiniteDouble("10000") > InfiniteDouble("1000"));
    ASSERT_TRUE(InfiniteDouble("0.01") > InfiniteDouble("0.009"));

}

TEST(infititeDouble, mulConstants) {
    std::string testData[11][3] = {
            {"11.999",  "9.99",      "119.87001"},
            {"18.222",  "2.888",     "52.625136"},
            {"100000",  "0.1",       "10000"},
            {"0.02",    "0.01",      "0.0002"},
            {"0.002",   "0.007",     "0.000014"},
            {"0.99999", "0.99999",   "0.9999800001"},
            {"1.2",     "1.2",       "1.44"},
            {"5.17",    "1.11",      "5.7387"},
            {"10",      "0.01",      "0.1"},
            {"10",      "0.0000001", "0.000001"},
            {"0.09", "0.01", "0.0009"}
    };
    for (int i = 0; i < 11; i++) {
        InfiniteDouble a = InfiniteDouble(testData[i][0]);
        InfiniteDouble b = InfiniteDouble(testData[i][1]);
        InfiniteDouble c = InfiniteDouble(testData[i][2]);
        InfiniteDouble mul = a * b;
        ASSERT_EQ(mul, c);
    }
}

TEST(infititeDouble, sumConstants) {
    std::string testData[11][3] = {
            {"0.99", "0.01", "1.0"},
            {"1.5",    "0.5",   "2.0"},
            {"0.001",  "0.02",  "0.021"},
            {"1.001",  "0.001", "1.002"},
            {"11.999", "9.99",  "21.989"},
            {"111.11", "1.1",  "112.21"},
            {"0.002",  "0.001", "0.003"},
            {"1.2",    "1.2",   "2.4"},
            {"5.17",   "1.11",  "6.28"},
            {"18.222", "2.888", "21.11"},

            {"0.09", "0.01", "0.1"}

    };

    for (int i = 0; i < 11; i++) {
        std::cout << i << std::endl;
        InfiniteDouble a = InfiniteDouble(testData[i][0]);
        InfiniteDouble b = InfiniteDouble(testData[i][1]);
        InfiniteDouble c = InfiniteDouble(testData[i][2]);
        InfiniteDouble sum = a + b;
        ASSERT_EQ(sum, c);
    }

}

TEST(infititeDouble, mulRandom) {
    double lower_bound = 0;
    double upper_bound = 1000000;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    for (int i = 0; i < 100; i++) {
        double a = unif(re);
        double b = unif(re);
        InfiniteDouble sum = InfiniteDouble(a) + InfiniteDouble(b);

        if (InfiniteDouble(a) * InfiniteDouble(b) != InfiniteDouble(a * b)) {
            std::cout << std::fixed << a << " * " << b << " = " << a * b << std::endl;
            std::cout << InfiniteDouble(a) << " * " << InfiniteDouble(b) << " = " << InfiniteDouble(a * b) << std::endl;
        }
        ASSERT_EQ((InfiniteDouble(a) * InfiniteDouble(b)), InfiniteDouble(a * b));
    }

}

TEST(infititeDouble, sumRandom) {
    double lower_bound = 0;
    double upper_bound = 1000000;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    for (int i = 0; i < 100; i++) {
        double a = unif(re);
        double b = unif(re);
        InfiniteDouble sum = InfiniteDouble(a) + InfiniteDouble(b);

        if (InfiniteDouble(a) + InfiniteDouble(b) != InfiniteDouble(a + b)) {
            std::cout << std::fixed << a << " + " << b << " = " << a + b << std::endl;
            std::cout << InfiniteDouble(a) << " + " << InfiniteDouble(b) << " = " << InfiniteDouble(a + b) << std::endl;
        }
        ASSERT_EQ(InfiniteDouble(a) +InfiniteDouble(b), InfiniteDouble(a + b));
    }

}