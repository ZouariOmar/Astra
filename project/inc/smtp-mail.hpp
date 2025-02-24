/**
 * @file smtp-mail.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Send email with SMTP (header file)
 * @version 0.1
 * @date 2025-02-23
 * @copyright Copyright (c) 2025
 * @link https://raw.githubusercontent.com/curl/curl/master/docs/examples/smtp-mail.c @endlink
 * @note `FROM_ADDR` must not be empty or have oly spaces
 */

// ? Pre-Processor prototype declaration part
#ifndef __SMTP_MAIL_HPP__
#define __SMTP_MAIL_HPP__

// ? Include prototype declaration part
// * Include std header (.h)
#include <iostream>
#include <stdio.h>
#include <string.h>

// * Include main libcurl header (.h)
#include <curl/curl.h>

// ? Public vars declaration part
// extern const char *payload_text;

// ? Structres prototype declaration part
struct upload_status {
  size_t bytes_read;
}; // upload_status struct

struct Email_ls {
  const char *from_addr,
      *from_app_password,
      *to_addr,
      *cc_addr,
      *subject,
      *body,
      *mail_server,
      *attachment_path;
  Email_ls(const char *, const char *, const char *, const char *, const char *, const char *, const char *, const char *);
  Email_ls(const char *, const char *, const char *, const char *);
  Email_ls(const char *, const char *, const char *);
}; // Email_ls struct

// ? Functions prototype declaration part
// size_t payload_source(char *, size_t, size_t, void *);

int sendEmail();

// ? Classes prototype declaration part
class Email {
private:
  static char *payload_text;
  static size_t payload_source(char *, size_t, size_t, void *);
  bool isOnlySpaces(const char *);
  const char
      *MAIL_SERVER,
      *FROM_ADDR,
      *FROM_APP_PASSWORD,
      *TO_ADDR,
      *CC_ADDR;

public:
  explicit Email(const Email_ls);
  int sendEmail();
  ~Email();

}; // Email class

#endif // __SMTP_MAIL_HPP__