/**
 * @file      EmployeesUI.cpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     EmployeesUI source file
 * @version   0.1
 * @date      2025-03-08
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/src/EmployeesUI.cpp
 * EmployeesUI.cpp @endlink
 */

//? Include prototype declaration part
#include "../inc/EmployeesUI.hpp"
#include "../inc/CSVGenerator.hpp"
#include "../inc/EmployeesStatistics.hpp"
#include "../inc/EmployeesUICharts.hpp"
#include "../inc/MediaPlayer.hpp"
#include "../inc/PdfGenerator.hpp"

//? Function prototype dev part

/**
 * @fn              EmployeesUI::EmployeesUI(std::vector<SqlParam>, QWidget *)
 * @brief           Construct a new EmployeesUI::EmployeesUI object
 * @param _employee {SqlParam}
 * @param parent    {QWidget *}
 */
EmployeesUI::EmployeesUI(SqlParam _employee, QWidget *parent)
    : QMainWindow(parent), employee(_employee), ui(new Ui::EmployeesUI),
      pdf_movie(new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/"
                           "project/assets/global/icons8-pdf.gif")),
      notification_movie(
          new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/project/"
                     "assets/global/icons8-notification.gif")),
      csv_movie(new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/"
                           "project/assets/Employees/icons8-document.gif")),
      refresh_movie(
          new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/project/"
                     "assets/Employees/icons8-refresh.gif")),
      shadow_effect_components(
          new QGraphicsDropShadowEffect[SHADOWS_EFFECT_COMBO_NUMBERS]) {
  __init__();
  MediaPlayer::playNotif(
      "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/sounds/"
      "mixkit-software-interface-start-2574.wav");
}

/**
 * @fn    EmployeesUI::~EmployeesUI()
 * @brief Destroy the EmployeesUI::EmployeesUI object
 */
EmployeesUI::~EmployeesUI() {
  delete ui;
  ui = nullptr;
  delete pdf_movie;
  pdf_movie = nullptr;
  delete notification_movie;
  notification_movie = nullptr;
  delete csv_movie;
  csv_movie = nullptr;
  delete refresh_movie;
  refresh_movie = nullptr;
  delete[] shadow_effect_components;
  shadow_effect_components = nullptr;
}

/**
 * @fn     EmployeesUI::__init__()
 * @brief  Initialize Employees first view interface
 * @return void
 */
inline void EmployeesUI::__init__() {
  ui->setupUi(this);              // Default QWidget setup
  __init_current_employee_UI__(); // Init current employee
  __init_employees_table__();     // Init Employees table view
  __init_employees_charts__();    // Init Employees charts

  // Hide forms and their components
  ui->Form->hide();
  ui->updateForm->hide();
  ui->profileImageInsert->hide();
  ui->EmployeesTableWidget->horizontalHeader()->setFixedHeight(40);

  // Set pushButtons Movie (as QIcon)
  set_pushButtonMovie(ui->PDF, pdf_movie);
  set_pushButtonMovie(ui->Notification, notification_movie);
  set_pushButtonMovie(ui->CSV, csv_movie);
  set_pushButtonMovie(ui->refresh, refresh_movie);

  // Set Shadow Effect for `NB_SHADOWS` componenets
  set_shadowEffect(ui->Background_navigation, &shadow_effect_components[0]);
  set_shadowEffect(ui->Search_bar, &shadow_effect_components[1]);
  set_shadowEffect(ui->Add_button, &shadow_effect_components[2]);
  set_shadowEffect(ui->PDF, &shadow_effect_components[3]);
  set_shadowEffect(ui->Filter, &shadow_effect_components[4]);
  set_shadowEffect(ui->Notification, &shadow_effect_components[5]);
  set_shadowEffect(ui->Form, &shadow_effect_components[6]);
  set_shadowEffect(ui->updateForm, &shadow_effect_components[7]);
  set_shadowEffect(ui->EmployeesTableWidget, &shadow_effect_components[8]);
  set_shadowEffect(ui->CSV, &shadow_effect_components[9]);
  set_shadowEffect(ui->refresh, &shadow_effect_components[10]);
}

/** @fn      EmployeesUI::__init_current__employee_UI__()
 *
 * @brief   Initialize current user/employee UI
 * @details Set profile image
 * @return  void
 */
