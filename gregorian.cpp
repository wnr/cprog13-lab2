#include "gregorian.h"
#include "kattistime.h"
#include <exception>

using namespace lab2;

/* Default constructor. Inits to current date. */
Gregorian::Gregorian() : Jesus(1970, 1, 1) {
  time_t seconds = k_time(NULL);

  int days = seconds/(60*60*24);

  int mjd = mod_julian_day() + days;

  /*double jd = mjd + 2400000.5;

  int a = jd+32044;
  double b = ((4*a)+3)/146097;
  int c = a-(146097*b/4);
  int d = ((4*c)+3)/1461;
  int e = c-(1461*d/4);
  int m = ((5*e)+2)/153;

  int day = e-(((153*m)+2)/5)+1;
  int month = m+3-(12*(m/10));
  int year = (100*b)+d-4800+(m/10);*/

  // // Julian day
  // long jd = mjd + 2400000.5;

  // int  l = jd + 68569;
  // int  n = 4 * l / 146097;

  // l = l - (146097 * n + 3) / 4;
  // int year = 4000 * (l + 1) / 1461001;

  // l = l - (1461 * year / 4) + 31;
  // int month = 80 * l / 2447;

  // int day = l - 2447 * month / 80;

  // l = month / 11;

  // month = month + 2 - 12 * l;
  // year = 100 * (n - 49) + year + l;
  //

  int jdn = mjd + 2400000.5 + 0.5;

  int y = 4716, v = 3, j = 1401, u = 5, m = 2, s = 153, n = 12, w = 2, r = 4, B = 274277, p = 1461, C = -38;

  int f = jdn + j + (((4 * jdn + B)/146097) * 3)/4 + C;
  int e = r * f + v;
  int g = mod(e, p)/r;
  int h = u * g + w;

  int day = (mod(h, s))/u + 1;
  int month = mod(h/s + m, n) + 1;
  int year = e/p - y + (n + m - month)/n;

  mDay = day;
  mMonth = month;
  mYear = year;
}

/* Initializing constructor. */
Gregorian::Gregorian(int year, int month, int day) : Jesus(year, month, day) {
  if(day > days_this_month()) {
    throw std::out_of_range("Illegal arguments");
  }
}

/* Copy constructor. */
Gregorian::Gregorian(const Date & date) : Jesus(1858, 11, 17) {
  Jesus::init(date);
}

/* Copy constructor. */
Gregorian::Gregorian(const Date * date) : Jesus(1858, 11, 17) {
  Jesus::init(*date);
}

/* Assignment operator. */
Gregorian & Gregorian::operator= (const Date & date) {
  if(this == &date) {
    return *this;
  }

  mYear = 1858;
  mMonth = 11;
  mDay = 17;

  Jesus::init(date);

  return *this;
}

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
  return lab2::mod(year(), 4) == 0 && (lab2::mod(year(), 100) != 0 || lab2::mod(year(), 400) == 0);
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
