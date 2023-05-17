#include "loancalc.h"

#include "ui_loancalc.h"

LoanCalc::LoanCalc(QWidget *parent) noexcept
    : QMainWindow(parent), ui(new Ui::LoanCalc) {
  ui->setupUi(this);
  connect(ui->pushButton_closeLoan, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCloseLoanClicked()));
  connect(ui->pushButton_calculate, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCalculateClicked()));
}

LoanCalc::~LoanCalc() {
  delete ui;
  delete loan_controller_;
}

void LoanCalc::OnPushButtonCloseLoanClicked() noexcept {
  close();
  emit loanMainWindow();
}

void LoanCalc::OnPushButtonCalculateClicked() noexcept {
  // INPUT
  double total_amount = ui->lineEdit_totalAmount->text().toDouble();
  double loan_term = ui->lineEdit_loanTerm->text().toDouble();
  double rate = ui->lineEdit_ineterstRate->text().toDouble();
  if (total_amount > 0 && loan_term > 0) {
    if (rate > 0) {
      // ANNUITY PAYMENT
      if (ui->radioButton_annuity->isChecked()) {
        std::vector<double> res_annuity =
            loan_controller_->GetLoanCalc(true, total_amount, loan_term, rate);
        double a = res_annuity[0], s = res_annuity[1];
        ui->lineEdit_paymentPerMonth->setText(QString::number(a, 'g', 7));
        ui->lineEdit_overpayment->setText(
            QString::number(a * loan_term - s, 'g', 7));
        ui->lineEdit_totalPayment->setText(
            QString::number(a * loan_term, 'g', 7));
      } else if (ui->radioButton_differential->isChecked()) {
        std::vector<double> res_dif =
            loan_controller_->GetLoanCalc(false, total_amount, loan_term, rate);
        double const_payment = res_dif[0], payment_per_month = res_dif[1],
               first_payment = res_dif[2];
        ui->lineEdit_paymentPerMonth->setText(
            QString::number(first_payment, 'g', 7) + " ... " +
            QString::number(const_payment, 'g', 7));
        ui->lineEdit_overpayment->setText(
            QString::number(payment_per_month - total_amount, 'g', 7));
        ui->lineEdit_totalPayment->setText(
            QString::number(payment_per_month, 'g', 7));
      }
    } else {
      double payment = total_amount / loan_term;
      ui->lineEdit_paymentPerMonth->setText(QString::number(payment, 'g', 7));
      ui->lineEdit_overpayment->setText("0");
      ui->lineEdit_totalPayment->setText(QString::number(total_amount, 'g', 7));
    }
  } else {
    ui->lineEdit_paymentPerMonth->setText("0");
    ui->lineEdit_overpayment->setText("0");
    ui->lineEdit_totalPayment->setText("0");
  }
}
