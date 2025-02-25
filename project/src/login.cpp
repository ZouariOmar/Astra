/**
 * @file login.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Login source file
 * @version 0.1
 * @date 2025-02-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/login.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/login.hpp"
#include "../inc/connect.hpp"

//? Function/Class prototype dev part

/**
 * @brief ### Construct a new Login::Login object
 *
 * @class Login
 * @param parent {QWidget *}
 */
Login::Login(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Login),
      gifTimer(new QTimer(this)),
      currentGifIndex(0),
      gifPaths({
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an00.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an01.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an02.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an03.gif",
          "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/login imgs/animations/an04.gif",
      }),
      currentMovie(nullptr) {
  ui->setupUi(this);
  setWindowTitle("Astra"); // Set window title

  connect(gifTimer, &QTimer::timeout, this, &Login::updateGif); // Set movieAnimation gif
  gifTimer->start(__LOGIN_GIF_ANIMATION__);

  // Install global events (make them detectable)
  ui->pushButton->installEventFilter(this);
  ui->pushButton_2->installEventFilter(this);
  ui->f_pwd->installEventFilter(this);

  // Hide sub interfaces
  ui->f_pwd_interface->hide();

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

/**
 * @brief ### Update the Gif every `__LOGIN_GIF_ANIMATION__`
 *
 *
 * @details This change make a beautiful animation
 * @class Login
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
 * @class Login
 */
void Login::on_pushButton_clicked() {
  string _username{ui->username->text().toStdString()},
      _password{ui->password->text().toStdString()};

  if (_username.empty() || _password.empty())
    QMessageBox::warning(
        this, tr("Astra"), tr("Username or password are empty!\n"
                              "Pleas fell the messing parts!"),
        QMessageBox::Ok);

  // Verify the validity of the given info
  Database *db = new Database();
  int aff{};
  vector<vector<string>> res = db->execute("SELECT * FROM Employees WHERE Username = '" + _username + "' AND Password = '" + _password + "'", aff);
  delete db; // Close oracle 1521 port

  if (res.empty())
    qDebug() << "User not found";
  else
    emit loginSuccessful();
}

/**
 * ####################################################
 * ########## Events & Effects handling part ##########
 * ####################################################
 */

/**
 * @brief ### Add the transaction animation in Enter/Leave events fo
 *
 * @param obj {QObject *}
 * @param event {QEvent *}
 * @return bool
 */
bool Login::eventFilter(QObject *obj, QEvent *event) {
  if (obj == ui->pushButton) // ? Check if the event come form the login btn (login interface)
    return login_btn_events(obj, ui->lg, event);
  else if (obj == ui->pushButton_2) // ? Check if the event come form the login btn (forget password interface)
    return login_btn_events(obj, ui->lg_2, event);
  else if (obj == ui->f_pwd) // ? Check if the object is the forget password label
    return forget_password_events(obj, event);
  return QWidget::eventFilter(obj, event);
}

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
 * @details This effect work only with `QGroupBox`
 * @class Login
 * @include QGraphicsOpacityEffect | QPropertyAnimation
 * @param group1 {QGroupBox *}
 * @param group2 {QGroupBox *}
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
 * @class Login
 * @param group {QGroupBox *}
 * @param startVal {const QVariant}
 * @param endVal {const QVariant}
 * @return {QPropertyAnimation *}
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
  QGroupBoxFadeOutEffect(ui->f_pwd_interface, ui->login);
}

/**
 * ######################################################
 * ########## / Events & Effects handling part ##########
 * ######################################################
 */