void EmployeesUI::__init_current_employee_UI__() const {
  QString profileImgPath("");
  if (!employee.strings.empty()) {
    profileImgPath = QString::fromStdString(
        employee
            .strings[Employees::EmployeeQueueFlags_strings::PROFILE_IMAGE_PATH]
            .second);
    if (profileImgPath.isEmpty() || !QFile::exists(profileImgPath))
      profileImgPath = "/home/zouari_omar/Documents/Daily/Projects/Astra/"
                       "project/assets/global/default.jpg";
  }
  scaleImg(profileImgPath, ui->User_Image);
  ui->welcome->setText(QString::fromStdString(
      "Welcome 👋, " +
      employee.strings[Employees::EmployeeQueueFlags_strings::USERNAME].second +
      " 📅 " __DATE__));
}

/** @fn     EmployeesUI::__init_form_group_box__()
 *
 * @brief  Init/Reset `ui->Form` components
 * @return void
 */
inline void EmployeesUI::__init_inset_form_group_box__() {
  ui->Form->hide();

  // Init/Reset form edit-elements
  ui->firstNameInsert->setText("");
  ui->lastNameInsert->setText("");
  ui->emailNameInsert->setText("");
  ui->passwordNameInsert->setText("");
  ui->departmentInsert->setCurrentText("");
  ui->jobInsert->setText("");
  ui->salaryInsert->setText("");
  ui->telInsert->setText("");
  ui->addressInsert->setText("");
  ui->birthdateInsert->clear();

  on_show_clicked(false);
}

/**
 * @fn     EmployeesUI::__init_form_group_box__()
 * @brief  Init/Reset `ui->updateForm` components
 * @return void
 */
inline void EmployeesUI::__init_update_form_group_box__() {
  ui->updateForm->hide();

  // Init/Reset form edit-elements
  ui->firstNameInsert_2->setText("");
  ui->lastNameInsert_2->setText("");
  ui->emailNameInsert_2->setText("");
  ui->passwordNameInsert_2->setText("");
  ui->departmentInsert_2->setCurrentIndex(0);
  ui->jobInsert_2->setText("");
  ui->salaryInsert_2->setText("");
  ui->telInsert_2->setText("");
  ui->addressInsert_2->setText("");
  ui->birthdateInsert_2->clear();
  ui->statusUpdate->setCurrentIndex(0);
  ui->profileImageInsert_2->setText("");

  on_show_2_clicked(false);
}

/**
 * @fn     EmployeesUI::__init_employees_table__()
 * @brief  Init/Async employees table view
 * @return void
 */
