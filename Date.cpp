#include "Date.h"

using namespace lab2;

/* << operator. Function used to print object by ostream. */
std::ostream & operator<< (std::ostream & os, const lab2::Date & date) {
  os << date.year() << "-" << date.month() << "-" << date.day();
  return os;
}

/* ======= Constructors ======= */

/* Default constructor. */
Date::Date() : mNumDaysPerWeek(0), mNumMonthsPerYear(0), mYear(0), mMonth(0), mDay(0) {}

/* Initializer constructor. */
Date::Date(int numDaysPerWeek, int numMonthsPerYear, int year, int month, int day) : mNumDaysPerWeek(numDaysPerWeek), mNumMonthsPerYear(numMonthsPerYear), mYear(year), mMonth(month), mDay(day) {}

/* Copy constructor. */
//TODO: Is it possible to copy one type of calender to another? If so, then what happens with the overloaded functions, etc?
Date::Date(const Date & date) : mNumDaysPerWeek(date.mNumDaysPerWeek), mNumMonthsPerYear(date.mNumMonthsPerYear), mYear(date.mYear), mMonth(date.mMonth), mDay(date.mDay) {}

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
  // Get the number of weeks elapsed. The integer conversion will make
  // make sure started weeks not counting. For example, if day is 6,
  // the elapsed number of weeks is 0.
  int numWeeks = (mDay - 1) / mNumDaysPerWeek;

  // Return the number of days passed in the current week by removed all
  // days that belong to other weeks.
  return mDay - numWeeks * mNumDaysPerWeek;
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
  int days = 0;

  int year = mYear;
  int month = mMonth;
  int day = mDay;

  int ySignum = mYear > date.mYear ? -1 : 1;
  int mSignum = mMonth > date.mMonth ? -1 : 1;
  int dSignum = mDay > date.mDay ? -1 : 1;

  for(; year != date.mYear; year += ySignum) {
    days += days_per_year();
  }

  for(; month != date.mMonth; month += mSignum) {
    days += days_in_month(month);
  }

  for(; day != date.mDay; day += dSignum) {
    days += mSignum;
  }

  return (*this) > date ? days : -days;
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

/* Gets the number of days since modified julian day. */
int Date::mod_julian_day() const {
  return 0; //TODO: Implement me.
}

/* ======= Private helper functions ======= */

/* Increase years. */
Date & Date::increase_year(int n) {
  if(n < 0) {
    throw EXCEPTION_ILLEGAL_ARGUMENT;
  }

  mYear += n;

  return *this;
}

/* Decrease years. */
Date & Date::decrease_year(int n) {
  if(n < 0) {
    throw EXCEPTION_ILLEGAL_ARGUMENT;
  }

  mYear -= n;

  return *this;
}

/* Increase months. */
Date & Date::increase_month(int n) {
  if(n < 0) {
    throw EXCEPTION_ILLEGAL_ARGUMENT;
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
    throw EXCEPTION_ILLEGAL_ARGUMENT;
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
    throw EXCEPTION_ILLEGAL_ARGUMENT;
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
    throw EXCEPTION_ILLEGAL_ARGUMENT;
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
