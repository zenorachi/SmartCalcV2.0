#include "model.h"

double s21::PolishNotation::CalculateExpression() {
  ConvertToPolish_();
  if (incorrect_expression_) return 0;
  double result = 0;
  stack<double> st;
  char* c_postfix = const_cast<char*>(input_string_.c_str());
  char* current_lexem = strtok(c_postfix, " ");
  while (current_lexem) {
    if (isdigit(current_lexem[0]))
      st.push(atof(current_lexem));
    else if (IsOperator_(current_lexem[0]))
      CalculateOperation_(st, current_lexem[0]);
    else if (IsFunction_(current_lexem[0]))
      CalculateFunction_(st, current_lexem[0]);
    else {
      incorrect_expression_ = true;
    }
    current_lexem = strtok(nullptr, " ");
  }
  SafeTop_(st);
  if (!incorrect_expression_) result = st.top();
  SafePop_(st);
  return result;
}

void s21::PolishNotation::CalculateOperation_(s21::stack<double>& st,
                                              char current) {
  double tmp1 = 0;
  SafeTop_(st);
  if (!incorrect_expression_) tmp1 = st.top();
  SafePop_(st);
  double tmp2 = 0;
  SafeTop_(st);
  if (!incorrect_expression_) tmp2 = st.top();
  SafePop_(st);
  if (incorrect_expression_) return;
  switch (current) {
    case '%':
      st.push(tmp1 * tmp2 / 100);
      break;
    case '^':
      st.push(pow(tmp2, tmp1));
      break;
    case '+':
      st.push(tmp2 + tmp1);
      break;
    case '-':
      st.push(tmp2 - tmp1);
      break;
    case '*':
      st.push((tmp2 * tmp1));
      break;
    case 'm':
      st.push(fmod(tmp2, tmp1));
      break;
    case '/':
      st.push(tmp2 / tmp1);
      break;
    default:
      incorrect_expression_ = true;
      break;
  }
}

void s21::PolishNotation::CalculateFunction_(s21::stack<double>& st,
                                             char current) {
  double tmp = st.top();
  SafePop_(st);
  if (incorrect_expression_) return;
  switch (current) {
    case 'l':
      st.push(log(tmp));
      break;
    case 's':
      st.push(sin(tmp));
      break;
    case 'c':
      st.push(cos(tmp));
      break;
    case 't':
      st.push(tan(tmp));
      break;
    case 'S':
      st.push(asin(tmp));
      break;
    case 'C':
      st.push(acos(tmp));
      break;
    case 'T':
      st.push(atan(tmp));
      break;
    case 'Q':
      st.push(sqrt(tmp));
      break;
    case 'L':
      st.push(log10(tmp));
      break;
    default:
      incorrect_expression_ = true;
      break;
  }
}
