#include "model.h"

std::string s21::PolishNotation::CheckExp_(const std::string& input) {
  std::string tmp_input = input;
  std::string num = "";
  for (int i = 0; i < (int)input.length(); ++i) {
    if (input[i] == 'e') {
      if (input[i + 1] == '-')
        tmp_input.replace(tmp_input.find("e-"), 2, "/10^");
      else
        tmp_input.replace(tmp_input.find('e'), 1, "*10^");
    }
  }
  return tmp_input;
}

bool s21::PolishNotation::IsOperator_(char sym) noexcept {
  return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^' ||
          sym == 'm' || sym == '%');
}

void s21::PolishNotation::NumToStr_(std::string& result_str,
                                    const std::string& input, int& i) {
  if (isdigit(input[i])) {
    int dot_counter = 0;
    while (isdigit(input[i]) || input[i] == '.') {
      if (input[i] == '.') ++dot_counter;
      result_str += input[i++];
    }
    if (dot_counter > 1) incorrect_expression_ = true;
  } else {
    result_str += "0.";
    while (isdigit(input[++i])) result_str += input[i];
  }
  --i;
}

bool s21::PolishNotation::IsFunction_(char sym) noexcept {
  return (sym == 's' || sym == 'S' || sym == 'c' || sym == 'C' || sym == 't' ||
          sym == 'T' || sym == 'l' || sym == 'L' || sym == 'Q');
}

int s21::PolishNotation::Priority_(char op) noexcept {
  int result = ERR;
  switch (op) {
    case '+':
    case '-':
      result = OP_1;
      break;
    case '*':
    case '/':
    case '%':
    case 'm':
      result = OP_2;
      break;
    case 's':
    case 'S':
    case 'c':
    case 'C':
    case 't':
    case 'T':
    case 'l':
    case 'L':
    case 'Q':
      result = OP_3;
      break;
    case '^':
      result = OP_4;
      break;
    default:
      incorrect_expression_ = true;
      break;
  }
  return result;
}
