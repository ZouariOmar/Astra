/**
 * @file EmployeesUICharts.cpp
 * @author @ZouariOmar (zouariomar20@gmail.com)
 * @brief EmployeesUICharts source file
 * @version 0.1
 * @date 2025-04-05
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/EmployeesUICharts.cpp EmployeesUICharts.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/EmployeesUICharts.hpp"

//? Function(s) prototype dev part

/**
 * @fn        Employees::EmployeesUICharts::EmployeesUICharts(QMainWindow *)
 * @brief     Construct a new Employees::EmployeesUICharts::EmployeesUICharts object
 * @param _ui {QMainWindow *}
 */
Employees::EmployeesUICharts::EmployeesUICharts(QMainWindow *_ui) : ui(_ui) {};

void Employees::EmployeesUICharts::clearPrevChart(QHBoxLayout *frame) {
  QLayoutItem *child;
  while ((child = frame->takeAt(0)) != nullptr) {
    if (child->widget()) {
      delete child->widget();
    }
    delete child;
  }
}

/**
 * @fn Employees::EmployeesUICharts::setPieChart(QHBoxLayout *, const std::vector<std::pair<std::string, double>> &)
 *
 * @brief Sets a pie chart on the provided layout with the given data.
 *
 * @details This function takes a horizontal layout and a set of data, where each data entry
 * represents a category (as a string) and its corresponding value (as a double).
 * It creates a pie chart using Qt's `QPieSeries` and `QChart` components. The chart
 * is populated with the provided data, and interactive animations (hover effects and
 * explosion) are added for better user experience.
 *
 * @note The pie chart's legend is updated with the percentage values when hovering over
 * each slice.
 *
 * @param frame The `QHBoxLayout` where the chart will be placed
 * @param data A vector of pairs where each pair consists of:
 *
 * - A `std::string` representing the category name.
 *
 * - A `double` representing the category value.
 *
 * @return void
 */
void Employees::EmployeesUICharts::setPieChart(QHBoxLayout *frame, const std::vector<std::pair<std::string, double>> &data) {
  // Clear previous chart
  clearPrevChart(frame);

  // Create pie series
  QPointer<QPieSeries> series = new QPieSeries();
  for (const auto &entry : data) {
    QPieSlice *slice = series->append(QString::fromStdString(entry.first), entry.second);
    QString baseLabel = QString::fromStdString(entry.first);
    slice->setLabel(baseLabel);

    QObject::connect(slice, &QPieSlice::hovered, [slice, baseLabel, entry](bool state) { //* Listen to slice hover action
      slice->setExploded(state);
      slice->setExplodeDistanceFactor(state ? 0.12 : 0.0);
      slice->setLabelVisible(state);
      slice->setLabel(state ? QString("%1 (%2%)").arg(baseLabel).arg(QString::number(entry.second, 'f', 2)) : baseLabel);
    });
  }

  QPointer<QChart> chart = new QChart(); // Create chart
  chart->addSeries(series);
  chart->setTitle("Employees Department Overview");
  chart->legend()->setAlignment(Qt::AlignRight);
  chart->setAnimationOptions(QChart::SeriesAnimations); // Smooth slice entry

  QPointer<QChartView> chartView = new QChartView(chart); // Create chart view and add to layout
  chartView->setRenderHint(QPainter::Antialiasing);
  frame->addWidget(chartView);
}

/**
 * @brief Sets a bar chart on the provided layout with the given data.
 *
 * This function takes a horizontal layout and a set of data, where each data entry
 * represents a category (as a string) and its corresponding value (as a double).
 * It creates a bar chart using Qt's `QBarSeries`, `QBarSet`, and `QChart` components.
 * The chart is populated with the provided data, and interactive animations (hover effects)
 * are added for better user experience.
 *
 * @param frame The `QHBoxLayout` where the chart will be placed.
 * @param data A vector of pairs where each pair consists of:
 *        - A `std::string` representing the category name.
 *        - A `double` representing the category value.
 */
