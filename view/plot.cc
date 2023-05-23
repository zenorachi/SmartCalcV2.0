#include "plot.h"

#include "ui_plot.h"

Plot::Plot(QWidget* parent) noexcept : QMainWindow(parent), ui(new Ui::Plot) {
  ui->setupUi(this);
  connect(ui->pushButton_close, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCloseClicked()));
  connect(ui->pushButton_setPlot, SIGNAL(clicked()), this,
          SLOT(OnPushButtonSetPlotClicked()));
}

Plot::~Plot() { delete ui; }

void Plot::SetFunc(const QString& input_func) noexcept { func_ = input_func; }

void Plot::OnPushButtonCloseClicked() noexcept {
  close();
  emit plotMainWindow();
}

void Plot::OnPushButtonSetPlotClicked() noexcept {
  SetSettings();
  int graph_counter = 0;

  for (X = x_begin_; X <= x_end_; X += step_) {
    QString tmp_func = func_;
    X = round((X * 100)) / 100;
    if (tmp_func.contains('x')) {
      tmp_func.replace('x', "(x)");
      QString tmpX = QString::number(X, 'g', 7);
      tmp_func.replace('x', tmpX);
    }
    s21::Controller controller_plot(tmp_func.toStdString());
    double result = controller_plot.GetCalculatedExpression("");
    if (controller_plot.GetPolishBool() || isinf(result) || isnan(result)) {
      ui->widget->addGraph();
      ui->widget->graph(graph_counter++)->addData(x, y);
      ui->widget->replot();
      x.clear();
      y.clear();
      continue;
    }
    DrawPlot(tmp_func);
  }

  ui->widget->addGraph();
  ui->widget->graph(graph_counter)->addData(x, y);

  ui->widget->replot();
}

void Plot::SetSettings() noexcept {
  QString min_x = ui->lineEdit_xMin->text(), maxX = ui->lineEdit_xMax->text();
  double tmp_min_x = min_x.toDouble();
  double tmp_max_x = maxX.toDouble();

  QString min_y = ui->lineEdit_yMin->text(), maxY = ui->lineEdit_yMax->text();
  double tmp_min_y = min_y.toDouble();
  double tmp_max_y = maxY.toDouble();

  ui->widget->xAxis->setRange(tmp_min_x, tmp_max_x);
  ui->widget->yAxis->setRange(tmp_min_y, tmp_max_y);

  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");

  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->setInteraction(QCP::iRangeZoom, true);

  x_begin_ = tmp_min_x;
  x_end_ = tmp_max_x;
  step_ = 0.05;

  x.clear();
  y.clear();
  ui->widget->clearGraphs();
}

void Plot::DrawPlot(QString tmp_func) noexcept {
  s21::Controller controller_plot(tmp_func.toStdString());
  double result_y = controller_plot.GetCalculatedExpression("");
  y.push_back(result_y);
  x.push_back(X);
}
