#include "../inc/template.h"

ModelUi::ModelUi(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  PDF_gif = new QMovie(ui->PDF);
  Notif_gif = new QMovie(ui->Notification);
  Wen_gif = new QMovie(ui->Wen);
  ui->Form->hide();

  // Initialization of the connections
  SetConnections();

  // Initialization of the images
  InitImages();
}

ModelUi::~ModelUi() {
  delete ui;
}

void ModelUi::SetConnections() {
  // Connect the Add button to the form
  connect(ui->Add_button, &QPushButton::clicked, [&] {
    ui->Form->show();
  });

  // Connect the Cancel button to the form
  connect(ui->Cancel_form, &QPushButton::clicked, [&] {
    ui->Form->hide();
  });
}

// Shape an image to be round depending of the xRadius and yRadius then put it in a label
void ModelUi::ScaleImage(const QString Path, QLabel *Label, qreal xRadius, qreal yRadius) const {
  QPixmap Image(Path);
  QSize Size = Label->size();
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
  Label->setPixmap(Image);
}

// Set gif as a button icon
void ModelUi::GifButton(QMovie *gif, const QString Path, QPushButton *Button) const {
  gif->setFileName(Path);

  connect(gif, &QMovie::frameChanged, [=] {
    Button->setIcon(gif->currentPixmap());
  });

  gif->start();
}

// Creates shadow for each element in the app
void ModelUi::ShadowEffect() {
  for (int i = 0; i < NB_SHADOWS; i++) {
    Shadow_Effect[i] = new QGraphicsDropShadowEffect;

    Shadow_Effect[i]->setBlurRadius(5);
    Shadow_Effect[i]->setXOffset(5);
    Shadow_Effect[i]->setYOffset(5);
    Shadow_Effect[i]->setColor(Qt::gray);
  }
}

// Creates an Icon with self predefined size for buttons
void ModelUi::IconButton(QPushButton *Button, QString Path, int W, int H) const {
  Button->setIcon(QIcon(Path));
  Button->setIconSize(QSize(W, H));
}

// Init Button Images
void ModelUi::InitImageButtons() {
  // Init gifs
  GifButton(PDF_gif, "../global/PDF.gif", ui->PDF);
  GifButton(Notif_gif, "../global/Notif.gif", ui->Notification);
  GifButton(Wen_gif, "../global/Wen.gif", ui->Wen);
}

// Init Widget Shadows
void ModelUi::InitShadows() { 
  ui->Background_navigation->setGraphicsEffect(Shadow_Effect[0]);
  ui->Search_bar->setGraphicsEffect(Shadow_Effect[1]);
  ui->Add_button->setGraphicsEffect(Shadow_Effect[2]);
  ui->PDF->setGraphicsEffect(Shadow_Effect[3]);
  ui->Filtre->setGraphicsEffect(Shadow_Effect[4]);
  ui->Notification->setGraphicsEffect(Shadow_Effect[5]);
  ui->Form->setGraphicsEffect(Shadow_Effect[6]);
}

// Init all images
void ModelUi::InitImages() {
  // Init label images
  // ScaleImage("../global/Person.jpg", ui->User_Image, 35, 35);
  // ui->Logo->setPixmap(QPixmap("../global/Logo.png").scaled(ui->Logo->size()));

  // Init button images
  InitImageButtons();

  // Init Shadow
  ShadowEffect();
  InitShadows();
}
