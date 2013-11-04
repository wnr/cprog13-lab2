#include "julian.h"
#include "kattistime.h"
#include "gregorian.h"
#include <exception>

using namespace lab2;

/* Default constructor. Inits to current date. */
Julian::Julian() : Jesus(1858, 11, 5) {
  Gregorian g = Gregorian();
  
  int mjd = g.mod_julian_day();
  
  add_day(mjd);
}

/* Initializing constructor. */
Julian::Julian(int year, int month, int day) : Jesus(year, month, day) {
  if(day > days_this_month()) {
    throw std::out_of_range("Illegal arguments");
  }
}

/* Copy constructor. */
Julian::Julian(const Date & date) : Jesus(1858, 11, 5) {
  Jesus::init(date);
}

/* Copy constructor. */
Julian::Julian(const Date * date) : Jesus(1858, 11, 5) {
  Jesus::init(*date);
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
