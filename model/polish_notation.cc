#include "model.h"

void s21::PolishNotation::ConvertToPolish_() {
  input_string_ = CheckExp_(input_string_);
  input_string_ = StrToTokens_(input_string_);
  if (incorrect_expression_) return;
  s21::stack<char> st;
  std::string postfix_expression;
  char* c_input = const_cast<char*>(input_string_.c_str());
  char* current_lexem = strtok(c_input, " ");
  while (current_lexem) {
    std::string tmp_prev = postfix_expression;
    if (isdigit(current_lexem[0]) || current_lexem[0] == '.' ||
        current_lexem[0] == 'x') {
      postfix_expression += current_lexem;
    } else if (current_lexem[0] == '(' || IsFunction_(current_lexem[0])) {
      st.push(current_lexem[0]);
    } else if (current_lexem[0] == ')') {
      RightBracket_(st, postfix_expression);
    } else if (IsOperator_(current_lexem[0])) {
      Operator_(st, postfix_expression, current_lexem);
    }
    current_lexem = strtok(nullptr, " ");
    if (current_lexem && tmp_prev != postfix_expression)
      postfix_expression += " ";
  }
  while (!st.empty() && st.top() != '(') {
    if (postfix_expression[postfix_expression.length() - 1] != ' ')
      postfix_expression += " ";
    postfix_expression += st.top();
    st.pop();
  }
  if (!st.empty()) incorrect_expression_ = true;
  input_string_ = postfix_expression;
}

void s21::PolishNotation::RightBracket_(s21::stack<char>& st,
                                        std::string& postfix_expression) {
  while (!st.empty() && st.top() != '(') {
    postfix_expression += st.top();
    st.pop();
    if (!st.empty() && st.top() != '(') postfix_expression += " ";
  }
  SafePop_(st);
}

void s21::PolishNotation::Operator_(s21::stack<char>& st,
                                    std::string& postfix_expression,
                                    char* current_lexem) {
  while (!st.empty() && st.top() != '(' &&
         Priority_(st.top()) >= Priority_(current_lexem[0])) {
    postfix_expression += st.top();
    st.pop();
    if (!st.empty() && st.top() != '(' &&
        Priority_(st.top()) >= Priority_(current_lexem[0]))
      postfix_expression += " ";
  }
  st.push(current_lexem[0]);
}

void s21::PolishNotation::CorrectBrackets_(const std::string& input,
                                           const int& i) {
  if (input[i] == '(') {
    if (i - 1 >= 0 && (isdigit(input[i - 1]) || input[i - 1] == 'x')) {
      incorrect_expression_ = true;
    }
  } else {
    if (i + 1 < (int)input.length() &&
        (isdigit(input[i + 1]) || isalpha(input[i + 1]))) {
      incorrect_expression_ = true;
    }
  }
}

std::string s21::PolishNotation::StrToTokens_(const std::string& input) {
  bool contains_x_or_number = false;
  std::string tmp_input = input;
  if (!input_string_.empty()) input_string_.clear();
  for (int i = 0; i < (int)tmp_input.length(); ++i) {
    if (tmp_input.substr(i, 3) == "sin") {
      input_string_ += "s";
      i += 2;
    } else if (tmp_input.substr(i, 3) == "cos") {
      input_string_ += "c";
      i += 2;
    } else if (tmp_input.substr(i, 3) == "tan") {
      input_string_ += "t";
      i += 2;
    } else if (tmp_input.substr(i, 3) == "mod") {
      input_string_ += "m";
      i += 2;
    } else if (tmp_input.substr(i, 3) == "log") {
      input_string_ += "L";
      i += 2;
    } else if (tmp_input.substr(i, 2) == "ln") {
      input_string_ += "l";
      i += 1;
    } else if (tmp_input.substr(i, 4) == "asin") {
      input_string_ += "S";
      i += 3;
    } else if (tmp_input.substr(i, 4) == "acos") {
      input_string_ += "C";
      i += 3;
    } else if (tmp_input.substr(i, 4) == "atan") {
      input_string_ += "T";
      i += 3;
    } else if (tmp_input.substr(i, 4) == "sqrt") {
      input_string_ += "Q";
      i += 3;
    } else if (isdigit(tmp_input[i]) || tmp_input[i] == '.') {
      NumToStr_(input_string_, tmp_input, i);
      contains_x_or_number = true;
    } else if (IsOperator_(tmp_input[i]) || tmp_input[i] == 'x' ||
               tmp_input[i] == '(' || tmp_input[i] == ')') {
      if (tmp_input[i] == 'x')
        input_string_ += "( x )";
      else if (tmp_input[i] == '(' || tmp_input[i] == ')') {
        CorrectBrackets_(tmp_input, i);
        input_string_ += tmp_input[i];
      } else if (tmp_input[i] == '-' &&
                 (i == 0 ||
                  (!isdigit(tmp_input[i - 1]) && tmp_input[i - 1] != ')')))
        input_string_ += "0 -";
      else
        input_string_ += tmp_input[i];
      contains_x_or_number = true;
    } else {
      incorrect_expression_ = true;
    }
    if (i < (int)tmp_input.length() - 1) input_string_ += " ";
  }
  if (!contains_x_or_number) incorrect_expression_ = true;
  return input_string_;
}
