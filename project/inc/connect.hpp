/**
 * @file connect.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Oracle-db connection header file
 * @version 0.1
 * @date 2025-02-13
 * @copyright Copyright (c) 2025
 * @link https://www.oracle.com oracle @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef __CONNECT_HPP__
#define __CONNECT_HPP__

// ? Include prototype declaration part
// * Include std includes (C++)
#include <iostream>
#include <vector>

// * Include oracle includes
#include <oracle/occi.h>

// * Use workspaces
using namespace oracle::occi;


// ? Classes prototype declaration part
class Database {
private:
  Environment *env;
  Connection *conn;

public:
  Database();
  Database(const char *, const char *, const char *);
  void execute(const std::string &query, int &affectedRows);
  std::vector<std::vector<std::string>> execute(const std::string &query);
  ~Database();
}; // Database class

#endif // __CONNECT_HPP__