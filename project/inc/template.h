#ifndef MODEL_UI
#define MODEL_UI

#include "../ui/ui_template.h"
#include <QtGui/QBitmap>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/qmovie.h>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>

#define NB_SHADOWS 7

QT_BEGIN_NAMESPACE
    namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class ModelUi : public QMainWindow
{
    Q_OBJECT

public:
    ModelUi(QWidget *parent = nullptr);
    ~ModelUi();

    void SetConnections();
    void ScaleImage(const QString Path, QLabel* Label, qreal xRadius, qreal yRadius) const;
    void GifButton(QMovie* gif, const QString Path, QPushButton* Button) const;
    void IconButton(QPushButton* Button , QString Path, int W, int H) const;
    void ShadowEffect();
    void InitImageButtons();
    void InitShadows();
    void InitImages();

private:
    Ui::MainWindow* ui;
    QMovie* PDF_gif,
          * Notif_gif,
          * Wen_gif;
    QGraphicsDropShadowEffect* Shadow_Effect[NB_SHADOWS];
};
#endif
