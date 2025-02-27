# C++ Password Manager

This project is a terminal-based password manager written in C++ with a simple encryption and verification mechanism. The application allows you to generate, store, search, sort, edit, and delete passwords, as well as manage categories. Data (including encrypted passwords) is stored in a text file and secured by a master password.

## Features
- **Password Generation:** Users can generate random passwords based on chosen criteria (length, use of uppercase letters, lowercase letters, and special characters).
- **Password Strength Verification:** The system checks whether a password meets the requirements for length, character variety, and uniqueness.
- **Encryption/Decryption:** Each line of data is encrypted using bitwise operations (XOR and bit inversion) with a master password.
- **Data Management:** Add new passwords, edit existing ones, delete passwords, and search for passwords by a provided substring.
- **Category Management:** Create, select, and delete password categories.
- **Security:** On the first run (or when the data file is empty), the user sets up a master password whose hash is stored in the file. Subsequent logins require verification of this master password.

## Requirements
- A C++ compiler supporting C++17 (for `std::filesystem`)
- A terminal environment

## Compilation and Running
1. Clone the repository and navigate to the project directory.
2. Compile the project, for example:
   ```bash
   g++ -std=c++17 main.cpp -o password_manager

