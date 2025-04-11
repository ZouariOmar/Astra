/**
 * @file      EmployeesUI.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     EmployeesUI header file
 * @version   0.1
 * @date      2025-03-08
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/EmployeesUI.hpp EmployeesUI.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_UI_HPP__
#define __EMPLOYEES_UI_HPP__
#define SHADOWS_EFFECT_COMBO_NUMBERS 9

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtGui/QBitmap>
#include <QtGui/QMovie>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>

//* Include custom header(s)
#include "../inc/Employees.hpp"

//* Include generated ui_.h file(s)
#include "../ui/ui_employees.h"

//? Classes prototype declaration part

/**
 * @namespace Ui
 * @brief     Ui namespace
 */
QT_BEGIN_NAMESPACE
namespace Ui {
class EmployeesUI;
}; // Namespace Ui
QT_END_NAMESPACE

/**
 * @class EmployeesUtils
 * @brief EmployeesUtils class
 */
class EmployeesUtils {
public:
  EmployeesUtils();

protected:
  std::string profileImgInsertHolder, profileImgUpdateHolder;
  void scaleImg(const QString &, QLabel *, const qreal, const qreal) const;
  std::string extractUsername(const std::string &, const unsigned short &length = 12) const;
  std::string strToUpper(std::string) const;
  void set_shadowEffect(QWidget *, QGraphicsDropShadowEffect *, const qreal xOffset = 5, const qreal yOffset = 5, const qreal blurRadius = 5, const QColor color = Qt::gray);
}; // Utils class

/**
 * @class EmployeesUI
 * @brief EmployeesUI class
 */
class EmployeesUI : public QMainWindow, private EmployeesUtils {
  Q_OBJECT

public:
  explicit EmployeesUI(SqlParam, QWidget *parent = nullptr);
  ~EmployeesUI();
  void set_employee(const SqlParam &);

private: //? Private EmployeesUI vars
  SqlParam employee;
  Ui::EmployeesUI *ui;
  QMovie *pdf_movie,
      *notification_movie;
  QGraphicsDropShadowEffect *shadow_effect_components;

private: //? Private EmployeesUI function
  inline void __init__();
  void __init_current__employee_UI__() const;
  inline void __init_inset_form_group_box__();
  inline void __init_update_form_group_box__();
  void __init_employees_table__();
  void __clear_employees_table__() const;
  inline void __init_employees_charts__();
  // void insertRow_employees_table();
  void syncUI();
  void set_pushButtonMovie(QPushButton *, QMovie *) const;

private slots:
  void on_show_clicked(bool);
  void on_show_2_clicked(bool);
  void on_Add_button_clicked();
  void on_Cancel_form_clicked();
  void on_Cancel_form_2_clicked();
  void on_insertBtn_clicked();
  void on_updateBtn_clicked();
  void on_profileImageInsert_clicked();
  void on_profileImageInsert_2_clicked();
  void on_Filter_activated(int);
  void on_PDF_clicked();
}; // EmployeesUI class

#endif // __EMPLOYEES_UI_HPP__
