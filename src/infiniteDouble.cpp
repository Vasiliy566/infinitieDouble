#include "infiniteDouble.h"

InfiniteDouble::InfiniteDouble() {
    sign = 1;
    digits = std::vector<int>(1, 0);
    exponent = 1;
}

InfiniteDouble::InfiniteDouble(const InfiniteDouble &id) {
    sign = id.sign;
    digits = id.digits;
    exponent = id.exponent;
}

InfiniteDouble::InfiniteDouble(std::string in) {
    int pointAmount = 0;
    int signAmount = 0;
    for (int i = 0; i < in.length(); i++) {
        assert (isdigit(in[i]) || in[i] == '.' || in[i] == '-');
        if (in[i] == '.') {
            pointAmount++;
        } else if (in[i] == '-') {
            signAmount++;
        }
    }
    assert(pointAmount <= 1);
    assert(signAmount <= 1);
    long exponent_ = 0;
    std::vector<int> digits_;
    int start = 0;
    if (in[0] == '-') {
        sign = -1;
        start++;
    } else {
        sign = 1;
    }

    if (in[start] == '0') {
        if (in.length() == start + 1) {
            exponent_ = 0;
        } else {
            assert(in[start + 1] == '.');
            assert(in.length() > start + 2);
            start += 2;
            while (in[start] == '0' && start < in.length()) {
                start++;
                exponent_--;
            }
        }
    } else {
        while (in[start] != '.') {
            start++;
            exponent_++;
        }
    }

    for (int i = 0; i < in.length(); i++) {
        if (isdigit(in[i])) {
            digits_.push_back((int) in[i] - 48);
        }
    }
    digits = std::move(digits_);
    exponent = exponent_;
}

InfiniteDouble::InfiniteDouble(double d) {
    InfiniteDouble res = InfiniteDouble(std::to_string(d));
    while (res.digits[res.digits.size() - 1] == 0) {
        res.digits.pop_back();
    }
    sign = res.sign;
    exponent = res.exponent;
    digits = std::move(res.digits);
}

InfiniteDouble InfiniteDouble::operator+(const InfiniteDouble &id) {
    InfiniteDouble res;
    long exp1 = exponent;
    long exp2 = id.exponent;
    long exp = std::max(exp1, exp2);
    std::vector<int> digits1(digits);
    std::vector<int> digits2(id.digits);

    while (exp1 != exp) {
        digits1.insert(digits1.begin(), 0);
        exp1++;
    }

    while (exp2 != exp) {
        digits2.insert(digits2.begin(), 0);
        exp2++;
    }

    int size = std::max(digits1.size(), digits2.size());

    while (digits1.size() != size) {
        digits1.push_back(0);
    }

    while (digits2.size() != size) {
        digits2.push_back(0);
    }

    size_t len = 1 + size;

    res.sign = sign;
    res.digits = std::vector<int>(len, 0);

    for (size_t i = 0; i < size; i++) {
        res.digits[i + 1] = digits1[i] + digits2[i];
    }

    for (size_t i = len - 1; i > 0; i--) {
        res.digits[i - 1] += res.digits[i] / 10;
        res.digits[i] %= 10;
    }

    res.exponent = exp + 1;
    if (res.exponent < 0){
        res.digits.erase(res.digits.begin());
        res.exponent --;
    }
    bool isZero = true;
    for (int i = 0; i < res.digits.size(); i++) {
        if (res.digits[i] != 0) {
            isZero = false;
            break;
        }
    }
    if (isZero) {
        return InfiniteDouble(); // default zero
    }
    while (res.digits[res.digits.size() - 1] == 0) { // from right
        res.digits.pop_back();
    }
    if (res.exponent > 0){
        while (res.digits[0] == 0) { // from left
           res.digits.erase(res.digits.begin());
            res.exponent--;
        }
    }

    return res;
}

InfiniteDouble InfiniteDouble::operator*(const InfiniteDouble &id) {
    InfiniteDouble res;
    res.sign = sign * id.sign;
    res.digits = std::vector<int>(digits.size() + id.digits.size(), 0);
    res.exponent = exponent + id.exponent;

    for (size_t i = 0; i < digits.size(); i++) {
        for (size_t j = 0; j < id.digits.size(); j++) {
            res.digits[i + j + 1] += digits[i] * id.digits[j];
        }
    }
    for (size_t i = digits.size() + id.digits.size() - 1; i > 0; i--) {
        res.digits[i - 1] += res.digits[i] / 10;
        res.digits[i] %= 10;
    }
    bool isZero = true;
    for (int i = 0; i < res.digits.size(); i++) {
        if (res.digits[i] != 0) {
            isZero = false;
            break;
        }
    }
    if (isZero) {
        return InfiniteDouble(); // default zero
    }
    while (res.digits[res.digits.size() - 1] == 0) { // from right
        res.digits.pop_back();
    }
    if (res.exponent > 0){
        while (res.digits[0] == 0) { // from left
            res.digits.erase(res.digits.begin());
            res.exponent--;
        }
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const InfiniteDouble &id) {
    if (id.sign == -1) {
        out << "-";
    }
    long exp = id.exponent;
    if (id.exponent == 0)
        exp++;

    for (int i = 0; i < id.digits.size(); i++) {
        if (exp < 0 && i == 1) {
            out << ".";
        }
        if (i == exp) {
            out << ".";
        }
        out << id.digits[i];
    }
    return out;
}

bool InfiniteDouble::operator==(const InfiniteDouble &id) const {
    if (sign != id.sign) {
        return false;
    }

    if (exponent != id.exponent) {
        return false;
    }

    if (digits.size() != id.digits.size()) {
        return false;
    }

    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != id.digits[i]) {
            return false;
        }
    }

    return true;
}

bool InfiniteDouble::operator>(const InfiniteDouble &id) const {
    if (sign != id.sign)
        return sign > id.sign;

    if (exponent != id.exponent)
        return (exponent > id.exponent) ^ (sign == -1);

    std::vector<int> d1(digits);
    std::vector<int> d2(id.digits);
    size_t size = std::max(d1.size(), d2.size());

    while (d1.size() != size)
        d1.push_back(0);

    while (d2.size() != size)
        d2.push_back(0);

    for (size_t i = 0; i < size; i++)
        if (d1[i] != d2[i])
            return (d1[i] > d2[i]) ^ (sign == -1);

    return false;
}

bool InfiniteDouble::operator<(const InfiniteDouble &id) const {
    return (*this > id || *this == id);
}

bool InfiniteDouble::operator>=(const InfiniteDouble &id) const {
    return (*this > id || *this == id);
}

bool InfiniteDouble::operator<=(const InfiniteDouble &id) const {
    return (*this < id || *this == id);
}

bool InfiniteDouble::operator!=(const InfiniteDouble &id) const {
    return (!(*this == id));
}