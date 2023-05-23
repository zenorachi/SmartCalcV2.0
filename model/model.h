/*! \mainpage SmartCalc-V2.0 Documentation
 *
 * \section Project Description
 * There is an implementation of calculator
 * in the CPP programming language using structured programming.
 * In addition to basic arithmetic operations such as add/subtract and
 * multiply/divide, there is an ability to calculate arithmetic expressions as
 * well as some mathematical functions (sine, cosine, logarithm, etc.). Besides
 * calculating expressions, it also supports the use of the x variable and the
 * graphing of the corresponding function. Also there are a credit and a deposit
 * calculators.
 *
 * \section Commands
 * Run "make" or "make all" to build the calculator.\n
 * Run "make install" to install the application on your PC.\n
 * Run "make uninstall" to uninstall the application.\n
 * Run "make dvi" to get this documentation.\n
 * Run "make dist" to archivate the application.\n
 * Run "make tests" to run the tests.\n
 */

#ifndef CPP3_SMART_CALC_V2_0_1_SRC_MODEL_MODEL_H_
#define CPP3_SMART_CALC_V2_0_1_SRC_MODEL_MODEL_H_

#include <cmath>
#include <cstring>
#include <vector>

#include "s21_stack.h"

namespace s21 {
/*!
        \brief Main class for processing input expression
*/
class PolishNotation {
 public:
  /*!
   * \brief Basic constructor for PolishNotation
   */
  PolishNotation() noexcept : incorrect_expression_(false) {
    input_string_ = "";
  }
  /*!
   * \brief Constructor with parameters for PolishNotation
   * \param input input expression
   */
  explicit PolishNotation(const std::string& input) noexcept
      : incorrect_expression_(false) {
    input_string_ = input;
  }

  /*!
   * \brief Destructor for PolishNotation
   */
  ~PolishNotation() { input_string_ = ""; }

  /*!
   * \brief Getter for string
   * \return input_string_
   */
  const std::string& GetStr() const noexcept { return input_string_; }
  /*!
   * \brief Getter for boolean variable is_incorrect_
   * \return is_incorrect_
   */
  bool GetBool() const noexcept { return incorrect_expression_; }
  /*!
   * \brief Setter for string
   * \param new_str input string (math expression)
   */
  void SetStr(const std::string& new_str) noexcept {
    incorrect_expression_ = false;
    if (!input_string_.empty()) input_string_.clear();
    input_string_ = new_str;
  }
  /*!
   * \brief Main method which calculates expression in postfix polish notation
   * \return result of calculated expression
   */
  double CalculateExpression();
  /*!
   * \brief Main method for Loan Calculator
   * \param is_annuity true if user wants to calculate annuity payments
   * \param total_amount total amount of loan
   * \param loan_term loan term
   * \param rate loan rate
   * \return vector which contains the results
   */
  std::vector<double> LoanCalculator(bool is_annuity, double total_amount,
                                     double loan_term, double rate);

 private:
  /*!
   * \brief Constants representing the priority of the operator and functions
   */
  enum PRIORITY { ERR, OP_1, OP_2, OP_3, OP_4 };
  /*!
   * \brief input expression
   */
  std::string input_string_;
  /*!
   * \brief Boolean variable for checks for incorrect expression
   */
  bool incorrect_expression_;
  /*!
   * \brief Auxiliary method to translate the input expression into lexemes
   */
  std::string StrToTokens_(const std::string& input);
  /*!
   * \brief Auxiliary method to check the exponential notation
   */
  std::string CheckExp_(const std::string& input);
  /*!
   * \brief Auxiliary method to check for correct expression (is based on
   * brackets)
   */
  void CorrectBrackets_(const std::string& input, const int& i);
  /*!
   * \brief Auxiliary method to check if the char is operator
   */
  static bool IsOperator_(char sym) noexcept;
  /*!
   * \brief Auxiliary method to translate a sequence of chars into a number
   */
  void NumToStr_(std::string& result_str, const std::string& input, int& i);
  /*!
   * \brief Main auxiliary method to convert the tokens string into postfix
   * polish expression
   */
  void ConvertToPolish_();
  /*!
   * \brief Auxiliary method to to check if the lexem is function
   */
  static bool IsFunction_(char sym) noexcept;
  /*!
   * \brief Auxiliary method to to check the priority of the operator or
   * function
   */
  int Priority_(char op) noexcept;
  /*!
   * \brief Auxiliary method to check that the expression contains the correct
   * brackets
   */
  void RightBracket_(s21::stack<char>& st, std::string& postfix_expression);
  /*!
   * \brief Auxiliary method for StrToTokens_()
   */
  void Operator_(s21::stack<char>& st, std::string& postfix_expression,
                 char* current_lexem);
  /*!
   * \brief Auxiliary method for CalculateExpression()
   */
  void CalculateOperation_(s21::stack<double>& st, char current);
  /*!
   * \brief Auxiliary method for CalculateExpression()
   */
  void CalculateFunction_(s21::stack<double>& st, char current);
  /*!
   * \brief Auxiliary method to safe pop()
   */
  template <typename T>
  void SafePop_(s21::stack<T>& st) {
    if (!st.empty()) {
      st.pop();
    } else {
      incorrect_expression_ = true;
    }
  }
  /*!
   * \brief Auxiliary method to safe top()
   */
  template <typename T>
  void SafeTop_(s21::stack<T>& st) {
    try {
      st.top();
    } catch (...) {
      incorrect_expression_ = true;
    }
  }
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V2_0_1_SRC_MODEL_MODEL_H_