void EmployeesUI::__init_employees_table__() {
  // Select all employees except the root admin
  Employees::Select *sl = new Employees::Select;
  std::vector<SqlParam> employees =
      sl->selectAllExcept(Employees::EmployeeInfo<std::string>(
          std::to_string(
              employee
                  .integers[Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID]
                  .second),
          Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID));
  delete sl;
  sl = nullptr;

  // Clear existing table
  __clear_employees_table__();

  // Set up the rows for the QTableWidget
  size_t rows = employees.size();
  ui->EmployeesTableWidget->setRowCount(rows);
  ui->EmployeesTableWidget->viewport()->update();

  // Populate columns 0 - 4 (non-button cells)
  for (size_t row{}; row < rows; row++) {
    { // Column 0: Image profile
      QTableWidgetItem *item(new QTableWidgetItem());
      std::string profileImgPath;
      if (!employees[row].strings.empty()) {
        profileImgPath =
            employees[row]
                .strings
                    [Employees::EmployeeQueueFlags_strings::PROFILE_IMAGE_PATH]
                .second;
        (!profileImgPath.empty() &&
         QFile::exists(QString::fromStdString(profileImgPath)))
            ? item->setIcon(QIcon(QString::fromStdString(profileImgPath)))
            : item->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/"
                                  "Astra/project/assets/global/default.jpg"));
        item->setData(Qt::UserRole, QString::fromStdString(profileImgPath));
        ui->EmployeesTableWidget->setItem(row, 0, item);
      }
    }
    { // Column 1: Username
      QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(
          employees[row]
              .strings[Employees::EmployeeQueueFlags_strings::USERNAME]
              .second));
      ui->EmployeesTableWidget->setItem(row, 1, item);
    }
    { // Column 2: Email
      QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(
          employees[row]
              .strings[Employees::EmployeeQueueFlags_strings::EMAIL]
              .second));
      ui->EmployeesTableWidget->setItem(row, 2, item);
    }
    { // Column 3: Department
      QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(
          employees[row]
              .strings[Employees::EmployeeQueueFlags_strings::DEPARTMENT]
              .second));
      ui->EmployeesTableWidget->setItem(row, 3, item);
    }
    { // Column 4: Status
      QTableWidgetItem *item = new QTableWidgetItem;
      std::string status =
          strToUpper(employees[row]
                         .strings[Employees::EmployeeQueueFlags_strings::STATUS]
                         .second);
      if (status == "ACTIVE")
        item->setIcon(
            QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/"
                  "assets/Employees/icons8-green-circle-48.png"));
      else if (status == "INACTIVE")
        item->setIcon(
            QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/"
                  "assets/Employees/icons8-yellow-circle-48.png"));
      else // SUSPENDED
        item->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/"
                            "project/assets/Employees/icons8-red-48.png"));
      item->setData(Qt::UserRole, QString::fromStdString(status));
      ui->EmployeesTableWidget->setItem(row, 4, item);
    }
  }

  for (size_t row{}; row < rows;
       row++) { // Set up column 5 with the action button for each row
    if (ui->EmployeesTableWidget->cellWidget(
            row, 5)) // Ensure previous widget is cleared
      ui->EmployeesTableWidget->setCellWidget(row, 5, nullptr);

    QPointer<QPushButton> button(new QPushButton);
    button->setIcon(
        QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
              "Employees/icons8-menu-vertical-50.png"));
    button->setStyleSheet("border-radius: 0px;padding-left: 0px;");

    // Create the menu
    QPointer<QMenu> menu(new QMenu(button));
    QPointer<QAction> updateAction(new QAction("Update", menu)),
        deleteAction(new QAction("Delete", menu));
    updateAction->setIcon(
        QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
              "Employees/icons8-edit-50.png"));
    deleteAction->setIcon(
        QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
              "Employees/icons8-delete-50.png"));
    menu->addAction(updateAction), menu->addAction(deleteAction),
        button->setMenu(menu);

    connect(
        updateAction, &QAction::triggered, this,
        [this, row, employees]() { // * On update signal
          ui->updateForm->show();
          __init_inset_form_group_box__();
          ui->updateForm->setTitle(QString::fromStdString(
              "     Update " +
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::USERNAME]
                  .second));
          // Hold the actual employee data into the `ui->updateForm`
          ui->lastNameInsert_2->setText(QString::fromStdString(
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::LASTNAME]
                  .second));
          ui->firstNameInsert_2->setText(QString::fromStdString(
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::FIRSTNAME]
                  .second));
          ui->emailNameInsert_2->setText(QString::fromStdString(
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::EMAIL]
                  .second));
          ui->passwordNameInsert_2->setText(QString::fromStdString(
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::PASSWORD]
                  .second));
          ui->departmentInsert_2->setCurrentText(QString::fromStdString(
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::DEPARTMENT]
                  .second));
          ui->jobInsert_2->setText(QString::fromStdString(
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::JOBTITLE]
                  .second));
          ui->salaryInsert_2->setText(QString::fromStdString(std::to_string(
              employees[row]
                  .integers[Employees::EmployeeQueueFlags_integers::SALARY]
                  .second)));
          ui->telInsert_2->setText(QString::fromStdString(std::to_string(
              employees[row]
                  .integers
                      [Employees::EmployeeQueueFlags_integers::PHONE_NUMBER]
                  .second)));
          ui->addressInsert_2->setText(QString::fromStdString(
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::ADDRESS]
                  .second));
          oracle::occi::Date date =
              employees[row]
                  .dates[Employees::EmployeeQueueFlags_dates::BIRTHDATE]
                  .second;
          profileImgUpdateHolder =
              employees[row]
                  .strings[Employees::EmployeeQueueFlags_strings::
                               PROFILE_IMAGE_PATH]
                  .second;
          if (!date.isNull()) {
            // Declare variables to hold date components
            u_int month, day, hour, min, sec;
            int year;
            date.getDate(
                year, month, day, hour, min,
                sec); // Extract the year, month, and day using getDate()
            ui->birthdateInsert_2->setDate(QDate(year, month, day));
          }
        });
    connect(
        deleteAction, &QAction::triggered, this,
        [this, row, employees]() { // * On delete signal
          Employees::Delete *del = new Employees::Delete;
          int affRow = del->del(Employees::EmployeeInfo(
              std::to_string(
                  employees[row]
                      .integers
                          [Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID]
                      .second),
              Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID));
          delete del;
          if (affRow) {
            MediaPlayer::playNotif(
                "/home/zouari_omar/Documents/Daily/Projects/Astra/project/"
                "assets/sounds/mixkit-software-interface-remove-2576.wav");
            QMessageBox::information(
                this, "Deletion Successful",
                "The employee has been successfully deleted!");
          } else {
            MediaPlayer::playNotif(
                "/home/zouari_omar/Documents/Daily/Projects/Astra/project/"
                "assets/sounds/mixkit-software-interface-start-2574.wav");
            QMessageBox::warning(
                this, "Deletion Failed",
                "Failed to delete the employee.\nPlease try again.");
          }

          ui->EmployeesTableWidget->removeRow(row);
          __init_employees_charts__();
        });

    ui->EmployeesTableWidget->setCellWidget(row, 5, button);
  }
}

