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
EmployeesUI::EmployeesUI(std::vector<SqlParam> _employee, QWidget *parent)
    : QMainWindow(parent),
      employee(_employee),
      ui(new Ui::EmployeesUI),
      pdf_movie(new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/global/icons8-pdf.gif")),
      notification_movie(new QMovie("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/global/icons8-notification.gif")),
      shadow_effect_components(new QGraphicsDropShadowEffect[SHADOWS_EFFECT_COMBO_NUMBERS]) {
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

  // Hide the update form
  ui->updateForm->hide();

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
  set_shadowEffect(ui->updateForm, &shadow_effect_components[7]);
}

/**
 * @brief ### Inint/Reset `ui->Form` QGroupBox
 *
 * @class   EmployeesUI
 * @return  void
 */
inline void EmployeesUI::__init_form_group_box__() {
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

inline void EmployeesUI::__init_update_form_group_box__() {
  ui->updateForm->hide();

  // Init/Reset form edit-elements
  ui->firstNameInsert_2->setText("");
  ui->lastNameInsert_2->setText("");
  ui->emailNameInsert_2->setText("");
  ui->passwordNameInsert_2->setText("");
  ui->departmentInsert_2->setCurrentText("");
  ui->jobInsert_2->setText("");
  ui->salaryInsert_2->setText("");
  ui->telInsert_2->setText("");
  ui->addressInsert_2->setText("");
  ui->birthdateInsert_2->clear();

  on_show_2_clicked(false);
}

/**
 * @brief ### Init/Async employees table view
 *
 * @class EmployeesUI
 */
inline void EmployeesUI::__init_employees_table__() {
  ui->EmployeesTableWidget->clear(); // Clear the table (need it for Async action)

  // Set the header label
  ui->EmployeesTableWidget->setHorizontalHeaderLabels(QStringList()
                                                      << "Profile Image"
                                                      << "Username"
                                                      << "Email"
                                                      << "Department"
                                                      << "Status"
                                                      << "Actions");

  // Select all employees except the root admin
  Employees::Select *sl = new Employees::Select;
  std::vector<SqlParam> employees = sl->selectAllExcept(Employees::EmployeeInfo<std::string>(
      std::to_string(employee[0].integers[Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID].second),
      Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID));

  // Set up the rows for the QTableWidget
  size_t rows{employees.size()};
  int columns{ui->EmployeesTableWidget->columnCount()}; // * 5 columns for now
  ui->EmployeesTableWidget->setRowCount(rows);          // Set row count

  for (size_t row{}; row < rows; ++row) {
    for (int col{}; col < columns; ++col) {
      QTableWidgetItem *item{nullptr};
      std::string profileImgPath;

      switch (col) {
      case 0: { // Show image profile
        if (!employees[row].strings.empty()) {
          profileImgPath = employees[row].strings[Employees::EmployeeQueueFlags_strings::PROFILE_IMAGE_PATH].second;

          if (!profileImgPath.empty() && QFile::exists(QString::fromStdString(profileImgPath))) {
            QPixmap pixmap(QString::fromStdString(profileImgPath));
            if (!pixmap.isNull()) {
              item = new QTableWidgetItem();
              item->setIcon(QIcon(pixmap));
            }
          } else {
            QPixmap defaultPixmap("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/global/default.jpg");
            item = new QTableWidgetItem();
            item->setIcon(QIcon(defaultPixmap)); // Set default image icon
          }

          // Center the image
          item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
          ui->EmployeesTableWidget->setItem(row, col, item);
          break;
        }
      }

      case 1: { // Show username
        item = new QTableWidgetItem(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::USERNAME].second));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;
      }

      case 2: { // Show email
        item = new QTableWidgetItem(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::EMAIL].second));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;
      }

      case 3: { // Show department
        item = new QTableWidgetItem(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::DEPARTMENT].second));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;
      }

      case 4: { // Show status
        item = new QTableWidgetItem(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::STATUS].second));
        ui->EmployeesTableWidget->setItem(row, col, item);
        break;
      }

      case 5: { // Show Actions (Button)
        QPushButton *button = new QPushButton("...");

        // Create menu
        QMenu *menu = new QMenu(button);
        QAction *updateAction = new QAction("Update", menu),
                *deleteAction = new QAction("Delete", menu);

        menu->addAction(updateAction), menu->addAction(deleteAction); // Add actions to the menu
        button->setMenu(menu);                                        // Set the menu for the button

        connect(updateAction, &QAction::triggered, this, [this, row, employees]() -> void { // * On Update click
          ui->updateForm->show();
          __init_form_group_box__();                                                                                                                         // Reset the insert form (in case it is already in use or open)
          ui->updateForm->setTitle(QString::fromStdString("     Update " + employees[row].strings[Employees::EmployeeQueueFlags_strings::USERNAME].second)); // Set the title "Update USERNAME"

          // Hold the actual employee data into the `ui->updateForm`
          ui->lastNameInsert_2->setText(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::LASTNAME].second));
          ui->firstNameInsert_2->setText(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::FIRSTNAME].second));
          ui->emailNameInsert_2->setText(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::EMAIL].second));
          ui->passwordNameInsert_2->setText(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::PASSWORD].second));
          ui->departmentInsert_2->setCurrentText(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::DEPARTMENT].second));
          ui->jobInsert_2->setText(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::JOBTITLE].second));
          ui->salaryInsert_2->setText(QString::fromStdString(std::to_string(employees[row].integers[Employees::EmployeeQueueFlags_integers::SALARY].second)));
          ui->telInsert_2->setText(QString::fromStdString(std::to_string(employees[row].integers[Employees::EmployeeQueueFlags_integers::PHONE_NUMBER].second)));
          ui->addressInsert_2->setText(QString::fromStdString(employees[row].strings[Employees::EmployeeQueueFlags_strings::ADDRESS].second));
          oracle::occi::Date date = employees[row].dates[Employees::EmployeeQueueFlags_dates::BIRTHDATE].second;
          if (!date.isNull()) {
            // Declare variables to hold date components
            u_int month, day, hour, min, sec;
            int year;
            date.getDate(year, month, day, hour, min, sec); // Extract the year, month, and day using getDate()
            ui->birthdateInsert_2->setDate(QDate(year, month, day));
          }
        });

        connect(deleteAction, &QAction::triggered, this, [this, row, employees]() -> void { // * On Delete click
          Employees::Delete del;
          int affRow = del.del(Employees::EmployeeInfo(
              std::to_string(employees[row].integers[Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID].second),
              Employees::EmployeeQueueFlags_integers::EMPLOYEE_ID));
          (affRow) ? QMessageBox::information(this, "Deletion Successful", "The employee has been successfully deleted!")
                   : QMessageBox::warning(this, "Deletion Failed", "Failed to delete the employee.\nPlease try again.");
          __init_employees_table__(); // Async EmployeesTableWidget update
        });

        ui->EmployeesTableWidget->setCellWidget(row, col, button);
        break;
      }

      default:
        break;
      }
    }
  }
}

