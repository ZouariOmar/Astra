/**
 * @file smtp-mail.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Send email with SMTP (header file)
 * @version 0.1
 * @date 2025-02-23
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/smtp-mail.cpp smtp-mail.cpp @endlink
 * @link https://raw.githubusercontent.com/curl/curl/master/docs/examples/smtp-mail.c smtp-mail.c @endlink
 */

/**
 * @brief ### How to use EmailSender object ?
 * ################################################
 * @example Simple example using EmailSender object
 * ################################################
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

// ? Pre-Processor prototype declaration part
#ifndef __SMTP_MAIL_HPP__
#define __SMTP_MAIL_HPP__

// ? Include prototype declaration part
// * Include std C++ header
#include <iostream>
#include <vector>

// * Include main libcurl header (.h)
#include <curl/curl.h>

// ? Structres prototype declaration part
struct EmailAuth {
  std::string from_addr,
      from_app_password,
      mail_server;
  explicit EmailAuth();
  explicit EmailAuth(const std::string, const std::string, const std::string _mail_server = std::getenv("MAIL_SERVER"));
}; // EmailAuth struct

struct EmailData {
  std::string
      to_addr,
      subject,
      body;
  std::vector<std::string>
      cc_addr,
      attachments;
  explicit EmailData(const std::string, const std::string, const std::string, const std::vector<std::string>, const std::vector<std::string>);
  explicit EmailData(const std::string, const std::string, const std::string);
}; // EmailData struct

// ? Classes prototype declaration part
class EmailSender {
public:
  explicit EmailSender(const EmailAuth);
  int send(EmailData);

private:
  EmailAuth *auth;
}; // EmailSender class

#endif // __SMTP_MAIL_HPP__