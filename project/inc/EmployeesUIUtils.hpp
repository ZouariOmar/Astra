/**
 * @file      EmployeesUIUtils.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     EmployeesUIUtils header file
 * @version   0.1
 * @date      2025-04-11
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/EmployeesUIUtils.hpp EmployeesUIUtils.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __EMPLOYEES_UI_UTILS_HPP__
#define __EMPLOYEES_UI_UTILS_HPP__

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>

//? Class prototype declaration part

/**
 * @class EmployeesUIUtils
 * @brief EmployeesUIUtils class
 */
class EmployeesUIUtils {
public:
  EmployeesUIUtils();

protected:
  std::string profileImgInsertHolder, profileImgUpdateHolder;
  void scaleImg(const QString &, QLabel *, const qreal, const qreal) const;
  std::string extractUsername(const std::string &, const unsigned short &length = 12) const;
  std::string strToUpper(std::string) const;
  void set_shadowEffect(QWidget *, QGraphicsDropShadowEffect *, const qreal xOffset = 5, const qreal yOffset = 5, const qreal blurRadius = 5, const QColor color = Qt::gray);
}; // EmployeesUIUtils class

#endif // __EMPLOYEES_UI_UTILS_HPP__