#ifndef FORM_H
#define FORM_H

#include <QKeyEvent>
#include <QWidget>

namespace s21 {
    namespace Ui {
        class Form;
    }

    class Form : public QWidget {
      Q_OBJECT

     public:
      explicit Form(QWidget *parent = nullptr) noexcept;
      ~Form();

      QString GetInputX() noexcept;

     signals:
      void mainWindow();

     private slots:
      QString OnPushButtonOkClicked() noexcept;

     private:
      s21::Ui::Form *ui;
      void keyPressEvent(QKeyEvent *event) override;
    };
}

#endif  // FORM_H
