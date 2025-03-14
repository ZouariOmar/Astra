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

/**
 * @brief ### Construct a new SqlParam::SqlParam object
 *
 * @struct                 SqlParam
 * @param strParams        {const std::vector<std::pair<unsigned int, const std::string>> &}
 * @param intParams        {const std::vector<std::pair<unsigned int, const int>> &}
 * @param timestampsParams {const std::vector<std::pair<unsigned int, const oracle::occi::Timestamp>> &}
 * @param blobsParams      {const std::vector<std::pair<unsigned int, const oracle::occi::Blob>>}
 */
SqlParam::SqlParam(const std::vector<std::pair<unsigned int, std::string>> &strParams,
                   const std::vector<std::pair<unsigned int, int>> &intParams,
                   const std::vector<std::pair<unsigned int, oracle::occi::Date>> &dateParams,
                   const std::vector<std::pair<unsigned int, oracle::occi::Timestamp>> &timestampsParams,
                   const std::vector<std::pair<unsigned int, std::vector<unsigned char>>> &blobsParams)
    : strings(strParams),
      integers(intParams),
      dates(dateParams),
      timestamps(timestampsParams),
      blobs(blobsParams) {};

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
  Statement *stmt = nullptr;

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
 * @brief ### Executes `SELECT` SQL query and return the `results`
 *
 * @class        Database
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

        case OCCI_SQLT_BLOB: {
          oracle::occi::Blob blob = rs->getBlob(i);

          if (blob.isNull()) // * For: ORA-32114: Cannot perform operation on a null LOB
            break;

          blob.open(OCCI_LOB_READONLY);

          std::vector<unsigned char> blobData(blob.length());
          blob.read(blob.length(), blobData.data(), blob.length());
          blob.close();

          row.blobs.emplace_back(i, blobData); // Store as std::vector<unsigned char>
          break;
        }

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
 * @brief ### Set the SQL parameters into `stmt`
 *
 * @details      Helper function
 * @class        Database
 * @param stmt   {Statement *}
 * @param params {const SqlParam &}
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

  for (const auto &param : params.blobs) {
    try {
      oracle::occi::Blob blob(conn); // Create a temporary BLOB
      blob.open(OCCI_LOB_READWRITE);
      blob.write(param.second.size(), (unsigned char *)param.second.data(), param.second.size());
      blob.close();

      stmt->setBlob(param.first, blob);
    } catch (SQLException &e) {
      std::cerr << "BLOB Binding Error: " << e.getMessage() << std::endl;
    }
  }
}

// * ============================
// ? === / Database functions ===
// * ============================