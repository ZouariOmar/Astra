/**
 * @file login.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Login source file
 * @version 0.1
 * @date 2025-02-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/login.cpp @endlink
 */

// ? Include prototype declaration part
#include "../inc/login.hpp"
#include "../inc/passwordGen.hpp"
#include "../inc/smtp-mail.hpp"

// ? Function/Class prototype dev part

// * ========================================
// ? === Login constructor and destructor ===
// * ========================================

/**
 * @brief ### Construct a new Login::Login object
 *
 * @class        Login
 * @param parent {QWidget *}
 */
Login::Login(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Login),
      gifPaths({
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an00.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an01.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an02.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an03.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an04.gif",
      }),
      currentGifIndex(0),
      gifTimer(new QTimer(this)),
      currentMovie(nullptr),
      generated_password("") {
  ui->setupUi(this);
  setWindowTitle("Astra"); // Set window title

  connect(gifTimer, &QTimer::timeout, this, &Login::updateGif); // Set movieAnimation gif
  gifTimer->start(__LOGIN_GIF_ANIMATION__);

  // Install global events (make them detectable)
  ui->pushButton->installEventFilter(this);
  ui->reset->installEventFilter(this);
  ui->f_pwd->installEventFilter(this);

  ui->f_pwd_interface->hide(); // Hide the forget password QGroupBox

  updateGif(); // Initialize the first GIF
}

/**
 * @brief ### Destroy the Login::Login object
 *
 * @class Login
 */
Login::~Login() {
  delete ui;
  delete gifTimer;
  delete currentMovie;
}

// * ==========================================
// ? === / Login constructor and destructor ===
// * ==========================================

/**
 * @brief ### Update the Gif every `__LOGIN_GIF_ANIMATION__`
 *
 *
 * @details This change make a beautiful animation
 * @class   Login
 * @return  void
 */
void Login::updateGif() {
  currentGifIndex = (currentGifIndex + 1) % gifPaths.size(); // Cycle through GIFs
  QMovie *newMovie = new QMovie(gifPaths[currentGifIndex]);

  newMovie->setScaledSize(ui->movieAnimation->size()); // Scale the GIF to match QLabel size

  ui->movieAnimation->setMovie(newMovie); // Update QLabel

  if (currentMovie) // Delete the old movie after setting the new one
    delete currentMovie;
  currentMovie = newMovie;

  newMovie->start(); // Start the new movie
}

/**
 * @brief ### Listen to Login button click action
 *
 * @class  Login
 * @return void
 */
void Login::on_pushButton_clicked() {
  std::string _username{ui->username->text().toStdString()},
      _password{ui->password->text().toStdString()};

  if (_username.empty() || _password.empty()) {
    QMessageBox::warning(
        this, tr("Astra"), tr("Username or password are empty!\n"
                              "Pleas fell the messing parts!"),
        QMessageBox::Ok);
    return;
  }

  // Assuming `Select` does not need to be dynamically allocated, we can use stack allocation.
  Employees::Select sl;

  // Execute the select query with the given parameters.
  std::vector<SqlParam> res = sl.selectAll(
      Employees::EmployeeInfo<std::string>(_username, Employees::EmployeeQueueFlags_strings::USERNAME),
      Employees::EmployeeInfo<std::string>(_password, Employees::EmployeeQueueFlags_strings::PASSWORD));

  // Check if the result is empty
  if (res.empty()) {
    // Show error message if the result is empty (i.e., login failed)
    QMessageBox::warning(
        this, tr("Astra"), tr("Username or password are incorrect!\nPlease try to login again!"),
        QMessageBox::Ok);
  } else {
    // Store the verified employee data and proceed to the next interface
    employee = res;         // Hold the verified employees data
    emit loginSuccessful(); // Emit the signal for successful login
  }
}

/**
 * @brief ### Get verified employee data
 *
 * @class  Login
 * @return std::vector<SqlParam>
 */
std::vector<SqlParam> Login::get_employee() {
  return employee;
}

// * ======================================
// ? === Events & Effects handling part ===
// * ======================================

/**
 * @brief ### Manage global events in login interface
 *
 * @class       Login
 * @param obj   {QObject *}
 * @param event {QEvent *}
 * @return      bool
 */
bool Login::eventFilter(QObject *obj, QEvent *event) {
  if (obj == ui->pushButton) // ? Check if the event come form the login btn (login interface)
    return login_btn_events(obj, ui->lg, event);
  else if (obj == ui->reset && ui->reset->isEnabled()) // ? Check if the event come form the login btn (forget password interface)
    return login_btn_events(obj, ui->lg_2, event);
  else if (obj == ui->f_pwd) // ? Check if the object is the forget password label
    return forget_password_events(obj, event);
  return QWidget::eventFilter(obj, event);
}

