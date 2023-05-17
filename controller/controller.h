#ifndef CPP3_SMART_CALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
#define CPP3_SMART_CALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_

#include <QString>

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  // CONSTRUCTORS
  Controller() noexcept;
  explicit Controller(const std::string& input) noexcept;

  // DESTRUCTOR
  ~Controller();

  // SETTER
  void SetInputStr(const std::string& new_str) noexcept;

  // GETTER
  bool GetPolishBool() const noexcept { return postfix_expression->GetBool(); }

  // CALCULATION METHOD
  double GetCalculatedExpression(const std::string& x_str) noexcept;

  // LOAN CALCULATOR
  std::vector<double> GetLoanCalc(bool is_annuity, double total_amount,
                                  double loan_term,
                                  double rate) const noexcept {
    return postfix_expression->LoanCalculator(is_annuity, total_amount,
                                              loan_term, rate);
  }

 private:
  PolishNotation* postfix_expression;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
