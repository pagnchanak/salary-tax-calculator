/* FINAL PROJECT FOR FUNDAMENTAL C++
 * PROJECT TOPIC: SALARY TAX CALCULATOR
 * AUTHOR: PAGNCHANAK CHEA
 * DATE: JULY 25, 2021
 * CLASS: PT-SD-12
 * EMAIL: pagnchanak@gmail.com
 */

#include <iostream>
#include "function.cpp"
using namespace std;

int main() {
    welcome(); //load welcome message, see function.cpp

    BEGIN:
    residency(); //load residency options, see function.cpp
    cin >> residencyStatus;

    //control on residency option, loop for invalid input
    while (residencyStatus < Resident || residencyStatus > NonResident) {
        cout << "Invalid option! Please try again!\n";
        residency();
        cin >> residencyStatus;
    }

    currency(); //load currency options, see function.cpp
    cin >> currencyOption;

    //control on currency option, loop for invalid input
    while (currencyOption < KHR || currencyOption > USD) {
        cout << "Invalid option! Please try again!\n";
        currency();
        cin >> currencyOption;
    }

    //input exchange rate if USD is chosen
    if (currencyOption == USD) {
        cout << "\nPlease input exchange rate (KHR/USD): ";
        cin >> exchangeRate;

        while (!cin) {
            cout << "Error! Please input amount in number! (e.g. 4000).\n"
                 << "Please input exchange rate (KHR/USD): ";
            cin >> exchangeRate;
        }
    }
    
    if (residencyStatus == Resident) {
        inputDataForResident();
        calculateResidentTax();
        displayResult();
    }
    else {
        inputDataForNonResident();
        calculateNonResidentTax();
        displayResult();
    }

    cout << "CALCULATE AGAIN?\n"
         << "0. No, 1. Yes\n"
         << "Choose an option: ";
    cin  >> recalcOption;
    while (recalcOption < No || recalcOption > Yes) {
        cout << "Invalid option! Please try again!\n"
             << "Choose an option: ";
        cin  >> recalcOption;
    }
    
    if (recalcOption == Yes) {
        exchangeRate = 1; //reset exchange rate
        goto BEGIN;
    }
    else {
        return 0;
    }
}