/**
 * @brief ### Set employee data
 *
 * @class           EmployeesUI
 * @param _employee {const std::vector<SqlParam> &}
 * @return          void
 */
void EmployeesUI::set_employee(const std::vector<SqlParam> &_employee) {
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
  __init_update_form_group_box__(); // Reset the Update form (in case it is already in use or open)
}

/**
 * @brief Listen to "Cancel" button click action inside `ui->Form` QGroupBox
 *
 * @class         EmployeesUI
 * @return        void
 */
void EmployeesUI::on_Cancel_form_clicked() {
  __init_form_group_box__();
}

/**
 * @brief Listen to "Cancel" button click action inside `ui->updateForm` QGroupBox
 *
 * @class         EmployeesUI
 * @return        void
 */
void EmployeesUI::on_Cancel_form_2_clicked() {
  __init_update_form_group_box__();
}

/**
 * @brief ### Listen to "Show More/Less" button click action inside `ui->Form` QGroupBox
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
 * @brief ### Listen to "Show More/Less" button click action inside `ui->updateForm` QGroupBox
 *
 * @class         EmployeesUI
 * @param checked bool
 * @return        void
 */
void EmployeesUI::on_show_2_clicked(bool checked) {
  if (checked) {
    ui->updateForm->resize(411, ui->Form->height());
    ui->profileImageInsert_2->show();
    ui->show_2->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/Employees/icons8-left.png"));
    ui->Cancel_form_2->move(380, ui->Cancel_form->y());
    ui->updateBtn->move(340, ui->insertBtn->y());
  } else {
    ui->updateForm->resize(211, ui->Form->height());
    ui->profileImageInsert_2->hide();
    ui->show_2->setIcon(QIcon("/home/zouari_omar/Documents/Daily/Projects/Astra/project/assets/Employees/icons8-right.png"));
    ui->Cancel_form_2->move(180, ui->Cancel_form->y());
    ui->updateBtn->move(140, ui->insertBtn->y());
  }
}

