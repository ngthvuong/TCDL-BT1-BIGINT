#ifndef BIGINT_H
#define BIGINT_h

#include <iostream>
#include <functional>

using namespace std;
class BigInt
{
private:
    static const int MAX_SIZE;
    char *value;
    bool sign;
    void reverseStr(char *);
    void removePrefix(char *, char);
    void init();
    void setValue(const char[]);
    char *convert16To10(const char[]);
    char *filterValue(const char[], function<int(int)>);
    int compareAbsValue(char[], char[]) const;
    char *addAbs(char[], char[]);
    char *subAbs(char[], char[]);


public:
    BigInt();
    BigInt(const char[]);
    BigInt(const BigInt &term);

    bool operator==(const BigInt &);
    bool operator!=(const BigInt &);
    bool operator>(const BigInt &);
    bool operator<(const BigInt &);
    bool operator>=(const BigInt &);
    bool operator<=(const BigInt &);

    BigInt operator=(const BigInt &);
    BigInt operator-() const;

    BigInt operator+(const BigInt &);
    BigInt operator-(const BigInt &);
    BigInt operator*(const BigInt &);
    BigInt operator/(const BigInt &);
    BigInt operator%(const BigInt &);

    friend istream &operator>>(istream &, BigInt &);
    friend ostream &operator<<(ostream &, const BigInt &);
};

#endif