/**
 * @brief ### Manage forget password events
 *
 * @class       Login
 * @param obj   {QObject *}
 * @param event {QEvent *}
 * @return      bool
 */
bool Login::forget_password_events(QObject *obj, QEvent *event) {
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

  return false; // Just to make compiler run
}

/**
 * @brief ### Manage login button in the login/forgetPassword QGroups
 *
 * @class       Login
 * @param obj   {QObject *}
 * @param icon  {QLabel *}
 * @param event {QEvent *}
 * @return      bool
 */
bool Login::login_btn_events(QObject *obj, QLabel *icon, QEvent *event) {
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
 * @brief #### Make a "fade out" effect to `group1` using opacity transition from `__FULL_VISIBLE__` to `__FULL_TRANSPARENT__` and hide `group1`, overwise for `group2`
 *
 * @class        Login
 * @details      This effect work only with `QGroupBox`
 * @include      QGraphicsOpacityEffect | QPropertyAnimation
 * @param group1 {QGroupBox *}
 * @param group2 {QGroupBox *}
 * @return       void
 */
void Login::QGroupBoxFadeOutEffect(QGroupBox *group1, QGroupBox *group2) {
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
 * @brief ### Make fade In/Out for `group`
 *
 * @class          Login
 * @param group    {QGroupBox *}
 * @param startVal {const QVariant}
 * @param endVal   {const QVariant}
 * @return         {QPropertyAnimation *}
 */
QPropertyAnimation *Login::FadeEffect(QGroupBox *group, const QVariant startVal, const QVariant endVal) {
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
 * @brief ### Listen to Return button click action
 *
 * @details This button is included inside the `f_pwd_interface` QGroupBox
 * @class Login
 */
void Login::on_returnBtn_clicked() {
  enableResetPassword(false);
  clearResetPassword();
  QGroupBoxFadeOutEffect(ui->f_pwd_interface, ui->login); // Redirect the user to login QGroupBox
}

/**
 * @brief ### Listen to `hide_show_btn` click action
 *
 * @details Change the echomode of the `QLineEdit` & the button icon of `QPushButton`
 * @class   Login
 */
void Login::on_hide_show_btn_clicked() {
  (ui->charCode->echoMode() == QLineEdit::Normal) ? change_hideShowBtnIcon(ui->charCode, ui->hide_show_btn) : change_hideShowBtnIcon(ui->charCode, ui->hide_show_btn, QLineEdit::Normal, "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/eye.png");
}

/**
 * @brief ### Listen to `hide_show_btn` click action
 *
 * @details Change the echomode of the `QLineEdit` & the button icon of `QPushButton`
 * @class   Login
 */
void Login::on_hide_show_btn_2_clicked() {
  (ui->password->echoMode() == QLineEdit::Normal) ? change_hideShowBtnIcon(ui->password, ui->hide_show_btn_2) : change_hideShowBtnIcon(ui->password, ui->hide_show_btn_2, QLineEdit::Normal, "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/eye.png");
}

/**
 * @brief ### Helper function
 *
 * @details        this->on_hide_show_btn_clicked() | this->on_hide_show_btn_clicked()
 * @class          Login
 * @param lineEdit {QLineEdit *}
 * @param btn      {QPushButton *}
 * @param mode     {const QLineEdit::EchoMode}
 * @param path     {const QString}
 */
void Login::change_hideShowBtnIcon(QLineEdit *lineEdit, QPushButton *btn, const QLineEdit::EchoMode mode, const QString path) {
  btn->setIcon(QIcon(path));
  lineEdit->setEchoMode(mode);
}

/**
 * @brief ### Verify the given mail and send a 6-chars reset code to reset the password
 *
 * @class Login
 */
void Login::on_sendEmailBtn_clicked() {
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
      generated_password = Password::generate();
      EmailSender email{EmailAuth{}};
      email.send(EmailData(
          _email,
          "Astra: Password Reset Request",
          EmailBody("/home/zouari_omar/Documents/Daily/Projects/Astra/project/html/forget_password_template.html",
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
 * @brief ### Verify the taped code and new/confirm password
 *
 * @class Login
 */
void Login::on_reset_clicked() {
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
 * @brief ### Reset the forget password QGroupBox to the default view (enable/disable proccess)
 *
 * @class        Login
 * @param status {const bool &}
 */
void Login::enableResetPassword(const bool &status) {
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
 * @brief ### Reset all forget password QLineEdit's to the default state (empty)
 *
 * @class Login
 */
void Login::clearResetPassword() {
  ui->email->setText("");
  ui->charCode->setText("");
  ui->newPassword->setText("");
  ui->confirmPassword->setText("");
}

// * ==========================================
// ? ======== / Helpers handling part =========
// * ==========================================