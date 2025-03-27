/**
 * @file employeesUI.hpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief # EmployeesUI header file
 * @version 0.1
 * @date 2025-03-08
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/employeesUI.hpp employeesUI.hpp @endlink
 */

// ? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_UI__
#define __EMPLOYEES_UI__
#define SHADOWS_EFFECT_COMBO_NUMBERS 8

// ? Include prototype declaration part
// * Include std libs (Qt)
#include <QtGui/QBitmap>
#include <QtGui/QMovie>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>

#include "../inc/employees.hpp"

// Include generated .ui files
#include "../ui/ui_employees.h"

// ? Classes prototype declaration part
QT_BEGIN_NAMESPACE
namespace Ui {
class EmployeesUI;
}
QT_END_NAMESPACE

class EmployeesUI : public QMainWindow {
  Q_OBJECT

public:
  explicit EmployeesUI(std::vector<SqlParam>, QWidget *parent = nullptr);
  ~EmployeesUI();
  void set_employee(const std::vector<SqlParam> &);

private: // ? Private EmployeesUI vars
  std::vector<SqlParam> employee;
  Ui::EmployeesUI *ui;
  QMovie *pdf_movie,
      *notification_movie;
  QGraphicsDropShadowEffect *shadow_effect_components;

private: // ? Private EmployeesUI function
  inline void __init__();
  inline void __init_employees_table__();
  inline void __init_form_group_box__();
  inline void __init_update_form_group_box__();
  void set_shadowEffect(QWidget *, QGraphicsDropShadowEffect *, const qreal xOffset = 5, const qreal yOffset = 5, const qreal blurRadius = 5, const QColor color = Qt::gray);
  void set_pushButtonMovie(QPushButton *, QMovie *) const;
  void scaleImg(const QString &, QLabel *, const qreal, const qreal) const;
  std::string extractUsername(const std::string &) const;

private slots:
  void on_show_clicked(bool);
  void on_show_2_clicked(bool);
  void on_Add_button_clicked();
  void on_Cancel_form_clicked();
  void on_Cancel_form_2_clicked();
  void on_insertBtn_clicked();
  void on_updateBtn_clicked();
  void on_profileImageInsert_clicked();
}; // EmployeesUI class

#endif // __EMPLOYEES_UI__
