#include "../model/model.h"
#include <gtest/gtest.h>

TEST(LoanCalculator, AnnuityPayment) {
    int total_amount = 100000;
    int term = 12;
    int rate = 10;
    s21::PolishNotation polish;
    std::vector<double> loan_res = polish.LoanCalculator(true, total_amount, term, rate);
    double el1 = loan_res[0];
    double el2 = loan_res[1];
    EXPECT_DOUBLE_EQ(el1, loan_res[0]);
    EXPECT_DOUBLE_EQ(el2, loan_res[1]);
    EXPECT_DOUBLE_EQ(loan_res.size(), 2);
}

TEST(LoanCalculator, DifferentialPayment) {
    int total_amount = 100000;
    int term = 12;
    int rate = 10;
    s21::PolishNotation polish;
    std::vector<double> loan_res = polish.LoanCalculator(false, total_amount, term, rate);
    double el1 = loan_res[0];
    double el2 = loan_res[1];
    EXPECT_DOUBLE_EQ(el1, loan_res[0]);
    EXPECT_DOUBLE_EQ(el2, loan_res[1]);
    EXPECT_DOUBLE_EQ(loan_res.size(), 3);
}
