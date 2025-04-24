/**
 * @file    CSVGenerator.hpp
 * @author  @ZouariOmar (zouariomar20@gmail.com)
 * @brief   CSVGenerator header file
 * @version 0.1
 * @date    2025-04-16
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/CSVGenerator.hpp CSVGenerator.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __CSVGENERATOR_HPP__
#define __CSVGENERATOR_HPP__

//? Include prototype declaration part
//* Include the stander c++ header(s)
#include <fstream>
#include <iostream>
#include <vector>

//? Classes prototype declaration part

/**
 * @class CSVGenerator
 * @brief CSVGenerator class
 */
class CSVGenerator {
public:
  static const unsigned int generateCSV(const std::string &, const std::vector<std::vector<std::string>> &);
}; // CSVGenerator class

#endif // __CSVGENERATOR_HPP__