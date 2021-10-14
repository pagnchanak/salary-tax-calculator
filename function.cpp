/* FINAL PROJECT FOR FUNDAMENTAL C++
 * PROJECT TOPIC: SALARY TAX CALCULATOR
 * AUTHOR: PAGNCHANAK CHEA
 * DATE: JULY 25, 2021
 * CLASS: PT-SD-12
 * EMAIL: pagnchanak@gmail.com
 *
 * THIS FILE IS FOR INCLUDE INTO MAIN.CPP
 * ONLY FUNCTIONS ARE WRITTEN HERE!
 */

#include <iostream>
#include <iomanip>
#include <locale>
#include "rule.cpp"
using namespace std;

//declare variables
int     residencyStatus;
int     currencyOption;
double  exchangeRate = 1;
double  monthlySalary;
double  fringeBenefit;
bool    spouse;
int     child;
double  taxBase;
double  taxRate;
double  taxOnSalaryInKHR;
double  taxOnSalaryInUSD;
double  taxOnFringeBenefitInKHR;
double  taxOnFringeBenefitInUSD;
double  netSalaryInKHR;
double  netSalaryInUSD;
bool    recalcOption;

enum    {Resident = 1, NonResident = 2};
enum    {KHR = 1, USD = 2};
enum    {Yes = 1, No = 0};

//display welcome text
void welcome() {
    cout << "* Welcome to Salary Tax Calculator!\n"
         << "* This program will calculate your Tax on Salary and Net Salary based on\n"
         << "* new guideline No. 006 MEF-GDT on Tax on Salary issued by Ministry of Economic and Finance\n"
         << "* dated March 23, 2020.\n"
         << "* \n"
         << "* This program is created in July 2021 by Pagnchanak Chea, Student of IT STEP Academy, class PT SD 12.\n"
         << "* This program will be required to be updated once the rules of Tax on Salary changes! Thank You!\n";
};

//display residency options
void residency() {
    cout << "\nResidency Status\n"
         << "1. Resident\n"
         << "2. Non-Resident\n"
         << "Please choose an option: ";
};

//display currency options
void currency() {
    cout << "\nWhich currency to use?\n"
         << "1. Khmer Riel\n"
         << "2. US Dollar\n"
         << "Please choose an option: ";
};

//get input from users the data for calculation
void inputDataForResident() {
    
    //input basic salary
    cout << "\nInput monthly salary: ";
    cin >> monthlySalary;
    while (!cin) {
    cout << "Error! Please input amount in number! Try again.\n"
             << "Input monthly salary: ";
        cin >> monthlySalary;
    }

    //input fringe benefit
    cout << "Input fringe benefit: ";
    cin >> fringeBenefit;
    while (!cin) {
        cout << "Error! Please input amount in number! Try again.\n"
             << "Input fringe benefit: ";
        cin >> fringeBenefit;
    }

    //input dependant
    cout << "\nDo you have a spouse as dependant?\n"
         << "0. No, 1. Yes\n"
         << "Choose an option: ";
    cin  >> spouse;
    while (spouse < No || spouse > Yes) {
        cout << "Invalid option! Please try again!\n"
             << "Choose an option: ";
        cin  >> spouse;
    }

    if (spouse == Yes) {
        cout << "\nHow many children do you have as dependant?\n"
             << "Input number of children: ";
        cin  >> child;
        while (!cin) {
            cout << "Error! Please input amount in number! Try again.\n"
                 << "Input number of children: ";
            cin >> child;
        }
    }
    else {
        child = 0;
    }
};

void inputDataForNonResident() {
    //input basic salary
    cout << "\nInput monthly salary: ";
    cin >> monthlySalary;
    while (!cin) {
        cout << "Error! Please input amount in number! Try again.\n"
             << "Input monthly salary: ";
        cin >> monthlySalary;
    }

    //input fringe benefit
    cout << "Input fringe benefit: ";
    cin >> fringeBenefit;
    while (!cin) {
        cout << "Error! Please input amount in number! Try again.\n"
             << "Input fringe benefit: ";
        cin >> fringeBenefit;
    }
};

