/**
 * @file connect.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Oracle-db connection source file
 * @version 0.1
 * @date 2025-02-13
 * @copyright Copyright (c) 2025
 * @link https://www.oracle.com oracle @endlink
 */

//? Include prototype declaration part
#include "../inc/connect.hpp"

// ? Function/Class prototype dev part

/**
 * @brief ### Construct a new Database::Database object
 * @details Use the session export it vars
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
 * @param user {const string &}
 * @param pass {const string &}
 * @param db {const string &}
 */
Database::Database(const char *username, const char *password, const char *database) {
  try {
    env = Environment::createEnvironment(Environment::DEFAULT);
    conn = env->createConnection(username, password, database);
    cout << "Connected to Oracle Database!" << endl;
  } catch (SQLException &e) {
    cerr << "Connection Error: " << e.getMessage() << endl;
    throw;
  }
}

/**
 * @brief Destroy the Database::Database object
 * @details Cleans up resources
 */
Database::~Database() {
  if (conn)
    env->terminateConnection(conn);
  if (env)
    Environment::terminateEnvironment(env);
  cout << "Database connection closed." << endl;
}

/**
 * @brief ### Executes any SQL query and returns the result (SELECT) or affected row count (INSERT/UPDATE/DELETE)
 *
 * @param query {const string &}
 * @param affectedRows {int &}
 * @return vector<vector<string>>
 */
vector<vector<string>> Database::execute(const string &query, int &affectedRows) {
  vector<vector<string>> results;
  affectedRows = 0; // Default to 0 affected rows

  try {
    Statement *stmt = conn->createStatement(query);

    // Check if it's a SELECT query
    if (query.find("SELECT") == 0 || query.find("select") == 0) {
      ResultSet *rs = stmt->executeQuery();
      int columnCount = rs->getColumnListMetaData().size();

      while (rs->next()) {
        vector<string> row;
        for (int i = 1; i <= columnCount; ++i)
          row.push_back(rs->getString(i));
        results.push_back(row);
      }

      stmt->closeResultSet(rs);
    } else
      affectedRows = stmt->executeUpdate(); // For INSERT, UPDATE, DELETE queries

    conn->terminateStatement(stmt);
  } catch (SQLException &e) {
    cerr << "Query Error: " << e.getMessage() << endl;
  }

  return results;
}