/**
 * @fn     EmployeesUI::__clear_employees_table__()
 * @brief  Clears the contents of the Employees Table `ui->EmployeesTableWidget`
 * @return void
 */
void EmployeesUI::__clear_employees_table__() const {
  int rows = ui->EmployeesTableWidget->rowCount(),
      cols = ui->EmployeesTableWidget->columnCount();

  for (int row{}; row < rows; ++row)
    for (int col{}; col < cols; ++col) {
      QWidget *widget = ui->EmployeesTableWidget->cellWidget(row, col);
      if (widget)
        ui->EmployeesTableWidget->setCellWidget(row, col, nullptr),
            widget->deleteLater();
      QTableWidgetItem *item = ui->EmployeesTableWidget->item(row, col);
      if (item)
        delete item;
    }
  ui->EmployeesTableWidget->clearContents();
  ui->EmployeesTableWidget->setRowCount(0);
  QApplication::processEvents();
}

/**
 * @fn     EmployeesUI::__init_employees_charts__()
 * @brief  Init/Async employees charts view
 * @return void
 */
void EmployeesUI::__init_employees_charts__() {
  EmployeesStatistics *stats = new EmployeesStatistics(employee);
  const std::vector<unsigned int> statuses(stats->getStatusStats());
  const std::vector<double> departments(stats->getDepartmentStats()),
      salaries(stats->getSalaryStats());
  delete stats;
  stats = nullptr;

  Employees::EmployeesUICharts charts(this);
  charts.setPieChart(
      ui->pieChartFrame,
      {{"Commercial",
        departments[Employees::EmployeeDepartmentFlags::COMMERCIAL]},
       {"Shops", departments[Employees::EmployeeDepartmentFlags::SHOPS]},
       {"Partners", departments[Employees::EmployeeDepartmentFlags::PARTNERS]},
       {"Events", departments[Employees::EmployeeDepartmentFlags::EVENTS]},
       {"Personals",
        departments[Employees::EmployeeDepartmentFlags::PERSONALS]},
       {"Employees",
        departments[Employees::EmployeeDepartmentFlags::EMPLOYEES]}});
  charts.setBarChart(
      ui->BarChartFrame,
      {{"Active", statuses[Employees::EmployeeStatusFlags::ACTIVE - 1]},
       {"Inactive", statuses[Employees::EmployeeStatusFlags::INACTIVE - 1]},
       {"Suspended", statuses[Employees::EmployeeStatusFlags::SUSPENDED - 1]}});
  charts.setBarLineChart(
      ui->BarLineChartFrame,
      {{"Commercial", salaries[Employees::EmployeeDepartmentFlags::COMMERCIAL]},
       {"Shops", salaries[Employees::EmployeeDepartmentFlags::SHOPS]},
       {"Partners", salaries[Employees::EmployeeDepartmentFlags::PARTNERS]},
       {"Events", salaries[Employees::EmployeeDepartmentFlags::EVENTS]},
       {"Personals", salaries[Employees::EmployeeDepartmentFlags::PERSONALS]},
       {"Employees", salaries[Employees::EmployeeDepartmentFlags::EMPLOYEES]}});
}

