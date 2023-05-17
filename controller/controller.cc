#include "controller.h"

// CONSTRUCTORS
s21::Controller::Controller() noexcept
    : postfix_expression(new PolishNotation) {}
s21::Controller::Controller(const std::string& input) noexcept {
  std::string correct_input = input;
  postfix_expression = new PolishNotation(input);
}

// DESTRUCTOR
s21::Controller::~Controller() { delete postfix_expression; }

// SETTER
void s21::Controller::SetInputStr(const std::string& new_str) noexcept {
  if (!postfix_expression)
    postfix_expression = new PolishNotation(new_str);
  else
    postfix_expression->SetStr(new_str);
}

// CALCULATION METHOD
double s21::Controller::GetCalculatedExpression(
    const std::string& x_str) noexcept {
  QString tmp_input = QString::fromStdString(postfix_expression->GetStr());
  if (tmp_input.contains('x')) {
    std::string tmp_input_x = x_str;
    if (!postfix_expression->GetStr().empty()) postfix_expression->SetStr("");
    PolishNotation tmp_polish("(" + tmp_input_x + ")");
    tmp_input_x = tmp_polish.GetStr();
    tmp_input.replace('x', QString::fromStdString(tmp_input_x));
    postfix_expression->SetStr(tmp_input.toStdString());
  }
  return postfix_expression->CalculateExpression();
}
