#include "julian.h"
#include "kattistime.h"
#include "gregorian.h"
#include <exception>

using namespace lab2;

/* Default constructor. Inits to current date. */
Julian::Julian() : Jesus(1858, 11, 5) {
  Gregorian g = Gregorian();

  int mjd = g.mod_julian_day();

  set_to_mjd(mjd);
}

/* Initializing constructor. */
Julian::Julian(int year, int month, int day) : Jesus(year, month, day) {
  if(day > days_this_month()) {
    throw std::out_of_range("Illegal arguments");
  }
}

/* Copy constructor. */
Julian::Julian(const Date & date) : Jesus(1858, 11, 5) {
  set_to_mjd(date.mod_julian_day());
}

/* Copy constructor. */
Julian::Julian(const Date * date) : Jesus(1858, 11, 5) {
  set_to_mjd(date->mod_julian_day());
}

/* Returns true if the current year is a leap year. */
bool Julian::is_leap() const {
  return lab2::mod(year(), 4) == 0;
}

/* Gets the number of days since modified julian day.
 * Pure virtual because the MJD depends on specific date calculations. */
int Julian::mod_julian_day() const {
  int a = (14 - month()) / 12;
  int y = year() + 4800 - a;
  int m = month() + 12 * a - 3;

  double jdn = day() + (153 * m + 2) / 5 + 365 * y + y / 4 -32083;

  double mjd = jdn - 2400000.5;

  if(mjd < 0) {
    mjd--;
  }

  return mjd;
}

/* Postfixed ++ operator. Adds one day. */
const Julian Julian::operator++ (int) {
  Julian j(*this);
  add_day();
  return j;
}

/* Postfixed -- operator. Removes one day. */
const Julian Julian::operator-- (int) {
  Julian j(*this);
  add_day(-1);
  return j;
}

/* Assignment operator. */
Julian & Julian::operator= (const Date & date) {
  if(this == &date) {
    return *this;
  }

  mYear = 1858;
  mMonth = 11;
  mDay = 5;

  set_to_mjd(date.mod_julian_day());

  return *this;
}

void Julian::set_to_mjd(int mjd) {
  int jdn = mjd + 2400000.5 + 0.5;

  int b = 0;
  int c = jdn + 32082;

  int d = (4*c + 3)/1461;
  int e = c - (int)(1461*d/4);
  int m = (5*e + 2)/153;

  int day = e - (int)((153*m + 2)/5) + 1;
  int month = m + 3 - 12 * (int)(m/10);
  int year = 100*b + d - 4800 + (int)(m/10);

  mDay = day;
  mMonth = month;
  mYear = year;
}
