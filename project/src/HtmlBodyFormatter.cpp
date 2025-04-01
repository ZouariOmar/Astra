/**
 * @file      HtmlBodyFormater.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     HtmlBodyFormater main source file
 * @version   0.1
 * @date      2025-03-30
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/HtmlBodyFormater.cpp HtmlBodyFormater.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/HtmlBodyFormatter.hpp"

//? Function/Class prototype dev part

/**
 * @fn           HtmlBodyFormater(const std::string, const std::unordered_map<std::string, const std::string>)
 * @brief        Construct a new HtmlBodyFormater::HtmlBodyFormater object
 * @note         `_param` should be formatted as `"{{PLACEHOLDER}}" : "VALUE"`
 * @param path   {const std::string &}
 * @param _param {const std::unordered_map<std::string, std::string> &}
 */
HtmlBodyFormater::HtmlBodyFormater(const std::string &path, const std::unordered_map<std::string, const std::string> &_param)
    : param(_param) {

  std::ifstream file(path); // Open the file using
  if (!file.is_open()) {    // Confirm file opening
    std::cerr << "Error: Failed to open file!" << std::endl;
    return;
  }

  // Read the file line by line into a `inner_html`
  std::string line;
  while (getline(file, line))
    inner_html += line;

  // Close the file
  file.close();
}

/**
 * @fn     HtmlBodyFormater::get_inner_html()
 * @brief  Get your file content in inner html format
 * @return std::string
 */
std::string HtmlBodyFormater::get_inner_html() {
  return format_inner_html(), inner_html;
}

/**
 * @fn      HtmlBodyFormater::format_inner_html()
 * @brief   Replaces placeholders in the inner HTML with corresponding values
 * @details This function iterates over a set of key-value pairs (`param`)
 * and replaces occurrences of each key in `inner_html` with its associated value.
 * @note    Placeholders in `inner_html` should be formatted as `{{PLACEHOLDER}}`
 * and will be replaced with their corresponding values.
 * @return  void
 */
void HtmlBodyFormater::format_inner_html() {
  for (const std::pair<const std::string, const std::string> &format : param) {
    size_t pos{};
    while ((pos = inner_html.find(format.first, pos)) != std::string::npos) {
      inner_html.replace(pos, format.first.length(), format.second);
      pos += format.second.length(); // Avoid infinite loop
    }
  }
}