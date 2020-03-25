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
    long exponent_ = 0;
    std::vector<int> digits_;
    int start = 0;
    if (in[in.length() - 1] == '.') {
        std::cout << "wrong format\n";
        sign = 0;
        return;
    }
    for (int i = 0; i < in.length(); i++) {
        if (!(isdigit(in[i]) || in[i] == '.' || in[i] == '-')) {
            std::cout << "undefined symbol in string. can be just [\".\", \"-\", numeric] \n";
            sign = 0;
            return;
        }
        if (in[i] == '.') {
            pointAmount++;
        } else if (in[i] == '-') {
            signAmount++;
        }
    }
    if (signAmount > 1) {
        std::cout << "too many signs in line\n";
        sign = 0;
        return;
    }
    if (pointAmount > 1) {
        std::cout << "too many points in line\n";
        sign = 0;
        return;
    }

    if (in[0] == '-') {
        sign = -1;
        start++;
    } else {
        sign = 1;
    }
    if (pointAmount < 1) {
        for (int i = 0; i < in.length(); i++) {
            if (isdigit(in[i])) {
                exponent_++;
                digits_.push_back((int) in[i] - 48);
            } else {
                std::cout << "undefined symbol in string. can be just [\".\", \"-\", numeric] \n";
                sign = 0;
                return;
            }
        }
    } else {
        if (in[start] == '0') {
            if (in.length() == start + 1) {
                exponent_ = 0;
            } else {
                if (in[start + 1] != '.') {
                    std::cout << "wrong format\n";
                    sign = 0;
                    return;
                }

                if (!(in.length() > start + 2)) {
                    std::cout << "wrong format\n";
                    sign = 0;
                    return;
                }
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

        bool isZero = true;
        for (int i = 0; i < digits_.size(); i++) {
            if (digits_[i] != 0) {
                isZero = false;
                break;
            }
        }
        if (isZero) {
            *this = InfiniteDouble(); // default zero
            return;
        }
        while (digits_[digits_.size() - 1] == 0 && (digits_.size() - 1 - exponent_ > 0)) { // from right
            digits_.pop_back();
        }
    }

    while ((exponent_ > 0) && (digits_[0] == 0) && ((digits_.size() > 1))) {
        digits_.erase(digits_.begin());
        exponent_--;
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
    std::vector<int> a = std::max(*this, id).digits;
    std::vector<int> b = std::min(*this, id).digits;
    long exp1 = std::max(exponent, id.exponent);
    long exp2 = std::min(exponent, id.exponent);;

    if (exp2 < 0 && exp1 > 0)
        exp2 = 1;

    if (!((exp1 <= 1) && (exp2 <= 1)))
        while (exp1 != exp2) {
            b.insert(b.begin(), 0);
            exp2++;
        }

    for (size_t i = 0; i < std::max(a.size(), b.size()); ++i) {
        if (i == a.size()) {
            a.push_back(0);
        }

        if (i < b.size()) {
            a[i] += b[i];
        }
    }

    for (size_t i = a.size() - 1; i > 0; i--) {
        a[i - 1] += a[i] / 10;
        a[i] %= 10;
    }

    InfiniteDouble res;
    res.sign = 1;
    res.digits = a;
    res.exponent = std::max(id.exponent, this->exponent);
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
    if (res.exponent > 1) {
        while (res.digits[0] == 0 && res.exponent > 1) { // from left
            res.digits.erase(res.digits.begin());
            //res.exponent--;
        }
    }
    while (res.digits[res.digits.size() - 1] == 0 && (res.digits.size() > std::abs(res.exponent))) { // from right
        res.digits.pop_back();
    }
    if (res.exponent < 1) {
        int zeroes = 0;
        while (true) {
            zeroes = 0;
            while (res.digits[zeroes] == 0) {
                zeroes++;
            }
            if (zeroes - 1 > (std::abs(res.exponent))) {
                res.digits.erase(res.digits.begin());
            } else { break; }
        }
    }
    return res;
}

InfiniteDouble InfiniteDouble::operator*(const InfiniteDouble &id) {
    size_t len = digits.size() + id.digits.size();
    InfiniteDouble res;
    res.sign = sign * id.sign;
    res.digits = std::vector<int>(len, 0);
    res.exponent = id.exponent + exponent - 1;
    for (size_t i = 0; i < digits.size(); i++) {
        for (size_t j = 0; j < id.digits.size(); j++) {
            res.digits[i + j + 1] += digits[i] * id.digits[j];
        }
    }
    int first_zero = -1;
    for (size_t i = 0; i < len; i++) {
        if (res.digits[i] != 0) {
            first_zero = i - 1;
            break;
        }
    }
    //assert(first_zero != -1);
    for (size_t i = len - 1; i > 0; i--) {
        res.digits[i - 1] += res.digits[i] / 10;
        res.digits[i] %= 10;
    }
    if (res.digits[first_zero] != 0) {
        res.exponent++;
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

    if (res.exponent > 1) {
        while (res.digits[0] == 0 && res.exponent > 1) { // from left
            res.digits.erase(res.digits.begin());
            //res.exponent--;
        }
    }
    while (res.digits[res.digits.size() - 1] == 0 && (res.digits.size() > std::abs(res.exponent))) { // from right
        res.digits.pop_back();
    }

    if (res.digits[0] == 0) {
        res.digits.erase(res.digits.begin());
    }
    if (res.exponent < 1) {
        int zeroes = 0;
        while (true) {
            zeroes = 0;
            while (res.digits[zeroes] == 0) {
                zeroes++;
            }
            if (zeroes - 1 > (std::abs(res.exponent))) {
                res.digits.erase(res.digits.begin());
            } else { break; }
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

    if (exponent != id.exponent) {
        bool b = (exponent > id.exponent);
        return (exponent > id.exponent);
    }

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
    return !(*this > id || *this == id);
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

bool InfiniteDouble::isOk() {
    return (sign == 1 || sign == -1);
}