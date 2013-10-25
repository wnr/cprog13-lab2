#include "Date.h"

using namespace lab2;

/* ======= Constructors ======= */

/* Default constructor. */
Date::Date() : numDaysPerWeek(0), numMonthsPerYear(0), year(0), month(0), day(0) {}

/* Initializer constructor. */
Date::Date(int daysPerWeek, int monthsPerYear, int year, int month, int day) : numDaysPerWeek(daysPerWeek), numMonthsPerYear(monthsPerYear), year(year), month(month), day(day) {}

/* Copy constructor. */
//TODO: Is it possible to copy one type of calender to another? If so, then what happens with the overloaded functions, etc?
Date::Date(const Date & date) : numDaysPerWeek(date.numDaysPerWeek), numMonthsPerYear(date.numMonthsPerYear), year(date.year), month(date.month), day(date.day) {}

/* ======= Getters ======= */

/* Gets the current year. */
int Date::year() const {
  return year;
}

/* Gets the current month. */
int Date::month() const {
  return month;
}
    
/* Gets the current day. */
int day() const {
  return day;
}

/* Gets the current week day. */
int week_day() const {
  // Get the number of weeks elapsed. The integer conversion will make
  // make sure started weeks not counting. For example, if day is 6,
  // the elapsed number of weeks is 0.
  int numWeeks = day / numDaysPerWeek;
  
  // Return the number of days passed in the current week by removed all
  // days that belong to other weeks.
  return day - numWeeks * numDaysPerWeek;
}
    
    /* Gets the number of days in a week. */
    int days_per_week() const;
    
    /* Gets the number of months in a year. */
    int months_per_year() const;
