/**
 * @file      LoginUI.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     LoginUI source file
 * @version   0.1
 * @date      2025-02-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/LoginUI.cpp LoginUI.cpp @endlink
 */

// ? Include prototype declaration part
#include "../inc/LoginUI.hpp"
#include "../inc/EmailSender.hpp"
#include "../inc/HtmlBodyFormatter.hpp"
#include "../inc/PasswordGenerator.hpp"

// ? Function/Class prototype dev part

// * ========================================
// ? === Login constructor and destructor ===
// * ========================================

/**
 * @fn           LoginUI::LoginUI(QWidget *)
 * @brief        Construct a new LoginUI::LoginUI object
 * @param parent {QWidget *}
 */
LoginUI::LoginUI(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Login),
      gifTimer(new QTimer(this)),
      currentMovie(nullptr),
      currentGifIndex(0),
      gifPaths({
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an00.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an01.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an02.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an03.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an04.gif",
      }),
      generated_password(""),
      employee({}) {
  ui->setupUi(this);
  setWindowTitle("Astra"); // Set window title

  connect(gifTimer, &QTimer::timeout, this, &LoginUI::updateGif); // Set movieAnimation gif
  gifTimer->start(__LOGIN_GIF_ANIMATION__);

  // Install global events (make them detectable)
  ui->pushButton->installEventFilter(this);
  ui->reset->installEventFilter(this);
  ui->f_pwd->installEventFilter(this);

  ui->f_pwd_interface->hide();          // Hide the forget password QGroupBox
  ui->FaceRecognitionInterface->hide(); // Hide the face recognition QGroupBox
  updateGif();                          // Initialize the first GIF
}

/**
 * @fn    LoginUI::~LoginUI()
 * @brief Destroy the LoginUI::LoginUI object
 */
LoginUI::~LoginUI() {
  delete ui;
  ui = nullptr;
  delete gifTimer;
  gifTimer = nullptr;
  delete currentMovie;
  currentMovie = nullptr;
}

// * ==========================================
// ? === / Login constructor and destructor ===
// * ==========================================

/**
 * @fn      LoginUI::updateGif()
 * @brief   Update the Gif every `__LOGIN_GIF_ANIMATION__`
 * @details This change make a beautiful animation
 * @return  void
 */
void LoginUI::updateGif() {
  currentGifIndex = (currentGifIndex + 1) % gifPaths.size(); // Cycle through GIFs
  QMovie *newMovie = new QMovie(gifPaths[currentGifIndex]);

  newMovie->setScaledSize(ui->movieAnimation->size()); // Scale the GIF to match QLabel size
  ui->movieAnimation->setMovie(newMovie);              // Update QLabel

  if (currentMovie) // Delete the old movie after setting the new one
    delete currentMovie;
  currentMovie = newMovie;

  newMovie->start(); // Start the new movie
}

/**
 * @fn     LoginUI::on_pushButton_clicked()
 * @brief  Listen to Login button click action
 * @return void
 */
void LoginUI::on_pushButton_clicked() {
  std::string _username{ui->username->text().toStdString()},
      _password{ui->password->text().toStdString()};

  if (_username.empty() || _password.empty()) {
    QMessageBox::warning(
        this, tr("Astra"), tr("Username or password are empty!\n"
                              "Pleas fell the messing parts!"),
        QMessageBox::Ok);
    return;
  }

  Employees::Select *sl(new Employees::Select); // Assuming `Select` does not need to be dynamically allocated, we can use stack allocation.
  std::vector<SqlParam> res = sl->selectAll(    // Execute the select query with the given parameters.
      Employees::EmployeeInfo<std::string>(_username, Employees::EmployeeQueueFlags_strings::USERNAME),
      Employees::EmployeeInfo<std::string>(_password, Employees::EmployeeQueueFlags_strings::PASSWORD));
  delete sl;
  sl = nullptr;

  if (res.empty()) {      // Check if the result is empty
    QMessageBox::warning( // Show error message if the result is empty (i.e., login failed)
        this, tr("Astra"), tr("Username or password are incorrect!\nPlease try to login again!"),
        QMessageBox::Ok);
  } else {                  // Store the verified employee data and proceed to the next interface
    employee = res[0];      // Hold the verified employees data
    emit loginSuccessful(); // Emit the signal for successful login
  }
}

