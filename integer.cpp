#include "integer.h"

static Integer ZERO(0);
static Integer ONE(1);
static Integer TWO(2);

// ---------- Constructors ----------
Integer::Integer()
{
    digits_ = new char[MAX_DIGITS];
    set_size(1);
    digits_[0] = 0;
    set_sign(PLUS);
}

Integer::Integer(const Integer& n)
{
    digits_ = new char[MAX_DIGITS];
    *this = n;
}

Integer::Integer(int n)
{
    digits_ = new char[MAX_DIGITS];
    create(n);
}

Integer::Integer(long long n)
{
    digits_ = new char[MAX_DIGITS];
    create(n);
}


Integer::Integer(const string &str)
{
    digits_ = new char[MAX_DIGITS];
    create(str.c_str());
}

Integer::Integer(const char *str)
{
    digits_ = new char[MAX_DIGITS];
    create(str);
}

Integer::~Integer()
{
    delete digits_;
}


// ---------- Accessors ----------
int Integer::sign() const
{
    return sign_;
};

unsigned int Integer::size() const
{
    return size_;
};

// Returns a string representation of the integer.
string Integer::to_string() const
{
    string s = (sign() == MINUS) ? "-" : "";

    for (int i = size() - 1; i >= 0; i--) {
        s += digits_[i] + '0';
    }

    return s;
}

// ---------- Mutators ----------
void Integer::set_sign(int sign)
{
    sign_ = sign;
}

void Integer::set_size(unsigned int size)
{
    size_ = size;
}

// ---------- Integer operations ----------

// Returns a new integer c = a + b
Integer Integer::add(Integer &a, Integer &b) const
{
    Integer c;
    int carry = 0, i;

    if (a.sign() == b.sign()) {
        c.set_sign(a.sign());
    } else {
        if (a.sign() == MINUS) {
            a.set_sign(PLUS);
            c = subtract(b, a);
            a.set_sign(MINUS);
        } else {
            b.set_sign(PLUS);
            c = subtract(a, b);
            b.set_sign(MINUS);
        }

        return c;
    }

    int max = std::max(a.size(), b.size());
    int n;

    for (i = 0; i < max; i++) {
        n = carry + a[i] + b[i];
        c[i] = n % BASE;
        carry = n / BASE;
    }

    if (carry > 0) {
        c[i++] = carry;
    }

    c.set_size(i);
    c.adjust();
    return c;
}

// Calculate a + b and store the result in c. a and b are positive.
void Integer::add(Integer& a, Integer& b, Integer& c) const
{
    int carry = 0, n, i;
    int max = std::max(a.size(), b.size());

    for (i = 0; i < max; i++) {
        n = a[i] + b[i] + carry;
        carry = n / BASE;
        c[i] = n % BASE;
    }

    if (carry > 0) {
        c[i++] = carry;
    }

    c.set_size(i);
    c.adjust();
}


// a and b are positive integers.
Integer Integer::subtract(Integer& a, Integer& b) const
{
    Integer ans;
    int borrow = 0, n;

    // Three special cases:
    //  a - (-b) ==  a + b
    // -a - b    == -a + (-b)
    // -a - (-b) == -a + b
    if (a.sign() == MINUS || b.sign() == MINUS) {  
        b.set_sign(MINUS * b.sign());
        ans = add(a, b);
        b.set_sign(MINUS * b.sign());
        return ans;
    }

    if (a == b) {
        return ZERO;
    }

    if (a < b) {
        ans = subtract(b, a);
        ans.set_sign(MINUS);
        return ans;
    }

    unsigned int i;

    for (i = 0; i < a.size(); i++) {
        n = a[i] - b[i] - borrow;
        borrow = (n < 0) ? 1 : 0;

        if (n < 0) {
            n += BASE;
        }

        ans[i] = n;
    }

    ans.set_size(i);
    ans.adjust();
    ans.set_sign(PLUS);

    return ans;
}

// a and b are positive and a > b
void Integer::subtract(Integer& a, Integer& b, Integer& c) const
{
    int n, borrow = 0;
    unsigned int i;

    for (i = 0; i < a.size(); i++) {
        n = a[i] - b[i] - borrow;

        if (n < 0) {
            n += BASE;
        }

        borrow = (n < 0) ? 1 : 0;
        c[i] = n;
    }

    c.set_size(i);
    c.adjust();
    c.set_sign(PLUS);
}