/**
 * @fn      EmployeesUI::on_profileImageInsert_clicked()
 * @brief   Listen to "Profile Image" employee button click action
 * @details `ui->profileImageInsert` inside `ui->Form`
 */
void EmployeesUI::on_profileImageInsert_clicked() {
  ui->profileImageInsert->setText(QFileDialog::getOpenFileName(this,
                                                               tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)")));
}

/**
 * @brief ### Listen to "Add" employee button click action
 *
 * @class  EmployeesUI
 * @return void
 */
void EmployeesUI::on_insertBtn_clicked() {
  // 1. Hold data from UI (Req data)
  std::string firstName = ui->firstNameInsert->text().toStdString();
  std::string lastName = ui->lastNameInsert->text().toStdString();
  std::string email = ui->emailNameInsert->text().toStdString();
  std::string password = ui->passwordNameInsert->text().toStdString();
  std::string department = ui->departmentInsert->currentText().toStdString();
  std::string job = ui->jobInsert->text().toStdString();
  int salary = ui->salaryInsert->text().toInt();
  int tel = ui->telInsert->text().toInt();
  std::string address = ui->addressInsert->text().toStdString();
  std::string birthday = ui->birthdateInsert->text().toStdString();
  std::string profileImgPath = ui->profileImageInsert->text().toStdString();
  // qDebug() << profileImgPath;

  int year = ui->birthdateInsert->date().year();
  int month = ui->birthdateInsert->date().month();
  int day = ui->birthdateInsert->date().day();
  oracle::occi::Date date(Environment::createEnvironment(Environment::DEFAULT), year, month, day);

  // 2. Verify the passed data
  std::pair<Employees::EmployeeCheckerFlags, const char *>
      st{Employees::EmployeeChecker::is_valid(email, firstName, lastName, password, department, {Employees::EmployeeCheckerFlags::UNIQUE_EMAIL, email.c_str()})};
  if (st.first) {
    QMessageBox::warning(this, tr("Astra"),
                         tr(st.second),
                         QMessageBox::Ok);
    return;
  }

  // 3. Insert the given data
  int affRow{};
  Employees::Insert *ist(new Employees::Insert);
  (ui->show->isChecked()) ? affRow = ist->insert(Employees::EmployeeInfo<std::string>(email, Employees::EmployeeQueueFlags_strings::EMAIL),
                                                 Employees::EmployeeInfo<std::string>(firstName, Employees::EmployeeQueueFlags_strings::FIRSTNAME),
                                                 Employees::EmployeeInfo<std::string>(lastName, Employees::EmployeeQueueFlags_strings::LASTNAME),
                                                 Employees::EmployeeInfo<std::string>(password, Employees::EmployeeQueueFlags_strings::PASSWORD),
                                                 Employees::EmployeeInfo<std::string>(department, Employees::EmployeeQueueFlags_strings::DEPARTMENT),
                                                 Employees::EmployeeInfo<std::string>(job, Employees::EmployeeQueueFlags_strings::JOBTITLE),
                                                 Employees::EmployeeInfo<std::string>(address, Employees::EmployeeQueueFlags_strings::ADDRESS),
                                                 Employees::EmployeeInfo<std::string>(profileImgPath, Employees::EmployeeQueueFlags_strings::PROFILE_IMAGE_PATH),
                                                 Employees::EmployeeInfo<int>(salary, Employees::EmployeeQueueFlags_integers::SALARY),
                                                 Employees::EmployeeInfo<int>(tel, Employees::EmployeeQueueFlags_integers::PHONE_NUMBER),
                                                 Employees::EmployeeInfo<oracle::occi::Date>(date, Employees::EmployeeQueueFlags_dates::BIRTHDATE))
                          : // Inset the required employee data
      affRow = ist->insert(Employees::EmployeeInfo<std::string>(email, Employees::EmployeeQueueFlags_strings::EMAIL),
                           Employees::EmployeeInfo<std::string>(firstName, Employees::EmployeeQueueFlags_strings::FIRSTNAME),
                           Employees::EmployeeInfo<std::string>(lastName, Employees::EmployeeQueueFlags_strings::LASTNAME),
                           Employees::EmployeeInfo<std::string>(password, Employees::EmployeeQueueFlags_strings::PASSWORD),
                           Employees::EmployeeInfo<std::string>(department, Employees::EmployeeQueueFlags_strings::DEPARTMENT));
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

  // 6. Reset the form (optional)
  __init_form_group_box__();
}

/**
 * @brief ### Listen to "Update" employee button click action
 *
 * @class  EmployeesUI
 * @return void
 */
void EmployeesUI::on_updateBtn_clicked() {
  // 1. Hold data from `ui->updateForm` (Req data)
  std::string firstName = ui->firstNameInsert_2->text().toStdString();
  std::string lastName = ui->lastNameInsert_2->text().toStdString();
  std::string email = ui->emailNameInsert_2->text().toStdString();
  std::string password = ui->passwordNameInsert_2->text().toStdString();
  std::string department = ui->departmentInsert_2->currentText().toStdString();
  std::string username = extractUsername(ui->updateForm->title().toStdString()); // * Can't be empty

  // 2. Verify the passed data
  std::pair<Employees::EmployeeCheckerFlags, const char *> status{Employees::EmployeeChecker::is_valid(email, firstName, lastName, password, department, {Employees::EmployeeCheckerFlags::UNIQUE_EMAIL_WITH_EXCEPTION, username.c_str()})};
  if (status.first) {
    QMessageBox::warning(this, tr("Astra"),
                         tr(status.second),
                         QMessageBox::Ok);
    return;
  }

  // 3. Update the given data
  int affRow{};
  Employees::Update *up(new Employees::Update);
  (ui->show_2->isChecked()) ? // TODO: Update All user data
      0
                            : // Update the required user data
      affRow = up->updateReq(Employees::EmployeeInfo(email, Employees::EmployeeQueueFlags_strings::EMAIL),
                             Employees::EmployeeInfo(firstName, Employees::EmployeeQueueFlags_strings::FIRSTNAME),
                             Employees::EmployeeInfo(lastName, Employees::EmployeeQueueFlags_strings::LASTNAME),
                             Employees::EmployeeInfo(password, Employees::EmployeeQueueFlags_strings::PASSWORD),
                             Employees::EmployeeInfo(department, Employees::EmployeeQueueFlags_strings::DEPARTMENT),
                             Employees::EmployeeInfo(username, Employees::EmployeeQueueFlags_strings::USERNAME));
  delete up;
  up = nullptr;

  // 4. Show a QMessageBox on success/failed operation
  (!affRow) ? QMessageBox::warning(this, tr("Astra"),
                                   tr("Error: Can't Update the given employee data!"),
                                   QMessageBox::Ok)
            : QMessageBox::information(this, tr("Astra"),
                                       tr("Employee Update it successfully!"),
                                       QMessageBox::Ok);

  // 5. Refresh the table (just show the update it employee)
  __init_employees_table__();

  // 6. Reset the form (optional)
  __init_update_form_group_box__();
}

/**
 * @brief ### Return the `username` from `ui->updateForm` title
 *
 * @param title {const std::string &}
 * @return      std::string
 */
std::string EmployeesUI::extractUsername(const std::string &title) const {
  return title.substr(12, title.size());
}
// * ========================================
// ? === / Events & signals handling part ===
// * ========================================
