/**
 * @file smtp-mail.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Send email with SMTP (source file)
 * @version 0.1
 * @date 2025-02-23
 * @copyright Copyright (c) 2025
 * @link https://raw.githubusercontent.com/curl/curl/master/docs/examples/smtp-mail.c @endlink
 */

//? Include prototype declaration part
#include "../inc/smtp-mail.hpp"

/**
 * @brief ### Construct a new Email_ls::Email_ls object
 *
 * @struct Email_ls
 * @param _from_addr {const char *}
 * @param _from_app_password {const char *}
 * @param _to_addr {const char *}
 * @param _cc_addr {const char *}
 * @param _subject {const char *}
 * @param _body {const char *}
 * @param _mail_server {const char *}
 */
Email_ls::Email_ls(const char *_from_addr,
                   const char *_from_app_password,
                   const char *_to_addr,
                   const char *_cc_addr,
                   const char *_subject,
                   const char *_body,
                   const char *_attachment_path,
                   const char *_mail_server)
    : from_addr(_from_addr),
      from_app_password(_from_app_password),
      to_addr(_to_addr),
      cc_addr(_cc_addr),
      subject(_subject),
      body(_body),
      attachment_path(_attachment_path),
      mail_server(_mail_server) {
}

/**
 * @brief ### Construct a new Email_ls::Email_ls object
 *
 * @struct Email_ls
 * @param _to_addr {const char *}
 * @param _cc_addr {const char *}
 * @param _subject {const char *}
 * @param _body {const char *}
 */
Email_ls::Email_ls(const char *_to_addr,
                   const char *_cc_addr,
                   const char *_subject,
                   const char *_body)
    : from_addr(getenv("ASTRA_ADDR")),
      from_app_password(getenv("ASTRA_APP_PASSWORD")),
      mail_server(getenv("MAIL_SERVER")),
      to_addr(_to_addr),
      cc_addr(_cc_addr),
      subject(_subject),
      body(_body) {
}

Email_ls::Email_ls(const char *_to_addr,
                   const char *_subject,
                   const char *_body)
    : from_addr(getenv("ASTRA_ADDR")),
      from_app_password(getenv("ASTRA_APP_PASSWORD")),
      mail_server(getenv("MAIL_SERVER")),
      to_addr(_to_addr),
      cc_addr(nullptr),
      subject(_subject),
      body(_body) {
}

char *Email::payload_text = nullptr;

Email::Email(const Email_ls email_list)
    : MAIL_SERVER(email_list.mail_server), FROM_ADDR(email_list.from_addr), FROM_APP_PASSWORD(email_list.from_app_password), TO_ADDR(email_list.to_addr), CC_ADDR(email_list.cc_addr) {
  if (!payload_text) {
    payload_text = new char[2048];
  }

  sprintf(payload_text, "Date: " __DATE__ "\r\n"
                        "To: A Receiver <%s> \r\n"
                        "From: Sender Person <%s>\r\n"
                        "Cc: <%s>\r\n"
                        "Subject: %s\r\n"
                        "MIME-Version: 1.0\r\n"
                        "Content-Type: multipart/mixed; boundary=\"boundary\"\r\n\r\n"
                        "--boundary\r\n"
                        "Content-Type: text/plain; charset=UTF-8\r\n"
                        "\r\n" /* empty line to divide headers from body, see RFC 5322 */
                        "%s\r\n"
                        "--boundary\r\n"
                        "Content-Type: application/octet-stream\r\n"
                        "Content-Transfer-Encoding: base64\r\n"
                        "Content-Disposition: attachment; filename=%s"
                        "\r\n"
                        "--boundary--",
          email_list.to_addr,
          email_list.from_addr,
          email_list.cc_addr,
          email_list.subject,
          email_list.body,
          "");

  std::cout << payload_text << std::endl;
}

Email::~Email() {
  delete[] payload_text;
  payload_text = nullptr;
}

bool Email::isOnlySpaces(const char *str) {
  while (*str) { // While we haven't reached the end of the string
    if (*str != ' ')
      return false;
    ++str;
  }

  return true; // All characters were spaces or the string was empty
}

/**
 * @brief ###
 *
 * @param ptr {char *}
 * @param size size_t
 * @param nmem size_t
 * @param userp {void *} => {struct upload_status *}
 * @return size_t
 */
size_t Email::payload_source(char *ptr, size_t size, size_t nmemb, void *userp) {
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;
  size_t room = size * nmemb;

  if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1))
    return 0;

  data = &payload_text[upload_ctx->bytes_read];

  if (data) {
    size_t len = strlen(data);
    if (room < len)
      len = room;
    memcpy(ptr, data, len);
    upload_ctx->bytes_read += len;

    return len;
  }

  return 0;
}

/**
 * @brief ### Main sender mail
 *
 * @return int
 */
int Email::sendEmail() {
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx = {0};

  curl = curl_easy_init();
  if (curl) {
    /*
     * This is the URL for your mailserver. Note the use of smtps:// rather
     * than smtp:// to request a SSL based connection.
     * We use Google mailserver */
    curl_easy_setopt(curl, CURLOPT_URL, MAIL_SERVER); // Using SSL Port

    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, FROM_ADDR);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, FROM_APP_PASSWORD);

    // Add SSL security layer
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    /*
     * If you want to connect to a site who is not using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

    /*
     * If the site you are connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl refuses to connect. You can skip this
     * check, but it makes the connection insecure
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    /*
     * Note that this option is not strictly required, omitting it results in
     * libcurl sending the MAIL FROM command with empty sender data. All
     * autoresponses should have an empty reverse-path, and should be directed
     * to the address in the reverse-path which triggered them. Otherwise,
     * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
     * details.
     * Most SMTP servers (especially Gmail) force the "From" address to be the authenticated user for security reasons.
     ! Gmail forces the "From" field to match this authenticated account. This is a security measure to prevent email spoofing.
     */
    // curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);

    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, TO_ADDR);
    if (CC_ADDR && strlen(CC_ADDR) && !isOnlySpaces(CC_ADDR)) // CC_ADDR not nullptr, not empty, doesn't contain only spaces
      recipients = curl_slist_append(recipients, CC_ADDR);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /* We are using a callback function to specify the payload (the headers and
     * body of the message). You could just use the CURLOPT_READDATA option to
     * specify a FILE pointer to read from. */
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    /*
     * Since the traffic is encrypted, it is useful to turn on debug
     * information within libcurl to see what is happening during the
     * transfer */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Free the list of recipients */
    curl_slist_free_all(recipients);

    /* curl does not send the QUIT command until you call cleanup, so you
     * should be able to reuse this connection for additional messages
     * (setting CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and
     * calling curl_easy_perform() again. It may not be a good idea to keep
     * the connection open for a long time though (more than a few minutes may
     * result in the server timing out the connection), and you do want to
     * clean up in the end.
     */
    curl_easy_cleanup(curl);
  }

  return (int)res;
}
