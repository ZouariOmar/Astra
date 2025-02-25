/**
 * @file smtp-mail.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Send email with SMTP (source file)
 * @version 0.1
 * @date 2025-02-23
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/smtp-mail.cpp smtp-mail.cpp @endlink
 * @link https://raw.githubusercontent.com/curl/curl/master/docs/examples/smtp-mail.c smtp-mail.c @endlink
 * See @link https://curl.se/libcurl/c/curl_mime_type.html "In the absence of a mime type!" @endlink
 */

//? Include prototype declaration part
#include "../inc/smtp-mail.hpp"

//? Function/Class prototype dev part

/**
 * @brief ### Construct a new EmailAuth::EmailAuth object
 *
 * @struct EmailAuth
 */
EmailAuth::EmailAuth()
    : from_addr(getenv("ASTRA_ADDR")),
      from_app_password(getenv("ASTRA_APP_PASSWORD")),
      mail_server(getenv("MAIL_SERVER")) {
}

/**
 * @brief ### Construct a new EmailAuth::EmailAuth object
 *
 * @struct                       EmailAuth
 * @param _from_addr             {const std::string}
 * @param _from_app_app_password {const std::string}
 * @param _mail_server           {const std::string}
 */
EmailAuth::EmailAuth(const std::string _from_addr, const std::string _from_app_app_password, const std::string _mail_server)
    : from_addr(_from_addr),
      from_app_password(_from_app_app_password),
      mail_server(_mail_server) {
}

/**
 * @brief ### Construct a new EmailData::EmailData object
 *
 * @struct         EmailAuth
 * @param _to_addr {const std::string}
 * @param _subject {const std::string}
 * @param _body    {const std::string}
 */
EmailData::EmailData(const std::string _to_addr, const std::string _subject, const std::string _body)
    : to_addr(_to_addr),
      subject(_subject),
      body(_body), cc_addr({}),
      attachments({}) {
}

/**
 * @brief ### Construct a new EmailData::EmailData object
 *
 * @struct             EmailAuth
 * @param _to_addr     {const std::string}
 * @param _subject     {const std::string}
 * @param _body        {const std::string}
 * @param _cc_addr     {const std::vector<std::string>}
 * @param _attachments {const std::vector<std::string>}
 */
EmailData::EmailData(const std::string _to_addr, const std::string _subject, const std::string _body, const std::vector<std::string> _cc_addr, const std::vector<std::string> _attachments)
    : to_addr(_to_addr),
      subject(_subject),
      body(_body), cc_addr(_cc_addr),
      attachments(_attachments) {
}

/**
 * @brief ### Construct a new EmailSender::EmailSender object
 *
 * @class            EmailSender
 * @param _emailAuth EmailAuth
 */
EmailSender::EmailSender(const EmailAuth _emailAuth)
    : auth(new EmailAuth(_emailAuth)) {
}

/**
 * @brief ### Send the given data using SMTP protocol (support it with libcurl)
 *
 * @class      EmailSender
 * @param data EmailData
 * @return int
 */
int EmailSender::send(EmailData data) {
  // Init part
  CURL *curl{nullptr};
  CURLcode res{CURLE_OK};
  curl_slist *recipients = nullptr;
  curl_slist *headers = nullptr;
  curl_mime *mime{nullptr};
  curl_mimepart *part{nullptr};
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    // ================================================
    // === Security configuration and debuging part ===
    // ================================================

    /*
     * This is the URL for your mailserver. Note the use of smtps:// rather
     * than smtp:// to request a SSL based connection.
     * We use Google mailserver
     */
    curl_easy_setopt(curl, CURLOPT_URL, auth->mail_server.c_str());

    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, auth->from_addr.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, auth->from_app_password.c_str());
    delete auth; // No need for the authorisation data
    auth = nullptr;

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
    // curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);

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
     * Since the traffic is encrypted, it is useful to turn on debug
     * information within libcurl to see what is happening during the
     * transfer
     */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // ==================================================
    // === / Security configuration and debuging part ===
    // ==================================================

    // ==============================================
    // === Email Data preparation && holding part ===
    // ==============================================

    // Add email headers(From & To & Cc & Subject)
    headers = curl_slist_append(headers, "From: Sender <sender@example.com>");     // !
    headers = curl_slist_append(headers, "To: Recipient <recipient@example.com>"); // !
    headers = curl_slist_append(headers, "Cc: <omar@example.com>");                // !
    headers = curl_slist_append(headers, "Subject: Test Email with Subject");      // !
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Add primary recipient
    recipients = curl_slist_append(recipients, data.to_addr.c_str());

    // Add CC recipients
    for (std::string &ccRecipient : data.cc_addr)
      recipients = curl_slist_append(recipients, ccRecipient.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    // Initialize MIME structure
    mime = curl_mime_init(curl);

    // Add body
    part = curl_mime_addpart(mime);
    curl_mime_data(part, data.body.c_str(), CURL_ZERO_TERMINATED);
    curl_mime_type(part, "text/html"); // Set content type to HTML

    // Add attachments
    for (std::string &attachment : data.attachments) {
      part = curl_mime_addpart(mime);
      curl_mime_filedata(part, attachment.c_str());
      // curl_mime_type(part, "image/png"); 
      curl_mime_encoder(part, "base64"); // ? Ensures Safe Delivery (Avoids data loss or character misinterpretation because SMTP only supports 7-bit ASCII text)
      curl_mime_filename(part, attachment.c_str());
    }

    // Set MIME for the email
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

    // ================================================
    // === / Email Data preparation && holding part ===
    // ================================================

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    (res != CURLE_OK) ? std::cerr << "Email send failed: " << curl_easy_strerror(res) << std::endl : std::cout << "Email sent successfully!" << std::endl;

    // Clean up proccess
    curl_slist_free_all(recipients); /* Free the list of recipients */
    curl_slist_free_all(headers);
    curl_mime_free(mime);
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

  curl_global_cleanup();

  return int(res);
}