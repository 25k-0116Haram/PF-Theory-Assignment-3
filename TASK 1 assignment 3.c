#include <stdio.h>

double calculateRepayment(double loan, double rate, int years, double installment, int year)
{
    if (loan <= 0 || years == 0)
        return 0;

    loan = loan + (loan * rate / 100.0);

    loan -= installment;
    if (loan < 0) loan = 0;   

    printf("Year %d: Remaining loan = %.2f\n", year, loan);

    return installment +
           calculateRepayment(loan, rate, years - 1, installment, year + 1);
}

int main()
{
    double loan = 100000;
    double rate = 5;
    int years = 3;
    double installment = 40000;

    printf("Repayment Schedule:\n");

    double total = calculateRepayment(loan, rate, years, installment, 1);

    printf("\nTotal repayment = %.2f\n", total);

    return 0;
}