/**
 * @fn     EmployeesUI::syncUI()
 * @brief  Synchronies UI data
 * @return void
 */
void EmployeesUI::syncUI() {
  ui->Filter->setCurrentIndex(Employees::EmployeeStatusFlags::ALL);
  ui->Search_bar->setText("");
  __init_employees_table__(), __init_employees_charts__();
}

/**
 * @fn              EmployeesUI::set_employee(const std::vector<SqlParam> &)
 * @brief           Set employee data
 * @param _employee {const SqlParam &}
 * @return          void
 */
void EmployeesUI::set_employee(const SqlParam &_employee) {
  employee = _employee;
}

// * ================================================
// ? ============ Effects handling part =============
// * ================================================

/**
 * @fn          EmployeesUI::set_pushButtonMovie(QPushButton *, QMovie *) const
 * @brief       Set GIF as a button icon
 * @param btn   {QPushButton *}
 * @param movie {QMovie *}
 * @return      void
 */
void EmployeesUI::set_pushButtonMovie(QPushButton *btn, QMovie *movie) const {
  connect(movie, &QMovie::frameChanged, [=] {
    if (!movie->currentPixmap().isNull())
      btn->setIcon(movie->currentPixmap());
  });
  movie->start();
}

// * ==========================================
// ? ======== / Effects handling part =========
// ? ====== `ui->Form` Events & signals =======
// * ==========================================

/**
 * @fn     EmployeesUI::on_Add_button_clicked()
 * @brief  Listen to "Add" button click action
 * @return void
 */
void EmployeesUI::on_Add_button_clicked() {
  ui->Form->show();
  __init_update_form_group_box__(); // Reset the Update form (in case it is
                                    // already in use or open)
}

/**
 * @fn     EmployeesUI::on_Cancel_form_clicked()
 * @brief  Listen to "Cancel" button click action inside `ui->Form` QGroupBox
 * @return void
 */
void EmployeesUI::on_Cancel_form_clicked() { __init_inset_form_group_box__(); }

/**
 * @fn            EmployeesUI::on_show_clicked(bool)
 * @brief         Listen to "Show More/Less" button click action inside
 * `ui->Form` QGroupBox
 * @param checked bool
 * @return        void
 */
void EmployeesUI::on_show_clicked(bool checked) {
  if (checked) {
    ui->Form->resize(410, ui->Form->height());
    ui->profileImageInsert->show();
    ui->show->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/"
                            "project/assets/Employees/icons8-left.png"));
    ui->Cancel_form->move(380, ui->Cancel_form->y());
    ui->insertBtn->move(340, ui->insertBtn->y());
  } else {
    ui->Form->resize(210, ui->Form->height());
    ui->profileImageInsert->hide();
    ui->show->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/"
                            "project/assets/Employees/icons8-right.png"));
    ui->Cancel_form->move(180, ui->Cancel_form->y());
    ui->insertBtn->move(140, ui->insertBtn->y());
  }
}

/**
 * @fn      EmployeesUI::on_profileImageInsert_clicked()
 * @brief   Listen to "Profile Image" employee button click action
 * @details `ui->profileImageInsert` inside `ui->Form`
 * @return  void
 */
void EmployeesUI::on_profileImageInsert_clicked() {
  profileImgInsertHolder =
      QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
                                   tr("Image Files (*.png *.jpg *.bmp)"))
          .toStdString();
}

/**
 * @fn      EmployeesUI::on_insertBtn_clicked()
 * @brief   Listen to "Add" employee button click action
 * @return  void
 */
