/**
 * @file sdes.cpp
 * @brief Implementation of Simplified Data Encryption Standard (SDES)
 * 
 * This file implements the core SDES algorithm including:
 * - Key generation and scheduling
 * - Permutation functions (P10, P8, P4)
 * - Left shifts (LS1, LS2)
 * - S-box substitutions
 * - Initial and inverse permutations
 * - Encryption and decryption functions
 */

#include <bits/stdc++.h>
#include <iomanip>
#include <sstream>
#include "sdes.h"

using namespace std;

// template<size_t N>
// string bitset_to_hex(const bitset<N>& bs) {
//     stringstream ss;
//     ss << "0x";
    
//     // Calculate how many hex digits we need
//     size_t hex_digits = (N + 3) / 4;  // Round up division
    
//     // Convert to hex, padding with leading zeros if needed
//     ss << setfill('0') << setw(hex_digits) << uppercase << hex << bs.to_ullong();
    
//     return ss.str();
// }

template<size_t N>
void print_bitsets(bitset<N> bs) {
    cout << bitset_to_hex(bs) << '\n';
}

/**
 * @brief Performs a left shift by 1 position on a 10-bit key
 * @param key 10-bit key to shift
 * @return Shifted 10-bit key
 */
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

    cout << "LS1 output: ";
    print_bitsets(ls1_key);

    return ls1_key;
}

/**
 * @brief Performs a left shift by 2 positions on a 10-bit key
 * @param key 10-bit key to shift
 * @return Shifted 10-bit key
 */
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

    cout << "LS2 output: ";
    print_bitsets(ls2_key);

    return ls2_key;
}

/**
 * @brief Performs P10 permutation on a 10-bit key
 * @param key 10-bit key to permute
 * @return Permuted 10-bit key
 */
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

    cout << "P10 output: ";
    print_bitsets(p10_key);

    return p10_key;
}

/**
 * @brief Performs P8 permutation on a 10-bit key to generate an 8-bit subkey
 * @param key 10-bit key to permute
 * @return 8-bit subkey
 */
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

    cout << "P8 output: ";
    print_bitsets(p8_key);

    return p8_key;
}

/**
 * @brief Performs P4 permutation on a 4-bit value
 * @param input 4-bit value to permute
 * @return Permuted 4-bit value
 */
bitset<4> p4(bitset<4> input) {
    bitset<4> result;

    result[3] = input[2];
    result[2] = input[0];
    result[1] = input[1];
    result[0] = input[3];

    cout << "P4 output: ";
    print_bitsets(result);

    return result;
}

/**
 * @brief Performs initial permutation on an 8-bit block
 * @param plaintext 8-bit block to permute
 * @return Permuted 8-bit block
 */
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

    cout << "IP output: ";
    print_bitsets(mixed_text);

    return mixed_text;
}

/**
 * @brief Performs inverse initial permutation on an 8-bit block
 * @param ciphertext 8-bit block to permute
 * @return Permuted 8-bit block
 */
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

    cout << "IP^-1 output: ";
    print_bitsets(plaintext);

    return plaintext;
}

/**
 * @brief Performs expansion/permutation on a 4-bit value to 8 bits
 * @param input 4-bit value to expand
 * @return Expanded 8-bit value
 */
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

    cout << "EP output: ";
    print_bitsets(output);

    return output;
}

/**
 * @brief Performs S-box 0 substitution
 * @param input 4-bit input value
 * @return 2-bit output value
 */
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
    
    cout << "S0 output: ";
    print_bitsets(result);
    
    return result;
}

/**
 * @brief Performs S-box 1 substitution
 * @param input 4-bit input value
 * @return 2-bit output value
 */
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
    
    cout << "S1 output: ";
    print_bitsets(result);
    
    return result;
}

/**
 * @brief Performs the F function mapping
 * @param input 4-bit input value
 * @param sk 8-bit subkey
 * @return 4-bit output value
 */
bitset<4> mapping_F(bitset<4> input, bitset<8> sk) {
    bitset<8> exp_mix_data = ep(input);
    bitset<8> sk_xor = exp_mix_data ^ sk;

    cout << "F function - After EP: ";
    print_bitsets(exp_mix_data);
    cout << "F function - After XOR with subkey: ";
    print_bitsets(sk_xor);

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

    cout << "F function final output: ";
    print_bitsets(p4_result);

    return p4_result;
}

/**
 * @brief Switches the left and right halves of an 8-bit block
 * @param bs 8-bit block to switch
 * @return Switched 8-bit block
 */
