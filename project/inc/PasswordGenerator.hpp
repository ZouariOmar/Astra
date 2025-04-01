/**
 * @file      PasswordGenerator.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     PasswordGenerator header file
 * @version   0.1
 * @date      2025-03-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/PasswordGenerator.hpp PasswordGenerator.hpp @endlink
 * @link https://en.cppreference.com/w/cpp/numeric/random/random_device std::random_device @endlink
 * @link https://www.geeksforgeeks.org/stdmt19937-class-in-cpp Mersenne twister algorithm @endlink
 * @link https://terminalroot.com/how-to-generate-sha256-hash-with-cpp-and-openssl How to Generate SHA256 Hash with C++ and OpenSSL @endlink
 * @link https://git-ce.rwth-aachen.de/wzl-mq-public/soil/cpp-interface/-/issues/647 SHA256_Init, SHA256_Update and SHA256_Final are depricated in OpenSSL 3.0 @endlink
 * @link https://docs.huihoo.com/doxygen/openssl/1.0.1c/index.html openssl doxygen @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __PASSWORDGENERATOR_HPP__
#define __PASSWORDGENERATOR_HPP__
#define PASSWORD_GENERATOR_DEFAULT_PATTERN "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+"
//? Include prototype declaration part
// * Include std C++ headers
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <random>
#include <sstream>

//? Error/Success Messages declaration part
#define ERR_SHA256_CREATE std::cerr << "Error: Can't create a new EVP_MD_CTX!" << std::endl
#define ERR_SHA256_INIT std::cerr << "Error: Can't initialize SHA-256!" << std::endl
#define ERR_SHA256_UPDATE std::cerr << "Error: Can't update SHA-256 hash!" << std::endl
#define ERR_SHA256_FINAL std::cerr << "Error: Can't finalize SHA-256 hash!" << std::endl

//? Class prototype declaration part
class PasswordGenerator {
public:
  static std::string generate(const int &length = 6, const std::string &pattern = PASSWORD_GENERATOR_DEFAULT_PATTERN);
  static std::string sha256sum(const std::string &);
}; // PasswordGenerator class

#endif // __PASSWORDGENERATOR_HPP__