void EmployeesUI::on_insertBtn_clicked() {
  // 1. Hold data from UI (Req data)
  std::string firstName = ui->firstNameInsert->text().toStdString(),
              lastName = ui->lastNameInsert->text().toStdString(),
              email = ui->emailNameInsert->text().toStdString(),
              password = ui->passwordNameInsert->text().toStdString(),
              department = ui->departmentInsert->currentText().toStdString(),
              job = ui->jobInsert->text().toStdString(),
              address = ui->addressInsert->text().toStdString(),
              birthday = ui->birthdateInsert->text().toStdString();
  int salary = ui->salaryInsert->text().toInt(),
      tel = ui->telInsert->text().toInt();
  oracle::occi::Date birthdayDate(
      Environment::createEnvironment(Environment::DEFAULT),
      ui->birthdateInsert->date().year(), ui->birthdateInsert->date().month(),
      ui->birthdateInsert->date().day());

  // 2. Verify the passed data
  std::pair<Employees::EmployeeCheckerFlags, const char *> st{
      Employees::EmployeeChecker::is_valid(
          email, firstName, lastName, password, department, "",
          {Employees::EmployeeCheckerFlags::UNIQUE_EMAIL, email.c_str()})};
  if (st.first) {
    QMessageBox::warning(this, tr("Astra"), tr(st.second), QMessageBox::Ok);
    return;
  }

  // 3. Insert the given data
  Employees::Insert *ist(new Employees::Insert);
  int affRow = ist->insert(
      Employees::EmployeeInfo<std::string>(
          email, Employees::EmployeeQueueFlags_strings::EMAIL),
      Employees::EmployeeInfo<std::string>(
          firstName, Employees::EmployeeQueueFlags_strings::FIRSTNAME),
      Employees::EmployeeInfo<std::string>(
          lastName, Employees::EmployeeQueueFlags_strings::LASTNAME),
      Employees::EmployeeInfo<std::string>(
          password, Employees::EmployeeQueueFlags_strings::PASSWORD),
      Employees::EmployeeInfo<std::string>(
          department, Employees::EmployeeQueueFlags_strings::DEPARTMENT),
      Employees::EmployeeInfo<std::string>(
          job, Employees::EmployeeQueueFlags_strings::JOBTITLE),
      Employees::EmployeeInfo<std::string>(
          address, Employees::EmployeeQueueFlags_strings::ADDRESS),
      Employees::EmployeeInfo<std::string>(
          profileImgInsertHolder,
          Employees::EmployeeQueueFlags_strings::PROFILE_IMAGE_PATH),
      Employees::EmployeeInfo<int>(
          salary, Employees::EmployeeQueueFlags_integers::SALARY),
      Employees::EmployeeInfo<int>(
          tel, Employees::EmployeeQueueFlags_integers::PHONE_NUMBER),
      Employees::EmployeeInfo<oracle::occi::Date>(
          birthdayDate, Employees::EmployeeQueueFlags_dates::BIRTHDATE));

  // 4. Show a QMessageBox on success/failed operation
  if (affRow) {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-remove-2576.wav");
    QMessageBox::information(
        this, tr("Astra"), tr("Employee added successfully!"), QMessageBox::Ok);
  } else {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-start-2574.wav");
    QMessageBox::warning(this, tr("Astra"),
                         tr("Error: Can't insert the given employee data!"),
                         QMessageBox::Ok);
  }
  // 5. Refresh the table (just add the last(new) inserted employee)
  syncUI();

  // 6. Reset the form (optional)
  __init_inset_form_group_box__();
}

void insertRow_employees_table() {}

// * ================================================
// ? ========= / `ui->Form` Events & signals ========
// ? ====== `ui->updateForm` Events & signals =======
// * ================================================

/**
 * @fn     EmployeesUI::on_Cancel_form_2_clicked()
 * @brief  Listen to "Cancel" button click action inside `ui->updateForm`
 * QGroupBox
 * @return void
 */
void EmployeesUI::on_Cancel_form_2_clicked() {
  __init_update_form_group_box__();
}

/**
 * @fn            EmployeesUI::on_show_2_clicked(bool)
 * @brief         Listen to "Show More/Less" button click action inside
 * `ui->updateForm` QGroupBox
 * @class         EmployeesUI
 * @param checked bool
 * @return        void
 */
void EmployeesUI::on_show_2_clicked(bool checked) {
  if (checked) {
    ui->updateForm->resize(610, ui->Form->height());
    ui->show_2->setIcon(
        QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
              "Employees/icons8-left.png"));
    ui->Cancel_form_2->move(580, ui->Cancel_form->y());
    ui->updateBtn->move(540, ui->insertBtn->y());
  } else {
    ui->updateForm->resize(210, ui->Form->height());
    ui->show_2->setIcon(
        QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
              "Employees/icons8-right.png"));
    ui->Cancel_form_2->move(180, ui->Cancel_form->y());
    ui->updateBtn->move(140, ui->insertBtn->y());
  }
}

