#include "gregorian.h"
#include "kattistime.h"
#include <exception>

using namespace lab2;

/* Default constructor. Inits to current date. */
Gregorian::Gregorian() : Jesus(1970, 1, 1) {
  time_t seconds = k_time(NULL);
  
  add_day(seconds/(60*60*24));
}

/* Initializing constructor. */
Gregorian::Gregorian(int year, int month, int day) : Jesus(year, month, day) {}

/* Gets the number of days since modified julian day.
 * Pure virtual because the MJD depends on specific date calculations. */
int Gregorian::mod_julian_day() const {
  int a = (14 - month()) / 12;
  int y = year() + 4800 - a;
  int m = month() + 12 * a - 3;
  
  double jdn = day() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
  
  double mjd = jdn - 2400000.5;
  
  if(mjd < 0) {
    mjd--;
  }
  
  return mjd;
}


/* Returns true if the current year is a leap year. */
bool Gregorian::is_leap() const {
  return year() % 4 == 0 && (year() % 100 != 0 || year() % 400 == 0);
}

/* Postfixed ++ operator. Adds one day. */
const Gregorian Gregorian::operator++ (int) {
  Gregorian g(*this);
  add_day();
  return g;
}

/* Postfixed -- operator. Removes one day. */
const Gregorian Gregorian::operator-- (int) {
  Gregorian g(*this);
  add_day(-1);
  return g;
}