bitset<8> switch_func(bitset<8> bs) {
    bitset<8> result;
    for (int i = 0; i < 4; i++) {
        result[i] = bs[i + 4];
        result[i + 4] = bs[i];
    }
    
    cout << "Switch function output: ";
    print_bitsets(result);

    return result;
}

/**
 * @brief Generates two 8-bit subkeys from a 10-bit key
 * @param key 10-bit master key
 * @return Vector containing two 8-bit subkeys
 */
vector<bitset<8>> generate_keys(bitset<10> key) {
    cout << "\nKey Generation Process:\n";
    cout << "Original key: ";
    print_bitsets(key);

    bitset<10> p10_key = p10(key);
    bitset<10> ls1_p10_key = ls1(p10_key);
    bitset<8> k1 = p8(ls1_p10_key);
    cout << "K1: ";
    print_bitsets(k1);

    bitset<10> ls2_p10_key = ls2(ls1_p10_key);
    bitset<8> k2 = p8(ls2_p10_key);
    cout << "K2: ";
    print_bitsets(k2);

    return {k1, k2};
}

/**
 * @brief Performs the F function on an 8-bit block
 * @param data 8-bit input block
 * @param k 8-bit subkey
 * @return 8-bit output block
 */
bitset<8> f(bitset<8> data, bitset<8> k) {
    bitset<4> L, R;
    bitset<8> output;
    for(int i=7; i>=0; i--) {
        if(i>=4) {
            L[i-4] = data[i];
        }
        else {
            R[i] = data[i];
        }
    }

    cout << "\nF function process:\n";
    cout << "Input data: ";
    print_bitsets(data);
    cout << "Left half: ";
    print_bitsets(L);
    cout << "Right half: ";
    print_bitsets(R);
    cout << "Subkey: ";
    print_bitsets(k);

    bitset<4> mapping_F_result = mapping_F(R, k);
    bitset<4> new_L = L ^ mapping_F_result;
    
    bitset<8> result;
    for(int i=0; i<4; i++) {
        result[i] = R[i];
    }
    for(int i=4; i<8; i++) {
        result[i] = new_L[i-4];
    }

    cout << "F function result: ";
    print_bitsets(result);

    return result;
}

/**
 * @brief Encrypts an 8-bit block using SDES
 * @param plaintext 8-bit block to encrypt
 * @param key 10-bit encryption key
 * @return 8-bit encrypted block
 */
bitset<8> sdes_encrypt(bitset<8> plaintext, bitset<10> key) {
    cout << "\nSDES Encryption Process:\n";
    cout << "Plaintext: ";
    print_bitsets(plaintext);
    cout << "Key: ";
    print_bitsets(key);

    vector<bitset<8>> keys = generate_keys(key);
    bitset<8> ip_result = ip(plaintext);
    bitset<8> f1_result = f(ip_result, keys[0]);
    bitset<8> switch_result = switch_func(f1_result);
    bitset<8> f2_result = f(switch_result, keys[1]);
    bitset<8> ciphertext = ip_inverse(f2_result);

    cout << "Final ciphertext: ";
    print_bitsets(ciphertext);

    return ciphertext;
}

/**
 * @brief Decrypts an 8-bit block using SDES
 * @param ciphertext 8-bit block to decrypt
 * @param key 10-bit decryption key
 * @return 8-bit decrypted block
 */
bitset<8> sdes_decrypt(bitset<8> ciphertext, bitset<10> key) {
    cout << "\nSDES Decryption Process:\n";
    cout << "Ciphertext: ";
    print_bitsets(ciphertext);
    cout << "Key: ";
    print_bitsets(key);

    vector<bitset<8>> keys = generate_keys(key);
    bitset<8> ip_result = ip(ciphertext);
    bitset<8> f2_result = f(ip_result, keys[1]);
    bitset<8> switch_result = switch_func(f2_result);
    bitset<8> f1_result = f(switch_result, keys[0]);
    bitset<8> plaintext = ip_inverse(f1_result);

    cout << "Final plaintext: ";
    print_bitsets(plaintext);

    return plaintext;
}

/*
int main() {
    bitset<10> key;
    bitset<8> plaintext;
    // read both from input file
    ifstream input("input1.txt");
    input >> key >> plaintext;

    cout << "plaintext: " << bitset_to_hex(plaintext) << '\n';
    // // apply sdes encryption
    bitset<8> ciphertext = sdes_encrypt(plaintext, key);
    cout << "ciphertext: " << bitset_to_hex(ciphertext) << '\n';
    bitset<8> decrypted = sdes_decrypt(ciphertext, key);
    cout << "decrypted: " << bitset_to_hex(decrypted) << '\n';

    return 0;
}
*/
