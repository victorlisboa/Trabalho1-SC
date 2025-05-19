# SDES Implementation with Operation Modes

This project implements the Simplified Data Encryption Standard (SDES) with two operation modes: Electronic Codebook (ECB) and Cipher Block Chaining (CBC).

## Project Structure

- `sdes.h`: Header file containing SDES function declarations and template implementations
- `sdes.cpp`: Implementation of SDES encryption/decryption functions
- `op_modes.cpp`: Implementation of ECB and CBC operation modes
- `input2.txt`: Input file containing:
  - 10-bit key
  - 32-bit message
  - 8-bit initialization vector (IV)
- `Makefile`: Build configuration for the project

## Features

### SDES Implementation
- 10-bit key generation
- 8-bit block encryption/decryption
- Key scheduling with P10, P8, LS1, and LS2 operations
- S-box substitutions
- Initial and inverse permutations

### Operation Modes
1. **ECB (Electronic Codebook)**
   - Each block is encrypted independently
   - Same plaintext blocks produce same ciphertext blocks
   - No chaining between blocks

2. **CBC (Cipher Block Chaining)**
   - Each block is XORed with previous ciphertext before encryption
   - First block is XORed with IV
   - Provides better security than ECB by preventing pattern recognition

## Building and Running

The project uses a Makefile for building and running. Here are the available commands:

1. Build the program:
```bash
make
```

2. Run the program:
```bash
make run
```

3. Clean build files:
```bash
make clean
```

4. Build and run in one command:
```bash
make run
```

## Input Format

The program expects an input file named `input2.txt` with the following format:
```
1010000010           # 10-bit key
11010111011011001011101011110000  # 32-bit message
01010101            # 8-bit IV
```

## Output

The program will display:
1. Original message blocks
2. ECB Mode:
   - Encrypted blocks
   - Decrypted blocks
3. CBC Mode:
   - Encrypted blocks
   - Decrypted blocks

Each operation will show detailed intermediate steps of the SDES algorithm, including:
- Key generation process
- Permutation operations
- S-box substitutions
- F-function operations
- Final encryption/decryption results

## Security Considerations

- ECB mode is not recommended for secure applications as it doesn't hide patterns in the plaintext
- CBC mode provides better security by chaining blocks together
- The IV should be random and unique for each encryption operation
- SDES is a simplified version of DES and should not be used for real security applications
