/**
 * @file employeesUI.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # EmployeesUI source file
 * @version 0.1
 * @date 2025-03-08
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/employeesUI.cpp employeesUI.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/employeesUI.hpp"

//? Function/Class prototype dev part

// * ==============================================
// ? === EmployeesUI constructor and destructor ===
// * ==============================================

/**
 * @brief ### Construct a new EmployeesUI::EmployeesUI object
 *
 * @class        Solution
 * @param parent {QWidget *}
 */
EmployeesUI::EmployeesUI(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EmployeesUI),
      pdf_movie(new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/global/icons8-pdf.gif")),
      notification_movie(new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/global/icons8-notification.gif")),
      shadow_effect_components(new QGraphicsDropShadowEffect[NB_SHADOWS]) {
  ui->setupUi(this);
  __init__();
}

/**
 * @brief ### Destroy the EmployeesUI::EmployeesUI object
 *
 * @class Solution
 */
EmployeesUI::~EmployeesUI() {
  delete ui;
  delete pdf_movie;
  delete notification_movie;
  delete[] shadow_effect_components;
}

/**
 * @brief ### Initialize Employees first view interface
 *
 * @details Helper fn --> EmployeesUI::EmployeesUI()
 * @class   EmployeesUI
 * @return  void
 */
inline void EmployeesUI::__init__() {
  // Hide the add form
  ui->Form->hide();

  // Hide Profile image form
  ui->profileImage->hide();

  // Set pushButtons Movie (as QIcon)
  set_pushButtonMovie(ui->PDF, pdf_movie);
  set_pushButtonMovie(ui->Notification, notification_movie);

  // Make the profile image rounded
  scaleImg("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/global/default.jpg", ui->User_Image, 35, 35);

  // Set Shadow Effect for `NB_SHADOWS` componenets
  set_shadowEffect(ui->Background_navigation, &shadow_effect_components[0]);
  set_shadowEffect(ui->Search_bar, &shadow_effect_components[1]);
  set_shadowEffect(ui->Add_button, &shadow_effect_components[2]);
  set_shadowEffect(ui->PDF, &shadow_effect_components[3]);
  set_shadowEffect(ui->Filtre, &shadow_effect_components[4]);
  set_shadowEffect(ui->Notification, &shadow_effect_components[5]);
  set_shadowEffect(ui->Form, &shadow_effect_components[6]);
}

// * ================================================
// ? === / EmployeesUI constructor and destructor ===
// ? ============ Effects handling part =============
// * ================================================

/**
 * @brief ### Shape an image to be round depending of the `xRadius` and `yRadius` then put it in a label
 *
 * @class         EmployeesUI
 * @param path    {const QString &}
 * @param label   {QLabel *}
 * @param xRadius {const qreal}
 * @param yRadius {const qreal}
 * @return        void
 */
void EmployeesUI::scaleImg(const QString &path, QLabel *label, const qreal xRadius, const qreal yRadius) const {
  QPixmap Image(path);
  QSize Size = label->size();
  const int h = Size.height(),
            w = Size.width();

  // Initialize image
  Image = Image.scaled(Size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

  // Create mask
  QBitmap map(Size);
  map.fill(Qt::color0);

  QPainter painter(&map);
  painter.setBrush(Qt::color1);
  painter.drawRoundedRect(0, 0, w, h, xRadius, yRadius);

  Image.setMask(map);
  label->setPixmap(Image);
}

/**
 * @brief ### Set GIF as a button icon
 *
 * @class       EmployeesUI
 * @param btn   {QPushButton *}
 * @param movie {QMovie *}
 */
void EmployeesUI::set_pushButtonMovie(QPushButton *btn, QMovie *movie) const {
  connect(movie, &QMovie::frameChanged, [=] {
    if (!movie->currentPixmap().isNull())
      btn->setIcon(movie->currentPixmap());
  });
  movie->start();
}

/**
 * @brief ### Set the shadow effect on `effect` and affected to `obj`
 *
 * @class        EmployeesUI
 * @param obj    {QWidget *}
 * @param effect {QGraphicsDropShadowEffect *}
 */
void EmployeesUI::set_shadowEffect(QWidget *obj, QGraphicsDropShadowEffect *effect) {
  effect->setBlurRadius(5);
  effect->setXOffset(5);
  effect->setYOffset(5);
  effect->setColor(Qt::gray);
  obj->setGraphicsEffect(effect);
}

// * ======================================
// ? ====== / Effects handling part =======
// ? === Events & signals handling part ===
// * ======================================

/**
 * @brief Listen to "Add" button click action
 *
 * @class         EmployeesUI
 * @return        void
 */
void EmployeesUI::on_Add_button_clicked() {
  ui->Form->show();
}

/**
 * @brief Listen to "Cancel" button click action
 *
 * @class         EmployeesUI
 * @return        void
 */
void EmployeesUI::on_Cancel_form_clicked() {
  ui->Form->hide();
}

/**
 * @brief ### Listen to "Show More/Less" button click action
 *
 * @class         EmployeesUI
 * @param checked bool
 * @return        void
 */
void EmployeesUI::on_show_clicked(bool checked) {
  if (checked) {
    ui->Form->resize(411, ui->Form->height());
    ui->profileImage->show();
    ui->show->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/Employees/icons8-left.png"));
    ui->Cancel_form->move(380, ui->Cancel_form->y());
    ui->insertBtn->move(340, ui->insertBtn->y());
  } else {
    ui->Form->resize(211, ui->Form->height());
    ui->profileImage->hide();
    ui->show->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/Employees/icons8-right.png"));
    ui->Cancel_form->move(180, ui->Cancel_form->y());
    ui->insertBtn->move(140, ui->insertBtn->y());
  }
}

// * ========================================
// ? === / Events & signals handling part ===
// * ========================================