// Return a * b. This method is known as "Long Multiplication".
// Complexity: O(n^2)
Integer Integer::multiply(Integer& a, Integer& b) const
{
    Integer ans;
    unsigned int i, j, k, n, carry_mult, carry_sum;

    for (i = 0; i < a.size(); i++) {
        carry_mult = carry_sum = 0;
        k = i; // Shifting

        for (j = 0; j < b.size(); j++) {
            n = a[i] * b[j] + carry_mult;
            carry_mult = n / BASE;

            n = ans[k] + n % BASE + carry_sum;
            carry_sum = n / BASE;

            ans[k] = n % BASE;
            k++;
        }

        if (carry_sum > 0 || carry_mult > 0) {
            ans[k++] = carry_sum + carry_mult;
        }

        ans.set_size(k);
    }

    if (ans == ZERO)
        ans.set_sign(PLUS);
    else
        ans.set_sign(a.sign() * b.sign());

    return ans;
}


// Return a * b. This method is known as Karatsuba algorithm.
// Complexity: O(n^(log_2 3)) ~ O(n^1.585)
// References:
// [1]  Algorithms and Data Structures: The Basic Toolbox, Kurt Hehlhorn, et al.
// [2]  en.wikipedia.org/wiki/Karatsuba_algorithm
Integer Integer::karatsuba(Integer& a, Integer& b)
{
    unsigned int alength = a.size();
    unsigned int blength = b.size();

    unsigned int half = (max(alength, blength) + 1) / 2;

    // For small numbers the long multiplication is more efficient
    if (max(alength, blength) < MIN_KARATSUBA) {
        return multiply(a, b);
    }

    Integer a0, a1, b0, b1;
    split(a, a0, a1, half);
    split(b, b0, b1, half);

    Integer p1 = karatsuba(a1, b1);
    Integer p0 = karatsuba(a0, b0);

    Integer sum1, sum2;
    add(a0, a1, sum1);
    add(b0, b1, sum2);

    Integer p2 = karatsuba(sum1, sum2);

    unsigned int i;
    int n, carry = 0;

    Integer ans;
    ans.set_size(alength + blength);

    for (i = 0; i < 2 * half; i++) {
        ans[i] = p0[i];
    }

    for (i = 2 * half; i < ans.size(); i++) {
        ans[i] = p1[i - 2 * half];
    }

    // Subtracts
    for (i = 0; i < p2.size(); i++) {
        n = p2[i] - p0[i] - carry;
        carry = (n < 0) ? 1 : 0;

        if (n < 0) {
            n += BASE;
        }

        p2[i] = n;
    }

    p2.adjust();

    for (i = 0; i < p2.size(); i++) {
        n = p2[i] - p1[i] - carry;
        carry = (n < 0) ? 1 : 0;

        if (n < 0) {
            n += BASE;
        }

        p2[i] = n;
    }

    p2.adjust();


    for (i = half; i < ans.size(); i++) {
        n = ans[i] + p2[i - half] + carry;
        carry = n / BASE;
        ans[i] = n % BASE;
    }

    ans.adjust();

    return ans;
}

// Returns *this^n. This method is known as Exponentiation by squaring.
Integer Integer::pow(unsigned int n)
{
    Integer p(1), base = *this;

    while (n > 0) {
        if (n % 2 == 1) {
            p *= base;
        }

        base = base.square();
        n /= 2;
    }

    return p;
}

// Returns (*this^exponent) % modulus.
Integer Integer::modpow(unsigned long long exp, const Integer& modulus) const
{
    Integer m(1), base = *this, mod = modulus;

    while (exp > 0) {
        if (exp % 2 == 1) {
            m = (m * base) % mod;
        }

        base = base.square() % mod;
        exp /= 2;
    }

    return m % mod;
}

// Returns (*this^exponent) % modulus.
Integer Integer::modpow(const Integer& exponent, const Integer& modulus) const
{
    Integer m(1), b = *this;
    Integer p = exponent, mod = modulus;

    while (p > ZERO) {
        if (p.odd()) {
            m = (m * b) % mod;
        }

        b = b.square() % mod;
        p /= TWO;
    }

    return m % mod;
}