/**
 * @fn     LoginUI::get_employee()
 * @brief  Get verified employee data
 * @return {const SqlParam}
 */
const SqlParam LoginUI::get_employee() {
  return employee;
}

/**
 * @fn     LoginUI::on_faceId_clicked()
 * @brief  Listen to FaceID button click action
 * @return void
 */
void LoginUI::on_faceId_clicked() {
  QGroupBoxFadeOutEffect(ui->login, ui->FaceRecognitionInterface);

  faceRecognition = new FaceRecognizer;
  camTimer = new QTimer(this);

  static bool processing{}, // To avoid threads stack overflow (can cause Empty frame)
      loginCompleted{};     // To avoid threads infinite run

  if (loginCompleted) {
    std::cerr << "User already logged in!" << '\n';
    return; // Skip further threads
  }

  (void)QtConcurrent::run([this]() {
    faceRecognition->load();
    QMetaObject::invokeMethod(this, [this]() {
      connect(camTimer, &QTimer::timeout, this, [this]() {
        if (processing)
          return;
        processing = true;
        std::string username = faceRecognition->recognize(ui->Cam);
        // faceRecognition->captureFrame(ui->Cam); //! Debugin mode
        (void)QtConcurrent::run([this, username]() {
          // std::string username = faceRecognition->recognize(ui->Cam); //! It cause ORA-24550 error
          processing = false;
          if (username.empty())
            return;
          std::cerr << "username..." << username << '\n';
          Employees::Select *sl(new Employees::Select);
          std::vector<SqlParam> employees = sl->selectAll(Employees::EmployeeInfo<std::string>(username, Employees::EmployeeQueueFlags_strings::USERNAME));
          if (employees.empty()) { // The given `username` not found in the database
            std::cerr << "The given `username` not found in the database..." << username << '\n';
            return;
          }
          employee = employees[0];

          QMetaObject::invokeMethod(this, [this]() {
            on_fp_returnBtn_clicked();
            emit loginSuccessful();
          });
          loginCompleted = true;
        });
      });
      camTimer->start(__CAMERA_DEFAULT_FPS__);
    });
  });
}

void LoginUI::on_fp_returnBtn_clicked() {
  if (faceRecognition) {
    delete faceRecognition;
    faceRecognition = nullptr;
  }
  if (camTimer) {
    camTimer->stop();
    delete camTimer;
    camTimer = nullptr;
  }
  QGroupBoxFadeOutEffect(ui->FaceRecognitionInterface, ui->login);
}

// * ======================================
// ? === Events & Effects handling part ===
// * ======================================

/**
 * @fn          LoginUI::eventFilter(QObject *, QEvent *)
 * @brief       Manage global events in login interface
 * @param obj   {QObject *}
 * @param event {QEvent *}
 * @return      bool
 */
bool LoginUI::eventFilter(QObject *obj, QEvent *event) {
  if (obj == ui->pushButton) // ? Check if the event come form the login btn (login interface)
    return login_btn_events(obj, ui->lg, event);
  else if (obj == ui->reset && ui->reset->isEnabled()) // ? Check if the event come form the login btn (forget password interface)
    return login_btn_events(obj, ui->lg_2, event);
  else if (obj == ui->f_pwd) // ? Check if the object is the forget password label
    return forget_password_events(obj, event);
  return QWidget::eventFilter(obj, event);
}

/**
 * @fn          LoginUI::forget_password_events(QObject *, QEvent *)
 * @brief       Manage forget password events
 * @param obj   {QObject *}
 * @param event {QEvent *}
 * @return      bool
 */
