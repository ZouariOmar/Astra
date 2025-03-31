/**
 * @file      Database.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     Database source file
 * @version   0.1
 * @date      2025-02-13
 * @copyright Copyright (c) 2025
 * @link https://www.oracle.com oracle @endlink
 */

//? Include prototype declaration part
#include "../inc/Database.hpp"

//? Function/Class prototype dev part

/**
 * @fn                     SqlParam::SqlParam(const std::vector<std::pair<unsigned int, std::string>> &, const std::vector<std::pair<unsigned int, int>> &, const std::vector<std::pair<unsigned int, oracle::occi::Date>> &, const std::vector<std::pair<unsigned int, oracle::occi::Timestamp>> &)
 * @brief                  Construct a new SqlParam::SqlParam object
 * @param strParams        {const std::vector<std::pair<unsigned int, std::string>> &}
 * @param intParams        {const std::vector<std::pair<unsigned int, int>> &}
 * @param dateParams       {const std::vector<std::pair<unsigned int, oracle::occi::Date>> &}
 * @param timestampsParams {const std::vector<std::pair<unsigned int, oracle::occi::Timestamp>> &}
 */
SqlParam::SqlParam(const std::vector<std::pair<unsigned int, std::string>> &strParams,
                   const std::vector<std::pair<unsigned int, int>> &intParams,
                   const std::vector<std::pair<unsigned int, oracle::occi::Date>> &dateParams,
                   const std::vector<std::pair<unsigned int, oracle::occi::Timestamp>> &timestampsParams)
    : strings(strParams),
      integers(intParams),
      dates(dateParams),
      timestamps(timestampsParams) {};

/**
 * @fn      Database
 * @brief   Construct a new Database::Database object
 * @details Use the ENV session export it vars
 */
Database::Database()
    : Database(
          getenv("oracle_username") ? getenv("oracle_username") : "",
          getenv("oracle_password") ? getenv("oracle_password") : "",
          getenv("oracle_database") ? getenv("oracle_database") : "") {
}

/**
 * @fn             Database
 * @brief          Construct a new Database::Database object
 * @param username {const char *}
 * @param password {const char *}
 * @param database {const char *}
 */
Database::Database(const char *username, const char *password, const char *database)
    : env(nullptr), conn(nullptr) {
  try {
    env = Environment::createEnvironment(Environment::DEFAULT);
    conn = env->createConnection(username, password, database);
    std::cout << "Connected to Oracle Database! " << std::endl;
  } catch (SQLException &e) {
    std::cerr << "Connection Error: " << e.getMessage() << std::endl;
    throw;
  }
}

/**
 * @fn      Database::~Database()
 * @brief   Destroy the Database::Database object
 * @details Cleans up resources
 */
Database::~Database() {
  if (conn)
    env->terminateConnection(conn);
  if (env)
    Environment::terminateEnvironment(env);
  conn = nullptr;
  env = nullptr;
  std::cout << "Database connection closed." << std::endl;
}

/**
 * @fn                 Database::execute(const std::string &, const SqlParam &, int &)
 * @brief              Executes `INSERT|UPDATE|DELETE` SQL query and update the `affectedRow` count
 * @param query        {const std::string &}
 * @param params       {const SqlParam &}
 * @param affectedRows {int &} -> Default:0
 * @return             void
 */
void Database::execute(const std::string &query, const SqlParam &params, int &affectedRows) {
  affectedRows = 0; // Default to 0 affected rows
  Statement *stmt(nullptr);

  try {
    // Prepare the statement
    stmt = conn->createStatement(query);

    // Set SQL params
    setSqlParams(stmt, params);

    // Execute the query (INSERT, UPDATE, DELETE)
    affectedRows = stmt->executeUpdate();

    // Commit the transaction (optional, depending on your DB settings)
    conn->commit();
  } catch (const SQLException &e) {
    std::cerr << "Query Error: " << e.getMessage() << std::endl;

    // Rollback transaction in case of error
    try {
      conn->rollback();
    } catch (const SQLException &rollbackErr) {
      std::cerr << "Rollback Error: " << rollbackErr.getMessage() << std::endl;
    }

    throw; // Re-throw the exception so the caller can handle it
  }

  // Ensure stmt is cleaned up even if an error occurs
  if (stmt)
    conn->terminateStatement(stmt);
}

/**
 * @fn           Database::execute(const std::string &, const SqlParam &)
 * @brief        Executes `SELECT` SQL query and return the `results`
 * @param query  {const std::string &}
 * @param params {const SqlParam &}
 * @return       std::vector<std::vector<std::string>>
 */
std::vector<SqlParam> Database::execute(const std::string &query, const SqlParam &params) {
  std::vector<SqlParam> results;

  try {
    Statement *stmt = conn->createStatement(query);
    setSqlParams(stmt, params);
    ResultSet *rs = stmt->executeQuery();

    std::vector<MetaData> columnsMetaData = rs->getColumnListMetaData();
    int columnCount = columnsMetaData.size();

    while (rs->next()) {
      SqlParam row;

      for (int i = 1; i <= columnCount; ++i) {
        MetaData columnMetaData = columnsMetaData[i - 1];
        int dataType = columnMetaData.getInt(MetaData::ATTR_DATA_TYPE);

        switch (dataType) {
        case OCCI_SQLT_NUM:
          row.integers.emplace_back(i, rs->getInt(i));
          break;

        case OCCI_SQLT_CHR:
        case OCCI_SQLT_VCS:
          row.strings.emplace_back(i, rs->getString(i));
          break;

        case OCCI_SQLT_DAT:
          row.dates.emplace_back(i, rs->getDate(i)); // Fetch and store as Date
          break;

        case OCCI_SQLT_TIMESTAMP: // Handling TIMESTAMP
          row.timestamps.emplace_back(i, rs->getTimestamp(i));
          break;

        default:
          std::cerr << "Unknown data type encountered: " << dataType << std::endl;
        }
      }

      results.push_back(row);
    }

    stmt->closeResultSet(rs);
    conn->terminateStatement(stmt);
  } catch (SQLException &e) {
    std::cerr << "Query Error: " << e.getMessage() << std::endl;
  }

  return results;
}

/**
 * @fn           Database::setSqlParams(Statement *, const SqlParam &)
 * @brief        Set the SQL parameters into `stmt`
 * @details      Helper function
 * @param stmt   {Statement *}
 * @param params {const SqlParam &}
 * @return       void
 */
void Database::setSqlParams(Statement *stmt, const SqlParam &params) {
  for (const auto &param : params.integers)
    stmt->setInt(param.first, param.second);

  for (const auto &param : params.strings)
    stmt->setString(param.first, param.second);

  for (const auto &param : params.dates)
    stmt->setDate(param.first, param.second);

  for (const auto &param : params.timestamps)
    stmt->setTimestamp(param.first, param.second);
}