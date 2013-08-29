#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <cstdarg>
#include <UnitTest++/UnitTest++.h>

#include "integer.h"
using namespace std;


char line[15010];

Integer read_int(ifstream &input)
{
    string line;
    getline(input, line);
    return Integer(line);
}

TEST(test_sum_1)
{
    ifstream input("tests/test_sum_1.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a + b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_sum_2)
{
    ifstream input("tests/test_sum_2.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a + b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_sum_3)
{
    ifstream input("tests/test_sum_3.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a + b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_sum_4)
{
    ifstream input("tests/test_sum_4.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a + b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_sum_5)
{
    ifstream input("tests/test_sum_5.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a + b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_subtract_1)
{
    ifstream input("tests/test_subtract_1.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a - b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_subtract_2)
{
    ifstream input("tests/test_subtract_2.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a - b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_subtract_3)
{
    ifstream input("tests/test_subtract_3.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a - b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_subtract_4)
{
    ifstream input("tests/test_subtract_4.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a - b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_subtract_5)
{
    ifstream input("tests/test_subtract_5.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a - b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mult_1)
{
    ifstream input("tests/test_mult_1.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a * b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mult_2)
{
    ifstream input("tests/test_mult_2.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a * b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mult_3)
{
    ifstream input("tests/test_mult_3.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a * b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mult_4)
{
    ifstream input("tests/test_mult_4.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a * b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mult_5)
{
    ifstream input("tests/test_mult_5.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a * b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_div_1)
{
    ifstream input("tests/test_div_1.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a / b;

        string ans;
        getline(input, ans);
        //log("1) %s\n", c.to_string().c_str());
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_div_2)
{
    ifstream input("tests/test_div_2.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a / b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_div_3)
{
    ifstream input("tests/test_div_3.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a / b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_div_4)
{
    ifstream input("tests/test_div_4.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a / b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_div_5)
{
    ifstream input("tests/test_div_5.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a / b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mod_1)
{
    ifstream input("tests/test_mod_1.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a % b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mod_2)
{
    ifstream input("tests/test_mod_2.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a % b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mod_3)
{
    ifstream input("tests/test_mod_3.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a % b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mod_4)
{
    ifstream input("tests/test_mod_4.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a % b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}

TEST(test_mod_5)
{
    ifstream input("tests/test_mod_5.txt");

    if (input.is_open()) {
        Integer a = read_int(input);
        Integer b = read_int(input);
        Integer c = a % b;

        string ans;
        getline(input, ans);
        CHECK_EQUAL(ans, c.to_string());
    }
}


int main(int argc, char** argv)
{
    return UnitTest::RunAllTests();
}

