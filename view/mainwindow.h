#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>

#include "../controller/controller.h"
#include "form.h"
#include "loancalc.h"
#include "plot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr) noexcept;
  ~MainWindow();

 private:
  Ui::MainWindow* ui_;
  Form* input_ui;
  Plot* my_plot_;
  LoanCalc* loan_ui_;
  s21::Controller* controller_;
  void keyPressEvent(QKeyEvent* event) override;

 private slots:
  void InitSlots() noexcept;
  void InitDigits() noexcept;
  void InitOperations() noexcept;
  void InitFunctions() noexcept;
  void GetInputString() noexcept;
  void OnPushButtonResetClicked() noexcept;
  void OnPushButtonEqualClicked() noexcept;
  void OnPushButtonDeleteClicked() noexcept;
  void OnPushButtonXInputClicked() noexcept;
  void on_pushButton_plot_clicked() noexcept;
  void OnPushButtonLoanCalcClicked() noexcept;
};

#endif  // MAINWINDOW_H
