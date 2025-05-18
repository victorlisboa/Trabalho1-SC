/**
 * @file op_modes.cpp
 * @brief Implementation of SDES operation modes (ECB and CBC)
 * 
 * This file implements two operation modes for SDES:
 * 1. Electronic Codebook (ECB) - Each block is encrypted independently
 * 2. Cipher Block Chaining (CBC) - Each block is XORed with previous ciphertext
 */

#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>
#include "sdes.h"

using namespace std;

/**
 * @brief Encrypts data using ECB mode
 * @param plaintext Vector of 8-bit blocks to encrypt
 * @param key 10-bit encryption key
 * @return Vector of encrypted 8-bit blocks
 */
vector<bitset<8>> ecb_encrypt(const vector<bitset<8>>& plaintext, const bitset<10>& key) {
    vector<bitset<8>> ciphertext;
    for (const auto& block : plaintext) {
        ciphertext.push_back(sdes_encrypt(block, key));
    }
    return ciphertext;
}

/**
 * @brief Decrypts data using ECB mode
 * @param ciphertext Vector of 8-bit blocks to decrypt
 * @param key 10-bit decryption key
 * @return Vector of decrypted 8-bit blocks
 */
vector<bitset<8>> ecb_decrypt(const vector<bitset<8>>& ciphertext, const bitset<10>& key) {
    vector<bitset<8>> plaintext;
    for (const auto& block : ciphertext) {
        plaintext.push_back(sdes_decrypt(block, key));
    }
    return plaintext;
}

/**
 * @brief Encrypts data using CBC mode
 * @param plaintext Vector of 8-bit blocks to encrypt
 * @param key 10-bit encryption key
 * @param iv 8-bit initialization vector
 * @return Vector of encrypted 8-bit blocks
 */
vector<bitset<8>> cbc_encrypt(const vector<bitset<8>>& plaintext, const bitset<10>& key, const bitset<8>& iv) {
    vector<bitset<8>> ciphertext;
    bitset<8> prev_block = iv;
    
    for (const auto& block : plaintext) {
        bitset<8> xored = block ^ prev_block;
        bitset<8> encrypted = sdes_encrypt(xored, key);
        ciphertext.push_back(encrypted);
        prev_block = encrypted;
    }
    return ciphertext;
}

/**
 * @brief Decrypts data using CBC mode
 * @param ciphertext Vector of 8-bit blocks to decrypt
 * @param key 10-bit decryption key
 * @param iv 8-bit initialization vector
 * @return Vector of decrypted 8-bit blocks
 */
vector<bitset<8>> cbc_decrypt(const vector<bitset<8>>& ciphertext, const bitset<10>& key, const bitset<8>& iv) {
    vector<bitset<8>> plaintext;
    bitset<8> prev_block = iv;
    
    for (const auto& block : ciphertext) {
        bitset<8> decrypted = sdes_decrypt(block, key);
        bitset<8> xored = decrypted ^ prev_block;
        plaintext.push_back(xored);
        prev_block = block;
    }
    return plaintext;
}

/**
 * @brief Prints a vector of bitsets in a readable format
 * @param blocks Vector of bitsets to print
 */
void print_blocks(const vector<bitset<8>>& blocks) {
    for (const auto& block : blocks) {
        cout << block << " ";
    }
    cout << endl;
}

int main() {
    // Read key, message, and IV from input2.txt
    bitset<10> key;
    bitset<8> iv;
    string message;
    ifstream input("input2.txt");
    input >> key;
    input >> message;
    input >> iv;
    
    // Parse the 32-bit message into 8-bit blocks
    vector<bitset<8>> plaintext;
    for (size_t i = 0; i < message.length(); i += 8) {
        string block = message.substr(i, 8);
        plaintext.push_back(bitset<8>(block));
    }
    
    // Display original message
    cout << "Original message: ";
    print_blocks(plaintext);
    
    // Demonstrate ECB mode
    cout << "\nECB Mode:" << endl;
    vector<bitset<8>> ecb_ciphertext = ecb_encrypt(plaintext, key);
    cout << "Encrypted: ";
    print_blocks(ecb_ciphertext);
    
    vector<bitset<8>> ecb_decrypted = ecb_decrypt(ecb_ciphertext, key);
    cout << "Decrypted: ";
    print_blocks(ecb_decrypted);
    
    // Demonstrate CBC mode
    cout << "\nCBC Mode:" << endl;
    vector<bitset<8>> cbc_ciphertext = cbc_encrypt(plaintext, key, iv);
    cout << "Encrypted: ";
    print_blocks(cbc_ciphertext);
    
    vector<bitset<8>> cbc_decrypted = cbc_decrypt(cbc_ciphertext, key, iv);
    cout << "Decrypted: ";
    print_blocks(cbc_decrypted);
    
    return 0;
}
