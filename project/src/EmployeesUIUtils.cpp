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
 * @fn            EmployeesUIUtils::scaleImg(const QString &, QLabel *) const
 * @brief         Shape an image to be round depending of the `xRadius` and `yRadius` then put it in a label
 * @param path    {const QString &}
 * @param label   {QLabel *}
 * @return        void
 */
void EmployeesUIUtils::scaleImg(const QString &path, QLabel *label) const {
  QPixmap image(path);
  if (image.isNull()) {
    qWarning("Failed to load image: %s", qUtf8Printable(path));
    return;
  }

  QSize labelSize = label->size();
  int w = labelSize.width(), h = labelSize.height();

  // Scale the image to cover the label area
  QPixmap scaled = image.scaled(w, h, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  // Prepare final transparent canvas
  QPixmap result(w, h);
  result.fill(Qt::transparent);

  // Clip image into a circle/ellipse
  QPainter painter(&result);
  painter.setRenderHint(QPainter::Antialiasing), painter.setRenderHint(QPainter::SmoothPixmapTransform);

  QPainterPath clipPath;
  clipPath.addEllipse(0, 0, w, h), painter.setClipPath(clipPath);

  // Center the image inside the clipped area
  int xOffset = (scaled.width() - w) / 2, yOffset = (scaled.height() - h) / 2;
  painter.drawPixmap(0, 0, scaled.copy(xOffset, yOffset, w, h));

  label->setPixmap(result); // Set the final rounded image to the QLabel
}

/**
 * @fn           EmployeesUIUtils::extractUsername(const std::string &) const
 * @brief        Return the `username` from `updateForm` title
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

/** @brief Extract all the data from a `QTableWidget *` into a `vector<vector<string>>`
 *
 * @param tableWidget {QTableWidget *}
 * @return            std::vector<std::vector<std::string>>
 */
std::vector<std::vector<std::string>> EmployeesUIUtils::extractTableData(QTableWidget *tableWidget) {
  std::vector<std::vector<std::string>> data;

  int rowCount(tableWidget->rowCount()),
      columnCount(tableWidget->columnCount() - 1); // Ignore the `Actions` column

  for (int row{}; row < rowCount; ++row) {
    std::vector<std::string> rowData;
    for (int col{}; col < columnCount; ++col) {
      QTableWidgetItem *item = tableWidget->item(row, col);
      if (col == 0) {
        rowData.push_back(item->data(Qt::UserRole).toString().toStdString());
        continue;
      }
      if (col == 4) {
        rowData.push_back(item->data(Qt::UserRole).toString().toStdString());
        continue;
      }
      (item) ? rowData.push_back(item->text().toStdString()) : rowData.push_back("");
    }
    data.push_back(rowData);
  }

  return data; // Return the result
}

void EmployeesUIUtils::filterEmployees(QTableWidget *tableWidget, QComboBox *filter, QLineEdit *searchBar) {
  QString searchText(searchBar->text().trimmed()),
      currentStatusFilter(filter->currentText());

  int rowCount = tableWidget->rowCount(),
      columnCount(tableWidget->columnCount() - 1); // Ignore the `Actions` column

  for (int row{}; row < rowCount; ++row) {
    bool matchesSearch{}, matchesStatus{};

    // Check search match in any column
    for (int col{}; col < columnCount; ++col) {
      QTableWidgetItem *item = tableWidget->item(row, col);
      if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
        matchesSearch = true;
        break;
      }
    }

    // Check status match in column 4 (status column)
    QTableWidgetItem *statusItem(tableWidget->item(row, 4));
    if (currentStatusFilter == "ALL") {
      matchesStatus = true;
    } else if (statusItem) {
      QVariant statusData = statusItem->data(Qt::UserRole);
      if (statusData.isValid() && statusData.toString() == currentStatusFilter)
        matchesStatus = true;
    }
    tableWidget->setRowHidden(row, !(matchesSearch && matchesStatus)); // Final row visibility based on both conditions
  }
}
