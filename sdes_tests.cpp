#include <bits/stdc++.h>
#include <cassert>

#define SDES_TESTS
#include "sdes.cpp"

using namespace std;

void test_ls1() {
    bitset<10> input("1010000010");
    bitset<10> expected("0100100100");
    bitset<10> result = ls1(input);
    assert(result == expected);
    cout << "LS1 test passed!" << endl;
}

void test_ls2() {
    bitset<10> input("0000111000");
    bitset<10> expected("0010000011");
    bitset<10> result = ls2(input);
    assert(result == expected);
    cout << "LS2 test passed!" << endl;
}

void test_p10() {
    bitset<10> input("1010000010");
    bitset<10> expected("1000001100");
    bitset<10> result = p10(input);
    assert(result == expected);
    cout << "P10 test passed!" << endl;
}

void test_p8() {
    bitset<10> input("0000111000");
    bitset<8> expected("10100100");
    bitset<8> result = p8(input);
    assert(result == expected);
    cout << "P8 test passed!" << endl;
}

void test_generate_keys() {
    bitset<10> input("1010000010");
    vector<bitset<8>> expected = {
        bitset<8>("10100100"),
        bitset<8>("01000011")
    };
    vector<bitset<8>> result = generate_keys(input);
    assert(result.size() == 2);
    assert(result[0] == expected[0]);
    assert(result[1] == expected[1]);
    cout << "Generate keys test passed!" << endl;
}

void test_sdes_encrypt() {
    bitset<10> key("1010000010");
    bitset<8> data("11010111");
    bitset<8> expected("11010111"); // This will need to be updated with actual expected output
    bitset<8> result = sdes_encrypt(data, key);
    assert(result == expected);
    cout << "SDES encrypt test passed!" << endl;
}

void test_ip() {
    bitset<8> input("11010111");
    bitset<8> expected("11011101");
    bitset<8> result = ip(input);
    assert(result == expected);
    cout << "IP test passed!" << endl;
}

void test_ip_inverse() {
    bitset<8> input("11011101");
    bitset<8> expected("11010111");
    bitset<8> result = ip_inverse(input);
    assert(result == expected);
    cout << "IP inverse test passed!" << endl;
}

void run_tests() {
    test_ls1();
    test_ls2();
    test_p10();
    test_p8();
    test_generate_keys();
    test_ip();
    test_ip_inverse();
    test_sdes_encrypt();
    
    cout << "All tests passed!" << endl;
}

int main() {
    run_tests();
    return 0;
}
