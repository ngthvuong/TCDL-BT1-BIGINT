#include "BigInt.h"
#include <cstring>
#include <iostream>
#include <functional>

using namespace std;

#define LESS -1
#define EQUAL 0
#define GREATER 1
#define ZERO \
    new char[BigInt::MAX_SIZE] { '0', '\0' }

const int BigInt::MAX_SIZE = 101;

void BigInt::reverseStr(char *val)
{
    int fIndex = 0;
    int bIndex = strlen(val) - 1;
    while (bIndex > fIndex)
    {
        char temp = val[bIndex];
        val[bIndex] = val[fIndex];
        val[fIndex] = temp;
        fIndex++;
        bIndex--;
    }
}

void BigInt::removePrefix(char *val, char preSymbol = '0')
{
    int valLength = strlen(val);
    int notZeroIndex = 0;
    for (int i = 0; i < valLength - 1; i++)
    {
        if (val[i] != preSymbol)
        {
            break;
        }
        notZeroIndex++;
    }
    strncpy(val, val + notZeroIndex, BigInt::MAX_SIZE - 1);
}

void BigInt::init()
{
    value = new char[MAX_SIZE];
    sign = true;
    value[MAX_SIZE - 1] = '\0';
}

char *BigInt::filterValue(const char val[], function<int(int)> isValidSymbolOnBase)
{
    char *result = new char[BigInt::MAX_SIZE];

    int j = 0;
    for (int i = 0; i < BigInt::MAX_SIZE; i++)
    {
        if (val[i] == '\0' || !isValidSymbolOnBase(val[i]))
        {
            break;
        }
        result[j] = val[i];
        j++;
    }
    result[j] = '\0';

    removePrefix(result);
    return result;
}
char *BigInt::convert16To10(const char val[])
{
    const char *fixedValue = "12345";
    char *result = new char[BigInt::MAX_SIZE];
    strncpy(result, fixedValue, BigInt::MAX_SIZE - 1);
    return result;
}
void BigInt::setValue(const char val[])
{
    char *abs = new char[BigInt::MAX_SIZE];
    sign = true;
    if (val[0] == '-' || val[0] == '+')
    {
        if (val[0] == '-')
        {
            sign = false;
        }
        strncpy(abs, val + 1, BigInt::MAX_SIZE - 1);
    }
    else
    {
        strncpy(abs, val, BigInt::MAX_SIZE - 1);
    }

    char *filterResult = new char[BigInt::MAX_SIZE];
    if (abs[0] == 'x')
    {
        char *abs_16 = new char[BigInt::MAX_SIZE];
        abs_16 = filterValue(abs + 1, [](int x)
                             { return isxdigit(x); });
        abs = convert16To10(abs_16);
        delete[] abs_16;
    }

    filterResult = filterValue(abs, [](int x)
                               { return isdigit(x); });
    strncpy(value, filterResult, BigInt::MAX_SIZE - 1);

    if (compareAbsValue(value, ZERO) == EQUAL)
    {
        sign = true;
    }

    delete[] abs;
    delete[] filterResult;
}

BigInt::BigInt()
{
    init();
}
BigInt::BigInt(const char val[])
{
    init();
    setValue(val);
}
BigInt::BigInt(const BigInt &term)
{
    init();
    char *inputValue = new char[BigInt::MAX_SIZE + 1];
    inputValue[0] = (term.sign) ? '+' : '-';
    strncpy(inputValue + 1, term.value, BigInt::MAX_SIZE - 1);
    setValue(inputValue);
}

