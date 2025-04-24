/**
 * @file      Database.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Database header file
 * @version   0.1
 * @date      2025-02-13
 * @copyright Copyright (c) 2025
 * @link https://www.oracle.com oracle @endlink
 * @link https://github.com/ZouariOmar/Astra/project/inc/Database.hpp
 * Database.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

//? Include prototype declaration part
//* Include std c++ header(s)
#include <oracle/occi.h>
#include <vector>

//* Use workspaces
using namespace oracle::occi;

//? Struct prototype declaration part

/**
 * @struct SqlParam
 * @brief  SqlParam struct
 * ? We use param.first as the parameter name
 * ? And param.second as the passed data
 */
struct SqlParam {
  std::vector<std::pair<unsigned int, std::string>>
      strings; // Parameters of type string
  std::vector<std::pair<unsigned int, int>> integers; // Parameters of type int
  std::vector<std::pair<unsigned int, oracle::occi::Date>>
      dates; // Parameters of type dates
  std::vector<std::pair<unsigned int, oracle::occi::Timestamp>>
      timestamps; // Parameters of type timestamp
  explicit SqlParam(
      const std::vector<std::pair<unsigned int, std::string>> &strParams = {},
      const std::vector<std::pair<unsigned int, int>> &intParams = {},
      const std::vector<std::pair<unsigned int, oracle::occi::Date>>
          &dateParams = {},
      const std::vector<std::pair<unsigned int, oracle::occi::Timestamp>>
          &timestampsParams = {});
}; // SqlParam struct

//? Classes prototype declaration part

/**
 * @class Database
 * @brief Database class
 */
class Database {
private:
  //* Database private vars
  Environment *env;
  Connection *conn;

  //* Database private functions
  inline void setSqlParams(Statement *, const SqlParam &);

public:
  //* Database constructors and destructor
  Database();
  Database(const char *, const char *, const char *);
  ~Database();

  //* Database public functions
  void execute(const std::string &query, const SqlParam &, int &affectedRows);
  std::vector<SqlParam> execute(const std::string &, const SqlParam &params);
}; // Database class

#endif // __DATABASE_HPP__
