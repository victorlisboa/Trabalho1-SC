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

bitset<4> p4(bitset<4> input) {
    bitset<4> result;

    result[3] = input[2];
    result[2] = input[0];
    result[1] = input[1];
    result[0] = input[3];

    return result;
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

bitset<8> ep(bitset<4> input) {
    /* Expansion/Permutation function */
    bitset<8> output;

    output[7] = input[0];
    output[6] = input[3];
    output[5] = input[2];
    output[4] = input[1];
    output[3] = input[2];
    output[2] = input[1];
    output[1] = input[0];
    output[0] = input[3];

    return output;
}

bitset<2> s0(bitset<4> input) {
    /* S-box 0 */
    vector<vector<int>> S0 = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2},
    };

    int row = (input[3] << 1) | input[0];
    int column = (input[2] << 1) | input[1];
    int value = S0[row][column];
    
    bitset<2> result;
    result[0] = value & 1;
    result[1] = (value >> 1) & 1;
    
    return result;
}

bitset<2> s1(bitset<4> input) {
    /* S-box 1 */
    vector<vector<int>> S0 = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3},
    };

    int row = (input[3] << 1) | input[0];
    int column = (input[2] << 1) | input[1];
    int value = S0[row][column];
    
    bitset<2> result;
    result[0] = value & 1;
    result[1] = (value >> 1) & 1;
    
    return result;
}

bitset<4> mapping_F(bitset<4> input, bitset<8> sk) {
    bitset<8> exp_mix_data = ep(input);
    bitset<8> sk_xor = exp_mix_data ^ sk;

    bitset<4> s0_input;
    s0_input[3] = sk_xor[7];
    s0_input[2] = sk_xor[6];
    s0_input[1] = sk_xor[5];
    s0_input[0] = sk_xor[4];
    bitset<2> s0_result = s0(s0_input);
    
    bitset<4> s1_input;
    s1_input[3] = sk_xor[3];
    s1_input[2] = sk_xor[2];
    s1_input[1] = sk_xor[1];
    s1_input[0] = sk_xor[0];
    bitset<2> s1_result = s1(s1_input);

    bitset<4> p4_input;
    p4_input[3] = s0_result[1];
    p4_input[2] = s0_result[0];
    p4_input[1] = s1_result[1];
    p4_input[0] = s1_result[0];
    
    bitset<4> p4_result = p4(p4_input);

    return p4_result;
}

bitset<8> switch_func(bitset<8> bs) {
    bitset<8> result;
    for (int i = 0; i < 4; i++) {
        result[i] = bs[i + 4];
        result[i + 4] = bs[i];
    }
    return result;
}

vector<bitset<8>> generate_keys(bitset<10> key) {
    bitset<10> p10_key = p10(key);
    bitset<10> ls1_p10_key = ls1(p10_key);
    bitset<10> ls2_p10_key = ls2(ls1_p10_key);
    bitset<8> k1 = p8(ls1_p10_key);
    bitset<8> k2 = p8(ls2_p10_key);
    
    return {k1, k2};
}

bitset<8> f(bitset<8> data, bitset<8> k) {
    bitset<4> L, R;
    bitset<8> output;
    for(int i=7; i>=0; i--) {
        if(i>=4) {
            L[i] = data[i];
        }
        else {
            R[i] = data[i];
        }
    }

    bitset<4> mapping_F_result = mapping_F(R, k);
    bitset<4> new_L = L ^ mapping_F_result;
    
    bitset<8> result;
    for(int i=0; i<4; i++) {
        result[i] = R[i];
    }
    for(int i=4; i<8; i++) {
        result[i] = new_L[i-4];
    }

    return result;
}

bitset<8> sdes_encrypt(bitset<8> plaintext, bitset<10> key) {
    vector<bitset<8>> keys = generate_keys(key);
    bitset<8> ip_result = ip(plaintext);
    bitset<8> f1_result = f(ip_result, keys[0]);
    bitset<8> switch_result = switch_func(f1_result);
    bitset<8> f2_result = f(switch_result, keys[1]);
    bitset<8> ciphertext = ip_inverse(f2_result);

    return ciphertext;
}

bitset<8> sdes_decrypt(bitset<8> ciphertext, bitset<10> key) {
    vector<bitset<8>> keys = generate_keys(key);
    bitset<8> ip_result = ip(ciphertext);
    bitset<8> f2_result = f(ip_result, keys[1]);
    bitset<8> switch_result = switch_func(f2_result);
    bitset<8> f1_result = f(switch_result, keys[0]);
    bitset<8> plaintext = ip_inverse(f1_result);

    return plaintext;
}

#ifndef SDES_TESTS
int main() {
    bitset<10> key;
    bitset<8> data;
    // read both from input file
    ifstream input("input.txt");
    input >> key >> data;

    cout << data << '\n';
    // apply sdes encryption
    bitset<8> encrypted = sdes_encrypt(data, key);
    cout << encrypted << '\n';
    bitset<8> decrypted = sdes_decrypt(data, key);
    cout << decrypted << '\n';

    return 0;
}
#endif
