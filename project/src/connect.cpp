/**
 * @file connect.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Oracle-db connection source file
 * @version 0.1
 * @date 2025-02-13
 * @copyright Copyright (c) 2025
 * @link https://www.oracle.com oracle @std::endlink
 */

//? Include prototype declaration part
#include "../inc/connect.hpp"

// ? Function/Class prototype dev part

// * ============================
// ? === SqlParam Constructor ===
// * ============================

SqlParam::SqlParam(const std::vector<std::pair<unsigned int, const std::string>> &strParams,
                   const std::vector<std::pair<unsigned int, const int>> &intParams,
                   const std::vector<std::pair<unsigned int, const oracle::occi::Timestamp>> &timestampsParams)
    : strings(strParams),
      integers(intParams),
      timestamps(timestampsParams) {};

// * ===========================================
// ? ========= / SqlParam Constructor ==========
// ? === Database Constructor and destructor ===
// * ===========================================

/**
 * @brief ### Construct a new Database::Database object
 *
 * @class   Database
 * @details Use the ENV session export it vars
 */
Database::Database()
    : Database(
          getenv("oracle_username") ? getenv("oracle_username") : "",
          getenv("oracle_password") ? getenv("oracle_password") : "",
          getenv("oracle_database") ? getenv("oracle_database") : "") {
}

/**
 * @brief Construct a new Database::Database object
 *
 * @class      Database
 * @param user {const std::string &}
 * @param pass {const std::string &}
 * @param db   {const std::string &}
 */
Database::Database(const char *username, const char *password, const char *database) {
  try {
    env = Environment::createEnvironment(Environment::DEFAULT);
    conn = env->createConnection(username, password, database);
    std::cout << "Connected to Oracle Database!" << std::endl;
  } catch (SQLException &e) {
    std::cerr << "Connection Error: " << e.getMessage() << std::endl;
    throw;
  }
}

/**
 * @brief Destroy the Database::Database object
 *
 * @details Cleans up resources
 * @class   Database
 */
Database::~Database() {
  if (conn)
    env->terminateConnection(conn);
  if (env)
    Environment::terminateEnvironment(env);
  std::cout << "Database connection closed." << std::endl;
}

// * =============================================
// ? === / Database Constructor and destructor ===
// * =============================================

// * ==========================
// ? === Database functions ===
// * ==========================

/**
 * @brief ### Executes `INSERT|UPDATE|DELETE` SQL query and update the `affectedRow` count
 *
 * @class              Database
 * @param query        {const std::string &}
 * @param params       {const SqlParam &}
 * @param affectedRows {int &} -> Default:0
 */
void Database::execute(const std::string &query, const SqlParam &params, int &affectedRows) {
  affectedRows = 0; // Default to 0 affected rows

  try {
    // Prepare the statement
    Statement *stmt = conn->createStatement(query);

    // Set SQL params
    setSqlParams(stmt, params);

    // Execute the query (INSERT, UPDATE, DELETE)
    affectedRows = stmt->executeUpdate();

    // Clean up
    conn->terminateStatement(stmt);
  } catch (SQLException &e) {
    std::cerr << "Query Error: " << e.getMessage() << std::endl;
  }
}

/**
 * @brief ### Executes `SELECT` SQL query and return the `results`
 *
 * @class        Database
 * @param query  {const std::string &}
 * @param params {const SqlParam &}
 * @return       std::vector<std::vector<std::string>>
 */
std::vector<std::vector<std::string>> Database::execute(const std::string &query, const SqlParam &params) {
  std::vector<std::vector<std::string>> results;
  try {
    // Prepare the statement
    Statement *stmt = conn->createStatement(query);

    // Set SQL params
    setSqlParams(stmt, params);

    // * Execute the query
    ResultSet *rs = stmt->executeQuery();

    // Retrieve the results
    int columnCount = rs->getColumnListMetaData().size();
    while (rs->next()) {
      std::vector<std::string> row;
      for (int i = 1; i <= columnCount; ++i)
        row.push_back(rs->getString(i));
      results.push_back(row);
    }

    // Clean up
    stmt->closeResultSet(rs);
    conn->terminateStatement(stmt);
  } catch (SQLException &e) {
    std::cerr << "Query Error: " << e.getMessage() << std::endl;
  }

  return results; // Return the result
}

/**
 * @brief ### Set the SQL parameters into `stmt`
 *
 * @details      Helper function
 * @class        Database
 * @param stmt   {Statement *}
 * @param params {const SqlParam &}
 */
void Database::setSqlParams(Statement *stmt, const SqlParam &params) {
  // Bind integer parameters by name
  for (const std::pair<unsigned int, const int> &param : params.integers)
    stmt->setInt(param.first, param.second);

  // Bind string parameters by name
  for (const std::pair<unsigned int, const std::string> &param : params.strings)
    stmt->setString(param.first, param.second);
}

// * ============================
// ? === / Database functions ===
// * ============================