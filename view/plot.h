#ifndef PLOT_H
#define PLOT_H

#include <QMainWindow>
#include <QVector>

#include "controller/controller.h"

namespace Ui {
class Plot;
}

class Plot : public QMainWindow {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr) noexcept;
  ~Plot();

  void SetFunc(const QString &input_func) noexcept;

 signals:
  void plotMainWindow();

 private slots:
  void OnPushButtonCloseClicked() noexcept;
  void OnPushButtonSetPlotClicked() noexcept;
  void SetSettings() noexcept;
  void DrawPlot(QString tmpFunc) noexcept;

 private:
  Ui::Plot *ui;
  double x_begin_, x_end_, step_, X;
  QString func_;
  QVector<double> x, y;
};

#endif  // PLOT_H
