/**
 * @file connect.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Oracle-db connection header file
 * @version 0.1
 * @date 2025-02-13
 * @copyright Copyright (c) 2025
 *
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
using namespace std;

// ? Classes prototype declaration part
class Database {
private:
  Environment *env;
  Connection *conn;

public:
  Database();
  Database(const char *, const char *, const char *);
  vector<vector<string>> execute(const string &query, int &);
  ~Database();
}; // Database class

#endif // __CONNECT_HPP__