bool LoginUI::forget_password_events(QObject *obj, QEvent *event) {
  switch (event->type()) {
  case QEvent::Enter:                                                                     // * OnEnter event
    return ui->f_pwd->setText("<font color='blue'><u>Forget Password?</u></font>"), true; // Blue & underline

  case QEvent::Leave:                                                               // * OnLeave event
    return ui->f_pwd->setText("<font color='white'>Forget Password?</font>"), true; // Reset color

  case QEvent::MouseButtonPress:
    return QGroupBoxFadeOutEffect(ui->login, ui->f_pwd_interface), true;

  default:
    return false;
  }

  return false; // Just to make compiler run (dummy)
}

/**
 * @fn          LoginUI::login_btn_events(QObject *, QLabel *, QEvent *)
 * @brief       Manage login button in the login/forgetPassword QGroups
 * @param obj   {QObject *}
 * @param icon  {QLabel *}
 * @param event {QEvent *}
 * @return      bool
 */
bool LoginUI::login_btn_events(QObject *obj, QLabel *icon, QEvent *event) {
  // Create animation object
  QPropertyAnimation *animation(new QPropertyAnimation(icon, "pos", this));
  animation->setDuration(1000);                      // 1s animation duration
  animation->setEasingCurve(QEasingCurve::OutCubic); // Smooth transition

  QPoint startPos = icon->pos(); // Get current position
  QPoint endPos;                 // Define target position

  if (event->type() == QEvent::Enter) {
    endPos = QPoint(__END_LG_Q_LABEL_X__, startPos.y()); // Move right
    ui->pushButton->setText("");                         // Remove login text on enter
  } else if (event->type() == QEvent::Leave) {
    endPos = QPoint(__START_LG_Q_LABEL_X__, startPos.y()); // Move left
    ui->pushButton->setText("Login");                      // Restore login text on leave
  } else
    return false; // Ignore other events

  animation->setStartValue(startPos);                      // Set start position
  animation->setEndValue(endPos);                          // Set end position
  animation->start(QAbstractAnimation::DeleteWhenStopped); // * Start & auto-delete
  return true;                                             // Event handled
}

/**
 * @fn           LoginUI::QGroupBoxFadeOutEffect(QGroupBox *, QGroupBox *)
 * @brief        Make a "fade out" effect to `group1` using opacity transition from `__FULL_VISIBLE__` to `__FULL_TRANSPARENT__` and hide `group1`, overwise for `group2`
 * @details      This effect work only with `QGroupBox`
 * @include      QGraphicsOpacityEffect | QPropertyAnimation
 * @param group1 {QGroupBox *}
 * @param group2 {QGroupBox *}
 * @return       void
 */
void LoginUI::QGroupBoxFadeOutEffect(QGroupBox *group1, QGroupBox *group2) {
  QPropertyAnimation *animation1 = FadeEffect(group1, __FULL_VISIBLE__, __FULL_TRANSPARENT__); // Fade out group1
  QPropertyAnimation *animation2 = FadeEffect(group2, __FULL_TRANSPARENT__, __FULL_VISIBLE__); // Fade in group2

  // Start both animations
  animation1->start(QAbstractAnimation::DeleteWhenStopped);
  animation2->start(QAbstractAnimation::DeleteWhenStopped);

  // Hide group1 and show group2 after the animation completes
  connect(animation1, &QPropertyAnimation::finished, [group1, group2]() {
    group1->hide(); // Hide group1 after it fades out
    group2->show(); // Show group2 after it fades in
  });
}

/**
 * @fn             LoginUI::FadeEffect(QGroupBox *, const QVariant, const QVariant)
 * @brief          Make fade In/Out for `group`
 * @param group    {QGroupBox *}
 * @param startVal {const QVariant}
 * @param endVal   {const QVariant}
 * @return         {QPropertyAnimation *}
 */
QPropertyAnimation *LoginUI::FadeEffect(QGroupBox *group, const QVariant startVal, const QVariant endVal) {
  QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(group);
  group->setGraphicsEffect(effect);

  // Create animation object
  QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
  animation->setDuration(1000);                      // 1s animation duration
  animation->setEasingCurve(QEasingCurve::OutCubic); // Smooth transition

  animation->setStartValue(startVal);
  animation->setEndValue(endVal);

  return animation;
}

