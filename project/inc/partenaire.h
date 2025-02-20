#ifndef PARTENAIRE_H
#define PARTENAIRE_H

#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class partenaire;
}
QT_END_NAMESPACE

class partenaire : public QMainWindow {
  Q_OBJECT

public:
  partenaire(QWidget *parent = nullptr);
  ~partenaire();

private:
  Ui::partenaire *ui;
  void a_propos(void);
};
#endif // PARTENAIRE_H
