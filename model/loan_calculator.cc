#include "model.h"

std::vector<double> s21::PolishNotation::LoanCalculator(bool is_annuity,
                                                        double total_amount,
                                                        double loan_term,
                                                        double rate) {
  std::vector<double> result;
  if (is_annuity) {
    double a = 0, k = 0, s = total_amount;
    double i = rate / 12 / 100;
    int n = (int)loan_term;
    k = (i * pow((1 + i), n)) / (pow((1 + i), n) - 1);
    a = k * s;
    result.push_back(a);
    result.push_back(s);
  } else {
    double const_payment = 0, payment_per_month = 0, percent_per_month = 0;
    const_payment = total_amount / loan_term;
    double tmpAmount = total_amount;
    int n = (int)loan_term;
    int d = 31;
    double first_payment = 0;
    bool is_added = false;
    for (; n > 0; n--) {
      percent_per_month = tmpAmount * (rate / 100) * d / 365;
      payment_per_month += const_payment + percent_per_month;
      tmpAmount -= const_payment;
      d = (d == 31) ? 30 : 31;
      if (!is_added) {
        first_payment += payment_per_month;
        is_added = true;
      }
    }
    result.push_back(const_payment);
    result.push_back(payment_per_month);
    result.push_back(first_payment);
  }
  return result;
}