/**
 * @fn      LoginUI::on_returnBtn_clicked()
 * @brief   Listen to Return button click action
 * @details This button is included inside the `f_pwd_interface` QGroupBox
 * @return  void
 */
void LoginUI::on_returnBtn_clicked() {
  enableResetPassword(false);
  clearResetPassword();
  QGroupBoxFadeOutEffect(ui->f_pwd_interface, ui->login); // Redirect the user to login QGroupBox
}

/**
 * @fn      LoginUI::on_hide_show_btn_clicked()
 * @brief   Listen to `hide_show_btn` click action
 * @details Change the echomode of the `QLineEdit` & the button icon of `QPushButton`
 * @return  void
 */
void LoginUI::on_hide_show_btn_clicked() {
  (ui->charCode->echoMode() == QLineEdit::Normal) ? change_hideShowBtnIcon(ui->charCode, ui->hide_show_btn) : change_hideShowBtnIcon(ui->charCode, ui->hide_show_btn, QLineEdit::Normal, "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/eye.png");
}

/**
 * @fn      LoginUI::on_hide_show_btn_2_clicked()
 * @brief   Listen to `hide_show_btn` click action
 * @details Change the echomode of the `QLineEdit` & the button icon of `QPushButton`
 * @return  void
 */
void LoginUI::on_hide_show_btn_2_clicked() {
  (ui->password->echoMode() == QLineEdit::Normal) ? change_hideShowBtnIcon(ui->password, ui->hide_show_btn_2) : change_hideShowBtnIcon(ui->password, ui->hide_show_btn_2, QLineEdit::Normal, "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/eye.png");
}

/**
 * @fn             LoginUI::change_hideShowBtnIcon(QLineEdit *, QPushButton *, const QLineEdit::EchoMode, const QString)
 * @brief          Helper function
 * @details        this->on_hide_show_btn_clicked() | this->on_hide_show_btn_clicked()
 * @param lineEdit {QLineEdit *}
 * @param btn      {QPushButton *}
 * @param mode     {const QLineEdit::EchoMode}
 * @param path     {const QString}
 * @return         void
 */
void LoginUI::change_hideShowBtnIcon(QLineEdit *lineEdit, QPushButton *btn, const QLineEdit::EchoMode mode, const QString path) {
  btn->setIcon(QIcon(path));
  lineEdit->setEchoMode(mode);
}

/**
 * @fn     LoginUI::on_sendEmailBtn_clicked()
 * @brief  Verify the given mail and send a 6-chars reset code to reset the password
 * @return void
 */