// Returns the absolute value of (*this).
Integer Integer::abs() const
{
    Integer temp = *this;
    temp.set_sign(temp.sign() * temp.sign());
    return temp;
}


// Returns the Greatest Common Divisor of (*this) and n.
Integer Integer::gcd(const Integer& n) const
{
    Integer a, b, temp;

    if (*this < n) {
        a = n;
        b = *this;
    } else {
        a = *this;
        b = n;
    }

    while (b > ZERO) {
        temp = a;
        a = b;
        b = temp % b;
    }

    return a;
}

// Returns the Least Common Multiple of (*this) and n.
Integer Integer::lcm(const Integer& n) const
{
    Integer a = n.abs();
    Integer b = this->abs();
    Integer g = this->gcd(n);
    return a / g * b;
}

// Returns the factorial of n: n!
Integer Integer::factorial(unsigned int n)
{
    Integer f(1);
    int d, carry = 0, size = 1;
    unsigned int i, j;

    for (i = 2; i <= n; i++) {
        carry = 0;
        size = f.size();

        for (j = 0; j < f.size(); j++) {
            d = f[j] * i + carry;
            carry = d / BASE;
            f[j] = d % BASE;
        }

        while (carry) {
            f[size++] = carry % BASE;
            carry /= BASE;
        }

        f.set_size(size);
    }

    return f;
}

// Returns (*this)^2.
Integer Integer::square()
{
    if (size() < MIN_KARATSUBA_SQUARE) {
        return multiply(*this, *this);
    }

    unsigned int i, half = (size() + 1) / 2;
    Integer a0, a1;
    split(*this, a0, a1, half);
    Integer square0 = a0.square();
    Integer square1 = a1.square();
    Integer ans;
    ans.set_size(size() + size());

    for (i = 0; i < 2 * half; i++) {
        ans[i] = square0[i];
    }

    for (i = 2 * half; i < ans.size(); i++) {
        ans[i] = square1[i - 2 * half];
    }

    Integer square2 = (a0 + a1).square();
    square2 -= square0;
    square2 -= square1;
    int n, carry = 0;

    for (i = half; i < ans.size(); i++) {
        n = ans[i] + square2[i - half] + carry;
        carry = n / BASE;
        ans[i] = n % BASE;
    }

    if (carry > 0) {
        ans[i++] = carry;
    }

    ans.adjust();

    return ans;
}


// Returns true if (*this) is probably prime, false otherwise.
// This method is known as: Miller-Rabin.
// NOTE: Experimental
bool Integer::is_probable_prime(int certainty) const
{
    Integer p = *this;

    if (p < TWO) {
        return false;
    }

    if (p != TWO && p.even()) {
        return false;
    }

    Integer minusone = p - ONE;
    Integer s = minusone;
    Integer a, temp, mod;
    srand(time(NULL));

    while (s.even()) {
        s /= TWO;
    }

    for (int i = 0; i < certainty; i++) {
        Integer aux;
        int size = rand() % 500;
        aux.set_size(size);

        for (int j = 0; j < size; j++) {
            aux[j] = rand() % 10;
        }

        aux.adjust();
        cout << aux << endl;


        a = aux % minusone + ONE;
        temp = s;
        mod = a.modpow(temp, p);

        while (temp != minusone && mod != ONE && mod != minusone) {
            mod = (mod * mod) % p;
            temp *= TWO;
        }

        if (mod != minusone && temp.even()) {
            return false;
        }
    }

    return true;
}


bool Integer::odd() const
{
    return digits_[0] % 2 == 1;
}

bool Integer::even() const
{
    return digits_[0] % 2 == 0;
}


// Returns a / b.
Integer Integer::divide(Integer& a, Integer& b) const
{
    Integer q, row;
    int asign = a.sign();
    int bsign = b.sign();
    int i;
    q.set_size(a.size());
    a.set_sign(PLUS);
    b.set_sign(PLUS);

    for (i = a.size() - 1; i >= 0; i--) {
        row <<= 1;
        row[0] = a[i];
        q[i] = 0;

        while (row >= b) {
            q[i]++;
            row -= b;
        }
    }

    q.adjust();

    if (q == ZERO)
        q.set_sign(PLUS);
    else
        q.set_sign(asign * bsign);

    a.set_sign(asign);
    b.set_sign(bsign);

    return q;
}