void Employees::EmployeesUICharts::setBarChart(QHBoxLayout *frame, const std::vector<std::pair<std::string, double>> &data) {
  // Clear previous chart if exists
  clearPrevChart(frame);

  // Create a bar set (set of bars for the chart)
  QPointer<QBarSet> barSet = new QBarSet("Categories");
  QStringList categories;

  // Populate the bar set and categories
  for (const auto &entry : data) {
    *barSet << entry.second;                           // Add the value of each category to the bar set
    categories << QString::fromStdString(entry.first); // Add category names
  }

  // Create a bar series
  QPointer<QBarSeries> barSeries = new QBarSeries();
  barSeries->append(barSet);

  // Set categories for the X-axis
  QPointer<QBarCategoryAxis> axisX = new QBarCategoryAxis();
  axisX->append(categories);
  

  // Create a Y-axis, set the range based on the `max_value` in the data and set integer ticks on the Y-axis
  QPointer<QValueAxis> axisY = new QValueAxis();
  double max_value = std::max_element(data.begin(), data.end(), [](const std::pair<std::string, double> &a, const std::pair<std::string, double> &b) {
                       return a.second < b.second;
                     })->second;
  axisY->setRange(0, max_value);      // Set the range of Y-axis based on max value
  axisY->setTickCount(max_value + 1); // Ensure the axis has enough ticks (rounded)
  axisY->setLabelFormat("%d");        // Only show integer values
  
  // Create a chart and add the bar series
  QPointer<QChart> chart = new QChart();
  chart->addSeries(barSeries);
  chart->addAxis(axisX, Qt::AlignBottom);
  chart->addAxis(axisY, Qt::AlignLeft);
  chart->setTitle("Employees Status Overview");
  chart->setAnimationOptions(QChart::AllAnimations); // Enable chart animations
  
  barSeries->attachAxis(axisX);
  barSeries->attachAxis(axisY);

  QPointer<QChartView> chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  frame->addWidget(chartView); // Add the chart view to the layout
}

void Employees::EmployeesUICharts::setBarLineChart(QHBoxLayout *frame, const std::vector<std::pair<std::string, double>> &data) {
  // Clear previous chart if exists
  clearPrevChart(frame);

  // Create a bar set (set of bars for the chart)
  QPointer<QBarSet> barSet = new QBarSet("Salaries");
  QStringList categories;

  // Populate the bar set and categories
  for (const auto &entry : data) {
    *barSet << entry.second;
    categories << QString::fromStdString(entry.first);
  }

  // Create a bar series and append the bar set
  QPointer<QBarSeries> barSeries = new QBarSeries();
  barSeries->append(barSet);

  // Create a line series (same data as bar)
  QPointer<QLineSeries> lineSeries = new QLineSeries();
  lineSeries->setName("Salaries (Line)");
  for (size_t i{}; i < data.size(); ++i)
    lineSeries->append(i, data[i].second);

  // Create category X-axis
  QPointer<QBarCategoryAxis> axisX = new QBarCategoryAxis();
  axisX->append(categories);
  axisX->setTitleText("Departments");

    // Create value Y-axis
  QPointer<QValueAxis> axisY = new QValueAxis();
  axisY->setTitleText("Salary");
  double maxVal = std::max_element(data.begin(), data.end(),
                                   [](const auto &a, const auto &b) { return a.second < b.second; })
                      ->second;
  axisY->setRange(0, maxVal * 1.1); // Add 10%

  // Style the line
  QPen pen(Qt::yellow);
  pen.setWidth(2);
  lineSeries->setPen(pen);

  QPointer<QChart> chart = new QChart();
  chart->legend()->setVisible(true);
  chart->addSeries(barSeries);
  chart->addSeries(lineSeries);
  chart->addAxis(axisX, Qt::AlignBottom);
  chart->addAxis(axisY, Qt::AlignLeft);
  chart->setTitle("Departments Total Salaries Overview");
  chart->setAnimationOptions(QChart::AllAnimations);

  barSeries->attachAxis(axisX);
  lineSeries->attachAxis(axisX);

  QPointer<QChartView> chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  frame->addWidget(chartView); // Add the chart view to the layout
}
