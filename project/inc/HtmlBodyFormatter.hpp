/**
 * @file      HtmlBodyFormater.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     HtmlBodyFormater main header file
 * @version   0.1
 * @date      2025-03-30
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/HtmlBodyFormater.hpp HtmlBodyFormater.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __HTML_BODY_FORMATER_HPP__
#define __HTML_BODY_FORMATER_HPP__

/**
 * @brief ### How to use HtmlBodyFormater object ?
 * #####################################################
 * @example Simple example using HtmlBodyFormater object
 * #####################################################
 * @code
 * std::vector<string> cc = {"<zouariomar20@gmail.com>"};
 * std::vector<string> attachments = {"/home/zouari_omar/Documents/Daily/Projects/Astra/project/src/main.cpp", "/home/zouari_omar/Downloads/test.png"};
 * EmailData data(
 *    "<omar.zouari@esprit.tn>", "Test Subject", "<html><body><h1>Hello Omar</h1><p>This is a test email.</p></body></html>", cc, attachments);
 * EmailAuth auth;
 * EmailSender email(auth);
 * email.send(data);
 * @endcode
 */

//? Include prototype declaration part
// * Include std C++ header
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

//? Class(es) prototype declaration part

/**
 * @class HtmlBodyFormater
 * @brief HtmlBodyFormater class
 */
class HtmlBodyFormater {
public:
  explicit HtmlBodyFormater(const std::string &, const std::unordered_map<std::string, const std::string> &_param = {});
  std::string get_inner_html();

private:
  void format_inner_html();
  std::string inner_html;
  const std::unordered_map<std::string, const std::string> param;
}; // HtmlBodyFormater class

#endif // __HTML_BODY_FORMATER_HPP__