int BigInt::compareAbsValue(char val1[], char val2[]) const
{
    int result = EQUAL;

    int term1Length = strlen(val1);
    int term2Length = strlen(val2);

    if (term1Length > term2Length)
    {
        result = GREATER;
    }
    else if (term1Length < term2Length)
    {
        result = LESS;
    }
    else
    {
        for (int i = 0; i < term1Length; i++)
        {
            int ele1 = val1[i] - '0';
            int ele2 = val2[i] - '0';

            if (ele1 > ele2)
            {
                result = GREATER;
                break;
            }
            else if (ele1 < ele2)
            {
                result = LESS;
            }
        }
    }

    return result;
}
bool BigInt::operator==(const BigInt &term)
{
    bool result = false;
    bool sameSignCondition = sign == term.sign;
    bool sameAbsCondition = compareAbsValue(value, term.value) == EQUAL;
    if (sameSignCondition && sameAbsCondition)
    {
        result = true;
    }
    return result;
}
bool BigInt::operator!=(const BigInt &term)
{
    return !(*this == term);
}
bool BigInt::operator>(const BigInt &term)
{
    bool result = false;
    bool neAndPoCondition = sign == true && term.sign == false;
    bool poAndPoCondition = sign == true && term.sign == true && compareAbsValue(value, term.value) == GREATER;
    bool neAndNeCondition = sign == false && term.sign == false && compareAbsValue(value, term.value) == LESS;

    if (neAndPoCondition || poAndPoCondition || neAndNeCondition)
    {
        result = true;
    }
    return result;
}
bool BigInt::operator<(const BigInt &term)
{
    bool result = false;
    bool neAndPoCondition = sign == false && term.sign == true;
    bool poAndPoCondition = sign == true && term.sign == true && compareAbsValue(value, term.value) == LESS;
    bool neAndNeCondition = sign == false && term.sign == false && compareAbsValue(value, term.value) == GREATER;

    if (neAndPoCondition || poAndPoCondition || neAndNeCondition)
    {
        result = true;
    }
    return result;
}
bool BigInt::operator>=(const BigInt &term)
{
    return (*this > term) || (*this == term);
}
bool BigInt::operator<=(const BigInt &term)
{
    return (*this < term) || (*this == term);
}

BigInt BigInt::operator=(const BigInt &term)
{
    strncpy(value, term.value, MAX_SIZE - 1);
    return *this;
}
BigInt BigInt::operator-() const
{
    BigInt result = *this;
    if (compareAbsValue(result.value, ZERO) == GREATER)
    {
        result.sign = !result.sign;
    }

    return result;
}

char *BigInt::addAbs(char val1[], char val2[])
{
    char *sum = new char[BigInt::MAX_SIZE];
    sum[BigInt::MAX_SIZE - 1] = '\0';

    int carry = 0;
    int index1 = strlen(val1) - 1;
    int index2 = strlen(val2) - 1;
    int index3 = 0;

    while (index1 >= 0 || index2 >= 0 || carry > 0)
    {
        int ele1 = (index1 >= 0) ? (val1[index1] - '0') : 0;
        int ele2 = (index2 >= 0) ? (val2[index2] - '0') : 0;
        int temp = ele1 + ele2 + carry;

        sum[index3] = temp % 10 + '0';
        carry = temp / 10;

        index1--;
        index2--;
        index3++;
    }
    sum[index3] = '\0';
    reverseStr(sum);

    return sum;
}
char *BigInt::subAbs(char val1[], char val2[])
{
    if (compareAbsValue(val1, val2) == LESS)
    {
        throw std::out_of_range("Subtrahend greater than Minuend.");
    }
    char *diff = new char[BigInt::MAX_SIZE];
    diff[BigInt::MAX_SIZE - 1] = '\0';

    int carry = 0;
    int index1 = strlen(val1) - 1;
    int index2 = strlen(val2) - 1;
    int index3 = 0;

    while (index1 >= 0 || index2 >= 0 || carry > 0)
    {
        int ele1 = (index1 >= 0) ? (val1[index1] - '0') : 0;
        int ele2 = (index2 >= 0) ? (val2[index2] - '0') + carry : carry;

        carry = 0;
        while (ele1 < ele2)
        {
            ele1 += 10;
            carry++;
        }
        int temp = ele1 - ele2;

        diff[index3] = temp + '0';

        index1--;
        index2--;
        index3++;
    }
    diff[index3] = '\0';
    reverseStr(diff);

    return diff;
}
BigInt BigInt::operator+(const BigInt &term)
{
    BigInt sum;

    if (sign == term.sign)
    {
        sum.sign = sign;
        sum.value = addAbs(value, term.value);
    }
    else
    {
        if (compareAbsValue(value, term.value) == EQUAL)
        {
            sum = "0";
        }
        else if (compareAbsValue(value, term.value) == GREATER)
        {
            sum.sign = sign;
            sum.value = subAbs(value, term.value);
        }
        else
        {
            sum.sign = term.sign;
            sum.value = subAbs(term.value, value);
        }
    }

    removePrefix(sum.value);
    return sum;
}
BigInt BigInt::operator-(const BigInt &term)
{
    return (*this + (-term));
};

istream &operator>>(istream &is, BigInt &num)
{
    char input[BigInt::MAX_SIZE];
    is >> input;
    num.setValue(input);
    return is;
}

ostream &operator<<(ostream &os, const BigInt &num)
{
    if (num.sign == 0)
    {
        os << "-";
    }
    os << num.value;
    return os;
}