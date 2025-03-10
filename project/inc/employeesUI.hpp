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
#define NB_SHADOWS 7

// ? Include prototype declaration part
// * Include std libs (Qt)
#include <QtGui/QBitmap>
#include <QtGui/QMovie>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QMainWindow>

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
  explicit EmployeesUI(QWidget *parent = nullptr);
  ~EmployeesUI();

private: // ? Private EmployeesUI vars
  Ui::EmployeesUI *ui;
  QMovie *pdf_movie,
      *notification_movie;
  QGraphicsDropShadowEffect *shadow_effect_components;

private: // ? Private EmployeesUI function
  inline void __init__();
  void set_shadowEffect(QWidget *, QGraphicsDropShadowEffect *);
  void set_pushButtonMovie(QPushButton *, QMovie *) const;
  void scaleImg(const QString &, QLabel *, const qreal, const qreal) const;

private slots:
  void on_show_clicked(bool);
  void on_Add_button_clicked();
  void on_Cancel_form_clicked();
}; // EmployeesUI class

#endif // __EMPLOYEES_UI__