// Returns n << p => n * 10^p.
Integer Integer::left_shift(const Integer& n, long long p) const
{
    Integer ans = n;

    if (ans == ZERO) {
        return ZERO;
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        ans[i + p] = ans[i];
    }

    for (int i = 0; i < p; i++) {
        ans[i] = 0;
    }

    ans.set_size(ans.size() + p);
    return ans;
}

// Returns n >> p => n / 10^p.
Integer Integer::right_shift(const Integer& n, long long p) const
{
    Integer ans = n;

    if (ans == ZERO) {
        return ZERO;
    }

    for (unsigned int i = 0; i + p < ans.size(); i++) {
        ans[i] = ans[i + p];
    }

    ans.set_size(ans.size() - p);
    return ans;

}

// Returns a "random" number.
// NOTE: This was the only think that came to my mind in my first attempt .. :).
// TODO: Implement a formal method, a linear congruential method, for example.
Integer Integer::random(int digits) const
{
    Integer n;
    int size = rand() % digits;

    for (int i = 0; i < size; i++) {
        n[i] = rand() % BASE;
    }

    if (size > 0) {
        n.set_size(size);
    }

    n.adjust();
    return n;
}

// Split number a in two parts of size half, if a.size() < 2 * half
// trailing zeros are added.
void Integer::split(const Integer& a, Integer& a0, Integer& a1, int half)
{
    int i;
    a0.set_size(half);
    a1.set_size(half);

    for (i = 0; i < half; i++) {
        a0[i] = a[i];
    }

    for (i = half; i < half + half; i++) {
        a1[i - half] = a[i];
    }

    a0.adjust();
    a1.adjust();
}

//  Compare a with b, possible results are:
//  0         : a and b are equals.
//  PLUS(1)   : b > a
//  MINUS(-1) : b < a
int Integer::compare(const Integer& a, const Integer& b) const
{
    if (a.sign() == MINUS && b.sign() == PLUS) {
        return PLUS;
    }

    if (a.sign() == PLUS && b.sign() == MINUS) {
        return MINUS;
    }

    if (b.size() > a.size()) {
        return PLUS * a.sign();
    }

    if (a.size() > b.size()) {
        return MINUS * a.sign();
    }

    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] > b[i]) {
            return MINUS * a.sign();
        }

        if (b[i] > a[i]) {
            return PLUS * a.sign();
        }
    }

    return 0;
}


// Returns true if the string is a valid representation
// of a integer number. I employ a simple automata for
// it where the final state is 3.
bool Integer::validate(const char *num)
{
    int size = strlen(num);
    int state = 1, final = 3;

    for (int i = 0; i < size; i++) {
        switch (state) {
        case 1:

            if (num[i] == '-' || isdigit(num[i])) {
                state = 3;
            } else {
                state = 2;
            }

            break;
        case 2:
            return false;
        case 3:

            if (isdigit(num[i])) {
                state = 3;
            } else {
                return false;
            }

            break;
        }
    }

    return state == final;
}

// Removes leading zeros
void Integer::adjust()
{
    while (size_ > 1 && digits_[size_ - 1] == 0) {
        size_--;
    }
}

// Create a Integer from n.
void Integer::create(long long n)
{
    int size = 0;

    if (n < 0) {
        n *= -1;
        set_sign(MINUS);
    } else {
        set_sign(PLUS);

        if (n == 0) {
            size = 1;
        }
    }

    while (n) {
        digits_[size++] = n % BASE;
        n /= BASE;
    }

    set_size(size);
}


// Create a Integer from the string n.
void Integer::create(const char* n)
{
    if (validate(n)) {
        int size = strlen(n);
        int i = 0, j = size - 1;

        if (n[0] == '-') {
            set_sign(MINUS);
        } else {
            set_sign(PLUS);
        }

        while (j >= 0 && n[j] != '-') {
            digits_[i++] = n[j--] - '0';
        }

        set_size(i);
        adjust();

    } else { // Zero by default
        set_sign(PLUS);
        set_size(1);
        digits_[0] = 0;
    }
}


