#ifndef DATE_H
#define DATE_H

#include <ostream>
#include <stdexcept>

namespace lab2 {
class Date;
  std::ostream & operator<<(std::ostream & os, const Date &);
}

/* Abstract interface class for representing dates. */
class lab2::Date {
protected:
  //The number of days in a week.
  int mNumDaysPerWeek;

  //The number of months in a year.
  int mNumMonthsPerYear;

  //The current year.
  int mYear;

  //The current month. 1 = first month of the year.
  int mMonth;

  //The current day of the month.
  int mDay;

public:
  /* Default constructor. */
  Date();

  /* Initializer constructor. */
  Date(int numDaysPerWeek, int numMonthsPerYear, int year, int month, int day);

  /* Copy constructor. */
  Date(const Date & date);

  virtual ~Date();

  /* ======= Getters ======= */

  /* Gets the current year. */
  int year() const;

  /* Gets the current month. */
  int month() const;

  /* Gets the current day. */
  int day() const;

  /* Gets the current week day. */
  int week_day() const;

  /* Gets the number of days in a week. */
  int days_per_week() const;

  /* Gets the number of months in a year. */
  int months_per_year() const;

  /* Gets the number of days of the current month. */
  int days_this_month() const;

  /* Gets the number of days per year. Will be computed if not overloaded. */
  virtual int days_per_year() const;

  /* Gets the week day name. */
  virtual std::string week_day_name() const = 0;

  /* Gets the month name. */
  virtual std::string month_name() const = 0;

  /* ======= Operators ======= */

  /* Assignment operator. */
  virtual Date & operator= (const Date & date);

  /* Prefixed ++ operator. Adds one day. */
  Date & operator++ ();

  /* Prefixed -- operator. Removes one day. */
  Date & operator-- ();

  /* += operator. Adds days. */
  Date & operator+= (int days);

  /* -= operator. Removes days. */
  Date & operator-= (int days);

  /* == operator. */
  bool operator== (const Date & date) const;

  /* != operator. */
  bool operator!= (const Date & date) const;

  /* < operator. */
  bool operator< (const Date & date) const;

  /* > operator. */
  bool operator> (const Date & date) const;

  /* <= operator. */
  bool operator<= (const Date & date) const;

  /* >= operator. */
  bool operator>= (const Date & date) const;

  /* - operator. Returns the number of days diffing the two dates. */
  int operator- (const Date & date) const;

  /* ======= Adder / Setters ======= */

  /* Adds years. */
  Date & add_year(int n = 1);

  /* Adds months. Will increment year if needed. */
  Date & add_month(int n = 1);

  /* Adds days. Will increment month if needed. Will increment year if needed. */
  Date & add_day(int n = 1);

  /* ======= Misc ======= */

  /* Gets the number of days since modified julian day.
   * Pure virtual because the MJD depends on specific date calculations. */
  virtual int mod_julian_day() const = 0;

protected:
  /* Gets the number of days of a given month. Pure virtual since this is unknown to the Date abstract class.
   * Is cyclic, so month = 13 = 1. */
  virtual int days_in_month(int month) const = 0;

  /* Increase years. */
  virtual Date & increase_year(int n = 1);

  /* Decrease years. */
  virtual Date & decrease_year(int n = 1);

  /* Increase months. */
  virtual Date & increase_month(int n = 1);

  /* Decrease months. */
  virtual Date & decrease_month(int n = 1);

  /* Increase days. */
  Date & increase_day(int n = 1);

  /* Decrease days. */
  Date & decrease_day(int n = 1);
};


#endif
