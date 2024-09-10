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
    BigInt result = "0";
    BigInt sixteen = "16";
    int val16Length = strlen(val);

    for (int i = val16Length - 1; i >= 0; i--)
    {
        int ele16 = val[i];
        BigInt ele10;
        if (ele16 >= '0' && ele16 <= '9')
        {
            ele10 = (BigInt)(ele16 - '0');
        }
        else if (ele16 >= 'a' && ele16 <= 'f')
        {
            ele10 = (BigInt)(10 + (ele16 - 'a'));
        }
        else if (ele16 >= 'A' && ele16 <= 'F')
        {
            ele10 = (BigInt)(10 + (ele16 - 'A'));
        }

        result = result + (ele10 * sixteen.power(val16Length - i - 1));
    }
    return result.value;
}
char *BigInt::convert10To16(const char val[])
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
BigInt::BigInt(int term)
{
    init();
    if (term < 0)
    {
        sign = false;
        term = -term;
    }
    else
    {
        sign = true;
    }
    int index = 0;
    int temp = term;
    do
    {
        value[index] = (temp % 10) + '0';
        temp /= 10;
        index++;
    } while (temp != 0);
    value[index] = '\0';

    reverseStr(value);
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
                break;
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

BigInt &BigInt::operator=(const BigInt &term)
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
        throw out_of_range("Subtrahend greater than Minuend.");
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
char *BigInt::mulAbs(char val1[], char val2[])
{
    char *prod = new char[BigInt::MAX_SIZE]{'0', '\0'};
    int startIndex = 0;

    for (int index1 = strlen(val1) - 1; index1 >= 0; index1--)
    {
        char *subProd = new char[BigInt::MAX_SIZE];
        subProd[BigInt::MAX_SIZE - 1] = '\0';

        // add n zero after a loop
        for (int i = 0; i < startIndex; i++)
        {
            subProd[i] = '0';
        }

        int subIndex = startIndex;
        int ele1 = val1[index1] - '0';
        int carry = 0;
        int index2 = strlen(val2) - 1;

        while (index2 >= 0 || carry > 0)
        {
            int ele2 = (index2 >= 0) ? val2[index2] - '0' : 0;
            int temp = ele2 * ele1 + carry;

            subProd[subIndex] = (temp % 10) + '0';
            carry = temp / 10;

            index2--;
            subIndex++;
        }
        subProd[subIndex] = '\0';
        reverseStr(subProd);
        prod = addAbs(prod, subProd);

        startIndex++;
        delete[] subProd;
    }

    removePrefix(prod);
    return prod;
}

BigInt BigInt::divAbsTo2(const BigInt &dividend)
{
    char *val = new char[BigInt::MAX_SIZE];
    char *quotient = new char[BigInt::MAX_SIZE];

    strncpy(val, dividend.value, BigInt::MAX_SIZE - 1);
    quotient[BigInt::MAX_SIZE - 1] = '\0';

    int valLength = strlen(val);
    int carry = 0;
    int quotientIndex = 0;

    for (int index = 0; index < valLength; index++)
    {
        int ele = (val[index] - '0') + carry * 10;

        if (ele < 2)
        {
            carry = ele;
            quotient[quotientIndex] = '0';
        }
        else
        {
            int sub = 1;
            for (sub; sub <= 10; sub++)
            {
                if (sub * 2 > ele)
                {
                    sub--;
                    break;
                }
            }
            quotient[quotientIndex] = sub + '0';
            carry = ele - sub * 2;
        }
        quotientIndex++;
    }

    quotient[quotientIndex] = '\0';

    BigInt result = quotient;

    delete[] quotient;
    delete[] val;

    return result;
}

BigInt BigInt::divAbs(char val1[], char val2[])
{
    BigInt quotient;

    if (compareAbsValue(val2, ZERO) == EQUAL)
    {
        throw out_of_range("Divisor is 0.");
    }
    else if (compareAbsValue(val1, val2) != GREATER)
    {
        quotient = "0";
    }
    else
    {
        BigInt a = val1;
        BigInt b = val2;

        BigInt l = "1";
        BigInt r = a;
        BigInt epsilon = "1";

        int test = 0;
        bool stop = false;

        do
        {
            quotient = divAbsTo2(r + l);

            if ((quotient * b) > a)
            {
                r = quotient;
            }
            else
            {
                l = quotient;
            }

            if ((r - l) == epsilon)
            {
                quotient = l;
                if (r * b == a)
                {
                    quotient = r;
                }
                stop = true;
            }
        } while (!stop);
    }
    return quotient;
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
BigInt BigInt::operator*(const BigInt &term)
{
    BigInt prod;
    prod.sign = (sign == term.sign) ? true : false;
    prod.value = mulAbs(value, term.value);
    return prod;
}
BigInt BigInt::operator/(const BigInt &term)
{
    BigInt quot = divAbs(value, term.value);
    quot.sign = (sign == term.sign) ? true : false;
    return quot;
}
BigInt BigInt::operator%(const BigInt &term)
{
    BigInt quot = divAbs(value, term.value);
    quot.sign = (sign == term.sign) ? true : false;

    BigInt remainder = abs() - (quot.abs() * term.abs());
    remainder.sign = sign;
    return remainder;
}

BigInt BigInt::abs() const
{
    BigInt result = *this;
    result.sign = true;
    return result;
}
BigInt BigInt::power(int n) const
{
    BigInt result = "1";
    for (int i = 0; i < n; i++)
    {
        result = result * (*this);
    }
    return result;
}
char *BigInt::hex()
{
    char *result = new char[BigInt::MAX_SIZE]{'0', '\0'};
    result[BigInt::MAX_SIZE - 1] = '\0';

    char *absValue = new char[BigInt::MAX_SIZE]{'0', '\0'};
    BigInt temp = abs();
    int remainder = 0;
    BigInt sixteen = "16";
    int index = 0;
    do
    {
        remainder = (int)(temp % sixteen);
        temp = temp / sixteen;
        if (remainder < 10)
        {
            absValue[index] = remainder + '0';
        }
        else if (remainder < 16)
        {
            absValue[index] = remainder + 'a' - 10;
        }
        index++;
    } while (temp > (BigInt)0);

    absValue[index] = '\0';
    reverseStr(absValue);

    index = 0;
    if (!sign)
    {
        result[index] = '-';
        index++;
    }

    result[index] = 'x';
    index++;

    strncpy(result + index, absValue, BigInt::MAX_SIZE - index - 1);

    return result;
}
BigInt BigInt::root(int n)
{

    if (n % 2 == 0 && sign == false)
    {
        throw out_of_range("The term must not be a negative value.");
    }

    BigInt b = abs();
    BigInt x = 1;

    for (int i = 0; i <= 200; i++)
    {
        BigInt stopValue = x;

        BigInt Bt1 = (BigInt)(n - 1) * x;
        BigInt Bt2 = b / (x.power(n - 1));
        x = (Bt1 + Bt2) / ((BigInt)n);

        if(x == stopValue){
            break;
        }
    }

    x.sign = sign;
    return x;
}

BigInt::operator int() const
{
    int result = 0;
    int length = strlen(value);
    for (int i = 0; i < length; i++)
    {
        int ele = value[i] - '0';
        result = (result * 10) + ele;
    }

    if (!sign)
    {
        result = -result;
    }
    return result;
}

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