/**
 * @fn      EmployeesUI::on_profileImageInsert_2_clicked()
 * @brief   Listen to "Profile Image" employee button click action
 * @details `ui->profileImageInsert_2` inside `ui->updateForm`
 * @return  void
 */
void EmployeesUI::on_profileImageInsert_2_clicked() {
  profileImgUpdateHolder =
      QFileDialog::getOpenFileName(this, tr("Open Image"), "/",
                                   tr("Image Files (*.png *.jpg *.bmp)"))
          .toStdString();
}

/**
 * @fn     EmployeesUI::on_updateBtn_clicked()
 * @brief  Listen to "Update" employee button click action
 * @return void
 */
void EmployeesUI::on_updateBtn_clicked() {
  // 1. Hold data from `ui->updateForm` (Req data)
  std::string firstName = ui->firstNameInsert_2->text().toStdString(),
              lastName = ui->lastNameInsert_2->text().toStdString(),
              email = ui->emailNameInsert_2->text().toStdString(),
              password = ui->passwordNameInsert_2->text().toStdString(),
              department = ui->departmentInsert_2->currentText().toStdString(),
              username = extractUsername(ui->updateForm->title().toStdString()),
              statusEmp = ui->statusUpdate->currentText().toStdString(),
              job = ui->jobInsert_2->text().toStdString(),
              address = ui->addressInsert_2->text().toStdString(),
              birthday = ui->birthdateInsert_2->text().toStdString();
  int salary = ui->salaryInsert_2->text().toInt(),
      tel = ui->telInsert_2->text().toInt();
  oracle::occi::Date birthdayDate(
      Environment::createEnvironment(Environment::DEFAULT),
      ui->birthdateInsert_2->date().year(),
      ui->birthdateInsert_2->date().month(),
      ui->birthdateInsert_2->date().day());

  // 2. Verify the passed data
  std::pair<Employees::EmployeeCheckerFlags, const char *> status{
      Employees::EmployeeChecker::is_valid(
          email, firstName, lastName, password, department, statusEmp,
          {Employees::EmployeeCheckerFlags::UNIQUE_EMAIL_WITH_EXCEPTION,
           username.c_str()})};
  if (status.first) {
    QMessageBox::warning(this, tr("Astra"), tr(status.second), QMessageBox::Ok);
    return;
  }

  // 3. Update the given data
  Employees::Update *up(new Employees::Update);
  int affRow = up->update(
      Employees::EmployeeInfo<std::string>(
          username, Employees::EmployeeQueueFlags_strings::USERNAME),
      Employees::EmployeeInfo<std::string>(
          email, Employees::EmployeeQueueFlags_strings::EMAIL),
      Employees::EmployeeInfo<std::string>(
          firstName, Employees::EmployeeQueueFlags_strings::FIRSTNAME),
      Employees::EmployeeInfo<std::string>(
          lastName, Employees::EmployeeQueueFlags_strings::LASTNAME),
      Employees::EmployeeInfo<std::string>(
          password, Employees::EmployeeQueueFlags_strings::PASSWORD),
      Employees::EmployeeInfo<std::string>(
          department, Employees::EmployeeQueueFlags_strings::DEPARTMENT),
      Employees::EmployeeInfo<std::string>(
          job, Employees::EmployeeQueueFlags_strings::JOBTITLE),
      Employees::EmployeeInfo<std::string>(
          address, Employees::EmployeeQueueFlags_strings::ADDRESS),
      Employees::EmployeeInfo<std::string>(
          profileImgUpdateHolder,
          Employees::EmployeeQueueFlags_strings::PROFILE_IMAGE_PATH),
      Employees::EmployeeInfo<std::string>(
          statusEmp, Employees::EmployeeQueueFlags_strings::STATUS),
      Employees::EmployeeInfo<int>(
          salary, Employees::EmployeeQueueFlags_integers::SALARY),
      Employees::EmployeeInfo<int>(
          tel, Employees::EmployeeQueueFlags_integers::PHONE_NUMBER),
      Employees::EmployeeInfo<oracle::occi::Date>(
          birthdayDate, Employees::EmployeeQueueFlags_dates::BIRTHDATE));
  delete up;
  up = nullptr;

  // 4. Show a QMessageBox on success/failed operation
  if (affRow) {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-remove-2576.wav");
    QMessageBox::information(this, tr("Astra"),
                             tr("Employee Update it successfully!"),
                             QMessageBox::Ok);
  } else {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-start-2574.wav");
    QMessageBox::warning(this, tr("Astra"),
                         tr("Error: Can't Update the given employee data!"),
                         QMessageBox::Ok);
  }
  // 5. Refresh the table (just show the update it employee)
  syncUI();

  // 6. Reset the form (optional)
  __init_update_form_group_box__();
}

