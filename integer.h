#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cassert>
#include <cstdarg>
#include <algorithm>
using namespace std;
#ifdef DEBUG
#undef DEBUG
#endif

#define DEBUG 1

const int BASE = 10;                            // Number base

const unsigned int MAX_DIGITS = 2000;           // Maximum number of digits
                                                // a number of Integer can hold.
                                                
const unsigned int MIN_KARATSUBA = 16;          // Constants used for Karatsuba
const unsigned int MIN_KARATSUBA_SQUARE = 32;   // algorithm (to achieve better
                                                // performance)
                                                
const int PLUS  =  1;   // Signs:   >= 0  -->  1
const int MINUS = -1;   //           < 0  --> -1 

// Utility function to write messages to STDERR only if DEBUG is defined
int log(const char* format, ...);

class Integer
{
public:
    Integer();
    ~Integer();
    Integer(const Integer& n);
    Integer(const char* str);
    Integer(const string &str);
    Integer(int n);
    Integer(long long n);

    // Accessors
    int sign() const;
    unsigned int size() const;
    string to_string() const;


    // Mutators
    void set_sign(int sign);
    void set_size(unsigned int size);



    Integer square();
    Integer pow(unsigned int p);
    Integer modpow(unsigned long long exp, const Integer& modulus) const;
    Integer modpow(const Integer& exponent, const Integer& modulus) const;
    Integer gcd(const Integer& n) const;
    Integer lcm(const Integer& n) const;
    Integer abs() const;
    bool is_probable_prime(int certainty) const;
    bool odd() const;
    bool even() const;
    static Integer factorial(unsigned int n);
    Integer random(int digits = MAX_DIGITS) const;

    // ---------- Operator overloading ----------
    friend ostream& operator<<(ostream &output, const Integer &n);
    Integer& operator=(long long n);
    Integer& operator=(const char* n);
    Integer& operator=(const Integer& n);
    bool operator==(const Integer& n) const;
    bool operator>(const Integer& n) const;
    bool operator<(const Integer& n) const;
    bool operator!=(const Integer& n) const;
    bool operator>=(const Integer& n) const;
    bool operator<=(const Integer& n) const;
    Integer operator<<(long long p) const;
    Integer operator>>(long long p) const;
    Integer& operator<<=(long long p);
    Integer& operator>>=(long long p);

    Integer operator+(Integer& n);
    Integer& operator+=(Integer& n);
    Integer& operator++();          // Prefix ++
    const Integer operator++(int);  // Postfix ++

    Integer operator-(Integer& n);
    Integer& operator-=(Integer& n);
    Integer& operator--();          // Prefix --
    const Integer operator--(int);  // Postfix --

    Integer operator*(Integer& n);
    Integer& operator*=(Integer& n);

    Integer operator/(Integer& n);
    Integer& operator/=(Integer& n);

    Integer operator%(Integer& n);
    Integer& operator%=(Integer& n);


    // Utility
    Integer reverse() const;

    // Accessors
    int operator[](unsigned int index) const;
    char& operator[](unsigned int index);


protected:
    bool validate(const char *num);
    void adjust();
    void create(long long n);
    void create(const char* n);

    // Integer operations
    Integer add(Integer& a, Integer& b) const;
    void add(Integer& a, Integer& b, Integer& c) const;
    Integer subtract(Integer& a, Integer& b) const;
    void subtract(Integer&a, Integer& b, Integer& c) const;
    Integer multiply(Integer& a, Integer& b) const;
    Integer karatsuba(Integer& a, Integer& b);
    Integer divide(Integer& a, Integer& b) const;

    Integer left_shift(const Integer& n, long long p) const;
    Integer right_shift(const Integer& n, long long p) const;

    int compare(const Integer& a, const Integer& b) const;
    void split(const Integer& a, Integer& a0, Integer& a1, int half);



private:
    char* digits_;
    int sign_;
    unsigned int size_;
};

#endif // INTEGER_H

