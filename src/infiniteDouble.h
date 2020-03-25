#ifndef INFINITY_DOUBLE_H
#define INFINITY_DOUBLE_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class InfiniteDouble {

    /// vector with all number digits
    // TODO: need to save in storage jsut 1 numeral. Create new structure for nums
    std::vector<int> digits;

    /// sign of digit
    /// possible values : {1, -1}
    /// TODO: need to save in storage just sign, replace with bool of create enum;
    int sign;

    /// exponent of number
    /// show how much numeral in the whole part
    long exponent;
public:
    /// default constrictor, creates zero
    InfiniteDouble();

    /// copying constrictor
    /// @param[in] : id
    InfiniteDouble(const InfiniteDouble &id);

    /// constructor from string
    /// @param[in] : in
    InfiniteDouble(const std::string in);

    /// constrictor from double
    /// convert double to string, than use constructor from string, than remove zeroes
    /// @param[in] : d
    InfiniteDouble(const double d);

    /// operator <<
    /// use it to print object
    /// @param[in] : out, id
    friend std::ostream &operator<<(std::ostream &out, const InfiniteDouble &id);

    /// operator ==
    /// just check that all field are equals
    /// @param[in] : id
    bool operator==(const InfiniteDouble &id) const;

    bool operator>(const InfiniteDouble &id) const;

    bool operator<(const InfiniteDouble &id) const;

    bool operator>=(const InfiniteDouble &id) const;

    bool operator<=(const InfiniteDouble &id) const;

    bool operator!=(const InfiniteDouble &id) const;


    /// operator *
    /// multiple of two InfiniteDouble
    /// result exponent = exponent1 + exponent2
    /// sign = sign1 * sign2
    /// digits - multiple vectors like a numbers, than delete zeroes
    /// @param[in] : id
    /// @param[out] : @InfiniteDouble, result of multiplying of x and current class
    InfiniteDouble operator*(const InfiniteDouble &id);

    /// operator +
    /// sum of two InfiniteDouble
    /// set each exponent as max of two exponents
    /// set zeroes in start were it needs
    /// sum every digit
    /// remove zeroes from start and from back
    /// @param[in] : id
    /// @param[out] : @InfiniteDouble, result of sum of x and current class
    // TODO: sum for negative InfiniteDouble
    InfiniteDouble operator+(const InfiniteDouble &id);

    /// return status of num, if sign not in {1, -1} return false;
    bool isOk();

};

#endif
