#include <bits/stdc++.h>

using namespace std;

bitset<10> ls1(bitset<10> key) {
    bitset<10> ls1_key;

    ls1_key[9] = key[8];
    ls1_key[8] = key[7];
    ls1_key[7] = key[6];
    ls1_key[6] = key[5];
    ls1_key[5] = key[9];
    ls1_key[4] = key[3];
    ls1_key[3] = key[2];
    ls1_key[2] = key[1];
    ls1_key[1] = key[0];
    ls1_key[0] = key[4];

    return ls1_key;
}

bitset<10> ls2(bitset<10> key) {
    bitset<10> ls2_key;

    ls2_key[9] = key[7];
    ls2_key[8] = key[6];
    ls2_key[7] = key[5];
    ls2_key[6] = key[9];
    ls2_key[5] = key[8];
    ls2_key[4] = key[2];
    ls2_key[3] = key[1];
    ls2_key[2] = key[0];
    ls2_key[1] = key[4];
    ls2_key[0] = key[3];

    return ls2_key;
}

bitset<10> p10(bitset<10> key) {
    bitset<10> p10_key;

    p10_key[9] = key[7];
    p10_key[8] = key[5];
    p10_key[7] = key[8];
    p10_key[6] = key[3];
    p10_key[5] = key[6];
    p10_key[4] = key[0];
    p10_key[3] = key[9];
    p10_key[2] = key[1];
    p10_key[1] = key[2];
    p10_key[0] = key[4];

    return p10_key;
}

bitset<8> p8(bitset<10> key) {
    bitset<8> p8_key;

    p8_key[7] = key[4];
    p8_key[6] = key[7];
    p8_key[5] = key[3];
    p8_key[4] = key[6];
    p8_key[3] = key[2];
    p8_key[2] = key[5];
    p8_key[1] = key[0];
    p8_key[0] = key[1];

    return p8_key;
}

bitset<8> ip(bitset<8> plaintext) {
    /* Initial permutation
    *  2 6 3 1 4 8 5 7
    */
    bitset<8> mixed_text;
    mixed_text[7] = plaintext[6];
    mixed_text[6] = plaintext[2];
    mixed_text[5] = plaintext[5];
    mixed_text[4] = plaintext[7];
    mixed_text[3] = plaintext[4];
    mixed_text[2] = plaintext[0];
    mixed_text[1] = plaintext[3];
    mixed_text[0] = plaintext[1];

    return mixed_text;
}

bitset<8> ip_inverse(bitset<8> ciphertext) {
    /* Inverse initial permutation
    *  4 1 3 5 7 2 8 6
    */
    bitset<8> plaintext;
    plaintext[6] = ciphertext[7];
    plaintext[2] = ciphertext[6];
    plaintext[5] = ciphertext[5];
    plaintext[7] = ciphertext[4];
    plaintext[4] = ciphertext[3];
    plaintext[0] = ciphertext[2];
    plaintext[3] = ciphertext[1];
    plaintext[1] = ciphertext[0];

    return plaintext;
}

vector<bitset<8>> generate_keys(bitset<10> key) {
    bitset<10> p10_key = p10(key);
    bitset<10> ls1_p10_key = ls1(p10_key);
    bitset<10> ls2_p10_key = ls2(ls1_p10_key);
    bitset<8> k1 = p8(ls1_p10_key);
    bitset<8> k2 = p8(ls2_p10_key);
    
    return {k1, k2};
}

bitset<8> sdes_encrypt(bitset<8> plaintext, bitset<10> key) {
    vector<bitset<8>> keys = generate_keys(key);
    bitset<8> mixed_plaintext = ip(plaintext);

    return plaintext;
}

#ifndef SDES_TESTS
int main() {
    bitset<10> key;
    bitset<8> data;
    // read both from input file
    ifstream input("input.txt");
    input >> key >> data;

    // apply sdes encryption
    bitset<8> encrypted = sdes_encrypt(data, key);

    return 0;
}
#endif
