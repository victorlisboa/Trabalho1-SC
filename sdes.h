/**
 * @file sdes.h
 * @brief Header file for Simplified Data Encryption Standard (SDES) implementation
 * 
 * This file contains the declarations for SDES encryption/decryption functions
 * and utility functions for bit manipulation and conversion.
 */

#ifndef SDES_H
#define SDES_H

#include <bitset>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/**
 * @brief Converts a bitset to its hexadecimal string representation
 * @tparam N Size of the bitset
 * @param bs The bitset to convert
 * @return String containing the hexadecimal representation with "0x" prefix
 */
template<size_t N>
string bitset_to_hex(const bitset<N>& bs) {
    stringstream ss;
    ss << "0x";
    
    // Calculate how many hex digits we need
    size_t hex_digits = (N + 3) / 4;  // Round up division
    
    // Convert to hex, padding with leading zeros if needed
    ss << setfill('0') << setw(hex_digits) << uppercase << hex << bs.to_ullong();
    
    return ss.str();
}

/**
 * @brief Encrypts an 8-bit block using SDES algorithm
 * @param plaintext 8-bit block to encrypt
 * @param key 10-bit encryption key
 * @return 8-bit encrypted block
 */
bitset<8> sdes_encrypt(bitset<8> plaintext, bitset<10> key);

/**
 * @brief Decrypts an 8-bit block using SDES algorithm
 * @param ciphertext 8-bit block to decrypt
 * @param key 10-bit decryption key
 * @return 8-bit decrypted block
 */
bitset<8> sdes_decrypt(bitset<8> ciphertext, bitset<10> key);

#endif // SDES_H
