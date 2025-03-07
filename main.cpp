
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>


using namespace std;


int main() {

    double fullPurchasePrice, downPayment, priceAfterDP, creditScore, APR, monthsFinanced;
    double monthlyPayment, interest, principal, remainingBalance;

    cout << "How much is the item's initial price before down payment? ";
    cin >> fullPurchasePrice;
    cout << "How much is your down payment? ";
    cin >> downPayment;
    cout << "What is your Credit Score? ";
    cin >> creditScore;
    cout << "How many months would you like to finance for? ";
    cin >> monthsFinanced;

    priceAfterDP = fullPurchasePrice - downPayment;

    if (creditScore <= 450) {
        APR = 0.2043;
    }
    else if (creditScore >= 451 && creditScore <= 649) {
        APR = 0.1284;
    }
    else if (creditScore >= 650 && creditScore <= 675) {
        APR = 0.1033;
    }
    else if (creditScore >= 676 && creditScore <= 700) {
        APR = 0.0675;
    }
    else if (creditScore >= 701 && creditScore <= 750) {
        APR = 0.0553;
    }
    else if (creditScore >= 751 && creditScore <= 800) {
        APR = 0.0403;
    }
    else if (creditScore >= 801 && creditScore <= 825) {
        APR = 0.0368;
    }
    else if (creditScore >= 826) {
        APR = 0.0296;
    }
    else {
        cout << "Credit Score is invalid. Please enter a valid Credit Score." << endl;
        return 1;
    }
    cout << "Your APR from your credit is " << APR * 100 << " %" << endl;

    double monthlyRate = APR / 12;

    if (monthlyRate > 0) {
        monthlyPayment = priceAfterDP * (monthlyRate * pow(1 + monthlyRate, monthsFinanced)) / (pow(1 + monthlyRate, monthsFinanced) - 1);
    }
    else {
        monthlyPayment = priceAfterDP / monthsFinanced;
    }
    remainingBalance = priceAfterDP;

    vector<vector<double>> monthlyFinanceTable(monthsFinanced, vector<double>(4));
    double totalPaid = 0.0;
    double totalInterestPaid = 0.0;

    for (int i = 0; i < monthsFinanced; ++i) {
        interest = remainingBalance * monthlyRate;
        principal = monthlyPayment - interest;
        remainingBalance -= principal;

        monthlyFinanceTable[i][0] = i + 1;
        monthlyFinanceTable[i][1] = monthlyPayment;
        monthlyFinanceTable[i][2] = interest;
        monthlyFinanceTable[i][3] = principal;

        totalPaid += monthlyPayment;
        totalInterestPaid += interest;
    }

    // Display Table
    cout << "\nLoan Payment Schedule\n";
    cout << "-------------------------------------------------------\n";
    cout << setw(8) << "Month" << setw(15) << "Payment" << setw(15) << "Interest" << setw(15) << "Principal" << endl;
    cout << "-------------------------------------------------------\n";
    for (const auto& row : monthlyFinanceTable) {
        cout << setw(8) << row[0] << setw(15) << fixed << setprecision(2) << row[1]
            << setw(15) << row[2] << setw(15) << row[3] << endl;
    }

    cout << "-------------------------------------------------------\n";
    cout << setw(8) << "Total" << setw(15) << fixed << setprecision(2) << totalPaid
        << setw(15) << totalInterestPaid << setw(15) << (totalPaid - priceAfterDP) << endl;

    return 0;
}

