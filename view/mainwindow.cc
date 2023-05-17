#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) noexcept
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  ui_->pushButton_equal->setCheckable(true);
  ui_->pushButton_xInput->setCheckable(true);

  // CONTROLLER
  controller_ = new s21::Controller("");

  // INPUT X
  input_ui = new Form;
  connect(input_ui, &Form::mainWindow, this, &MainWindow::show);

  // PLOT
  my_plot_ = new Plot;
  connect(my_plot_, &Plot::plotMainWindow, this, &MainWindow::show);

  // LOAN CALCULATOR
  loan_ui_ = new LoanCalc;
  connect(loan_ui_, &LoanCalc::loanMainWindow, this, &MainWindow::show);

  // CONNECT BUTTONS
  InitSlots();
}

MainWindow::~MainWindow() {
  delete ui_;
  delete controller_;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Backspace) {
    OnPushButtonDeleteClicked();
  } else if (event->key() == Qt::Key_Return) {
    OnPushButtonEqualClicked();
  } else if (event->key() == Qt::Key_Escape) {
    OnPushButtonResetClicked();
  } else if (event->KeyPress) {
    if (event->key() != Qt::Key_Space && event->key() != Qt::Key_Tab) {
      if (ui_->pushButton_equal->isChecked()) {
        ui_->output->setText("");
        ui_->pushButton_equal->setChecked(false);
      }
      QString keyboard_input = "";
      keyboard_input = ui_->output->text() + event->text();
      ui_->output->setText(keyboard_input);
    }
  }
}

void MainWindow::InitSlots() noexcept {
  // DIGITS
  InitDigits();
  // FUNCTIONS
  InitFunctions();
  // OPERATIONS
  InitOperations();
  // X
  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(GetInputString()));
  // AC
  connect(ui_->PushButtonReset, SIGNAL(clicked()), this,
          SLOT(OnPushButtonResetClicked()));
  // =
  connect(ui_->pushButton_equal, SIGNAL(clicked()), this,
          SLOT(OnPushButtonEqualClicked()));
  // DELETE
  connect(ui_->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(OnPushButtonDeleteClicked()));
  // X INPUT
  connect(ui_->pushButton_xInput, SIGNAL(clicked()), this,
          SLOT(OnPushButtonXInputClicked()));
  // LOAN CALCULATOR
  connect(ui_->pushButtonLoanCalc, SIGNAL(clicked()), this,
          SLOT(OnPushButtonLoanCalcClicked()));
}

void MainWindow::InitDigits() noexcept {
  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(GetInputString()));
  // DOT
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(GetInputString()));
}

void MainWindow::InitOperations() noexcept {
  // PLUS
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  // MINUS
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  // DIVISION
  connect(ui_->pushButton_divide, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  // PERCENT
  connect(ui_->pushButton_percent, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  // MULTIPLICATION
  connect(ui_->pushButton_multiply, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  // BRACKETS
  connect(ui_->pushButton_leftBracket, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  connect(ui_->pushButton_rightBracket, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
}

void MainWindow::InitFunctions() noexcept {
  // MOD, POW
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(GetInputString()));
  // LOG, LN
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(GetInputString()));
  // SIN, COS, TAN
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(GetInputString()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(GetInputString()));
  // ASIN, ACOS, ATAN
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
  // SQRT
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(GetInputString()));
}

void MainWindow::GetInputString() noexcept {
  QPushButton *button = (QPushButton *)sender();
  if (ui_->pushButton_equal->isChecked()) {
    ui_->output->setText("");
    ui_->pushButton_equal->setChecked(false);
  }
  QString input = "";
  input = ui_->output->text() + button->text();
  ui_->output->setText(input);
}

void MainWindow::OnPushButtonEqualClicked() noexcept {
  QString infix = ui_->output->text();
  controller_->SetInputStr(infix.toStdString());
  double result =
      controller_->GetCalculatedExpression(input_ui->GetInputX().toStdString());
  QString out_str;
  if (controller_->GetPolishBool())
    out_str = "ERROR";
  else
    out_str = QString::number(result, 'g', 7);
  ui_->output->setText(out_str);
  ui_->pushButton_equal->setChecked(true);
}

void MainWindow::OnPushButtonDeleteClicked() noexcept {
  QString tmp = ui_->output->text();
  tmp.chop(1);
  ui_->output->setText(tmp);
}

void MainWindow::OnPushButtonXInputClicked() noexcept {
  ui_->pushButton_xInput->setChecked(true);
  input_ui->show();
}

void MainWindow::on_pushButton_plot_clicked() noexcept {
  my_plot_->SetFunc(ui_->output->text());
  my_plot_->show();
}

void MainWindow::OnPushButtonResetClicked() noexcept {
  ui_->output->setText("");
}

void MainWindow::OnPushButtonLoanCalcClicked() noexcept { loan_ui_->show(); }