// ---------- Operator overloading ----------
ostream& operator<<(ostream &output, const Integer& n)
{
    output << n.to_string();
    return output;
}


Integer& Integer::operator=(long long n)
{
    create(n);
    return *this;
}

Integer& Integer::operator=(const char* n)
{
    create(n);
    return *this;
}

Integer& Integer::operator=(const Integer& n)
{
    set_size(n.size());
    set_sign(n.sign());

    for (unsigned int i = 0; i < size(); i++) {
        digits_[i] = n[i];
    }

    return *this;
}

// Relational operators
bool Integer::operator==(const Integer& n) const
{
    return compare(*this, n) == 0;
}

bool Integer::operator!=(const Integer& n) const
{
    return compare(*this, n) != 0;
}

bool Integer::operator<(const Integer& n) const
{
    return compare(*this, n) == PLUS;
}

bool Integer::operator>(const Integer& n) const
{
    return compare(*this, n) == MINUS;
}

bool Integer::operator<=(const Integer& n) const
{
    return *this < n || *this == n;
}

bool Integer::operator>=(const Integer& n) const
{
    return *this > n || *this == n;
}


// Bitwise operators

// Multiply n by 10^p
Integer Integer::operator<<(long long p) const
{
    return left_shift(*this, p);
}

// Divides n by 10^p
Integer Integer::operator>>(long long p) const
{
    return right_shift(*this, p);
}

// Overload <<= operator
Integer& Integer::operator<<=(long long p)
{
    *this = left_shift(*this, p);
    return *this;
}

// Overload >>= operator
Integer& Integer::operator>>=(long long p)
{
    *this = right_shift(*this, p);
    return *this;
}


// Overloading addition
Integer Integer::operator+(Integer& n)
{
    return add(*this, n);
}

Integer& Integer::operator+=(Integer& n)
{
    *this = add(*this, n);
    return *this;
}

// Prefix ++ operator
Integer& Integer::operator++()
{
    *this += ONE;
    return *this;
}

// Postfix ++ operator
const Integer Integer::operator++(int)
{
    Integer temp = *this;
    *this += ONE;
    return temp;
}

// Overloading subtract
Integer Integer::operator-(Integer& n)
{
    return subtract(*this, n);
}

Integer& Integer::operator-=(Integer& n)
{
    *this = subtract(*this, n);
    return *this;
}

// Prefix -- operator
Integer& Integer::operator--()
{
    *this -= ONE;
    return *this;
}

//Postfix -- operator
const Integer Integer::operator--(int)
{
    Integer temp = *this;
    *this -= ONE;
    return temp;
}


Integer Integer::operator*(Integer& n)
{
    Integer ans = karatsuba(*this, n);
    ans.set_sign(sign() * n.sign());
    return ans;
}

Integer& Integer::operator*=(Integer& n)
{
    *this = multiply(*this, n);
    return *this;
}

Integer Integer::operator/(Integer& n)
{
    return divide(*this, n);
}

Integer& Integer::operator/=(Integer& n)
{
    *this = divide(*this, n);
    return *this;
}


Integer Integer::operator%(Integer& n)
{
    if (*this < n) {
        return *this;
    }

    Integer q = divide(*this, n);
    Integer p = n * q;
    Integer r = subtract(*this, p);
    return r;
}

Integer& Integer::operator%=(Integer& n)
{
    *this = *this % n;
    return *this;
}

// Accessor methods
int Integer::operator[](unsigned int index) const
{
    assert(index < MAX_DIGITS);

    if (index < size()) {
        return digits_[index];
    }

    return 0;
}

char& Integer::operator[](unsigned int index)
{
    assert(index < MAX_DIGITS);

    if (index >= size()) { // Zero if index is out of bounds
        digits_[index] = 0;
    }

    return digits_[index];
}



// Utility
Integer Integer::reverse() const
{
    Integer temp = *this;

    for (unsigned int i = 0; i < size(); i++) {
        temp[i] = digits_[size() - i - 1];
    }

    return temp;
}


// Print messages to STDERR only if DEBUG is defined.
int log(const char* format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    int code = vfprintf(stderr, format, args);
    va_end(args);
    return code;
#else
    return 0;
#endif
}

