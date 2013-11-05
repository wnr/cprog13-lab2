#include "date.h"
#include <iomanip>
#include <typeinfo>

using namespace lab2;

/* << operator. Function used to print object by ostream. */
std::ostream & operator<< (std::ostream & os, const lab2::Date & date) {
  os << /*typeid(date).name() <<*/ date.year() << "-" << std::setw(2) << std::setfill('0') << date.month() << "-" << std::setw(2) << std::setfill('0') << date.day();
  return os;
}

/* ======= Constructors ======= */

/* Default constructor. */
Date::Date() : mNumDaysPerWeek(0), mNumMonthsPerYear(0), mYear(0), mMonth(0), mDay(0) {}

/* Initializer constructor. */
Date::Date(int numDaysPerWeek, int numMonthsPerYear, int year, int month, int day) : mNumDaysPerWeek(numDaysPerWeek), mNumMonthsPerYear(numMonthsPerYear), mYear(year), mMonth(month), mDay(day) {
  if(month < 1 || day < 1 || month > numMonthsPerYear) {
    throw std::out_of_range("Illegal constructor arguments");
  }
}

/* Copy constructor. */
//TODO: Is it possible to copy one type of calender to another? If so, then what happens with the overloaded functions, etc?
Date::Date(const Date & date) : mNumDaysPerWeek(date.mNumDaysPerWeek), mNumMonthsPerYear(date.mNumMonthsPerYear), mYear(date.mYear), mMonth(date.mMonth), mDay(date.mDay) {}

Date::~Date() {}

/* ======= Getters ======= */

/* Gets the current year. */
int Date::year() const {
  return mYear;
}

/* Gets the current month. */
int Date::month() const {
  return mMonth;
}

/* Gets the current day. */
int Date::day() const {
  return mDay;
}

/* Gets the current week day. */
int Date::week_day() const {
  int mjd = mod_julian_day();

  return ((mjd + 2) % days_per_week()) + 1;
}

/* Gets the number of days in a week. */
int Date::days_per_week() const {
  return mNumDaysPerWeek;
}

/* Gets the number of months in a year. */
int Date::months_per_year() const {
  return mNumMonthsPerYear;
}

/* Gets the number of days of the current month. */
int Date::days_this_month() const {
  return days_in_month(mMonth);
}

/* Gets the number of days per year. Will be computed if not overloaded. */
int Date::days_per_year() const {
  int days = 0;

  for(int m = 1; m <= mNumMonthsPerYear; m++) {
    days += days_in_month(m);
  }

  return days;
}

/* ======= Operators ======= */

Date & Date::operator= (const Date & date) {
  if(this != &date) {
    mNumDaysPerWeek = date.mNumDaysPerWeek;
    mNumMonthsPerYear = date.mNumMonthsPerYear;
    mYear = date.mYear;
    mMonth = date.mMonth;
    mDay = date.mDay;
  }

  return *this;
}

/* Prefixed ++ operator. Adds one day. */
Date & Date::operator++ () {
  return this->add_day(1);
}

/* Prefixed -- operator. Removes one day. */
Date & Date::operator-- () {
  return this->add_day(-1);
}

/* += operator. Adds days. */
Date & Date::operator+= (int days) {
  return this->add_day(days);
}

/* -= operator. Removes days. */
Date & Date::operator-= (int days) {
  return this->add_day(-days);
}

/* == operator. */
//TODO: This only checks field values. Maybe should check if it is a different date type aswell?
bool Date::operator== (const Date & date) const {
  return mNumDaysPerWeek == date.mNumDaysPerWeek && mNumMonthsPerYear == date.mNumMonthsPerYear && mYear == date.mYear && mMonth == date.mMonth && mDay == date.mDay;
}

/* != operator. */
bool Date::operator!= (const Date & date) const {
  return !((*this) == date);
}

/* < operator. */
bool Date::operator< (const Date & date) const {
  if(mYear < date.mYear) {
    return true;
  } else if(mYear > date.mYear) {
    return false;
  }

  if(mMonth < date.mMonth) {
    return true;
  } else if(mMonth > date.mMonth) {
    return false;
  }

  if(mDay < date.mDay) {
    return true;
  }

  return false;
}

/* > operator. */
bool Date::operator> (const Date & date) const {
  return !((*this) < date || (*this) == date);
}

/* <= operator. */
bool Date::operator<= (const Date & date) const {
  return !((*this) > date);
}

/* >= operator. */
bool Date::operator>= (const Date & date) const {
  return !((*this) < date);
}

/* - operator. Returns the number of days diffing the two dates. */
int Date::operator- (const Date & date) const {
  int a = this->mod_julian_day();
  int b = date.mod_julian_day();

  if(a > b) {
    return a - b;
  }

  return b - a;
}

/* ======= Adder / Setters ======= */

/* Adds years. */
Date & Date::add_year(int n) {
  if(n > 0) {
    increase_year(n);
  } else if(n < 0) {
    decrease_year(-n);
  }

  return *this;
}

/* Adds months. Will increment year if needed. */
Date & Date::add_month(int n) {
  if(n > 0) {
    return increase_month(n);
  } else if(n < 0) {
    return decrease_month(-n);
  }

  return *this;
}

/* Adds days. Will increment month if needed. Will increment year if needed. */
Date & Date::add_day(int n) {
  if(n > 0) {
    return increase_day(n);
  } else if(n < 0) {
    return decrease_day(-n);
  }

  return *this;
}

/* ======= Misc ======= */

/* ======= Private helper functions ======= */

/* Increase years. */
Date & Date::increase_year(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }

  mYear += n;

  return *this;
}

/* Decrease years. */
Date & Date::decrease_year(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }

  mYear -= n;

  return *this;
}

/* Increase months. */
Date & Date::increase_month(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }

  for(; n > 0; n--) {
    mMonth++;

    if(mMonth > mNumMonthsPerYear) {
      mMonth = 1;
      add_year();
    }

    if(mDay > days_in_month(mMonth)) {
      mDay = std::min(days_in_month(mMonth), mDay);
    }
  }

  return *this;
}

/* Decrease months. */
Date & Date::decrease_month(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }

  for(; n > 0; n--) {
    mMonth--;

    if(mMonth < 1) {
      mMonth = mNumMonthsPerYear;
      decrease_year();
    }

    if(mDay > days_in_month(mMonth)) {
      mDay = std::min(days_in_month(mMonth), mDay);
    }
  }

  return *this;
}

/* Increase days. */
Date & Date::increase_day(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }

  for(; n > 0; n--) {
    mDay++;

    if(mDay > days_this_month()) {
      mDay = 1;
      increase_month();
    }
  }

  return *this;
}

/* Decrease days. */
Date & Date::decrease_day(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }

  for(; n > 0; n--) {
    mDay--;

    if(mDay < 1) {
      mDay = days_in_month(mMonth - 1);
      decrease_month();
    }
  }

  return *this;
}
