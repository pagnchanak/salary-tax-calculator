/* FINAL PROJECT FOR FUNDAMENTAL C++
 * PROJECT TOPIC: SALARY TAX CALCULATOR
 * AUTHOR: PAGNCHANAK CHEA
 * DATE: JULY 25, 2021
 * CLASS: PT-SD-12
 * EMAIL: pagnchanak@gmail.com
 *
 * THIS FILE IS FOR INCLUDE IN FUNCTION.CPP
 * THIS FILE CONTAINS RULES OF TAX ON SALARY.
 * FOR FUTURE REVISION OF TAX TIER, IT CAN BE EASILY MAINTAINED HERE.
 * CURRENT RULES BASED ON: https://kromanews.com/archives/6249 
 */

//define tax rules here, for future change on tier level only, can be easily amended here
//exemption from tax base per spouse/child
double  dependantExemption = 150000;

//define tier range
double  tier0 = 0;
double  tier1 = 1300000;
double  tier2 = 2000000;
double  tier3 = 8500000;
double  tier4 = 12500000;

//define tax rate for each tier
double  tier0TaxRate = 0;
double  tier1TaxRate = 0.05;
double  tier2TaxRate = 0.10;
double  tier3TaxRate = 0.15;
double  tier4TaxRate = 0.20;
double  nonResidentTaxRate = 0.20;
double  fringeBenefitTaxRate = 0.20;
 
//define variance per tier, to ease calculation
double  tier0Variance = tier0 * tier0TaxRate;
double  tier1Variance = tier1 * (tier1TaxRate - tier0TaxRate) + tier0Variance;
double  tier2Variance = tier2 * (tier2TaxRate - tier1TaxRate) + tier1Variance;
double  tier3Variance = tier3 * (tier3TaxRate - tier2TaxRate) + tier2Variance;
double  tier4Variance = tier4 * (tier4TaxRate - tier3TaxRate) + tier3Variance;