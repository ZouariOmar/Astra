/**
 * @file    CSVGenerator.cpp
 * @author  @ZouariOmar (zouariomar20@gmail.com)
 * @brief   CSVGenerator source file
 * @version 0.1
 * @date    2025-04-16
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/CSVGenerator.cpp
 * CSVGenerator.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/CSVGenerator.hpp"

//? Function prototype dev part

/** @brief Generate a `.csv` file in `filePath` using `table`
 *
 * @fn             CSVGenerator::generateCSV(const std::string &, const
 * std::vector<std::vector<std::string>> &)
 * @param filePath {const std::string &}
 * @param table    {const std::vector<std::vector<std::string>> &}
 * @return         {const unsigned int}
 */
const unsigned int
CSVGenerator::generateCSV(const std::string &filePath,
                          const std::vector<std::vector<std::string>> &table) {
  std::ofstream csv(filePath); // Create and open a .csv file

  if (!csv.is_open())
    return EXIT_FAILURE; // Error code, could not open file

  for (const std::vector<std::string> &row : table) {
    for (size_t i{}, len(row.size()); i < len; ++i) {
      csv << row[i];
      if (i < row.size() - 1)
        csv << ',';
    }
    csv << '\n';
  }

  return csv.close(), EXIT_SUCCESS;
}
