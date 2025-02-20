#include "../inc/partenaire.h"
#include "../ui/ui_partenaire.h"
#include <QtWidgets/QMessageBox>

partenaire::partenaire(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::partenaire) {
  ui->setupUi(this);

  // Connexion correcte du bouton
  connect(ui->action_A_propos, &QAction::triggered, this, &partenaire::a_propos);
  connect(ui->action_D_connexion, &QAction::triggered, this, &QApplication::quit);
}

partenaire::~partenaire() {
  delete ui;
}

void partenaire::a_propos(void) {
  QMessageBox::information(this, "a propos", "ceci est une application pour la gestion des partenariats .\n vous pouvez remplir le champs pour ajouter un \n partenaire en selection Fichier.");
}
