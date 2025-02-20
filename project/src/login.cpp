/**
 * @file login.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # Login source file
 * @version 0.1
 * @date 2025-02-18
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/login.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/login.hpp"
#include "../inc/connect.hpp"

//? Function/Class prototype dev part

/**
 * @brief ### Construct a new Login::Login object
 *
 * @param parent {QWidget *}
 */
Login::Login(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
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
  ui->pushButton->installEventFilter(this);

  updateGif(); // Initialize the first GIF
}

/**
 * @brief ### Destroy the Login::Login object
 */
Login::~Login() {
  delete ui;
  delete gifTimer;
  delete currentMovie;
}

/**
 * @brief ### Update the Gif every `__LOGIN_GIF_ANIMATION__`
 * @details This change make a beautiful animation
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
 * @brief ### Add the transaction animation in Enter/Leave events fo
 *
 * @param obj {QObject *}
 * @param event {QEvent *}
 * @return bool
 */
bool Login::eventFilter(QObject *obj, QEvent *event) {
  if (obj == ui->pushButton) { // Check if the hovered object is login btn
    if (!ui->lg)               // Ensure QLabel exists
      return false;

    // Create animation object
    QPropertyAnimation *animation(new QPropertyAnimation(ui->lg, "pos", this));
    animation->setDuration(1000);                      // 1s animation duration
    animation->setEasingCurve(QEasingCurve::OutCubic); // Smooth transition

    QPoint startPos = ui->lg->pos(); // Get current position
    QPoint endPos;                   // Define target position

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
  return QWidget::eventFilter(obj, event);
}

/**
 * @brief ### Listen to Login button click action
 */
void Login::on_pushButton_clicked() {
  string _username{ui->username->text().toStdString()},
      _password{ui->password->text().toStdString()};

  if (_username.empty() || _password.empty())
    QMessageBox::warning(this, tr("Astra"), tr("Username or password are empty!\n"
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