//calculation for residence
double calculateResidentTax() {
    taxBase = (monthlySalary * exchangeRate) - ((spouse + child) * dependantExemption);
        
    //calclate tax on salary based on tier
    if (taxBase <= tier1){
        taxOnSalaryInKHR = taxBase * tier0TaxRate - tier0Variance;
        taxRate = tier0TaxRate;
    }
    else if (taxBase <= tier2) {
        taxOnSalaryInKHR = taxBase * tier1TaxRate - tier1Variance;
        taxRate = tier1TaxRate;
    }
    else if (taxBase <= tier3) {
        taxOnSalaryInKHR = taxBase * tier2TaxRate - tier2Variance;
        taxRate = tier2TaxRate;
    }
    else if (taxBase <= tier4) {
        taxOnSalaryInKHR = taxBase * tier3TaxRate - tier3Variance;
        taxRate = tier3TaxRate;
    }
    else {
        taxOnSalaryInKHR = taxBase * tier4TaxRate - tier4Variance;
        taxRate = tier4TaxRate;
    }

    taxOnSalaryInUSD = taxOnSalaryInKHR / exchangeRate;
    taxOnFringeBenefitInKHR = (fringeBenefit * exchangeRate) * fringeBenefitTaxRate;
    taxOnFringeBenefitInUSD = taxOnFringeBenefitInKHR / exchangeRate;
    netSalaryInKHR = ((monthlySalary + fringeBenefit) * exchangeRate) - (taxOnSalaryInKHR + taxOnFringeBenefitInKHR);
    netSalaryInUSD = netSalaryInKHR / exchangeRate;
    return taxOnSalaryInKHR, taxOnSalaryInUSD, taxOnFringeBenefitInKHR, taxOnFringeBenefitInUSD, netSalaryInKHR, netSalaryInUSD, taxRate;
};

//calculation for non-residence
double calculateNonResidentTax() {
    taxOnSalaryInKHR = (monthlySalary * exchangeRate) * nonResidentTaxRate;
    taxOnSalaryInUSD = taxOnSalaryInKHR / exchangeRate;
    taxOnFringeBenefitInKHR = (fringeBenefit * exchangeRate) * fringeBenefitTaxRate;
    taxOnFringeBenefitInUSD = taxOnFringeBenefitInKHR / exchangeRate;
    netSalaryInKHR = ((monthlySalary + fringeBenefit) * exchangeRate) - (taxOnSalaryInKHR + taxOnFringeBenefitInKHR);
    netSalaryInUSD = netSalaryInKHR / exchangeRate;
    taxRate = nonResidentTaxRate;
    return taxOnSalaryInKHR, taxOnSalaryInUSD, taxOnFringeBenefitInKHR, taxOnFringeBenefitInUSD, netSalaryInKHR, netSalaryInUSD, taxRate;
};

struct separated : numpunct<char> {
   string do_grouping() const { return "\03"; }
};

//display calculation result
void displayResult() {
    locale our_local (cout.getloc(), new separated);
    cout.imbue (our_local);
    cout << fixed;
    cout << setprecision(0);
    if (currencyOption == KHR) {
        cout << "\n------------------------------TAX AMOUNT------------------------------\n"
             << "Tax Rate              : " << taxRate * 100 << "%\n"
             << "Tax on Salary         : " << taxOnSalaryInKHR << " Riel\n"
             << "Tax on Fringe Benefit : " << taxOnFringeBenefitInKHR << " Riel\n"
             << "Total Tax Amount      : " << taxOnSalaryInKHR + taxOnFringeBenefitInKHR << " Riel\n\n"
             << "------------------------------NET SALARY------------------------------\n"
             << "Net Salary            : " << netSalaryInKHR << " Riel\n\n";
    }
    else {
        cout << "\n------------------------------TAX AMOUNT------------------------------\n"
             << "Tax Rate                    : " << taxRate * 100 << "%\n\n"
             << "Tax on Salary (KHR)         : " << taxOnSalaryInKHR << " Riel\n"
             << "Tax on Salary (USD)         : " << taxOnSalaryInUSD << " USD\n\n"
             << "Tax on Fringe Benefit (KHR) : " << taxOnFringeBenefitInKHR << " Riel\n"
             << "Tax on Fringe Benefit (USD) : " << taxOnFringeBenefitInUSD << " USD\n\n"
             << "Total Tax Amount (KHR)      : " << taxOnSalaryInKHR + taxOnFringeBenefitInKHR << " Riel\n"
             << "Total Tax Amount (USD)      : " << taxOnSalaryInUSD + taxOnFringeBenefitInUSD << " USD\n\n"
             << "------------------------------NET SALARY------------------------------\n"
             << "Net Salary (KHR)            : " << netSalaryInKHR << " Riel\n"
             << "Net Salary (USD)            : " << netSalaryInUSD << " USD\n\n";
    }
};