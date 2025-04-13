/**
 * @file      PdfGenerator.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     PdfGenerator source file
 * @version   0.1
 * @date      2025-04-11
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/PdfGenerator.cpp PdfGenerator.cpp @endlink
 */

//? Include prototype declaration part
//* Include std Qt header(s)

#include <QtGui/QPdfWriter>
#include <QtWebEngineCore/QWebEngineSettings>
#include <QtWebEngineWidgets/QWebEngineView>

//* Include custom header(s)
#include "../inc/EmployeesStatistics.hpp"
#include "../inc/HtmlBodyFormatter.hpp"
#include "../inc/PdfGenerator.hpp"

//? Function prototype dev part

/**
 * @fn             PdfGenerator::generatePdf(const QString &, const SqlParam &)
 * @brief          Generate a .pdf file from `filePath`, it return `EXIT_SUCCESS` if the .pdf file generated successfully, otherwise return `EXIT_FAILURE`
 * @param filePath {const QString &}
 * @param emp      {const SqlParam &} - Main user/employee data
 * @return         const unsigned int
 * @link https://forum.qt.io/topic/119534/proper-way-to-display-local-images-in-qtwebengineview/3 BlankLocalImageIssue @endlink
 */
const unsigned int PdfGenerator::generatePdf(const QString &filePath, const SqlParam &emp) {
  int pdf_generation_life_time_status{EXIT_SUCCESS};
  QWebEngineView *webView(new QWebEngineView());
  QWebEnginePage *page(webView->page());

  // Give `QWebEnginePage` some access
  page->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
  page->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
  page->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);

  EmployeesStatistics *stats = new EmployeesStatistics(emp);
  const std::vector<unsigned int> statuses(stats->getStatusStats());
  const std::vector<double> departments(stats->getDepartmentStats());
  delete stats;
  stats = nullptr;

  // Load the .html file template
  HtmlBodyFormater tmp("/home/zouari_omar/Documents/Daily/Projects/Astra/project/html/Report_template.html",
                       {{"{{GENERATED_DATE}}", __DATE__},
                        {"{{GENERATED_BY}}", emp.strings[Employees::EmployeeQueueFlags_strings::USERNAME].second},
                        {"{{ACTIVE_VALUE}}", std::to_string(statuses[Employees::EmployeeStatusFlags::ACTIVE - 1])},
                        {"{{INACTIVE_VALUE}}", std::to_string(statuses[Employees::EmployeeStatusFlags::INACTIVE - 1])},
                        {"{{SUSPENDED_VALUE}}", std::to_string(statuses[Employees::EmployeeStatusFlags::SUSPENDED - 1])},
                        {"{{COMMERCIAL_VALUE}}", std::to_string(departments[Employees::EmployeeDepartmentFlags::COMMERCIAL])},
                        {"{{SHOPS_VALUE}}", std::to_string(departments[Employees::EmployeeDepartmentFlags::SHOPS])},
                        {"{{EVENTS_VALUE}}", std::to_string(departments[Employees::EmployeeDepartmentFlags::PARTNERS])},
                        {"{{PARTNERS_VALUE}}", std::to_string(departments[Employees::EmployeeDepartmentFlags::EVENTS])},
                        {"{{PERSONALS_VALUE}}", std::to_string(departments[Employees::EmployeeDepartmentFlags::PERSONALS])},
                        {"{{EMPLOYEES_VALUE}}", std::to_string(departments[Employees::EmployeeDepartmentFlags::EMPLOYEES])}});

  // Set the inner html to `QWebEnginePage`
  page->setHtml(QString::fromStdString(tmp.get_inner_html()), QUrl::fromLocalFile("/home/zouari_omar/Documents/Daily/Projects/Astra/project/html/"));

  // Wait for page load before generating PDF
  QObject::connect(page, &QWebEnginePage::loadFinished, [=, &pdf_generation_life_time_status](bool success) -> void {
    if (!success) {
      qDebug() << "Failed to load the HTML file !";
      pdf_generation_life_time_status = EXIT_FAILURE;
      return;
    }
    // Generate PDF
    page->printToPdf(filePath, QPageLayout(QPageSize(QPageSize::A4), QPageLayout::Portrait, QMarginsF(10, 10, 10, 10)));
  });

  page->deleteLater(), webView->deleteLater(); // Free allocated vars

  // Return `pdf_generation_life_time_status`
  // Show/Hide a preview (! need to comment the deleteLater instructions)
  return /*webView->show(),*/ pdf_generation_life_time_status;
}