void LoginUI::on_sendEmailBtn_clicked() {
  std::string _email{ui->email->text().toStdString()}; // Hold the input it email

  // Select user information using 'email'
  Employees::Select *sl(new Employees::Select);
  std::vector<SqlParam> employee = sl->selectAll(Employees::EmployeeInfo<std::string>(_email, Employees::EmployeeQueueFlags_strings::EMAIL));
  delete sl;
  sl = nullptr;

  if (employee.empty()) {
    QMessageBox::warning(this, tr("Astra"),
                         tr("This Email doesn't exist!"),
                         QMessageBox::Ok);
    return;
  }

  QProgressDialog *progressDialog = new QProgressDialog("Sending password reset email...", "Cancel", 0, 0, this);
  progressDialog->setWindowTitle("Processing...");
  progressDialog->setWindowModality(Qt::WindowModal);
  progressDialog->setCancelButton(nullptr);
  progressDialog->setMinimumDuration(0);
  progressDialog->show();

  (void)QtConcurrent::run([this, _email, employee, progressDialog]() {
    try {
      generated_password = PasswordGenerator::generate();
      EmailSender email{EmailAuth{}};
      email.send(EmailData(
          _email,
          "Astra: Password Reset Request",
          HtmlBodyFormater("/home/zouari_omar/Documents/Daily/Projects/Astra/project/html/forget_password_template.html",
                           {
                               {"{{name}}", employee[0].strings[Employees::EmployeeQueueFlags_strings::FIRSTNAME].second},
                               {"{{prename}}", employee[0].strings[Employees::EmployeeQueueFlags_strings::LASTNAME].second},
                               {"{{password}}", generated_password},
                           })
              .get_inner_html()));

      // Update the UI after sending the email
      QMetaObject::invokeMethod(progressDialog, [progressDialog]() {
            progressDialog->close();
            progressDialog->deleteLater();  // Ensure deletion happens in the main thread
            QMessageBox::information(progressDialog->parentWidget(), "Success", "Email sent successfully!"); }, Qt::QueuedConnection);
      enableResetPassword(true);
    } catch (const std::exception &e) {
      QMetaObject::invokeMethod(progressDialog, [progressDialog, e]() {
            progressDialog->close();
            progressDialog->deleteLater();  // Ensure deletion happens in the main thread
            QMessageBox::critical(progressDialog->parentWidget(), "Error", QString("Failed to send email: ") + e.what()); }, Qt::QueuedConnection);
    }
  });
}

/**
 * @fn     LoginUI::on_reset_clicked()
 * @brief  Verify the taped code and new/confirm password
 * @return void
 */
void LoginUI::on_reset_clicked() {
  if (ui->charCode->text().isEmpty() || ui->newPassword->text().isEmpty() || ui->confirmPassword->text().isEmpty()) {
    std::cerr << "Error: field(s) is/are empty!" << std::endl;
    return;
  }

  if (ui->charCode->text().toStdString() != generated_password) {
    std::cerr << "Error: Wrong 6-characters-code!" << std::endl;
    return;
  }

  if (ui->newPassword->text() != ui->confirmPassword->text()) {
    std::cerr << "Error: Pls verify new/confirm passwords!" << std::endl;
    return;
  }

  // Update password and redirect the usr to login QGroup box
  Employees::Update up{Employees::Update()};
  up.update(Employees::EmployeeInfo(ui->confirmPassword->text().toStdString(), Employees::EmployeeQueueFlags_strings::PASSWORD), Employees::EmployeeInfo(ui->email->text().toStdString(), Employees::EmployeeQueueFlags_strings::EMAIL));
  QMessageBox::information(this, tr("Success"),
                           tr("Your password have been changed successfully!"),
                           QMessageBox::Ok);
  enableResetPassword(false);
  clearResetPassword();
  QGroupBoxFadeOutEffect(ui->f_pwd_interface, ui->login); // Redirect the user to login QGroupBox
}

// * ========================================
// ? === / Events & Effects handling part ===
// ? ======== Helpers handling part =========
// * ========================================

/**
 * @fn           LoginUI::enableResetPassword(const bool &)
 * @brief        Reset the forget password QGroupBox to the default view (enable/disable proccess)
 * @param status {const bool &}
 * @return       void
 */
void LoginUI::enableResetPassword(const bool &status) {
  ui->email->setEnabled(!status);
  ui->sendEmailBtn->setEnabled(!status);
  ui->usr_2->setEnabled(!status);
  ui->charCode->setEnabled(status);
  ui->hide_show_btn->setEnabled(status);
  ui->lock_3->setEnabled(status);
  ui->newPassword->setEnabled(status);
  ui->confirmPassword->setEnabled(status);
  ui->reset->setEnabled(status);
  ui->lg_2->setEnabled(status);
}

/**
 * @fn     LoginUI::clearResetPassword()
 * @brief  Reset all forget password QLineEdit's to the default state (empty)
 * @return void
 */
void LoginUI::clearResetPassword() {
  ui->email->setText("");
  ui->charCode->setText("");
  ui->newPassword->setText("");
  ui->confirmPassword->setText("");
}

// * ==========================================
// ? ======== / Helpers handling part =========
// * ==========================================
