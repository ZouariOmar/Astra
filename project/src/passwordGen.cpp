/**
 * @file passwordGen.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Password generator source file
 * @version 0.1
 * @date 2025-03-01
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/passwordGen.cpp passwordGen.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/passwordGen.hpp"

//? Function/Class prototype dev part

/**
 * @brief ### Generate a random password using the system seed and "Mersenne twister algorithm"
 *
 * @class         Password
 * @param pattern {const std::string}
 * @param length  {const int}
 * @return        std::string
 */
std::string Password::generate(const int &length, const std::string &pattern) {
  std::random_device rd;                                            // Obtain a random seed from the system (or i can obtain it from `std::srand(std::time(0))`)
  std::mt19937 gen(rd());                                           // Use the random device to initialize the generator
  std::uniform_int_distribution<size_t> dis(0, pattern.size() - 1); // Define a distribution for selecting indices

  std::string password;
  for (int i{}; i < length; i++)
    password += pattern[dis(gen)]; // Obtain a random character and add it to `password`

  return password; // Return the generated password
}

/**
 * @brief ### Hash the given `data` on 32-bit format using sha256 encryption protocol
 *
 * @details SHA-256 is used for secure password hashing
 * ! Test with:
 * @code
 *   $printf "Terminal Root" | sha256sum
 * @endcode
 * @class      Password
 * @param data {const std::string}
 * @return     std::string
 */
std::string Password::sha256sum(const std::string &data) {
  unsigned char hash[EVP_MAX_MD_SIZE]; // Store hex strings
  unsigned int length{};               // To store the length of the resulting hash

  EVP_MD_CTX *context = EVP_MD_CTX_new(); // Create an EVP context
  if (!context)
    return ERR_SHA256_CREATE, "";

  if (!EVP_DigestInit_ex(context, EVP_sha256(), nullptr)) // Initialize SHA-256
    return ERR_SHA256_INIT, EVP_MD_CTX_free(context), "";

  if (!EVP_DigestUpdate(context, data.c_str(), data.size())) // Update the context with the input data
    return ERR_SHA256_UPDATE, EVP_MD_CTX_free(context), "";

  if (!EVP_DigestFinal_ex(context, hash, &length)) // Finalize the hash and get its length
    return ERR_SHA256_FINAL, EVP_MD_CTX_free(context), "";

  EVP_MD_CTX_free(context); // Clean up the context

  // Convert the hash to a hexadecimal string
  std::stringstream ss;
  for (unsigned int i{}; i < length; i++)
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

  return ss.str();
}