/** @fn EmployeesUI::on_Filter_activated(const QString &)
 *
 * @brief     Re-evaluate table on search input change
 * @param arg {const QString &}
 * @return    void
 */
void EmployeesUI::on_Search_bar_textChanged(const QString &arg) {
  Q_UNUSED(arg);
  filterEmployees(ui->EmployeesTableWidget, ui->Filter, ui->Search_bar);
}

/** @fn EmployeesUI::on_Filter_activated(const QString &)
 *
 * @brief     Re-evaluate table on filter change
 * @param arg {const QString &}
 * @return    void
 */
void EmployeesUI::on_Filter_currentTextChanged(const QString &arg) {
  Q_UNUSED(arg);
  filterEmployees(ui->EmployeesTableWidget, ui->Filter, ui->Search_bar);
}

/** @brief Listen to `ui->PDF` click action
 *
 * @fn     EmployeesUI::on_PDF_clicked()
 * @return void
 * @link
 * https://www.qcustomplot.com/index.php/tutorials/specialcases/textdocument
 * @endlink
 */
void EmployeesUI::on_PDF_clicked() {
  QString pdfPath = QFileDialog::getSaveFileName(nullptr, "Save as PDF...",
                                                 "Report", "PDF Files (*.pdf)");
  if (pdfPath.isEmpty()) {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-start-2574.wav");
    QMessageBox::warning(this, tr("Astra - Warning"), tr("No file selected!"));
    return;
  }

  if (!pdfPath.endsWith(".pdf", Qt::CaseInsensitive))
    pdfPath += ".pdf"; // Ensure it has the .pdf extension

  if (PdfGenerator::generatePdf(pdfPath, employee)) {
    QMessageBox::warning(this, tr("Astra - PDF Generator"),
                         tr("PDF Generated Failed!"), QMessageBox::Ok);
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-start-2574.wav");
  } else {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-remove-2576.wav");
    QMessageBox::information(
        this, tr("Astra - Pdf Generator"),
        tr(("PDF Generated Successfully at: \n" + pdfPath.toStdString())
               .c_str()),
        QMessageBox::Ok);
  }
}

/** @brief Listen to `ui->refresh` click action
 *
 * @fn     EmployeesUI::on_refresh_clicked()
 * @return void
 */
void EmployeesUI::on_refresh_clicked() {
  MediaPlayer::playNotif(
      "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/sounds/"
      "mixkit-message-pop-alert-2354.mp3");
  syncUI();
}

void EmployeesUI::on_CSV_clicked() {
  QString csvPath = QFileDialog::getSaveFileName(
      nullptr, "Save as csv...", "Employees table", "CSV Files (*.csv)");
  if (csvPath.isEmpty()) {
    QMessageBox::warning(this, tr("Astra - Warning"), tr("No file selected!"));
    return;
  }

  if (!csvPath.endsWith(".csv", Qt::CaseInsensitive))
    csvPath += ".csv"; // Ensure it has the .csv extension
  if (CSVGenerator::generateCSV(csvPath.toStdString(),
                                extractTableData(ui->EmployeesTableWidget))) {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-start-2574.wav");
    QMessageBox::warning(this, tr("Astra - CSV Generator"),
                         tr("CSV Generated Failed!"), QMessageBox::Ok);
  } else {
    MediaPlayer::playNotif(
        "/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/"
        "sounds/mixkit-software-interface-remove-2576.wav");
    QMessageBox::information(
        this, tr("Astra - CSV Generator"),
        tr(("CSV Generated Successfully at: \n" + csvPath.toStdString())
               .c_str()),
        QMessageBox::Ok);
  }
}

// * ==========================================================
// ? ====== / `ui->updateForm` Events & signals ===============
// * ==========================================================
