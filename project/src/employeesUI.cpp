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
#include "../inc/employees.hpp"

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
EmployeesUI::EmployeesUI(std::vector<std::string> _employee, QWidget *parent)
    : QMainWindow(parent),
      employee(_employee),
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
  ui->profileImageInsert->hide();

  // Init Employees table view
  __init_employees_table__();

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

/**
 * @brief ### Init/Async employees table view
 *
 * @class EmployeesUI
 */
inline void EmployeesUI::__init_employees_table__() {
  Employees::Select *sl(new Employees::Select);
  std::vector<std::vector<std::string>> employees = sl->selectAllExcept(Employees::EmployeeInfo("2", Employees::EmployeeQueueFlags::EMPLOYEE_ID));
  delete sl;
  sl = nullptr;

  size_t rows{employees.size()};
  int columns{ui->EmployeesTableWidget->columnCount()}; // * 5 columns for now
  ui->EmployeesTableWidget->setRowCount(rows);          // Set row count

  for (size_t row{}; row < rows; ++row) { // Iterate over rows
    for (int col{}; col < columns; ++col) {
      QTableWidgetItem *item{nullptr};
      QPushButton *button{nullptr};
      switch (col) {
      case 0: // Show image profile
        item = new QTableWidgetItem(QString::fromStdString(employees[row][Employees::EmployeeQueueFlags::PROFILE_IMAGE]));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;

      case 1: // Show username
        item = new QTableWidgetItem(QString::fromStdString(employees[row][Employees::EmployeeQueueFlags::USERNAME]));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;

      case 2: // Show email
        item = new QTableWidgetItem(QString::fromStdString(employees[row][Employees::EmployeeQueueFlags::EMAIL]));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;

      case 3: // Show department
        item = new QTableWidgetItem(QString::fromStdString(employees[row][Employees::EmployeeQueueFlags::DEPARTMENT]));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;

      case 4: // Show status
        item = new QTableWidgetItem(QString::fromStdString(employees[row][Employees::EmployeeQueueFlags::STATUS]));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;

      case 5: // Show Actions
        button = new QPushButton("hello mama!");
        ui->EmployeesTableWidget->setCellWidget(row, col, button);
        break;

      default:
        break;
      }
    }
  }
}

void EmployeesUI::set_employee(const std::vector<std::string> &_employee) {
  employee = _employee;
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
 * @class            EmployeesUI
 * @param obj        {QWidget *}
 * @param effect     {QGraphicsDropShadowEffect *}
 * @param xOffset    {const qreal}
 * @param yOffset    {const qreal}
 * @param blurRadius {const qreal}
 * @param color      {const QColor}
 * @return           void
 */
void EmployeesUI::set_shadowEffect(QWidget *obj, QGraphicsDropShadowEffect *effect, const qreal xOffset, const qreal yOffset, const qreal blurRadius, const QColor color) {
  effect->setXOffset(xOffset);
  effect->setYOffset(yOffset);
  effect->setBlurRadius(blurRadius);
  effect->setColor(color);
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
    ui->profileImageInsert->show();
    ui->show->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/Employees/icons8-left.png"));
    ui->Cancel_form->move(380, ui->Cancel_form->y());
    ui->insertBtn->move(340, ui->insertBtn->y());
  } else {
    ui->Form->resize(211, ui->Form->height());
    ui->profileImageInsert->hide();
    ui->show->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/Employees/icons8-right.png"));
    ui->Cancel_form->move(180, ui->Cancel_form->y());
    ui->insertBtn->move(140, ui->insertBtn->y());
  }
}

/**
 * @brief ###
 *
 * @class  EmployeesUI
 * @return void
 */
void EmployeesUI::on_insertBtn_clicked() {
  // 1. Hold data from UI
  std::string firstName = ui->firstNameInsert->text().toStdString();
  std::string lastName = ui->lastNameInsert->text().toStdString();
  std::string email = ui->emailNameInsert->text().toStdString();
  std::string password = ui->passwordNameInsert->text().toStdString();
  std::string department = ui->departmentInsert->currentText().toStdString();

  // 2. Verify if the given email exist
  Employees::Select *sl(new Employees::Select);
  std::vector<std::string> employee = sl->selectAll(Employees::EmployeeInfo(email, Employees::EmployeeQueueFlags::EMAIL));
  delete sl;
  sl = nullptr;

  if (!employee.empty()) {
    QMessageBox::warning(this, tr("Astra"),
                         tr("This Email Exist, you can't added it again!"),
                         QMessageBox::Ok);
    return;
  }

  // 3. If not, insert the given data
  Employees::Insert *ist(new Employees::Insert);
  int affRow = ist->insertReq(Employees::EmployeeInfo(email, Employees::EmployeeQueueFlags::EMAIL),
                              Employees::EmployeeInfo(firstName, Employees::EmployeeQueueFlags::FIRSTNAME),
                              Employees::EmployeeInfo(lastName, Employees::EmployeeQueueFlags::LASTNAME),
                              Employees::EmployeeInfo(password, Employees::EmployeeQueueFlags::PASSWORD),
                              Employees::EmployeeInfo(department, Employees::EmployeeQueueFlags::DEPARTMENT));
  delete ist;
  ist = nullptr;

  // 4. Show a QMessageBox on success/failed operation
  (!affRow) ? QMessageBox::warning(this, tr("Astra"),
                                   tr("Error: Can't insert the given employee data!"),
                                   QMessageBox::Ok)
            : QMessageBox::information(this, tr("Astra"),
                                       tr("Employee added successfully!"),
                                       QMessageBox::Ok);

  // 5. Refresh the table (just add the last(new) inserted employee)
  __init_employees_table__();
}
// * ========================================
// ? === / Events & signals handling part ===
// * ========================================
