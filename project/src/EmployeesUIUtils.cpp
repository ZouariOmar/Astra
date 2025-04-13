/**
 * @file      EmployeesUIUtils.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     EmployeesUIUtils source file
 * @version   0.1
 * @date      2025-04-11
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/EmployeesUIUtils.cpp EmployeesUIUtils.cpp @endlink
 */

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtGui/QPainter>

//* Include custom header(s)
#include "../inc/EmployeesUIUtils.hpp"

//? Function prototype dev part

/**
 * @fn    EmployeesUIUtils::EmployeesUIUtils()
 * @brief Construct a new EmployeesUIUtils::EmployeesUIUtils object
 */
EmployeesUIUtils::EmployeesUIUtils()
    : profileImgInsertHolder(""), profileImgUpdateHolder("") {};

/**
 * @fn            EmployeesUIUtils::scaleImg(const QString &, QLabel *, const qreal, const qreal) const
 * @brief         Shape an image to be round depending of the `xRadius` and `yRadius` then put it in a label
 * @param path    {const QString &}
 * @param label   {QLabel *}
 * @param xRadius {const qreal}
 * @param yRadius {const qreal}
 * @return        void
 */
void EmployeesUIUtils::scaleImg(const QString &path, QLabel *label, const qreal xRadius, const qreal yRadius) const {
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
 * @fn           EmployeesUIUtils::extractUsername(const std::string &) const
 * @brief        Return the `username` from `ui->updateForm` title
 * @param title  {const std::string &}
 * @param length {const unsigned short &}
 * @return       std::string
 */
std::string EmployeesUIUtils::extractUsername(const std::string &title, const unsigned short &length) const {
  return title.substr(12, title.size());
}

/**
 * @fn      EmployeesUIUtils::strToUpper(std::string) const
 * @brief   Transform `s` to uppercase string
 * @param s {std::string &}
 * @return  std::string
 */
std::string EmployeesUIUtils::strToUpper(std::string s) const {
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}

/**
 * @fn               EmployeesUIUtils::set_shadowEffect(QWidget *, QGraphicsDropShadowEffect *, const qreal, const qreal, const qreal, const QColor)
 * @brief            Set the shadow effect on `effect` and affected to `obj`
 * @param obj        {QWidget *}
 * @param effect     {QGraphicsDropShadowEffect *}
 * @param xOffset    {const qreal}
 * @param yOffset    {const qreal}
 * @param blurRadius {const qreal}
 * @param color      {const QColor}
 * @return           void
 */
void EmployeesUIUtils::set_shadowEffect(QWidget *obj, QGraphicsDropShadowEffect *effect, const qreal xOffset, const qreal yOffset, const qreal blurRadius, const QColor color) {
  effect->setXOffset(xOffset), effect->setYOffset(yOffset);
  effect->setBlurRadius(blurRadius);
  effect->setColor(color);
  obj->setGraphicsEffect(effect);
}